#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qss.h>
#include <dialog.h>
#include <QThread>
#include <dll_resolve.h>
#include <device_operator.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QssMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void aboutMeslot();
    void quit_frame();
signals:


private slots:


    void on_btn_readCard_clicked();

private:
    Ui::MainWindow *ui;
    Dialog d;
    QPoint offset;
    QGraphicsDropShadowEffect* shadow;
    bool exit;
    Dll_Resolve _dll_Resolve;
    Device_Operator* dev_oper;
};
#endif // MAINWINDOW_H
