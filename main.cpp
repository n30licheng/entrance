#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSplashScreen>
#include <config.h>
#include <QMessageBox>
#include <QThread>

void initQss()
{
    QFile file(":/qss/css/qss.css");
    if (!file.open(QIODevice::ReadOnly))
        exit(0);
    QTextStream in(&file);
    QString css = in.readAll();
    qDebug()<<css.size();
    qApp->setStyleSheet(css);
    qApp->setFont(QFont("微软雅黑", 9));
    return;
}

int main(int argc, char *argv[])
{
    int res=0;
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QStringLiteral(":/qss/icon/app.png")));
    initQss();

    // QApplication::addLibraryPath("./plugins");
     QSplashScreen splash(QPixmap(":/qss/icon/splashscreen.jpg"));
     splash.setDisabled(true); //禁用用户的输入事件响应
     QFont serifFont("Times", 10, QFont::Bold);
     splash.setFont(serifFont);
     splash.show();
     Config& config=Config::get_instance();
     res=config.readConfig();
     if(res==-1){
         QMessageBox::critical(nullptr,QObject::tr("配置文件"),QObject::tr("读配置文件失败"));
         return -1;
     }
     QThread::sleep(1);
     splash.hide();

    MainWindow w;
    w.show();
   //w.showMaximized();
    //w.showFullScreen();
    return a.exec();
}
