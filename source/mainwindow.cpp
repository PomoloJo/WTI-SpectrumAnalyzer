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

    m_p_work_thread = new CWorkThread(this, 1);
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
    }
    return QObject::eventFilter(target, event);
}


void MainWindow::on_btn_start_clicked()
{
    qDebug() << "btn_start clicked ";

    QString btn_start_text(ui->btn_start->text());
    if (btn_start_text.contains("start", Qt::CaseInsensitive))
    {
        QCustomPlot* p_custom_plot = ui->widget_plot;

        // �������graph
        p_custom_plot->clearGraphs();

        // ���һ������
        QCPGraph* pgraph = p_custom_plot->addGraph();

        //����X�᷶Χ
        p_custom_plot->xAxis->setRange(0, 10000);
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

        //�ػ棬Ӧ�����и��ĵ�����
        p_custom_plot->replot();

        m_p_work_thread->start();
        ui->btn_start->setText("      STOP      ");
    }
    else
    {
        m_p_work_thread->stopRunning();
        ui->btn_start->setText("      START      ");
        is_first_time_to_replot = true;
    }


}

void MainWindow::timeToReplot(const double* recv_data, const int point_num)
{
    QCustomPlot* p_custom_plot = ui->widget_plot;
    static QVector<double> x(point_num);

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
        qDebug() << "run replot";
        QVector<double> y(recv_data, recv_data + point_num);
        p_custom_plot->graph(0)->setData(x, y);
        //�ػ棬Ӧ�����и��ĵ�����
        p_custom_plot->replot();
    }
}



