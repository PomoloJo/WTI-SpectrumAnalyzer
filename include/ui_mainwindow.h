/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *title_widget;
    QHBoxLayout *horizontalLayout;
    QLabel *title_label;
    QSpacerItem *horizontalSpacer_title;
    QPushButton *btn_min;
    QPushButton *btn_max;
    QPushButton *btn_close;
    QWidget *menu_widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_about;
    QPushButton *btn_amc;
    QSpacerItem *horizontalSpacer_menu;
    QWidget *main_widget;
    QHBoxLayout *horizontalLayout_3;
    QDockWidget *dockWidget_task;
    QWidget *dockWidgetContents_task;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QFrame *frame_threshold;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox_threshold;
    QLabel *label_3;
    QGridLayout *gridLayout_threshold;
    QRadioButton *radioButton_level;
    QRadioButton *radioButton_auto;
    QRadioButton *radioButton_peak;
    QRadioButton *radioButton_history;
    QPushButton *btn_history;
    QHBoxLayout *horizontalLayout_offset;
    QLabel *label_offset;
    QSpinBox *spinBox_offset;
    QSlider *horizontalSlider_offset;
    QFrame *line_threshold;
    QLabel *label_task_list;
    QFrame *frame_task_list;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBox_task;
    QListWidget *listWidget_task;
    QHBoxLayout *horizontalLayout_task_btn;
    QPushButton *btn_task_modify;
    QPushButton *btn_task_add;
    QPushButton *btn_task_delete;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_page1;
    QCustomPlot *widget_plot;
    QWidget *widget_amc;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_amc;
    QHBoxLayout *horizontalLayout_amc_freq;
    QLabel *label_amc_freq;
    QDoubleSpinBox *doubleSpinBox_amc_freq;
    QHBoxLayout *horizontalLayout_amc_bw;
    QLabel *label_amc_bw;
    QDoubleSpinBox *doubleSpinBox_amc_bw;
    QSpacerItem *verticalSpacer_amc;
    QCustomPlot *widget_plot_amc;
    QTextBrowser *textBrowser_amc;
    QWidget *page_2;
    QLabel *label_page_2;
    QTabWidget *tabWidget;
    QWidget *tab_ctrl;
    QVBoxLayout *verticalLayout_6;
    QDockWidget *dockWidget_ctrl;
    QWidget *dockWidgetContents_ctrl;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_ctrl;
    QHBoxLayout *horizontalLayout_devices;
    QLabel *label_devices;
    QComboBox *comboBox_devices;
    QHBoxLayout *horizontalLayout_freq;
    QLabel *label_freq;
    QDoubleSpinBox *doubleSpinBox_freq;
    QHBoxLayout *horizontalLayout_bw;
    QLabel *label_bw;
    QDoubleSpinBox *doubleSpinBox_bw;
    QHBoxLayout *horizontalLayout_rbw;
    QLabel *label_rbw;
    QDoubleSpinBox *doubleSpinBox_rbw;
    QHBoxLayout *horizontalLayout_vbw;
    QLabel *label_vbw;
    QDoubleSpinBox *doubleSpinBox_vbw;
    QHBoxLayout *horizontalLayout_start_btn;
    QSpacerItem *horizontalLayout_start_btn_2;
    QPushButton *btn_start;
    QSpacerItem *horizontalLayout_start_btn_3;
    QSpacerItem *verticalSpacer_ctrl;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_8;
    QTextBrowser *textBrowser;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1900, 1000);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(35, 55, 65);\n"
"color: rgb(240, 240, 240);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        title_widget = new QWidget(centralwidget);
        title_widget->setObjectName(QString::fromUtf8("title_widget"));
        title_widget->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 63, 65);\n"
"background-color: rgb(20, 28, 36);"));
        horizontalLayout = new QHBoxLayout(title_widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        title_label = new QLabel(title_widget);
        title_label->setObjectName(QString::fromUtf8("title_label"));
        title_label->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(title_label);

        horizontalSpacer_title = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_title);

        btn_min = new QPushButton(title_widget);
        btn_min->setObjectName(QString::fromUtf8("btn_min"));
        btn_min->setMinimumSize(QSize(45, 35));
        btn_min->setMaximumSize(QSize(45, 35));

        horizontalLayout->addWidget(btn_min);

        btn_max = new QPushButton(title_widget);
        btn_max->setObjectName(QString::fromUtf8("btn_max"));
        btn_max->setMinimumSize(QSize(45, 35));
        btn_max->setMaximumSize(QSize(45, 35));

        horizontalLayout->addWidget(btn_max);

        btn_close = new QPushButton(title_widget);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setMinimumSize(QSize(45, 35));
        btn_close->setMaximumSize(QSize(45, 35));

        horizontalLayout->addWidget(btn_close);


        verticalLayout_3->addWidget(title_widget);

        menu_widget = new QWidget(centralwidget);
        menu_widget->setObjectName(QString::fromUtf8("menu_widget"));
        horizontalLayout_2 = new QHBoxLayout(menu_widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_about = new QPushButton(menu_widget);
        btn_about->setObjectName(QString::fromUtf8("btn_about"));

        horizontalLayout_2->addWidget(btn_about);

        btn_amc = new QPushButton(menu_widget);
        btn_amc->setObjectName(QString::fromUtf8("btn_amc"));

        horizontalLayout_2->addWidget(btn_amc);

        horizontalSpacer_menu = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_menu);


        verticalLayout_3->addWidget(menu_widget);

        main_widget = new QWidget(centralwidget);
        main_widget->setObjectName(QString::fromUtf8("main_widget"));
        sizePolicy.setHeightForWidth(main_widget->sizePolicy().hasHeightForWidth());
        main_widget->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(main_widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        dockWidget_task = new QDockWidget(main_widget);
        dockWidget_task->setObjectName(QString::fromUtf8("dockWidget_task"));
        dockWidget_task->setMaximumSize(QSize(300, 524287));
        dockWidget_task->setStyleSheet(QString::fromUtf8("background-color: rgb(40, 50, 60);"));
        dockWidgetContents_task = new QWidget();
        dockWidgetContents_task->setObjectName(QString::fromUtf8("dockWidgetContents_task"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_task);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(dockWidgetContents_task);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        frame_threshold = new QFrame(dockWidgetContents_task);
        frame_threshold->setObjectName(QString::fromUtf8("frame_threshold"));
        frame_threshold->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 52, 65);"));
        frame_threshold->setFrameShape(QFrame::WinPanel);
        frame_threshold->setFrameShadow(QFrame::Sunken);
        frame_threshold->setLineWidth(1);
        verticalLayout_5 = new QVBoxLayout(frame_threshold);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBox_threshold = new QCheckBox(frame_threshold);
        checkBox_threshold->setObjectName(QString::fromUtf8("checkBox_threshold"));

        verticalLayout_5->addWidget(checkBox_threshold);

        label_3 = new QLabel(frame_threshold);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_5->addWidget(label_3);

        gridLayout_threshold = new QGridLayout();
        gridLayout_threshold->setObjectName(QString::fromUtf8("gridLayout_threshold"));
        radioButton_level = new QRadioButton(frame_threshold);
        radioButton_level->setObjectName(QString::fromUtf8("radioButton_level"));
        radioButton_level->setMinimumSize(QSize(100, 0));

        gridLayout_threshold->addWidget(radioButton_level, 0, 0, 1, 1);

        radioButton_auto = new QRadioButton(frame_threshold);
        radioButton_auto->setObjectName(QString::fromUtf8("radioButton_auto"));
        radioButton_auto->setMinimumSize(QSize(100, 0));

        gridLayout_threshold->addWidget(radioButton_auto, 0, 1, 1, 1);

        radioButton_peak = new QRadioButton(frame_threshold);
        radioButton_peak->setObjectName(QString::fromUtf8("radioButton_peak"));
        radioButton_peak->setMinimumSize(QSize(100, 0));

        gridLayout_threshold->addWidget(radioButton_peak, 1, 0, 1, 1);

        radioButton_history = new QRadioButton(frame_threshold);
        radioButton_history->setObjectName(QString::fromUtf8("radioButton_history"));
        radioButton_history->setMinimumSize(QSize(100, 0));

        gridLayout_threshold->addWidget(radioButton_history, 1, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_threshold);

        btn_history = new QPushButton(frame_threshold);
        btn_history->setObjectName(QString::fromUtf8("btn_history"));

        verticalLayout_5->addWidget(btn_history);

        horizontalLayout_offset = new QHBoxLayout();
        horizontalLayout_offset->setSpacing(10);
        horizontalLayout_offset->setObjectName(QString::fromUtf8("horizontalLayout_offset"));
        label_offset = new QLabel(frame_threshold);
        label_offset->setObjectName(QString::fromUtf8("label_offset"));

        horizontalLayout_offset->addWidget(label_offset);

        spinBox_offset = new QSpinBox(frame_threshold);
        spinBox_offset->setObjectName(QString::fromUtf8("spinBox_offset"));
        spinBox_offset->setMinimum(-100);
        spinBox_offset->setMaximum(100);

        horizontalLayout_offset->addWidget(spinBox_offset);

        horizontalSlider_offset = new QSlider(frame_threshold);
        horizontalSlider_offset->setObjectName(QString::fromUtf8("horizontalSlider_offset"));
        horizontalSlider_offset->setMinimum(-100);
        horizontalSlider_offset->setMaximum(100);
        horizontalSlider_offset->setOrientation(Qt::Horizontal);
        horizontalSlider_offset->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_offset->addWidget(horizontalSlider_offset);


        verticalLayout_5->addLayout(horizontalLayout_offset);


        verticalLayout->addWidget(frame_threshold);

        line_threshold = new QFrame(dockWidgetContents_task);
        line_threshold->setObjectName(QString::fromUtf8("line_threshold"));
        line_threshold->setFrameShape(QFrame::HLine);
        line_threshold->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_threshold);

        label_task_list = new QLabel(dockWidgetContents_task);
        label_task_list->setObjectName(QString::fromUtf8("label_task_list"));

        verticalLayout->addWidget(label_task_list);

        frame_task_list = new QFrame(dockWidgetContents_task);
        frame_task_list->setObjectName(QString::fromUtf8("frame_task_list"));
        frame_task_list->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 52, 65);"));
        frame_task_list->setFrameShape(QFrame::WinPanel);
        frame_task_list->setFrameShadow(QFrame::Sunken);
        verticalLayout_4 = new QVBoxLayout(frame_task_list);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        checkBox_task = new QCheckBox(frame_task_list);
        checkBox_task->setObjectName(QString::fromUtf8("checkBox_task"));

        verticalLayout_4->addWidget(checkBox_task);

        listWidget_task = new QListWidget(frame_task_list);
        new QListWidgetItem(listWidget_task);
        new QListWidgetItem(listWidget_task);
        listWidget_task->setObjectName(QString::fromUtf8("listWidget_task"));
        listWidget_task->setFrameShape(QFrame::Box);
        listWidget_task->setFrameShadow(QFrame::Sunken);
        listWidget_task->setLineWidth(2);
        listWidget_task->setMidLineWidth(0);

        verticalLayout_4->addWidget(listWidget_task);

        horizontalLayout_task_btn = new QHBoxLayout();
        horizontalLayout_task_btn->setObjectName(QString::fromUtf8("horizontalLayout_task_btn"));
        btn_task_modify = new QPushButton(frame_task_list);
        btn_task_modify->setObjectName(QString::fromUtf8("btn_task_modify"));

        horizontalLayout_task_btn->addWidget(btn_task_modify);

        btn_task_add = new QPushButton(frame_task_list);
        btn_task_add->setObjectName(QString::fromUtf8("btn_task_add"));

        horizontalLayout_task_btn->addWidget(btn_task_add);

        btn_task_delete = new QPushButton(frame_task_list);
        btn_task_delete->setObjectName(QString::fromUtf8("btn_task_delete"));

        horizontalLayout_task_btn->addWidget(btn_task_delete);


        verticalLayout_4->addLayout(horizontalLayout_task_btn);


        verticalLayout->addWidget(frame_task_list);

        dockWidget_task->setWidget(dockWidgetContents_task);

        horizontalLayout_3->addWidget(dockWidget_task);

        stackedWidget = new QStackedWidget(main_widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        verticalLayout_7 = new QVBoxLayout(page_1);
        verticalLayout_7->setSpacing(2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        verticalLayout_page1 = new QVBoxLayout();
        verticalLayout_page1->setSpacing(2);
        verticalLayout_page1->setObjectName(QString::fromUtf8("verticalLayout_page1"));
        widget_plot = new QCustomPlot(page_1);
        widget_plot->setObjectName(QString::fromUtf8("widget_plot"));

        verticalLayout_page1->addWidget(widget_plot);

        widget_amc = new QWidget(page_1);
        widget_amc->setObjectName(QString::fromUtf8("widget_amc"));
        widget_amc->setMaximumSize(QSize(16777215, 250));
        widget_amc->setStyleSheet(QString::fromUtf8("background-color: rgb(40, 50, 60);"));
        horizontalLayout_4 = new QHBoxLayout(widget_amc);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_amc = new QVBoxLayout();
        verticalLayout_amc->setObjectName(QString::fromUtf8("verticalLayout_amc"));
        horizontalLayout_amc_freq = new QHBoxLayout();
        horizontalLayout_amc_freq->setObjectName(QString::fromUtf8("horizontalLayout_amc_freq"));
        label_amc_freq = new QLabel(widget_amc);
        label_amc_freq->setObjectName(QString::fromUtf8("label_amc_freq"));

        horizontalLayout_amc_freq->addWidget(label_amc_freq);

        doubleSpinBox_amc_freq = new QDoubleSpinBox(widget_amc);
        doubleSpinBox_amc_freq->setObjectName(QString::fromUtf8("doubleSpinBox_amc_freq"));
        doubleSpinBox_amc_freq->setMaximum(100000.000000000000000);

        horizontalLayout_amc_freq->addWidget(doubleSpinBox_amc_freq);


        verticalLayout_amc->addLayout(horizontalLayout_amc_freq);

        horizontalLayout_amc_bw = new QHBoxLayout();
        horizontalLayout_amc_bw->setObjectName(QString::fromUtf8("horizontalLayout_amc_bw"));
        label_amc_bw = new QLabel(widget_amc);
        label_amc_bw->setObjectName(QString::fromUtf8("label_amc_bw"));

        horizontalLayout_amc_bw->addWidget(label_amc_bw);

        doubleSpinBox_amc_bw = new QDoubleSpinBox(widget_amc);
        doubleSpinBox_amc_bw->setObjectName(QString::fromUtf8("doubleSpinBox_amc_bw"));
        doubleSpinBox_amc_bw->setMaximum(100000.000000000000000);

        horizontalLayout_amc_bw->addWidget(doubleSpinBox_amc_bw);


        verticalLayout_amc->addLayout(horizontalLayout_amc_bw);

        verticalSpacer_amc = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_amc->addItem(verticalSpacer_amc);


        horizontalLayout_4->addLayout(verticalLayout_amc);

        widget_plot_amc = new QCustomPlot(widget_amc);
        widget_plot_amc->setObjectName(QString::fromUtf8("widget_plot_amc"));
        widget_plot_amc->setMinimumSize(QSize(300, 0));

        horizontalLayout_4->addWidget(widget_plot_amc);

        textBrowser_amc = new QTextBrowser(widget_amc);
        textBrowser_amc->setObjectName(QString::fromUtf8("textBrowser_amc"));

        horizontalLayout_4->addWidget(textBrowser_amc);


        verticalLayout_page1->addWidget(widget_amc);


        verticalLayout_7->addLayout(verticalLayout_page1);

        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_page_2 = new QLabel(page_2);
        label_page_2->setObjectName(QString::fromUtf8("label_page_2"));
        label_page_2->setGeometry(QRect(500, 270, 591, 151));
        stackedWidget->addWidget(page_2);

        horizontalLayout_3->addWidget(stackedWidget);

        tabWidget = new QTabWidget(main_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(300, 0));
        tabWidget->setMaximumSize(QSize(330, 16777215));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(40, 50, 60);"));
        tab_ctrl = new QWidget();
        tab_ctrl->setObjectName(QString::fromUtf8("tab_ctrl"));
        tab_ctrl->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_6 = new QVBoxLayout(tab_ctrl);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        dockWidget_ctrl = new QDockWidget(tab_ctrl);
        dockWidget_ctrl->setObjectName(QString::fromUtf8("dockWidget_ctrl"));
        dockWidget_ctrl->setMaximumSize(QSize(300, 524287));
        dockWidget_ctrl->setStyleSheet(QString::fromUtf8(""));
        dockWidgetContents_ctrl = new QWidget();
        dockWidgetContents_ctrl->setObjectName(QString::fromUtf8("dockWidgetContents_ctrl"));
        horizontalLayout_5 = new QHBoxLayout(dockWidgetContents_ctrl);
        horizontalLayout_5->setSpacing(15);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(10, 10, 10, 10);
        verticalLayout_ctrl = new QVBoxLayout();
        verticalLayout_ctrl->setObjectName(QString::fromUtf8("verticalLayout_ctrl"));
        horizontalLayout_devices = new QHBoxLayout();
        horizontalLayout_devices->setObjectName(QString::fromUtf8("horizontalLayout_devices"));
        label_devices = new QLabel(dockWidgetContents_ctrl);
        label_devices->setObjectName(QString::fromUtf8("label_devices"));

        horizontalLayout_devices->addWidget(label_devices);

        comboBox_devices = new QComboBox(dockWidgetContents_ctrl);
        comboBox_devices->addItem(QString());
        comboBox_devices->setObjectName(QString::fromUtf8("comboBox_devices"));

        horizontalLayout_devices->addWidget(comboBox_devices);


        verticalLayout_ctrl->addLayout(horizontalLayout_devices);

        horizontalLayout_freq = new QHBoxLayout();
        horizontalLayout_freq->setObjectName(QString::fromUtf8("horizontalLayout_freq"));
        label_freq = new QLabel(dockWidgetContents_ctrl);
        label_freq->setObjectName(QString::fromUtf8("label_freq"));

        horizontalLayout_freq->addWidget(label_freq);

        doubleSpinBox_freq = new QDoubleSpinBox(dockWidgetContents_ctrl);
        doubleSpinBox_freq->setObjectName(QString::fromUtf8("doubleSpinBox_freq"));
        doubleSpinBox_freq->setMaximum(100000.000000000000000);

        horizontalLayout_freq->addWidget(doubleSpinBox_freq);


        verticalLayout_ctrl->addLayout(horizontalLayout_freq);

        horizontalLayout_bw = new QHBoxLayout();
        horizontalLayout_bw->setObjectName(QString::fromUtf8("horizontalLayout_bw"));
        label_bw = new QLabel(dockWidgetContents_ctrl);
        label_bw->setObjectName(QString::fromUtf8("label_bw"));

        horizontalLayout_bw->addWidget(label_bw);

        doubleSpinBox_bw = new QDoubleSpinBox(dockWidgetContents_ctrl);
        doubleSpinBox_bw->setObjectName(QString::fromUtf8("doubleSpinBox_bw"));
        doubleSpinBox_bw->setMaximum(100000.000000000000000);

        horizontalLayout_bw->addWidget(doubleSpinBox_bw);


        verticalLayout_ctrl->addLayout(horizontalLayout_bw);

        horizontalLayout_rbw = new QHBoxLayout();
        horizontalLayout_rbw->setObjectName(QString::fromUtf8("horizontalLayout_rbw"));
        label_rbw = new QLabel(dockWidgetContents_ctrl);
        label_rbw->setObjectName(QString::fromUtf8("label_rbw"));

        horizontalLayout_rbw->addWidget(label_rbw);

        doubleSpinBox_rbw = new QDoubleSpinBox(dockWidgetContents_ctrl);
        doubleSpinBox_rbw->setObjectName(QString::fromUtf8("doubleSpinBox_rbw"));
        doubleSpinBox_rbw->setMaximum(100000.000000000000000);

        horizontalLayout_rbw->addWidget(doubleSpinBox_rbw);


        verticalLayout_ctrl->addLayout(horizontalLayout_rbw);

        horizontalLayout_vbw = new QHBoxLayout();
        horizontalLayout_vbw->setObjectName(QString::fromUtf8("horizontalLayout_vbw"));
        label_vbw = new QLabel(dockWidgetContents_ctrl);
        label_vbw->setObjectName(QString::fromUtf8("label_vbw"));

        horizontalLayout_vbw->addWidget(label_vbw);

        doubleSpinBox_vbw = new QDoubleSpinBox(dockWidgetContents_ctrl);
        doubleSpinBox_vbw->setObjectName(QString::fromUtf8("doubleSpinBox_vbw"));
        doubleSpinBox_vbw->setMaximum(100000.000000000000000);

        horizontalLayout_vbw->addWidget(doubleSpinBox_vbw);


        verticalLayout_ctrl->addLayout(horizontalLayout_vbw);

        horizontalLayout_start_btn = new QHBoxLayout();
        horizontalLayout_start_btn->setObjectName(QString::fromUtf8("horizontalLayout_start_btn"));
        horizontalLayout_start_btn_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_start_btn->addItem(horizontalLayout_start_btn_2);

        btn_start = new QPushButton(dockWidgetContents_ctrl);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        horizontalLayout_start_btn->addWidget(btn_start);

        horizontalLayout_start_btn_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_start_btn->addItem(horizontalLayout_start_btn_3);


        verticalLayout_ctrl->addLayout(horizontalLayout_start_btn);

        verticalSpacer_ctrl = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_ctrl->addItem(verticalSpacer_ctrl);


        horizontalLayout_5->addLayout(verticalLayout_ctrl);

        dockWidget_ctrl->setWidget(dockWidgetContents_ctrl);

        verticalLayout_6->addWidget(dockWidget_ctrl);

        tabWidget->addTab(tab_ctrl, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_8 = new QVBoxLayout(tab_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        textBrowser = new QTextBrowser(tab_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_8->addWidget(textBrowser);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout_3->addWidget(tabWidget);


        verticalLayout_3->addWidget(main_widget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1900, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        title_label->setText(QCoreApplication::translate("MainWindow", "TitleLabel", nullptr));
        btn_min->setText(QString());
        btn_max->setText(QString());
        btn_close->setText(QString());
        btn_about->setText(QCoreApplication::translate("MainWindow", "ABOUT", nullptr));
        btn_amc->setText(QCoreApplication::translate("MainWindow", "AMC", nullptr));
        dockWidget_task->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\273\273\345\212\241\351\235\242\346\235\277", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\227\250\351\231\220\345\210\222\345\210\206\346\226\271\345\274\217", nullptr));
        checkBox_threshold->setText(QCoreApplication::translate("MainWindow", "\347\273\230\345\210\266\345\210\260\345\233\276\344\270\212", nullptr));
        label_3->setText(QString());
        radioButton_level->setText(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\351\230\210\345\200\274", nullptr));
        radioButton_auto->setText(QCoreApplication::translate("MainWindow", "\350\207\252 \351\200\202 \345\272\224", nullptr));
        radioButton_peak->setText(QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\345\263\260\345\200\274", nullptr));
        radioButton_history->setText(QCoreApplication::translate("MainWindow", "\345\216\206\345\217\262\346\225\260\346\215\256", nullptr));
        btn_history->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_offset->setText(QCoreApplication::translate("MainWindow", "\345\201\217\347\247\273\351\207\217\350\260\203\346\225\264", nullptr));
        label_task_list->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\212\241\345\210\227\350\241\250", nullptr));
        checkBox_task->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\347\233\221\346\265\213\344\273\273\345\212\241", nullptr));

        const bool __sortingEnabled = listWidget_task->isSortingEnabled();
        listWidget_task->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_task->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "test_1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_task->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "test_2", nullptr));
        listWidget_task->setSortingEnabled(__sortingEnabled);

        btn_task_modify->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        btn_task_add->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        btn_task_delete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        label_amc_freq->setText(QCoreApplication::translate("MainWindow", "\344\270\255\345\277\203\351\242\221\347\202\271(MHz)", nullptr));
        label_amc_bw->setText(QCoreApplication::translate("MainWindow", "\345\270\246\345\256\275(Mhz)", nullptr));
        label_page_2->setText(QCoreApplication::translate("MainWindow", "label_page_2", nullptr));
        dockWidget_ctrl->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\216\247\345\210\266\351\235\242\346\235\277", nullptr));
        label_devices->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\351\200\211\346\213\251", nullptr));
        comboBox_devices->setItemText(0, QCoreApplication::translate("MainWindow", "bb60c", nullptr));

        label_freq->setText(QCoreApplication::translate("MainWindow", "\344\270\255\345\277\203\351\242\221\347\202\271(MHz)", nullptr));
        label_bw->setText(QCoreApplication::translate("MainWindow", "\345\270\246\345\256\275(Mhz)", nullptr));
        label_rbw->setText(QCoreApplication::translate("MainWindow", "RBW(kHz)", nullptr));
        label_vbw->setText(QCoreApplication::translate("MainWindow", "VBW(kHz)", nullptr));
        btn_start->setText(QCoreApplication::translate("MainWindow", "   START   ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_ctrl), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
