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

    // ȥ��ϵͳ���ı�����
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // ��װ�¼���������this���title_widgetʵ�������ק������
    ui->title_widget->installEventFilter(this);
    // ��װ�¼���������this���widget_plot���¼�
    ui->widget_plot->installEventFilter(this);
    ui->widget_plot->setMouseTracking(true);

    // ���Ͻǰ�ť�¼�����
    ui->btn_close->installEventFilter(this);
    ui->btn_max->installEventFilter(this);
    ui->btn_min->installEventFilter(this);

    // �����̣߳��ڶ���������ʱ������Ĭ��ֵ0ms
    m_p_work_thread = new CWorkThread(this, 500);

    // ���״̬��
    m_mouse_coordinate = new QLabel("realtime mouse coordinate", this);
    // addWidget�Ǵ����������, addPermanentWidget�Ǵ����������
    //ui->statusbar->addWidget(new QLabel("1", this));
    ui->statusbar->addPermanentWidget(m_mouse_coordinate);

    connect(m_p_work_thread, &CWorkThread::sendData, this, &MainWindow::timeToReplot);

    // ���һ��������Ϊʵ����������
    QCPGraph* pgraph = ui->widget_plot->addGraph();
    // ��ӵڶ���������Ϊ��ֵ����
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
     
    //ui->btn_close->setIcon(QIcon(":/icons/close.png")); // ��д����vs���ƺ��޷���Ч
    ui->btn_close->setIcon(QIcon("./resource/icons/close1.png"));
    ui->btn_max->setIcon(QIcon("./resource/icons/max1.png"));
    ui->btn_min->setIcon(QIcon("./resource/icons/min1.png"));

    // dark theme
    ui->widget_plot->setBackground(QColor(8, 8, 8));
    ui->widget_plot->xAxis->grid()->setPen(QPen(QColor(32, 32, 32), 1, Qt::PenStyle::DashLine));//������
    ui->widget_plot->yAxis->grid()->setPen(QPen(QColor(32, 32, 32), 1, Qt::PenStyle::DashLine));//������
    ui->widget_plot->xAxis->grid()->setSubGridPen(QPen(QColor(25, 25, 25), 1, Qt::DotLine));//��������
    ui->widget_plot->yAxis->grid()->setSubGridPen(QPen(QColor(25, 25, 25), 1, Qt::DotLine));//��������
    ui->widget_plot->xAxis->grid()->setSubGridVisible(true);//��ʾx����������
    ui->widget_plot->yAxis->grid()->setSubGridVisible(true);//��ʾy����������

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

// ��д�¼�������
bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
    // Ŀǰ��Ҫ����д����¼�
    // ����ʵʱ��ʾxyֵ
    static float pos_x;
    static float pos_y;
    // ��¼�����״̬
    static bool mouse_left_btn_pressed = false;
    static bool mouse_right_btn_pressed = false;
    // ��¼�������
    static QPoint mousePoint;
    // plot�õ�ƫ����
    static QPoint single_plot_delta{};
    static QPoint total_plot_delta{};
    // total_plot_delta ��ֵ�� release ֮ǰ��Ҫ���ֲ��䣬������Ҫһ�����Ա����ʼλ��
    static int x_start_pos{};
    static int y_start_pos{};
    // ���ڼ�¼���������ŵ���ʾ�����С
    static int plot_x_range;
    static int plot_y_range;

    QMouseEvent* mouse_event = (QMouseEvent*)event;

    // ��Ŀ�������Ͻ�button
    // ���ﲻҪ return��ֱ�� break��  return ����¼��ص������Ǻ��������Ĳ�������ر��¼�Ҳ�ֶ�д��
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

    // ��Ŀ���Ǳ�����ʱʵ����ק
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

    // ��Ŀ���ǻ�ͼ��ͼ����ʱʵ�����ţ���ʾ�����
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
                // ��ʾ��Χ����
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
                    // ��ק�������ɵ���1000�Ǿ���ֵ
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
                    // ���ű������ɵ���1000�Ǿ���ֵ
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
        
        // Ӧ���豸ѡ��������ⲿ�ָ���Ϊ�����ļ�����
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

        // �������graph
        p_custom_plot->clearGraphs();
        // �ڳ�ʼ����ʱ���Ѿ���ӣ�����Ϊ��һ���������������ߣ������������
        // ���һ��������Ϊʵ����������
        QCPGraph* pgraph = p_custom_plot->addGraph();
        // ��ӵڶ���������Ϊ��ֵ����
        QCPGraph* threshold_graph = p_custom_plot->addGraph();
        // ��ֵ������ɫ�͸�ʽ
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

        // ����Y�᷶Χ
        p_custom_plot->yAxis->setRange(-100, 0);
        // ���ô�С
        p_custom_plot->resize(ui->widget_plot->width(), ui->widget_plot->height());
        // ���Խ������λ�÷Ŵ���С����ק ���Ŵ���С����ϵ
        //p_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        //p_custom_plot->axisRect()->setRangeDrag(Qt::Vertical);// Qt::Horizontal

        // �ػ棬Ӧ�����и��ĵ�����
        p_custom_plot->replot();

        m_p_work_thread->start();
        ui->btn_start->setText("      STOP      ");
    }
    else
    {
        // ����exeǿ���˳�
        // ������Ӧд�þ������ӻ���ͨ�������ʽת��һ�£�������ɱ����ͬ������������
        //std::string device_exe = std::string("TASKKILL /F /IM fake_data.exe");  // + exe_name;
        std::string device_exe = std::string("TASKKILL /F /IM bb60c.exe");
        WinExec(device_exe.c_str(), SW_HIDE);
        // ��������
        m_p_work_thread->stopRunning();        
        ui->btn_start->setText("      START      ");
    }
    // ֻҪ�����ť����ˢ���ػ�
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

// ������ͼ�仯�ĺ��ĺ���, graph(0)�������ߣ�graph(1)��ֵ����
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
    //�ػ棬Ӧ�����и��ĵ�����
    p_custom_plot->replot();
}

// ������spinbox����
void MainWindow::on_horizontalSlider_offset_valueChanged(int slider_value)
{
    m_slide_value = slider_value;
    ui->spinBox_offset->setValue(slider_value);
}

// spinbox�뻬�����
void MainWindow::on_spinBox_offset_valueChanged(int spinbox_value)
{
    ui->horizontalSlider_offset->setValue(spinbox_value);
}

void MainWindow::on_btn_history_clicked()
{
    // ���Ŀ¼�Ƿ���ڣ������������½�
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
        QMessageBox msgbox_save_peak(QMessageBox::NoIcon, "SAVE FILE", QString::fromLocal8Bit("�ļ�����ɹ�������·��Ϊ:\n") + file_name, QMessageBox::Ok);
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

    // �ı䰴ť��ʾ
    if (m_plot_status == PlotStatus::WITH_THRESHOLD_PEAK)
    {
        ui->btn_history->show();
        ui->btn_history->setText(QString::fromLocal8Bit("����Ϊ��ʷ��ֵ�����ļ�"));
    }
    else if (m_plot_status == PlotStatus::WITH_THRESHOLD_HISTORY)
    {
        ui->btn_history->show();
        // BUG! ��ȡ��ͬ��������ʷ��ֵ����ʱ�����, ��������Ϊ��ȫ��ͬ�ĵĲ���
        ui->btn_history->setText(QString::fromLocal8Bit("��ȡ��ʷ��ֵ�ļ�"));
    }
    else
    {
        ui->btn_history->hide();
    }
}