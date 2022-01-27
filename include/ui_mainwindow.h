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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
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
    QPushButton *pushButton_about;
    QSpacerItem *horizontalSpacer_menu;
    QWidget *main_widget;
    QHBoxLayout *horizontalLayout_4;
    QDockWidget *dockWidget_task;
    QWidget *dockWidgetContents_task;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QFrame *frame_threshold;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox_threshold;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_level;
    QRadioButton *radioButton_level;
    QSlider *horizontalSlider_level;
    QHBoxLayout *horizontalLayout_auto;
    QRadioButton *radioButton_auto;
    QSlider *horizontalSlider_auto;
    QHBoxLayout *horizontalLayout_peak;
    QRadioButton *radioButton_peak;
    QSlider *horizontalSlider_peak;
    QHBoxLayout *horizontalLayout_history;
    QRadioButton *radioButton_history;
    QSlider *horizontalSlider_history;
    QFrame *line_threshold;
    QLabel *label_task_list;
    QFrame *frame_task_list;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidget_task;
    QHBoxLayout *horizontalLayout_task_btn;
    QPushButton *btn_task_modify;
    QPushButton *btn_task_add;
    QPushButton *btn_task_delete;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *widget_plot;
    QWidget *page_2;
    QLabel *label_page_2;
    QDockWidget *dockWidget_ctrl;
    QWidget *dockWidgetContents_ctrl;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_ctrl;
    QHBoxLayout *horizontalLayout_devices;
    QLabel *label_devices;
    QComboBox *comboBox_devices;
    QHBoxLayout *horizontalLayout_freq;
    QLabel *label;
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
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1500, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 18, 31);\n"
"color: rgb(220, 220, 220);"));
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
        pushButton_about = new QPushButton(menu_widget);
        pushButton_about->setObjectName(QString::fromUtf8("pushButton_about"));

        horizontalLayout_2->addWidget(pushButton_about);

        horizontalSpacer_menu = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_menu);


        verticalLayout_3->addWidget(menu_widget);

        main_widget = new QWidget(centralwidget);
        main_widget->setObjectName(QString::fromUtf8("main_widget"));
        sizePolicy.setHeightForWidth(main_widget->sizePolicy().hasHeightForWidth());
        main_widget->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(main_widget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        dockWidget_task = new QDockWidget(main_widget);
        dockWidget_task->setObjectName(QString::fromUtf8("dockWidget_task"));
        dockWidget_task->setMaximumSize(QSize(300, 524287));
        dockWidget_task->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 63, 65);\n"
"background-color: rgb(20, 28, 36);"));
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

        horizontalLayout_level = new QHBoxLayout();
        horizontalLayout_level->setObjectName(QString::fromUtf8("horizontalLayout_level"));
        radioButton_level = new QRadioButton(frame_threshold);
        radioButton_level->setObjectName(QString::fromUtf8("radioButton_level"));
        radioButton_level->setMinimumSize(QSize(100, 0));

        horizontalLayout_level->addWidget(radioButton_level);

        horizontalSlider_level = new QSlider(frame_threshold);
        horizontalSlider_level->setObjectName(QString::fromUtf8("horizontalSlider_level"));
        horizontalSlider_level->setMinimum(-100);
        horizontalSlider_level->setMaximum(100);
        horizontalSlider_level->setOrientation(Qt::Horizontal);
        horizontalSlider_level->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_level->addWidget(horizontalSlider_level);


        verticalLayout_5->addLayout(horizontalLayout_level);

        horizontalLayout_auto = new QHBoxLayout();
        horizontalLayout_auto->setObjectName(QString::fromUtf8("horizontalLayout_auto"));
        radioButton_auto = new QRadioButton(frame_threshold);
        radioButton_auto->setObjectName(QString::fromUtf8("radioButton_auto"));
        radioButton_auto->setMinimumSize(QSize(100, 0));

        horizontalLayout_auto->addWidget(radioButton_auto);

        horizontalSlider_auto = new QSlider(frame_threshold);
        horizontalSlider_auto->setObjectName(QString::fromUtf8("horizontalSlider_auto"));
        horizontalSlider_auto->setMinimum(-100);
        horizontalSlider_auto->setMaximum(100);
        horizontalSlider_auto->setOrientation(Qt::Horizontal);
        horizontalSlider_auto->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_auto->addWidget(horizontalSlider_auto);


        verticalLayout_5->addLayout(horizontalLayout_auto);

        horizontalLayout_peak = new QHBoxLayout();
        horizontalLayout_peak->setObjectName(QString::fromUtf8("horizontalLayout_peak"));
        radioButton_peak = new QRadioButton(frame_threshold);
        radioButton_peak->setObjectName(QString::fromUtf8("radioButton_peak"));
        radioButton_peak->setMinimumSize(QSize(100, 0));

        horizontalLayout_peak->addWidget(radioButton_peak);

        horizontalSlider_peak = new QSlider(frame_threshold);
        horizontalSlider_peak->setObjectName(QString::fromUtf8("horizontalSlider_peak"));
        horizontalSlider_peak->setMinimum(-100);
        horizontalSlider_peak->setMaximum(100);
        horizontalSlider_peak->setOrientation(Qt::Horizontal);
        horizontalSlider_peak->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_peak->addWidget(horizontalSlider_peak);


        verticalLayout_5->addLayout(horizontalLayout_peak);

        horizontalLayout_history = new QHBoxLayout();
        horizontalLayout_history->setObjectName(QString::fromUtf8("horizontalLayout_history"));
        radioButton_history = new QRadioButton(frame_threshold);
        radioButton_history->setObjectName(QString::fromUtf8("radioButton_history"));
        radioButton_history->setMinimumSize(QSize(100, 0));

        horizontalLayout_history->addWidget(radioButton_history);

        horizontalSlider_history = new QSlider(frame_threshold);
        horizontalSlider_history->setObjectName(QString::fromUtf8("horizontalSlider_history"));
        horizontalSlider_history->setMinimum(-100);
        horizontalSlider_history->setMaximum(100);
        horizontalSlider_history->setOrientation(Qt::Horizontal);
        horizontalSlider_history->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_history->addWidget(horizontalSlider_history);


        verticalLayout_5->addLayout(horizontalLayout_history);


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

        horizontalLayout_4->addWidget(dockWidget_task);

        stackedWidget = new QStackedWidget(main_widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        verticalLayout_2 = new QVBoxLayout(page_1);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        widget_plot = new QCustomPlot(page_1);
        widget_plot->setObjectName(QString::fromUtf8("widget_plot"));

        verticalLayout_2->addWidget(widget_plot);

        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_page_2 = new QLabel(page_2);
        label_page_2->setObjectName(QString::fromUtf8("label_page_2"));
        label_page_2->setGeometry(QRect(500, 270, 591, 151));
        stackedWidget->addWidget(page_2);

        horizontalLayout_4->addWidget(stackedWidget);

        dockWidget_ctrl = new QDockWidget(main_widget);
        dockWidget_ctrl->setObjectName(QString::fromUtf8("dockWidget_ctrl"));
        dockWidget_ctrl->setMaximumSize(QSize(300, 524287));
        dockWidget_ctrl->setStyleSheet(QString::fromUtf8("background-color: rgb(60, 63, 65);\n"
"background-color: rgb(20, 28, 36);"));
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
        label = new QLabel(dockWidgetContents_ctrl);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_freq->addWidget(label);

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

        horizontalLayout_4->addWidget(dockWidget_ctrl);


        verticalLayout_3->addWidget(main_widget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1500, 23));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        title_label->setText(QCoreApplication::translate("MainWindow", "TitleLabel", nullptr));
        btn_min->setText(QCoreApplication::translate("MainWindow", "min", nullptr));
        btn_max->setText(QCoreApplication::translate("MainWindow", "max", nullptr));
        btn_close->setText(QString());
        pushButton_about->setText(QCoreApplication::translate("MainWindow", "about", nullptr));
        dockWidget_task->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\273\273\345\212\241\351\235\242\346\235\277", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\227\250\351\231\220\345\210\222\345\210\206\346\226\271\345\274\217", nullptr));
        checkBox_threshold->setText(QCoreApplication::translate("MainWindow", "\347\273\230\345\210\266\345\210\260\345\233\276\344\270\212", nullptr));
        label_3->setText(QString());
        radioButton_level->setText(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\351\230\210\345\200\274", nullptr));
        radioButton_auto->setText(QCoreApplication::translate("MainWindow", "\350\207\252 \351\200\202 \345\272\224", nullptr));
        radioButton_peak->setText(QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\345\263\260\345\200\274", nullptr));
        radioButton_history->setText(QCoreApplication::translate("MainWindow", "\345\216\206\345\217\262\346\225\260\346\215\256", nullptr));
        label_task_list->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\212\241\345\210\227\350\241\250", nullptr));

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
        label_page_2->setText(QCoreApplication::translate("MainWindow", "label_page_2", nullptr));
        dockWidget_ctrl->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\216\247\345\210\266\351\235\242\346\235\277", nullptr));
        label_devices->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\351\200\211\346\213\251", nullptr));
        comboBox_devices->setItemText(0, QCoreApplication::translate("MainWindow", "bb60c", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\344\270\255\345\277\203\351\242\221\347\202\271(MHz)", nullptr));
        label_bw->setText(QCoreApplication::translate("MainWindow", "\345\270\246\345\256\275(Mhz)", nullptr));
        label_rbw->setText(QCoreApplication::translate("MainWindow", "RBW(kHz)", nullptr));
        label_vbw->setText(QCoreApplication::translate("MainWindow", "VBW(kHz)", nullptr));
        btn_start->setText(QCoreApplication::translate("MainWindow", "   START   ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
