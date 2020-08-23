#include "config.h"
#include <QCoreApplication>
#include <QDebug>


#define CONFIG_FILENAME "admission.ini"



Config& Config::get_instance(){

    static Config instance;
    return instance;
}
Config::Config()
{
    encrypt=new QAESEncryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    quint8 key_16[16] =  {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    for (int i=0; i<16; i++)
        key16.append(key_16[i]);
}
Config::~Config(){
    delete encrypt;
}
int  Config::readConfig(){
    int res=0;
    try {
        QSettings setting(QCoreApplication::applicationDirPath()+"/"+CONFIG_FILENAME,QSettings::IniFormat);
        //setting.setIniCodec("UTF-8");
        this->setHostName(setting.value("DataSource/Host").toString().toStdString());
        this->setPort(setting.value("DataSource/Port").toInt());
        this->setDatabaseName(setting.value("DataSource/DatabaseName").toString().toStdString());
        this->setUserName(setting.value("DataSource/UserName").toString().toStdString());
        QByteArray str=setting.value("DataSource/Password").toString().toUtf8();
        QString str_encode= decode(str);
        this->setPassword(str_encode.toStdString());
        //decode(this->password);
        if(this->getHostName()=="")
            res=-1;
    } catch (QException& ex) {
        res=-1;
    }
    return res;
}
int Config::saveConfig(){
    int res=0;
    try {
        QSettings setting(QCoreApplication::applicationDirPath()+"/"+CONFIG_FILENAME,QSettings::IniFormat);
        //setting.setIniCodec("UTF-8");
        setting.setValue("DataSource/Host",QString::fromStdString(this->getHostName()));
        setting.setValue("DataSource/Port",QString::number(this->getPort(),10));
        setting.setValue("DataSource/DatabaseName",QString::fromStdString(this->getDatabaseName()));
        setting.setValue("DataSource/UserName",QString::fromStdString(this->getUserName()));
        QByteArray temp_encry=QString::fromStdString(this->getPassword()).toUtf8();

//        QByteArray aa=QString("hncjxy@123").toUtf8();
//        int a=aa.size();
//        int b=key16.size();
//        int aaa=(a%b);
        for(int i=temp_encry.size();i<key16.size();i++)
            temp_encry[i]='\0';

        QString temp_dencry=encryption(temp_encry);
        setting.setValue("DataSource/Password",temp_dencry);


    } catch (QException& ex) {
        res=-1;
    }
    return res;
}
void Config::setHostName(const string& _hostName){
    this->hostName=_hostName;
}
string& Config::getHostName(){
    return this->hostName;
}

void Config::setPort(int _port){
    this->port=_port;
}
int Config::getPort(){
    return this->port;
}

void Config::setDatabaseName(const string& _databaseName){
    this->databaseName=_databaseName;
}
string& Config::getDatabaseName(){
    return this->databaseName;
}

void Config::setUserName(const string& _userName){
    this->userName=_userName;
}
string& Config::getUserName(){
    return this->userName;
}

void Config::setPassword(const string& _password)
{
    this->password=_password;
}
string& Config::getPassword(){
    return this->password;
}

QString Config::encryption(QByteArray& plainText)
{
    QByteArray encodedText = encrypt->encode(plainText, key16);
    return QString(encodedText.toHex());

}
QString Config::decode(QByteArray& encodedText){
    QByteArray byteArray = QByteArray::fromHex(encodedText);
    QByteArray decodedText = encrypt->decode(byteArray, key16);
    return QString(decodedText);
}
