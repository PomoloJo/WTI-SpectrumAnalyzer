#pragma once
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include "CWorkThread.h"

#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::MainWindow *ui;

    CWorkThread* m_p_work_thread;

    bool is_first_time_to_replot{ true };

    void initUi();
    void initMember();


private slots:
    // 只要把函数名改成 on_按键名_clicked(),
    // moc文件中的 QMetaObject::connectSlotsByName 就会自动把按键和该槽函数连接起来
    void on_btn_start_clicked();

    void timeToReplot(const double*, const int point_num);
};
#endif // MAINWINDOW_H_
