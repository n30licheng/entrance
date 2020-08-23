#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <dialog.h>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QssMainWindow(parent)
    , ui(new Ui::MainWindow)
    , d(this)
{
    ui->setupUi(this);
    exit=false;
    setWindowIcon(QIcon(":/qss/icon/app.png"));
    setWindowTitle("QssDemo");
    setTitleCenter(true);
    statusBar()->addWidget(new QLabel("  Ready  "));
    //statusBar()->addWidget(new QLabel("bbb"));
    //this->showMaximized();
    connect(this->titleBar(),&QssTitleBar::aboutMe,this,&MainWindow::aboutMeslot);
    //connect(m_iconBtn, SIGNAL(clicked()), this, SLOT(aboutMeslots()));
    connect(get_titleBar(),&QssTitleBar::quit,this,&MainWindow::quit_frame);


    if(!this->_dll_Resolve.load_resolve_dll()){  //加载dll文件失败，或解悉函数失败
        QMessageBox::warning(this,QObject::tr("加载dll"),QObject::tr("加载dll文件失败，或解悉函数失败"));
        qApp->exit(-1);
    }
    dev_oper=new Device_Operator(&this->_dll_Resolve);



}
void MainWindow::quit_frame()
{
    this->get_frame()->close();
}
MainWindow::~MainWindow()
{
    delete dev_oper;
    delete ui;
}

void MainWindow::aboutMeslot()
{
     QssMessageBox::regard("本系统是基于Qt5.13.2(MinGw7.3.0,64位)\n"
                           "作者：李成\n"
                           "技术支持：QQ（2901981531）\n"
                           "Copyright © 2004-2020 licheng. All rights reserved.\n"
                           "© 2004-2020 李成 拥有所有版权",this,QString::fromUtf8("关于"));

}


void MainWindow::on_btn_readCard_clicked()
{
    Card_Data cardData;
    if(!dev_oper->read_CardData(&cardData)){
        QMessageBox::warning(this,QObject::tr("读卡数据"),cardData.strerr);
        return ;
    }
    ui->txt_name->setText(cardData.name);
    ui->txt_id->setText(cardData.ID.simplified());
    ui->txt_gander->setText(cardData.gander);
    ui->txt_address->setText(cardData.address);
    ui->lbl_pic->setPixmap(QPixmap::fromImage(cardData.image));
//    QString aa=ui->txt_id->text().trimmed();
//    if(ui->txt_id->text().trimmed() !="" )
//        ui->tableView->setModel(dao->findbyID(ui->txt_id->text().trimmed()));

}
