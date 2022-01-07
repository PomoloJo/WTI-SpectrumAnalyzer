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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *widget_plot;
    QWidget *page_2;
    QLabel *label_page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
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
    QSpacerItem *horizontalSpacer_start_2;
    QPushButton *btn_start;
    QSpacerItem *horizontalSpacer_start_1;
    QSpacerItem *verticalSpacer_ctrl_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1763, 892);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        verticalLayout_2 = new QVBoxLayout(page_1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
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

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1763, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_devices = new QHBoxLayout();
        horizontalLayout_devices->setObjectName(QString::fromUtf8("horizontalLayout_devices"));
        label_devices = new QLabel(dockWidgetContents);
        label_devices->setObjectName(QString::fromUtf8("label_devices"));

        horizontalLayout_devices->addWidget(label_devices);

        comboBox_devices = new QComboBox(dockWidgetContents);
        comboBox_devices->addItem(QString());
        comboBox_devices->setObjectName(QString::fromUtf8("comboBox_devices"));

        horizontalLayout_devices->addWidget(comboBox_devices);


        verticalLayout->addLayout(horizontalLayout_devices);

        horizontalLayout_freq = new QHBoxLayout();
        horizontalLayout_freq->setObjectName(QString::fromUtf8("horizontalLayout_freq"));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_freq->addWidget(label);

        doubleSpinBox_freq = new QDoubleSpinBox(dockWidgetContents);
        doubleSpinBox_freq->setObjectName(QString::fromUtf8("doubleSpinBox_freq"));
        doubleSpinBox_freq->setMaximum(100000.000000000000000);

        horizontalLayout_freq->addWidget(doubleSpinBox_freq);


        verticalLayout->addLayout(horizontalLayout_freq);

        horizontalLayout_bw = new QHBoxLayout();
        horizontalLayout_bw->setObjectName(QString::fromUtf8("horizontalLayout_bw"));
        label_bw = new QLabel(dockWidgetContents);
        label_bw->setObjectName(QString::fromUtf8("label_bw"));

        horizontalLayout_bw->addWidget(label_bw);

        doubleSpinBox_bw = new QDoubleSpinBox(dockWidgetContents);
        doubleSpinBox_bw->setObjectName(QString::fromUtf8("doubleSpinBox_bw"));
        doubleSpinBox_bw->setMaximum(100000.000000000000000);

        horizontalLayout_bw->addWidget(doubleSpinBox_bw);


        verticalLayout->addLayout(horizontalLayout_bw);

        horizontalLayout_rbw = new QHBoxLayout();
        horizontalLayout_rbw->setObjectName(QString::fromUtf8("horizontalLayout_rbw"));
        label_rbw = new QLabel(dockWidgetContents);
        label_rbw->setObjectName(QString::fromUtf8("label_rbw"));

        horizontalLayout_rbw->addWidget(label_rbw);

        doubleSpinBox_rbw = new QDoubleSpinBox(dockWidgetContents);
        doubleSpinBox_rbw->setObjectName(QString::fromUtf8("doubleSpinBox_rbw"));
        doubleSpinBox_rbw->setMaximum(100000.000000000000000);

        horizontalLayout_rbw->addWidget(doubleSpinBox_rbw);


        verticalLayout->addLayout(horizontalLayout_rbw);

        horizontalLayout_vbw = new QHBoxLayout();
        horizontalLayout_vbw->setObjectName(QString::fromUtf8("horizontalLayout_vbw"));
        label_vbw = new QLabel(dockWidgetContents);
        label_vbw->setObjectName(QString::fromUtf8("label_vbw"));

        horizontalLayout_vbw->addWidget(label_vbw);

        doubleSpinBox_vbw = new QDoubleSpinBox(dockWidgetContents);
        doubleSpinBox_vbw->setObjectName(QString::fromUtf8("doubleSpinBox_vbw"));
        doubleSpinBox_vbw->setMaximum(100000.000000000000000);

        horizontalLayout_vbw->addWidget(doubleSpinBox_vbw);


        verticalLayout->addLayout(horizontalLayout_vbw);

        horizontalLayout_start_btn = new QHBoxLayout();
        horizontalLayout_start_btn->setObjectName(QString::fromUtf8("horizontalLayout_start_btn"));
        horizontalSpacer_start_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_start_btn->addItem(horizontalSpacer_start_2);

        btn_start = new QPushButton(dockWidgetContents);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        horizontalLayout_start_btn->addWidget(btn_start);

        horizontalSpacer_start_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_start_btn->addItem(horizontalSpacer_start_1);


        verticalLayout->addLayout(horizontalLayout_start_btn);

        verticalSpacer_ctrl_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_ctrl_2);


        horizontalLayout_2->addLayout(verticalLayout);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_page_2->setText(QCoreApplication::translate("MainWindow", "label_page_2", nullptr));
        dockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\216\247\345\210\266\351\235\242\346\235\277", nullptr));
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
