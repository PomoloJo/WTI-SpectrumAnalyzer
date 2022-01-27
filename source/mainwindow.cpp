#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();

    // 去除系统带的标题栏
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 安装事件过滤器，this监控title_widget实现鼠标拖拽标题栏
    ui->title_widget->installEventFilter(this);
    // 安装事件过滤器，this监控widget_plot的事件
    ui->widget_plot->installEventFilter(this);
    ui->widget_plot->setMouseTracking(true);

    // 右上角按钮事件过滤
    ui->btn_close->installEventFilter(this);

    // 工作线程，第二个参数是时间间隔，默认值0ms
    m_p_work_thread = new CWorkThread(this);

    // 添加状态栏
    m_mouse_coordinate = new QLabel("realtime mouse coordinate", this);
    // addWidget是从左往右添加, addPermanentWidget是从右往左添加
    //ui->statusbar->addWidget(new QLabel("1", this));
    ui->statusbar->addPermanentWidget(m_mouse_coordinate);

    connect(m_p_work_thread, &CWorkThread::sendData, this, &MainWindow::timeToReplot);
}

MainWindow::~MainWindow()
{
    delete m_p_work_thread;
    delete ui;
}


void MainWindow::initUi()
{
    // icons setting
    ui->btn_close->setFlat(true);
    ui->btn_max->setFlat(true);
    ui->btn_min->setFlat(true);
     
    //ui->btn_close->setIcon(QIcon(":/icons/close.png")); // 该写法在vs中似乎无法生效
    ui->btn_close->setIcon(QIcon("./resource/icons/close4.png"));

    // dark theme
    ui->widget_plot->setBackground(QColor(8, 8, 8));
    ui->widget_plot->xAxis->grid()->setPen(QPen(QColor(32, 32, 32), 1, Qt::PenStyle::DashLine));//网格线
    ui->widget_plot->yAxis->grid()->setPen(QPen(QColor(32, 32, 32), 1, Qt::PenStyle::DashLine));//网格线
    ui->widget_plot->xAxis->grid()->setSubGridPen(QPen(QColor(25, 25, 25), 1, Qt::DotLine));//子网格线
    ui->widget_plot->yAxis->grid()->setSubGridPen(QPen(QColor(25, 25, 25), 1, Qt::DotLine));//子网格线
    ui->widget_plot->xAxis->grid()->setSubGridVisible(true);//显示x轴子网格线
    ui->widget_plot->yAxis->grid()->setSubGridVisible(true);//显示y轴子网格线

    ui->widget_plot->xAxis->setTickLabelColor(QColor(128, 128, 255));
    ui->widget_plot->yAxis->setTickLabelColor(QColor(128, 128, 255));
    ui->widget_plot->xAxis->setRangeUpper(0);
    ui->widget_plot->xAxis->setRangeLower(10000);
    ui->widget_plot->yAxis->setRangeUpper(0);
    ui->widget_plot->yAxis->setRangeLower(-100);
    ui->widget_plot->xAxis->setNumberFormat("ebc");
}

void MainWindow::initMember()
{
    qDebug() << "init";
}

// 重写事件过滤器
bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
    // 目前主要是重写鼠标事件
    // 用于实时显示xy值
    static float pos_x;
    static float pos_y;
    // 记录鼠标点击状态
    static bool mouse_left_btn_pressed = false;
    static bool mouse_right_btn_pressed = false;
    // 记录鼠标坐标
    static QPoint mousePoint;
    // plot用的偏移量
    static QPoint single_plot_delta{};
    static QPoint total_plot_delta{};
    // total_plot_delta 的值在 release 之前需要保持不变，所以需要一个可以变的起始位置
    static int x_start_pos{};
    static int y_start_pos{};
    // 用于记录坐标轴缩放的显示区域大小
    static int plot_x_range;
    static int plot_y_range;

    QMouseEvent* mouse_event = (QMouseEvent*)event;

    // 当目标是右上角button
    // 这里不要 return，直接 break。  return 会把事件截掉，除非后续触发的操作比如关闭事件也手动写上
    if (ui->btn_close == target)
    {
        switch (event->type()) 
        {
            case QEvent::HoverEnter:
            {
                ui->btn_close->setIcon(QIcon("./resource/icons/close2.png"));
                break;
            }
            case QEvent::HoverLeave:
            {
                ui->btn_close->setIcon(QIcon("./resource/icons/close4.png"));
                break;
            }
            case QEvent::MouseButtonPress:
            {
                ui->btn_close->setIcon(QIcon("./resource/icons/close3.png"));
                break;
            }
            case QEvent::MouseButtonRelease:
            {
                ui->btn_close->setIcon(QIcon("./resource/icons/close4.png"));
                break;
            }
            default:
                break;
        }
    }

    // 当目标是标题栏时实现拖拽
    if (ui->title_widget == target)
    {
        switch (event->type())
        {
            case QEvent::MouseButtonPress:
            {
                if (mouse_event->buttons() == Qt::LeftButton) 
                {
                    mouse_left_btn_pressed = true;
                    mousePoint = mouse_event->globalPos() - this->pos();
                    return true;
                }
            }
            case QEvent::MouseButtonRelease:
            {
                mouse_left_btn_pressed = false;
                return true;
            }
            case QEvent::MouseMove:
            {
                if (mouse_left_btn_pressed && (mouse_event->buttons() && Qt::LeftButton)) 
                {
                    this->move(mouse_event->globalPos() - mousePoint);
                    return true;
                }
            }
            default:
                break;
        }
    }

    // 当目标是绘图绘图窗口时实现缩放，显示坐标等
    if (ui->widget_plot == target)
    {
        switch (event->type())
        {
            case QEvent::MouseButtonPress:
            {
                if (mouse_event->buttons() == Qt::LeftButton) 
                {
                    mouse_left_btn_pressed = true;
                    mousePoint = mouse_event->globalPos();
                    plot_x_range = ui->widget_plot->xAxis->range().size();
                    plot_y_range = ui->widget_plot->yAxis->range().size();
                    //qDebug() << "left x press" << total_plot_delta.x();
                    break;
                }
                else if (mouse_event->buttons() == Qt::RightButton)
                {
                    mouse_right_btn_pressed = true;
                    mousePoint = mouse_event->globalPos();
                    plot_x_range = ui->widget_plot->xAxis->range().size();
                    plot_y_range = ui->widget_plot->yAxis->range().size();
                    //qDebug() << "right x press" << total_plot_delta.x();
                    break;
                }
            }
            case QEvent::MouseButtonRelease:
            {
                if (mouse_left_btn_pressed)
                {
                    mouse_left_btn_pressed = false;
                    mousePoint = mouse_event->globalPos();
                    total_plot_delta.setX(x_start_pos);
                    total_plot_delta.setY(y_start_pos);
                    //qDebug() << "left x release" << total_plot_delta.x();
                }
                else if (mouse_right_btn_pressed)
                {
                    mouse_right_btn_pressed = false;
                    mousePoint = mouse_event->globalPos();
                    plot_x_range = ui->widget_plot->xAxis->range().size();
                    plot_y_range = ui->widget_plot->yAxis->range().size();
                    total_plot_delta.setX(x_start_pos);
                    total_plot_delta.setY(y_start_pos);
                    //qDebug() << "right x release" << total_plot_delta.x();
                }
                // 显示范围限制
                if (total_plot_delta.x() < 0)
                    total_plot_delta.setX(0);
                if (total_plot_delta.y() > 200)
                    total_plot_delta.setY(200);
                break;
            }
            case QMouseEvent::MouseMove:
            {  
                if (mouse_left_btn_pressed && (mouse_event->buttons() && Qt::LeftButton)) 
                {   
                    single_plot_delta = mouse_event->globalPos() - mousePoint;
                    // 拖拽比例，可调，1000是经验值
                    auto x_drag_ratio = plot_x_range / 1000.0;
                    x_start_pos = total_plot_delta.x() - single_plot_delta.x() * x_drag_ratio;
                    auto y_drag_ratio = plot_y_range / 1000.0;
                    y_start_pos = total_plot_delta.y() + single_plot_delta.y() * y_drag_ratio;
                    if (x_start_pos >= 0 || y_start_pos <= 200)
                    {
                        if (x_start_pos >= 0)
                        {
                            ui->widget_plot->xAxis->setRange(
                                x_start_pos,
                                plot_x_range, 
                                Qt::AlignLeft);
                        }
                        if (y_start_pos <= 200)
                        {
                            ui->widget_plot->yAxis->setRange(
                                y_start_pos,
                                plot_y_range,
                                Qt::AlignRight);
                        }
                        ui->widget_plot->replot();
                    }
                    return true;
                }

                if (mouse_right_btn_pressed && (mouse_event->buttons() && Qt::RightButton))
                {
                    single_plot_delta = mouse_event->globalPos() - mousePoint;
                    // 缩放比例，可调，1000是经验值
                    auto x_zoom_ratio = plot_x_range / 1000.0;
                    x_start_pos = total_plot_delta.x() + single_plot_delta.x() * x_zoom_ratio;
                    auto y_zoom_ratio = plot_y_range / 1000.0;
                    y_start_pos = total_plot_delta.y() + single_plot_delta.y() * y_zoom_ratio;
                    if (x_start_pos >= 0 || y_start_pos <= 200)
                    {
                        if (x_start_pos >= 0)
                        {
                            ui->widget_plot->xAxis->setRange(
                                x_start_pos,
                                plot_x_range - 2 * (single_plot_delta.x() * x_zoom_ratio),
                                Qt::AlignLeft);
                        }
                        if (y_start_pos <= 200)
                        {
                            ui->widget_plot->yAxis->setRange(
                                y_start_pos,
                                plot_y_range + 2 * (single_plot_delta.y() * y_zoom_ratio),
                                Qt::AlignRight);
                        }
                        ui->widget_plot->replot();
                    }
                    return true;
                }

                pos_x = ui->widget_plot->xAxis->pixelToCoord(mouse_event->pos().x());
                pos_y = ui->widget_plot->yAxis->pixelToCoord(mouse_event->pos().y());
                //qDebug() << pos_x << ", " << pos_y;
                m_mouse_coordinate->setText(QString("%1,   %2 dBm").arg(pos_x).arg(pos_y));
                break;
            }
            default:
                break;
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
        //cmdline_str.sprintf("device_driver\\bb60c\\bb60c.exe %fe6 %fe6 %fe3 %fe3 %f", freq, bw, rbw, vbw, sweep_time);
        cmdline_str.sprintf("device_driver\\fake_data.exe");
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

        Sleep(2500);


        QCustomPlot* p_custom_plot = ui->widget_plot;

        // 清除所有graph
        p_custom_plot->clearGraphs();

        // 添加一条曲线
        QCPGraph* pgraph = p_custom_plot->addGraph();
        // line color:green
        // pgraph->setPen(QPen(QColor(16, 255, 32)));
        // change line color
        QLinearGradient gradient(0, 100, 0, 500);
        gradient.setColorAt(0.3, QColor(16, 255, 32));
        gradient.setColorAt(0.6, QColor(32, 230, 128));
        gradient.setColorAt(0.9, QColor(32, 200, 255));
        pgraph->setPen(QPen(QBrush(gradient), 1));

        // 设置Y轴范围
        p_custom_plot->yAxis->setRange(-100, 0);
        // 设置大小
        p_custom_plot->resize(ui->widget_plot->width(), ui->widget_plot->height());
        // 可以进行鼠标位置放大缩小、拖拽 、放大缩小坐标系
        //p_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        //p_custom_plot->axisRect()->setRangeDrag(Qt::Vertical);// Qt::Horizontal

        // 重绘，应用所有更改的设置
        p_custom_plot->replot();

        m_p_work_thread->start();
        ui->btn_start->setText("      STOP      ");
    }
    else
    {
        // 接收exe强制退出
        std::string device_exe = std::string("TASKKILL /F /IM fake_data.exe");  // + exe_name;
        WinExec(device_exe.c_str(), SW_HIDE);

        // 结束进程
        m_p_work_thread->stopRunning();
    
        ui->btn_start->setText("      START      ");
    }
    // 只要点击按钮，就刷新重绘
    is_first_time_to_replot = true;
}

void MainWindow::on_btn_close_clicked()
{
    QString btn_start_text(ui->btn_start->text());
    if (btn_start_text.contains("stop", Qt::CaseInsensitive))
    {
        on_btn_start_clicked();
    }
    Sleep(500);
    this->close();
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