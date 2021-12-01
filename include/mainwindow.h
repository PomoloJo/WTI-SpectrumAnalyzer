#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CWorkThread.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    CWorkThread *_p_my_thread;

    void initUi();
    void initMember();


private slots:
    // 只要把函数名改成 on_按键名_clicked(),
    // moc文件中的 QMetaObject::connectSlotsByName 就会自动把按键和该槽函数连接起来
    void on_btn_start_clicked();
};
#endif // MAINWINDOW_H
