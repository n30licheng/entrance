#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <Qss.h>
namespace Ui {
class Dialog;
}

class Dialog : public QssDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
