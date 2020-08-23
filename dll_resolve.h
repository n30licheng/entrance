#ifndef DLL_RESOLVE_H
#define DLL_RESOLVE_H
typedef int __stdcall (*CVR_InitComm) (int Port);    //初始化
typedef int __stdcall (*CVR_Authenticate) (void);     //卡认证
typedef int __stdcall (*CVR_Read_Content)(int active);  //读卡
typedef int __stdcall (*GetPeopleIDCode)(char *strTmp, int *strLen);    //获取身份证号
typedef int __stdcall (*GetPeopleName)(char *strTmp, int *strLen);      //获取姓名
typedef int __stdcall (*GetPeopleNameU)(char *strTmp, int *strLen);      //获取姓名
typedef int __stdcall (*GetPeopleSex)(char *strTmp, int *strLen);       //获取性别
typedef int __stdcall (*GetPeopleSexU)(char *strTmp, int *strLen);       //获取性别
typedef int __stdcall (*GetPeopleNation)(char *strTmp, int *strLen);    //获取民族
typedef int __stdcall (*GetPeopleAddress)(char *strTmp, int *strLen);   //获取地址
typedef int __stdcall (*GetPeopleAddressU)(char *strTmp, int *strLen);   //获取地址
typedef int __stdcall (*GetJpgData)(unsigned char * jpgData, int * pLen); //获取照片
typedef int __stdcall (*Getbase64JpgDataU)(unsigned char * jpgData, int * pLen); //获取照片
typedef int __stdcall (*GetBMPData)(unsigned char * jpgData, int * pLen);
typedef int __stdcall (*Getbase64BMPDataU)(unsigned char * jpgData, int * pLen);
typedef int __stdcall (*CVR_CloseComm)();                    //关闭链接
#define DLL_FILE "termb.dll"


#include <QLibrary>
class Dll_Resolve
{
public:
    Dll_Resolve();
    ~Dll_Resolve();
    CVR_InitComm        func_Cvr_InitComm =nullptr;          //初始化
    CVR_Authenticate    func_Cvr_Authenticate =nullptr;     //卡认证
    CVR_Read_Content    func_Cvr_Read_Content =nullptr;     //读卡
    GetPeopleIDCode     func_Cvr_GetPeopleIDCode =nullptr;  //获取身份证号
    GetPeopleName       func_Cvr_GetPeopleName =nullptr;    //获取姓名
    GetPeopleNameU      func_Cvr_GetPeopleNameU =nullptr;
    GetPeopleSex        func_Cvr_GetPeopleSex =nullptr;     //获取性别
    GetPeopleSexU       func_Cvr_GetPeopleSexU =nullptr;     //获取性别
    GetPeopleNation     func_Cvr_GetPeopleNation =nullptr;  //获取民族
    GetPeopleAddress    func_Cvr_GetPeopleAddress =nullptr; //获取地址
    GetPeopleAddressU    func_Cvr_GetPeopleAddressU =nullptr; //获取地址
    GetJpgData          func_Cvr_GetJpgData =nullptr;       //获取姓名
    Getbase64JpgDataU   func_Cvr_Getbase64JpgDataU =nullptr;       //获取姓名
    GetBMPData          func_Cvr_GetBMPData =nullptr;
    Getbase64BMPDataU          func_Cvr_Getbase64BMPDataU =nullptr;
    CVR_CloseComm       func_Cvr_CloseComm =nullptr;        //关闭链接
    bool load_resolve_dll();      //加载DLL文件,并解释函数
    bool get_resolved();
private:
    QLibrary* termblib=nullptr;
    //false表示解析失败，true解析成功
    bool resolved=false;
};

#endif // DLL_RESOLVE_H
