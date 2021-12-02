#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();

    _p_work_thread = new CWorkThread(this, 1);
    connect(_p_work_thread, &CWorkThread::sendData, this, &MainWindow::timeToReplot);
}

MainWindow::~MainWindow()
{
    delete _p_work_thread;
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


void MainWindow::on_btn_start_clicked()
{
    qDebug() << "btn_start clicked ";

    QString btn_start_text(ui->btn_start->text());
    if (btn_start_text.contains("start", Qt::CaseInsensitive))
    {
        QCustomPlot* p_custom_plot = ui->widget_plot;

        //�������graph
        p_custom_plot->clearGraphs();

        //���һ������
        QCPGraph* pgraph = p_custom_plot->addGraph();

        //������׼������ �������� 
        QVector<double> x(10000);
        QVector<double> y(10000);

        for (int i = 0; i < x.size(); i++)
        {
            x[i] = i;
            y[i] = rand();
        }

        //��������
        p_custom_plot->graph(0)->setData(x, y);
        //����X�᷶Χ
        p_custom_plot->xAxis->setRange(0, x.size());
        //����Y�᷶Χ
        p_custom_plot->yAxis->setRange(-30, 30);
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

        _p_work_thread->start();
        ui->btn_start->setText("      STOP      ");
    }
    else
    {
        _p_work_thread->stopRunning();
        ui->btn_start->setText("      START      ");
    }


}

void MainWindow::timeToReplot(double* recv_data)
{
    qDebug() << "run replot";

    QCustomPlot* p_custom_plot = ui->widget_plot;
    //�������graph
    p_custom_plot->clearGraphs();
    //���һ������
    QCPGraph* pgraph = p_custom_plot->addGraph();
    QVector<double> x(10000);
    for (int i = 0; i < x.size(); i++)
    {
        x[i] = i;
    }
    QVector<double> y(recv_data, recv_data + 10000);
    p_custom_plot->graph(0)->setData(x, y);
    //�ػ棬Ӧ�����и��ĵ�����
    p_custom_plot->replot();
}



