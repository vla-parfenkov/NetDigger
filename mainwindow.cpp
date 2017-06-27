#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSniff = new CQTSniffer();
    timer = new QTimer;

    connect(ui->StartSniff,SIGNAL(clicked()),this,SLOT(on_StartSniff_clicked()));
    connect(this, SIGNAL(run_sniff()),QSniff,SLOT(start_sniff()));
    connect(ui->StopSniff, SIGNAL(clicked()),QSniff, SLOT(stop_sniff()));
    connect(ui->StopSniff,SIGNAL(clicked()),timer,SLOT(stop()));
    connect(QSniff,SIGNAL(packet_ready(QString)),this,SLOT(add_String_to_Listen(QString)));
    connect(this,SIGNAL(set_filter(QString)),QSniff,SLOT(set_filter(QString)));
    connect(ui->SafeInFile, SIGNAL(clicked(bool)), QSniff, SLOT(safe_in_file(bool)));
    connect(QSniff, SIGNAL(set_graph_data(quint8,quint32,quint64)),this,SLOT(add_graph_data(quint8,quint32,quint64)));
    connect(timer,SIGNAL(timeout()),this,SLOT(graph_replot()));

    set_graphplot_setting();
    Time_zero_plot = QDateTime::currentDateTime().toTime_t() * (quint64)1000;//to ms

}

MainWindow::~MainWindow()
{
    delete ui;
    delete QSniff;
    delete timer;
}



void MainWindow::set_graphplot_setting()
{
    ui->qplot->setInteraction(QCP::iRangeZoom, true);
    ui->qplot->setInteraction(QCP::iRangeDrag, true);
    ui->qplot->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->qplot->axisRect()->setRangeDrag(Qt::Horizontal);
    //ui->qplot->xAxis->setTickLabel(QCPAxis::ltDateTime);   // Подпись координат по Оси X в качестве Даты и Времени
    //ui->qplot->xAxis->setDateTimeFormat("hh:mm");

    // Настраиваем шрифт по осям координат
    ui->qplot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    ui->qplot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Автоматическое масштабирование тиков по Оси X
    //ui->qplot->xAxis->setAutoTickStep(true);

    /* Делаем видимыми оси X и Y по верхней и правой границам графика,
     * но отключаем на них тики и подписи координат
     * */
    ui->qplot->xAxis2->setVisible(true);
    ui->qplot->yAxis2->setVisible(true);
    ui->qplot->xAxis2->setTicks(false);
    ui->qplot->yAxis2->setTicks(false);
    ui->qplot->xAxis2->setTickLabels(false);
    ui->qplot->yAxis2->setTickLabels(false);

    ui->qplot->legend->setVisible(true);   //Включаем Легенду графика
    // Устанавливаем Легенду в левый верхний угол графика
    ui->qplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->qplot->addGraph();
    ui->qplot->graph(0)->setName("tcp");
    ui->qplot->graph(0)->setPen(QPen(QColor(Qt::red)));
    ui->qplot->graph(0)->setAntialiased(false);
    ui->qplot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
    ui->qplot->addGraph();
    ui->qplot->graph(1)->setName("udp");
    ui->qplot->graph(1)->setPen(QPen(QColor(Qt::blue)));
    ui->qplot->graph(1)->setAntialiased(false);
    ui->qplot->graph(1)->setLineStyle(QCPGraph::lsImpulse);
    ui->qplot->addGraph();
    ui->qplot->graph(2)->setName("other");
    ui->qplot->graph(2)->setPen(QPen(QColor(Qt::green)));
    ui->qplot->graph(2)->setAntialiased(false);
    ui->qplot->graph(2)->setLineStyle(QCPGraph::lsImpulse);
}


void MainWindow::on_StartSniff_clicked()
{
    emit run_sniff();
    timer->start(500); //500 ms

}

void MainWindow::add_String_to_Listen(QString new_string)
{
    ui->listWidget->addItem(new_string);
}

void MainWindow::graph_replot()
{

    ui->qplot->rescaleAxes();      // Масштабируем график по данным
    ui->qplot->replot();
}

void MainWindow::add_graph_data(quint8 protocol, quint32 size, quint64 time)
{
    time -= Time_zero_plot;
    switch (protocol) {
    case ID_TCP:
    {
        ui->qplot->graph(0)->addData(time,size);
        break;
    }
    case ID_UDP:
    {
        ui->qplot->graph(1)->addData(time,size);
        break;
    }
    default:
    {
        ui->qplot->graph(2)->addData(time,size);
        break;
    }
    }
}

void MainWindow::on_buttonAll_clicked()
{
    if(ui->buttonAll->isChecked())
    {
        emit set_filter("");
    }
}

void MainWindow::on_buttonTCP_clicked()
{
    if(ui->buttonTCP->isChecked())
    {
        emit set_filter("tcp");
    }
}

void MainWindow::on_buttonUDP_clicked()
{
    if(ui->buttonUDP->isChecked())
    {
        emit set_filter("udp");
    }
}

void MainWindow::on_buttonIGMP_clicked()
{
    if(ui->buttonIGMP->isChecked())
    {
        emit set_filter("igmp");
    }
}
