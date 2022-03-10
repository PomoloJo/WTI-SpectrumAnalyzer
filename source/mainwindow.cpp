#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_plot_status(PlotStatus::NORMAL_PLOT),
    is_first_time_to_replot(true),
    m_recv_data(nullptr)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();

    m_point_num = 0;

    // 去除系统带的标题栏
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 安装事件过滤器，this监控title_widget实现鼠标拖拽标题栏
    ui->title_widget->installEventFilter(this);
    // 安装事件过滤器，this监控widget_plot的事件
    ui->widget_plot->installEventFilter(this);
    ui->widget_plot->setMouseTracking(true);

    // 右上角按钮事件过滤
    ui->btn_close->installEventFilter(this);
    ui->btn_max->installEventFilter(this);
    ui->btn_min->installEventFilter(this);

    // 工作线程，第二个参数是时间间隔，默认值0ms
    m_p_work_thread = new CWorkThread(this, 500);

    // 添加状态栏
    m_mouse_coordinate = new QLabel("realtime mouse coordinate", this);
    // addWidget是从左往右添加, addPermanentWidget是从右往左添加
    //ui->statusbar->addWidget(new QLabel("1", this));
    ui->statusbar->addPermanentWidget(m_mouse_coordinate);

    connect(m_p_work_thread, &CWorkThread::sendData, this, &MainWindow::timeToReplot);

    // 添加一条曲线作为实际数据曲线
    QCPGraph* pgraph = ui->widget_plot->addGraph();
    // 添加第二条曲线作为阈值曲线
    QCPGraph* threshold_graph = ui->widget_plot->addGraph();
        
    ui->tabWidget->setStyleSheet(
        "QTabWidget::pane{ border:none; }\
        QTabBar::tab { \
            min-width:100px; \
            color: gray; \
            border-top-left-radius: 2px; \
            border-top-right-radius: 2px; \
            padding:2px;}\
        QTabBar::tab:hover{ background:rgb(255, 255, 255, 100); }\
        QTabBar::tab:!selected {margin-top: 0px;} \
        QTabBar::tab:selected {color: white; background:rgb(40,50,60);}"
    );
    ui->tabWidget->setCurrentIndex(0);
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
    ui->btn_close->setIcon(QIcon("./resource/icons/close1.png"));
    ui->btn_max->setIcon(QIcon("./resource/icons/max1.png"));
    ui->btn_min->setIcon(QIcon("./resource/icons/min1.png"));

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

    ui->btn_history->hide();
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
            ui->btn_close->setIcon(QIcon("./resource/icons/close2.png")); break;
        case QEvent::HoverLeave:
            ui->btn_close->setIcon(QIcon("./resource/icons/close1.png")); break;
        case QEvent::MouseButtonPress:
            ui->btn_close->setIcon(QIcon("./resource/icons/close3.png")); break;
        case QEvent::MouseButtonRelease:
            ui->btn_close->setIcon(QIcon("./resource/icons/close1.png")); break;
        default: break;
        }
    }
    if (ui->btn_max == target)
    {
        switch (event->type())
        {
        case QEvent::HoverEnter:
            ui->btn_max->setIcon(QIcon("./resource/icons/max2.png")); break;
        case QEvent::HoverLeave:
            ui->btn_max->setIcon(QIcon("./resource/icons/max1.png")); break;
        case QEvent::MouseButtonPress:
            ui->btn_max->setIcon(QIcon("./resource/icons/max3.png")); break;
        case QEvent::MouseButtonRelease:
            ui->btn_max->setIcon(QIcon("./resource/icons/max1.png")); break;
        default: break;
        }
    }
    if (ui->btn_min == target)
    {
        switch (event->type())
        {
        case QEvent::HoverEnter:
            ui->btn_min->setIcon(QIcon("./resource/icons/min2.png")); break;
        case QEvent::HoverLeave:
            ui->btn_min->setIcon(QIcon("./resource/icons/min1.png")); break;
        case QEvent::MouseButtonPress:
            ui->btn_min->setIcon(QIcon("./resource/icons/min3.png")); break;
        case QEvent::MouseButtonRelease:
            ui->btn_min->setIcon(QIcon("./resource/icons/min1.png")); break;
        default: break;
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
                if (m_point_num != 0 && m_center_freq != 0 && m_bw != 0)
                {
                    pos_x = (pos_x / m_point_num * m_bw + m_center_freq - m_bw / 2);// *1000000;
                    m_mouse_coordinate->setText(QString("%1 MHz,   %2 dBm").arg(pos_x).arg(pos_y));
                }
                else
                    m_mouse_coordinate->setText(QString("%1 points,   %2 dBm").arg(pos_x).arg(pos_y));
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

        m_center_freq = ui->doubleSpinBox_freq->value();
        m_bw = ui->doubleSpinBox_bw->value();
        m_rbw = ui->doubleSpinBox_rbw->value();
        m_vbw = ui->doubleSpinBox_vbw->value();
        m_sweep_time = 0.001;

        m_freq_start = m_center_freq - m_bw / 2;
        m_freq_end = m_center_freq + m_bw / 2;
        
        // 应将设备选择与参数这部分更改为独立文件或函数
        QString cmdline_str;
        cmdline_str.sprintf("device_driver\\bb60c\\bb60c.exe %fe6 %fe6 %fe3 %fe3 %f", m_center_freq, m_bw, m_rbw, m_vbw, m_sweep_time);
        //cmdline_str.sprintf("device_driver\\fake_data.exe");
        //cmdline_str.sprintf("device_driver\\bb60c\\bb60c.exe 3000.000000e6 500.000000e6 100e3 10e3 0.01");
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
        // 在初始化的时候已经添加，但因为上一句清理了所有曲线，下面重新添加
        // 添加一条曲线作为实际数据曲线
        QCPGraph* pgraph = p_custom_plot->addGraph();
        // 添加第二条曲线作为阈值曲线
        QCPGraph* threshold_graph = p_custom_plot->addGraph();
        // 阈值曲线颜色和格式
        QPen line_pen;
        line_pen.setColor(Qt::yellow);
        line_pen.setWidth(1);
        ui->widget_plot->graph(1)->setPen(line_pen);
        ui->widget_plot->graph(1)->setLineStyle(QCPGraph::lsLine);
        
        // line color:green
        // pgraph->setPen(QPen(QColor(16, 255, 32)));
        // change line color
        QLinearGradient gradient(0, 100, 0, 600);
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
        // 进程名应写得尽量复杂或者通过别的形式转换一下，以免误杀其他同名的正常进程
        //std::string device_exe = std::string("TASKKILL /F /IM fake_data.exe");  // + exe_name;
        std::string device_exe = std::string("TASKKILL /F /IM bb60c.exe");
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

void MainWindow::on_btn_max_clicked()
{
    if (windowState() == Qt::WindowNoState)
    {
        //showFullScreen();
        setWindowState(Qt::WindowMaximized);
    }
    else
    {
        //showNormal();
        setWindowState(Qt::WindowNoState);
    }
}

void MainWindow::on_btn_min_clicked()
{
    //showMinimized();
    setWindowState(Qt::WindowMinimized);
}

// 产生绘图变化的核心函数, graph(0)数据曲线，graph(1)阈值曲线
void MainWindow::timeToReplot(const double* recv_data, const int point_num)
{
    QCustomPlot* p_custom_plot = ui->widget_plot;
    static int old_point_num{};

    //qDebug() << point_num;
    if (point_num == 0)
    {
        qDebug() << "Warning! point_num == 0 !  Bug!";
        return;
    }
    if (m_recv_data != recv_data)
    {
        m_recv_data = recv_data;
    }
    if (old_point_num != point_num)
    {
        m_point_num = point_num;
        old_point_num = point_num;
        QVector<double>(point_num).swap(x_data);
        QVector<double>(point_num).swap(y_line);
    }

    if (is_first_time_to_replot)
    {
        qDebug() << "first time to replot";
        p_custom_plot->xAxis->setRange(0, point_num);
        for (int i = 0; i < point_num; ++i)
        {
            x_data[i] = i;
            y_line[i] = -200;
        }
        is_first_time_to_replot = false;
    }
    else
    {
        QVector<double> y_recv_copy(recv_data, recv_data + point_num);
        QVector<double> active_points;
        switch(m_plot_status)
        {
            case(PlotStatus::NORMAL_PLOT):
            {
                p_custom_plot->graph(0)->setData(x_data, y_recv_copy);
                p_custom_plot->graph(1)->setData(x_data, y_line);
                break;
            }
            case(PlotStatus::WITH_THRESHOLD_LEVEL):
            {
                if (ui->checkBox_task->isChecked())
                {
                    active_points.clear();
                    int count = 0, begin = 0, end = 0;
                    double tmp = 0;
                    bool begin_flag = false;
                    for (int i = 0; i < point_num; ++i)
                    {
                        y_line[i] = m_slide_value;
                        if (active_points.size() <= 30)
                        {
                            if (y_recv_copy[i] > m_slide_value && !begin_flag)
                            {
                                if (i * m_bw / m_point_num + m_freq_start - tmp > 0.05)
                                {
                                    tmp = i * m_bw / m_point_num + m_freq_start;
                                    active_points.push_back(tmp);
                                    begin_flag = true;
                                }
                            }
                            else if (y_recv_copy[i] < m_slide_value && begin_flag)
                            {
                                if (i * m_bw / m_point_num + m_freq_start - tmp > 0.05)
                                {
                                    tmp = i * m_bw / m_point_num + m_freq_start;
                                    active_points.push_back(tmp);
                                    begin_flag = false;
                                }
                            }
                        }
                    }
                    for (int i = 0; i < active_points.size() - 2; )
                    {
                        ui->textBrowser->append(QString::number(active_points[i]) + "," + QString::number(active_points[i + 1]));
                        ui->textBrowser->moveCursor(ui->textBrowser->textCursor().End);
                        i += 2;
                    }
                    if (active_points.size() > 2)
                        ui->textBrowser->insertPlainText("\n\n");
                }
                else
                {
                    for (int i = 0; i < point_num; ++i)
                    {
                        y_line[i] = m_slide_value;
                    }
                }
                p_custom_plot->graph(0)->setData(x_data, y_recv_copy);
                p_custom_plot->graph(1)->setData(x_data, y_line);
                break;
            }
            case(PlotStatus::WITH_THRESHOLD_PEAK):
            {
                QVector<double> y_slide(y_line);
                for (int i = 0; i < point_num; ++i)
                {
                    if (y_recv_copy[i] > y_line[i])
                    {
                        y_line[i] = y_recv_copy[i];
                    }
                    y_slide[i] = y_line[i] + m_slide_value;
                }
                p_custom_plot->graph(0)->setData(x_data, y_recv_copy);
                p_custom_plot->graph(1)->setData(x_data, y_slide);
                break;
            }
            case(PlotStatus::WITH_THRESHOLD_HISTORY):
            {
                QVector<double> y_slide(y_line);
                if (ui->checkBox_task->isChecked())
                {
                    active_points.clear();
                    int count = 0, begin = 0, end = 0;
                    double tmp = 0;
                    bool begin_flag = false;
                    for (int i = 0; i < point_num; ++i)
                    {
                        y_slide[i] = y_line[i] + m_slide_value;
                        if (active_points.size() <= 30)
                        {
                            if (y_recv_copy[i] > y_slide[i] && !begin_flag)
                            {
                                if (i * m_bw / m_point_num + m_freq_start - tmp > 0.05)
                                {
                                    tmp = i * m_bw / m_point_num + m_freq_start;
                                    active_points.push_back(tmp);
                                    begin_flag = true;
                                }
                            }
                            else if (y_recv_copy[i] < y_slide[i] && begin_flag)
                            {
                                if (i * m_bw / m_point_num + m_freq_start - tmp > 0.05)
                                {
                                    tmp = i * m_bw / m_point_num + m_freq_start;
                                    active_points.push_back(tmp);
                                    begin_flag = false;
                                }
                            }
                        }
                    }
                    for (int i = 0; i < active_points.size() - 2; )
                    {
                        ui->textBrowser->append(QString::number(active_points[i]) + "," + QString::number(active_points[i + 1]));
                        ui->textBrowser->moveCursor(ui->textBrowser->textCursor().End);
                        i += 2;
                    }
                    if (active_points.size() > 2)
                        ui->textBrowser->insertPlainText("\n\n");
                }
                else
                {
                    for (int i = 0; i < point_num; ++i)
                    {
                        y_slide[i] = y_line[i] + m_slide_value;
                    }
                }
                p_custom_plot->graph(0)->setData(x_data, y_recv_copy);
                p_custom_plot->graph(1)->setData(x_data, y_slide);
                break;
            }
            case(PlotStatus::WITH_THRESHOLD_AUTO):
            {
                QVector<double> y_used_for_auto(y_recv_copy.begin(), y_recv_copy.end());
                int const_step = 25, const_step_2 = 50, const_step_3 = 200;
                double tmp_value = m_slide_value;
                int diff_1 = 12, diff_2 = 5, diff_3 = 8;
                for (int i = 0; i < point_num; ++i)
                {
                    if (i < point_num - const_step)
                    {
                        if (!(i % const_step))
                        {
                            double max = *std::max_element(y_recv_copy.begin() + i, y_recv_copy.begin() + i + const_step);
                            double min = *std::min_element(y_recv_copy.begin() + i, y_recv_copy.begin() + i + const_step);
                            tmp_value = max - min > diff_1 ? min : ((max + min) / 2);
                        }
                    }
                    y_line[i] = tmp_value + m_slide_value;
                }
                for (int i = 0; i < point_num; ++i)
                {
                    if (i < point_num - const_step_2)
                    {
                        if (!(i % const_step_2))
                        {
                            double max = *std::max_element(y_line.begin() + i, y_line.begin() + i + const_step);
                            double min = *std::min_element(y_line.begin() + i, y_line.begin() + i + const_step);
                            tmp_value = max - min > diff_2 ? min : ((max + min) / 2);
                        }
                    }
                    y_used_for_auto[i] = tmp_value + m_slide_value;
                }
                for (int i = 0; i < point_num; ++i)
                {
                    if (i < point_num - const_step_3)
                    {
                        if (!(i % const_step_3))
                        {
                            double max = *std::max_element(y_used_for_auto.begin() + i, y_used_for_auto.begin() + i + const_step);
                            double min = *std::min_element(y_used_for_auto.begin() + i, y_used_for_auto.begin() + i + const_step);
                            tmp_value = max - min > diff_3 ? min : ((max + min) / 2);
                        }
                    }
                    y_line[i] = tmp_value + m_slide_value;
                }

                p_custom_plot->graph(0)->setData(x_data, y_recv_copy);
                p_custom_plot->graph(1)->setData(x_data, y_line);
                break;
            }
            default:
            {
                p_custom_plot->graph(0)->setData(x_data, y_recv_copy);
                p_custom_plot->graph(1)->setData(x_data, y_line);
                break;
            }
        }
    }
    //重绘，应用所有更改的设置
    p_custom_plot->replot();
}

// 滑块与spinbox关联
void MainWindow::on_horizontalSlider_offset_valueChanged(int slider_value)
{
    m_slide_value = slider_value;
    ui->spinBox_offset->setValue(slider_value);
}

// spinbox与滑块关联
void MainWindow::on_spinBox_offset_valueChanged(int spinbox_value)
{
    ui->horizontalSlider_offset->setValue(spinbox_value);
}

void MainWindow::on_btn_history_clicked()
{
    // 检查目录是否存在，若不存在则新建
    QString dir_str = "./history_data";
    QDir dir;
    if (!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
    }

    if (PlotStatus::WITH_THRESHOLD_PEAK == m_plot_status)
    {
        QDateTime datetime;
        QString time_str = datetime.currentDateTime().toString("yyyyMMddHHmmss");
        QString file_name = "history_data/" + time_str + ".hisdat";
        QFile file(file_name);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        out << y_line;
        file.close();
        QMessageBox msgbox_save_peak(QMessageBox::NoIcon, "SAVE FILE", QString::fromLocal8Bit("文件保存成功，保存路径为:\n") + file_name, QMessageBox::Ok);
        msgbox_save_peak.exec();
    }
    else if (PlotStatus::WITH_THRESHOLD_HISTORY == m_plot_status)
    {
        QString file_name = QFileDialog::getOpenFileName(this, tr("Choose File"), "./history_data", tr("History Data(*hisdat)"));
        if (file_name != "")
        {
            QFile file(file_name);
            file.open(QIODevice::ReadOnly);
            QDataStream in(&file);
            in >> y_line;
            file.close();
        }
    }
}

void MainWindow::plotStatusChange()
{
    for (int i = 0; i < m_point_num; ++i)
    {
        y_line[i] = -200;
    }
    if (!ui->checkBox_threshold->isChecked())
        m_plot_status = PlotStatus::NORMAL_PLOT;
    else
    {
        if (ui->radioButton_level->isChecked()) m_plot_status = PlotStatus::WITH_THRESHOLD_LEVEL;
        else if (ui->radioButton_auto->isChecked()) m_plot_status = PlotStatus::WITH_THRESHOLD_AUTO;
        else if (ui->radioButton_peak->isChecked()) m_plot_status = PlotStatus::WITH_THRESHOLD_PEAK;
        else if (ui->radioButton_history->isChecked()) m_plot_status = PlotStatus::WITH_THRESHOLD_HISTORY;
    }

    // 改变按钮显示
    if (m_plot_status == PlotStatus::WITH_THRESHOLD_PEAK)
    {
        ui->btn_history->show();
        ui->btn_history->setText(QString::fromLocal8Bit("保存为历史峰值数据文件"));
    }
    else if (m_plot_status == PlotStatus::WITH_THRESHOLD_HISTORY)
    {
        ui->btn_history->show();
        // BUG! 读取不同点数的历史峰值数据时会崩溃, 建议设置为完全相同的的参数
        ui->btn_history->setText(QString::fromLocal8Bit("读取历史峰值文件"));
    }
    else
    {
        ui->btn_history->hide();
    }
}