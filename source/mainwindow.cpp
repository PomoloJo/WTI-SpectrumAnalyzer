#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();

    // ��װ�¼���������this���widget_plot���¼�
    ui->widget_plot->installEventFilter(this);
    ui->widget_plot->setMouseTracking(true);

    m_p_work_thread = new CWorkThread(this, 200);

    // ���״̬��
    m_status_bar = statusBar();//����״̬��
    m_mouse_coordinate = new QLabel("realtime mouse coordinate", this);
    //addWidget�Ǵ����������, addPermanentWidget�Ǵ����������
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

// ��д�¼������������ڹ�������¼�
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

        // �������graph
        p_custom_plot->clearGraphs();

        // ���һ������
        QCPGraph* pgraph = p_custom_plot->addGraph();

        //����X�᷶Χ
        //p_custom_plot->xAxis->setRange(0, 10000);
        //����Y�᷶Χ
        p_custom_plot->yAxis->setRange(-100, 0);
        //x������
        p_custom_plot->xAxis->setLabel("X");
        //Y������
        p_custom_plot->yAxis->setLabel("Y");
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
        // ǿ���˳�
        std::string device_exe = std::string("TASKKILL /F /IM bb60c.exe");  // + exe_name;
        WinExec(device_exe.c_str(), SW_HIDE);

        m_p_work_thread->stopRunning();
        ui->btn_start->setText("      START      ");
    }
    // ֻҪ�����ť����ˢ���ػ�
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
        //�ػ棬Ӧ�����и��ĵ�����
        p_custom_plot->replot();
    }
}



