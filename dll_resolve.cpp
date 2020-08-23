#include "dll_resolve.h"
#include <QDebug>

Dll_Resolve::Dll_Resolve()
{

}
 Dll_Resolve::~Dll_Resolve()
{
     if(termblib){
         delete termblib;
         termblib=nullptr;
     }
}

bool Dll_Resolve::load_resolve_dll()
 {
     bool res=true;
     termblib=nullptr;
     termblib=new QLibrary(DLL_FILE); //声明所用到的dll文件
     if(termblib->load()){
         func_Cvr_InitComm=(CVR_InitComm)termblib->resolve("CVR_InitComm"); //援引 add() 函数
         if(!func_Cvr_InitComm){
            res=false;
            qDebug()<<QObject::tr("CVR_InitComm 解析失败")<<termblib->errorString();
         }
         //卡认证
         func_Cvr_Authenticate =(CVR_Authenticate)termblib->resolve("CVR_Authenticate");
         if(!func_Cvr_Authenticate){
             res=false;
             qDebug()<<QObject::tr("CVR_Authenticate 解析失败")<<termblib->errorString();
         }
         //读卡操作
         func_Cvr_Read_Content=(CVR_Read_Content)termblib->resolve("CVR_Read_Content");
         if(!func_Cvr_Read_Content){
             res=false;
             qDebug()<<QObject::tr("CVR_Read_Content 解析失败")<<termblib->errorString();
         }
         //获取身份证号
         func_Cvr_GetPeopleIDCode=(GetPeopleIDCode)termblib->resolve("GetPeopleIDCode");
         if(!func_Cvr_GetPeopleIDCode){
             res=false;
             qDebug()<<QObject::tr("GetPeopleIDCode 解析失败")<<termblib->errorString();
         }

         func_Cvr_GetPeopleName=(GetPeopleName)termblib->resolve("GetPeopleName");
         if(!func_Cvr_GetPeopleName){
             res=false;
             qDebug()<<QObject::tr("GetPeopleName 解析失败")<<termblib->errorString();
         }
        func_Cvr_GetPeopleNameU=(GetPeopleNameU)termblib->resolve("GetPeopleNameU");
        if(!func_Cvr_GetPeopleNameU){
            res=false;
            qDebug()<<QObject::tr("GetPeopleNameU 解析失败")<<termblib->errorString();
        }
//         func_Cvr_GetPeopleName=(GetPeopleName)termblib->resolve("GetPeopleNameU");
//         if(!func_Cvr_GetPeopleName){
//             res=false;
//             qDebug()<<QObject::tr("GetPeopleName 解析失败")<<termblib->errorString();
//         }


         func_Cvr_GetPeopleSex=(GetPeopleSex)termblib->resolve("GetPeopleSex");
         if(!func_Cvr_GetPeopleSex){
             res=false;
             qDebug()<<QObject::tr("GetPeopleSex 解析失败")<<termblib->errorString();
         }
         func_Cvr_GetPeopleSexU=(GetPeopleSexU)termblib->resolve("GetPeopleSexU");
         if(!func_Cvr_GetPeopleSexU){
             res=false;
             qDebug()<<QObject::tr("GetPeopleSexU  解析失败")<<termblib->errorString();
         }

         func_Cvr_GetPeopleAddress=(GetPeopleAddress)termblib->resolve("GetPeopleAddress");
         if(!func_Cvr_GetPeopleAddress){
             res=false;
             qDebug()<<QObject::tr("GetPeopleAddress 解析失败")<<termblib->errorString();
         }
         func_Cvr_GetPeopleAddressU=(GetPeopleAddressU)termblib->resolve("GetPeopleAddressU");
         if(!func_Cvr_GetPeopleAddressU){
             res=false;
             qDebug()<<QObject::tr("GetPeopleAddressU 解析失败")<<termblib->errorString();
         }

         func_Cvr_GetJpgData=(GetJpgData)termblib->resolve("GetJpgData");
         if(!func_Cvr_GetJpgData){
             res=false;
             qDebug()<<QObject::tr("GetJpgData 解析失败")<<termblib->errorString();
         }
         func_Cvr_GetBMPData=(GetBMPData)termblib->resolve("GetBMPData");
         if(!func_Cvr_GetBMPData){
             res=false;
             qDebug()<<QObject::tr("GetBMPData 解析失败")<<termblib->errorString();
         }
         func_Cvr_Getbase64JpgDataU=(Getbase64JpgDataU)termblib->resolve("Getbase64JpgDataU");
         if(!func_Cvr_Getbase64JpgDataU){
             res=false;
             qDebug()<<QObject::tr("Getbase64JpgDataU 解析失败")<<termblib->errorString();
         }
         func_Cvr_Getbase64BMPDataU=(Getbase64BMPDataU)termblib->resolve("Getbase64BMPDataU");
         if(!func_Cvr_Getbase64BMPDataU){
             res=false;
             qDebug()<<QObject::tr("Getbase64BMPDataU 解析失败")<<termblib->errorString();
         }


         func_Cvr_CloseComm=(CVR_CloseComm)termblib->resolve("CVR_CloseComm");
         if(!func_Cvr_CloseComm){
             res=false;
             qDebug()<<QObject::tr("func_Cvr_CloseComm 解析失败")<<termblib->errorString();
         }
     }else{
         qDebug()<<QObject::tr("termb.dll load faild.")<<termblib->errorString();
         res=false;
     }
     resolved=res;
     return res;
 }
bool Dll_Resolve:: get_resolved(){
    return this->resolved;
}
