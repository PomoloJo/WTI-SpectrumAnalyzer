#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();

    // ȥ��ϵͳ���ı�����
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // ��װ�¼���������this���title_widgetʵ�������ק������
    ui->title_widget->installEventFilter(this);
    // ��װ�¼���������this���widget_plot���¼�
    ui->widget_plot->installEventFilter(this);
    ui->widget_plot->setMouseTracking(true);

    // ���Ͻǰ�ť�¼�����
    ui->btn_close->installEventFilter(this);

    // �����̣߳��ڶ���������ʱ������Ĭ��ֵ0ms
    m_p_work_thread = new CWorkThread(this);

    // ���״̬��
    m_mouse_coordinate = new QLabel("realtime mouse coordinate", this);
    // addWidget�Ǵ����������, addPermanentWidget�Ǵ����������
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
     
    //ui->btn_close->setIcon(QIcon(":/icons/close.png")); // ��д����vs���ƺ��޷���Ч
    ui->btn_close->setIcon(QIcon("./resource/icons/close4.png"));

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

        // �������graph
        p_custom_plot->clearGraphs();

        // ���һ������
        QCPGraph* pgraph = p_custom_plot->addGraph();
        // line color:green
        // pgraph->setPen(QPen(QColor(16, 255, 32)));
        // change line color
        QLinearGradient gradient(0, 100, 0, 500);
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
        std::string device_exe = std::string("TASKKILL /F /IM fake_data.exe");  // + exe_name;
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
        //�ػ棬Ӧ�����и��ĵ�����
        p_custom_plot->replot();
    }
}