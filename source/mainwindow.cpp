#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();

    // 安装事件过滤器，this监控widget_plot的事件
    ui->widget_plot->installEventFilter(this);
    ui->widget_plot->setMouseTracking(true);

    m_p_work_thread = new CWorkThread(this, 200);

    // 添加状态栏
    m_status_bar = statusBar();//创建状态栏
    m_mouse_coordinate = new QLabel("realtime mouse coordinate", this);
    //addWidget是从左往右添加, addPermanentWidget是从右往左添加
    //status_bar->addWidget(new QLabel("1", this));
    m_status_bar->addPermanentWidget(m_mouse_coordinate);


    connect(m_p_work_thread, &CWorkThread::sendData, this, &MainWindow::timeToReplot);
}

MainWindow::~MainWindow()
{
    delete m_p_work_thread;
    delete ui;
}


void MainWindow::initUi()
{
    // add every dock_widget into list
    QList<QDockWidget*> dock_list;
    dock_list.append(ui->dockWidget);
    // or use {dockWidget1, dockWidget2, ...} directly
    resizeDocks(dock_list, {300}, Qt::Horizontal);
}

void MainWindow::initMember()
{
    qDebug() << "test";
}

// 重写事件过滤器，用于过滤鼠标事件
bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
    static float pos_x;
    static float pos_y;
    static bool mouse_right_btn_pressed = false;
    QMouseEvent* mouse_event = (QMouseEvent*)event;
    if (target == ui->widget_plot)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (mouse_event->buttons() == Qt::RightButton)
            {
                mouse_right_btn_pressed = true;
                ui->widget_plot->axisRect()->setRangeZoom(Qt::Vertical);
                return true;
            }
        }
        else if ((event->type() == QEvent::MouseButtonRelease) && mouse_right_btn_pressed)
        {
            mouse_right_btn_pressed = false;
            ui->widget_plot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
            return true;
        }

        if (mouse_event->type() == QMouseEvent::MouseMove)
        {
            pos_x = ui->widget_plot->xAxis->pixelToCoord(mouse_event->pos().x());
            pos_y = ui->widget_plot->yAxis->pixelToCoord(mouse_event->pos().y());
            //qDebug() << pos_x << ", " << pos_y;
            m_mouse_coordinate->setText(QString("%1,   %2 dbm").arg(pos_x).arg(pos_y));
        }   
    }
    return QObject::eventFilter(target, event);
}


void MainWindow::on_btn_start_clicked()
{
    qDebug() << "btn_start clicked ";

    QString btn_start_text(ui->btn_start->text());
    if (btn_start_text.contains("start", Qt::CaseInsensitive))
    {
        STARTUPINFO si;
        memset(&si, 0, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;
        PROCESS_INFORMATION pi;
        memset(&pi, 0, sizeof(PROCESS_INFORMATION));

        auto freq = ui->doubleSpinBox_freq->value();
        auto bw = ui->doubleSpinBox_bw->value();
        auto rbw = ui->doubleSpinBox_rbw->value();
        auto vbw = ui->doubleSpinBox_vbw->value();
        auto sweep_time = 0.001;
        QString cmdline_str;
        cmdline_str.sprintf("device_driver\\bb60c\\bb60c.exe %fe6 %fe6 %fe3 %fe3 %f", freq, bw, rbw, vbw, sweep_time);
        qDebug() <<cmdline_str;
        //WCHAR cmdline[] = L"device_driver\\bb60c\\bb60c.exe 1000.000000e6 100.000000e6 100e3 10e3 0.001";
        auto cmdline_temp = cmdline_str.toStdWString();
        auto cmdline_final = const_cast<wchar_t*>(cmdline_temp.c_str());
        if (!CreateProcess(NULL,cmdline_final,NULL,NULL,FALSE,
            0,NULL,NULL,&si,&pi))
        {
            qDebug() << "process create failed";
        }
        else
        {
            qDebug() << "process create success";
        }
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);

        Sleep(3000);


        QCustomPlot* p_custom_plot = ui->widget_plot;

        // 清除所有graph
        p_custom_plot->clearGraphs();

        // 添加一条曲线
        QCPGraph* pgraph = p_custom_plot->addGraph();

        //设置X轴范围
        //p_custom_plot->xAxis->setRange(0, 10000);
        //设置Y轴范围
        p_custom_plot->yAxis->setRange(-100, 0);
        //x轴名字
        p_custom_plot->xAxis->setLabel("X");
        //Y轴名字
        p_custom_plot->yAxis->setLabel("Y");
        //设置大小
        p_custom_plot->resize(ui->widget_plot->width(), ui->widget_plot->height());
        //可以进行鼠标位置放大缩小、拖拽 、放大缩小坐标系
        p_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        //p_custom_plot->axisRect()->setRangeDrag(Qt::Vertical);// Qt::Horizontal

        //重绘，应用所有更改的设置
        p_custom_plot->replot();

        m_p_work_thread->start();
        ui->btn_start->setText("      STOP      ");
    }
    else
    {
        // 强制退出
        std::string device_exe = std::string("TASKKILL /F /IM bb60c.exe");  // + exe_name;
        WinExec(device_exe.c_str(), SW_HIDE);

        m_p_work_thread->stopRunning();
        ui->btn_start->setText("      START      ");
    }
    // 只要点击按钮，就刷新重绘
    is_first_time_to_replot = true;
}

void MainWindow::timeToReplot(const double* recv_data, const int point_num)
{
    QCustomPlot* p_custom_plot = ui->widget_plot;
    static int old_point_num{};
    static QVector<double> x;
    if (old_point_num != point_num)
    {
        old_point_num = point_num;
        QVector<double>(point_num).swap(x);
    }

    if (is_first_time_to_replot)
    {
        qDebug() << "first time to replot";
        p_custom_plot->xAxis->setRange(0, point_num);
        for (int i = 0; i < point_num; i++)
        {
            x[i] = i;
        }
        is_first_time_to_replot = false;
    }
    else
    {
        //qDebug() << "run replot";
        QVector<double> y(recv_data, recv_data + point_num);
        p_custom_plot->graph(0)->setData(x, y);
        //重绘，应用所有更改的设置
        p_custom_plot->replot();
    }
}



