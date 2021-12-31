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

// 重写事件过滤器，用于过滤鼠标事件
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

        // 清除所有graph
        p_custom_plot->clearGraphs();

        // 添加一条曲线
        QCPGraph* pgraph = p_custom_plot->addGraph();

        //设置X轴范围
        p_custom_plot->xAxis->setRange(0, 10000);
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

        //重绘，应用所有更改的设置
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
        //重绘，应用所有更改的设置
        p_custom_plot->replot();
    }
}



