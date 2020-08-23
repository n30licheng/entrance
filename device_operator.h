#ifndef DEVICE_OPERATOR_H
#define DEVICE_OPERATOR_H
#include <dll_resolve.h>
#include <QImage>
struct Card_Data{
    QString name;
    QString gander;
    QString ID;
    QString address;
    QString strerr;
    QImage image;
};

class Device_Operator
{
public:
    Device_Operator(Dll_Resolve* _Dll_Resolve);
    bool read_CardData(struct Card_Data* cd);
    ~Device_Operator();
private:
    Dll_Resolve* _Dll_Resolve=nullptr;
};

#endif // DEVICE_OPERATOR_H
