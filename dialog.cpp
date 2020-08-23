#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QssDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("tes dialog");
    setWindowIcon(QIcon(":/qss/icon/app.png"));
}

Dialog::~Dialog()
{
    delete ui;
}
