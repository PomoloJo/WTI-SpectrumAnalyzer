#pragma once
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <iostream>
#include "ui_mainwindow.h"
#include "CWorkThread.h"
#include "CAmcThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double getAmcFreq() { return ui->doubleSpinBox_amc_freq->value(); }
    double getAmcBw() { return ui->doubleSpinBox_amc_bw->value(); }

public slots:
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::MainWindow *ui;

    CWorkThread* m_p_work_thread;
    CAmcThread* m_p_amc_thread;

    //QStatusBar* m_status_bar;
    QLabel* m_mouse_coordinate;
    // 接收数据的地址
    const double* m_recv_data;
    // 记录要绘制的点数
    int m_point_num;
    // 记录输入参数
    double m_center_freq;
    double m_bw;
    double m_rbw;
    double m_vbw;
    double m_sweep_time;
    // 根据输入参数计算额外参数
    double m_freq_start;
    double m_freq_end;
    // 记录绘图状态
    enum class PlotStatus
    {
        NORMAL_PLOT,
        WITH_THRESHOLD_LEVEL,
        WITH_THRESHOLD_AUTO,
        WITH_THRESHOLD_PEAK,
        WITH_THRESHOLD_HISTORY
    };
    PlotStatus m_plot_status;
    // 初次绘制标志位
    bool is_first_time_to_replot;
    
    // 用于所有曲线的 x_data
    QVector<double> x_data;
    // 用于阈值曲线的 y_line
    QVector<double> y_line;
    // 记录阈值曲线slide偏移
    int m_slide_value;

    // 记录AMC返回记录
    int m_amc_result[13];

    // functions
    void initUi();
    void initMember();


private slots:
    // 只要把函数名改成 on_按键名_clicked(),  格式: on_对象名_信号名(参数)
    // moc文件中的 QMetaObject::connectSlotsByName 就会自动把按键和该槽函数连接起来
    void on_btn_start_clicked();
    void on_btn_close_clicked();
    void on_btn_max_clicked();
    void on_btn_min_clicked();
    void on_horizontalSlider_offset_valueChanged(int slider_value);
    void on_spinBox_offset_valueChanged(int spinbox_value);
    void plotStatusChange();
    void on_checkBox_threshold_clicked() { plotStatusChange(); }
    void on_radioButton_level_clicked() { plotStatusChange(); }
    void on_radioButton_auto_clicked() { plotStatusChange(); }
    void on_radioButton_peak_clicked() { plotStatusChange(); }
    void on_radioButton_history_clicked() { plotStatusChange(); }  
    void on_btn_history_clicked();
    void on_btn_amc_clicked();

    void timeToReplot(const double*, const int point_num);
    void showAmcResult(const int modulation);
};
#endif // MAINWINDOW_H_
