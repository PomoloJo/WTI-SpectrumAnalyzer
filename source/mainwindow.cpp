#include "./include/mainwindow.h"
#include "./include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->initMember();
}

MainWindow::~MainWindow()
{
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

    QCustomPlot* p_custom_plot =ui->widget_plot;

    //清除所有graph
    p_custom_plot->clearGraphs();

    //添加一条曲线
    QCPGraph* pgraph = p_custom_plot->addGraph();

    //给曲线准备数据 设置数据 
    QVector<double> x(100000);
    QVector<double> y(100000);

    for (int i = 0; i < x.size(); i++)
    {
        x[i] = i;
        y[i] = rand();
    }

    //设置数据
    p_custom_plot->graph(0)->setData(x, y);
    //设置X轴范围
    p_custom_plot->xAxis->setRange(0, x.size());
    //设置Y轴范围
    p_custom_plot->yAxis->setRange(-30, 30);
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


    _p_my_thread = new CWorkThread(this, 1);
    _p_my_thread->start();

}


