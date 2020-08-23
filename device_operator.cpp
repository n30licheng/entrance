#include "device_operator.h"
#include <QTextCodec>

#include <QtDebug>
Device_Operator::Device_Operator(Dll_Resolve* _Dll_Resolve)
{
    this->_Dll_Resolve=_Dll_Resolve;
}

bool Device_Operator::read_CardData(struct Card_Data* cd)
{
    int res;
    if(!this->_Dll_Resolve->get_resolved())// //加载函数失败
        return false;
    int iUsb, iRetUSB = 0;
    for (iUsb = 1001; iUsb <= 1016; iUsb++)  //USB
    {
        iRetUSB = this->_Dll_Resolve->func_Cvr_InitComm(iUsb);
        if (iRetUSB == 1)
            break;
    }
    if(iRetUSB == 0){
        cd->strerr=QObject::tr("USB端口初始化失败");
        return false;
    }
    res=this->_Dll_Resolve->func_Cvr_Authenticate();  //若卡片放置后发生认证错误时，请移走卡片重新放置
    switch(res){
    case 0:
        cd->strerr=QObject::tr("动态库未加载");
        return false;
    case 1:
        //QMessageBox::question(this,"认证","卡片认证成功");
        break;
    case 2:
        cd->strerr=QObject::tr("寻卡失败");
        return false;
    case 3:
        cd->strerr=QObject::tr("选卡失败");
        return false;
    case 4:
        cd->strerr=QObject::tr("未连接读卡器");
        return false;
    }

    res=this->_Dll_Resolve->func_Cvr_Read_Content(1);
    switch(res){
    case 1:
        //QMessageBox::question(this,"读卡信息","读卡信息成功");
        break;
    case 0:
        cd->strerr=QObject::tr("读卡信息失败");
        return false;
    case 4:
        cd->strerr=QObject::tr("未连接读卡器");
        return false;
    case 99:
        cd->strerr=QObject::tr("动态库未加载");
        return false;
    }
#define ERR_OUT(arg) {cd->strerr=QObject::tr(#arg);res=this->_Dll_Resolve->func_Cvr_CloseComm();return false;}
     char strtmp[70]={0};
     int len=70;
     res=this->_Dll_Resolve->func_Cvr_GetPeopleIDCode(strtmp,&len);
     qDebug()<<res;
     if(res==0){
        ERR_OUT("获取身份证失败")
     }
     cd->ID=QString::fromLocal8Bit(strtmp,len-1);



     res=this->_Dll_Resolve->func_Cvr_GetPeopleNameU(strtmp,&len);
     if(res==0){
        ERR_OUT("获取姓名失败")
     }
//     QString str = "刘阿芬";
//      QChar *data = str.data();
//      while (!data->isNull()) {
//          qDebug() << data->unicode();
//          ++data;
//      }
     //QTextCodec *codec = QTextCodec::codecForName("UTF-16");
      //QString strAll=codec->toUnicode(strtmp);
     cd->name=QString::fromUtf16((unsigned short*)strtmp);   //从dll读取来的是utf-16

     res=this->_Dll_Resolve->func_Cvr_GetPeopleSexU(strtmp,&len);
     if(res==0){
          ERR_OUT("获取性别失败")
     }
     cd->gander=QString::fromUtf16((unsigned short*)strtmp);
     //cd->gander=QString::fromLocal8Bit(strtmp,len-1);

     res=this->_Dll_Resolve->func_Cvr_GetPeopleAddressU(strtmp,&len);
     if(res==0){
        ERR_OUT("获取地址失败")
     }
     cd->address=QString::fromUtf16((unsigned short*)strtmp);
     //cd->address=QString::fromLocal8Bit(strtmp,len-1);
    //unsigned char* images=new unsigned char[38862];
     unsigned char images[38862]={0};
     int imagelen=0;
     res=this->_Dll_Resolve->func_Cvr_GetJpgData(images,&imagelen);
     qDebug()<<imagelen;
     if(res==0){
        ERR_OUT("获取照片失败")
     }
     cd->image.loadFromData(images,imagelen,"JPEG");
     res=this->_Dll_Resolve->func_Cvr_CloseComm();
     return true;
}

Device_Operator::~Device_Operator()
{

}
