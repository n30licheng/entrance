#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <QSettings>
#include <QException>
#include <qaesencryption.h>

using namespace std;
class Config
{
private:
    string hostName;         //主机名
    int port;                    //端口
    string databaseName;          //数据库名
    string userName;              //用户名
    string password;            //密码
    Config();
    QByteArray key16;
    QString encryption(QByteArray& plainText);
    QString decode(QByteArray& encodedText);
    QAESEncryption* encrypt;
public:
    ~Config();
    static Config& get_instance();
    int readConfig();
    int saveConfig();
    void setHostName(const string& hostName);
    string& getHostName();

    void setPort(int _port);
    int getPort();

    void setDatabaseName(const string& _databaseName);
    string& getDatabaseName();

    void setUserName(const string& _userName);
    string& getUserName();

    void setPassword(const string& _password);
    string& getPassword();

};

#endif // CONFIG_H
