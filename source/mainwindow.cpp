#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();

    //ȥ��ϵͳ���ı�����
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //��װ�¼���������this���title_widgetʵ�������ק������
    ui->title_widget->installEventFilter(this);
    // ��װ�¼���������this���widget_plot���¼�
    ui->widget_plot->installEventFilter(this);
    ui->widget_plot->setMouseTracking(true);

    //���Ͻǰ�ť�¼�����
    ui->btn_close->installEventFilter(this);

    // �����̣߳��ڶ���������ʱ������Ĭ��ֵ0ms
    m_p_work_thread = new CWorkThread(this);

    // ���״̬��
    m_mouse_coordinate = new QLabel("realtime mouse coordinate", this);
    //addWidget�Ǵ����������, addPermanentWidget�Ǵ����������
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


    ui->widget_plot->setBackground(QColor(8, 8, 8));
    ui->widget_plot->xAxis->grid()->setPen(QPen(QColor(32, 32, 32), 1, Qt::PenStyle::DashLine));//������
    ui->widget_plot->yAxis->grid()->setPen(QPen(QColor(32, 32, 32), 1, Qt::PenStyle::DashLine));//������
    ui->widget_plot->xAxis->grid()->setSubGridPen(QPen(QColor(25, 25, 25), 1, Qt::DotLine));//��������
    ui->widget_plot->yAxis->grid()->setSubGridPen(QPen(QColor(25, 25, 25), 1, Qt::DotLine));//��������
    ui->widget_plot->xAxis->grid()->setSubGridVisible(true);//��ʾx����������
    ui->widget_plot->yAxis->grid()->setSubGridVisible(true);//��ʾy����������
}

void MainWindow::initMember()
{
    qDebug() << "init";
}

// ��д�¼�������
bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
    // Ŀǰ��Ҫ����д����¼�
    static float pos_x;
    static float pos_y;
    static bool mouse_left_btn_pressed = false;
    static bool mouse_right_btn_pressed = false;
    static QPoint mousePoint;
    QMouseEvent* mouse_event = (QMouseEvent*)event;

    // ��Ŀ�������Ͻ�button
    // ���ﲻҪ return true��ֱ�� break �ͺã���Ϊ����¼��ص������Ǻ��������Ĳ�������ر��¼�Ҳ�ֶ�д��
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
                if (mouse_event->buttons() == Qt::LeftButton) {
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
                if (mouse_left_btn_pressed && (mouse_event->buttons() && Qt::LeftButton)) {
                    this->move(mouse_event->globalPos() - mousePoint);
                    return true;
                }
            }
            default:
                break;
        }
    }

    // ��Ŀ���ǻ�ͼ��ͼ����ʱʵ�����ţ���ʾ���������¼�
    if (ui->widget_plot == target)
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
            m_mouse_coordinate->setText(QString("%1,   %2 dBm").arg(pos_x).arg(pos_y));
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
        cmdline_str.sprintf("device_driver\\bb60c\\fake_data.exe");
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
        pgraph->setPen(QPen(QColor(16, 255, 32)));

        //����X�᷶Χ
        //p_custom_plot->xAxis->setRange(0, 10000);
        //����Y�᷶Χ
        p_custom_plot->yAxis->setRange(-100, 0);
        //���ô�С
        p_custom_plot->resize(ui->widget_plot->width(), ui->widget_plot->height());
        //���Խ������λ�÷Ŵ���С����ק ���Ŵ���С����ϵ
        p_custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        //p_custom_plot->axisRect()->setRangeDrag(Qt::Vertical);// Qt::Horizontal

        //�ػ棬Ӧ�����и��ĵ�����
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
    //Sleep(1000);
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



