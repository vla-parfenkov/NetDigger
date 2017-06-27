#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSniff = new CQTSniffer();
    timer = new QTimer;
    ui->StartSniff->setEnabled(false);
    counter_log = 0;

    connect(ui->StartSniff,SIGNAL(clicked()),this,SLOT(on_StartSniff_clicked()));
    connect(this, SIGNAL(run_sniff()),QSniff,SLOT(start_sniff()));
    connect(ui->StopSniff, SIGNAL(clicked()),QSniff, SLOT(stop_sniff()));
    connect(ui->StopSniff,SIGNAL(clicked()),timer,SLOT(stop()));
    connect(QSniff,SIGNAL(packet_ready(QString)),this,SLOT(add_String_to_Listen(QString)));
    connect(this,SIGNAL(set_filter(QString)),QSniff,SLOT(set_filter(QString)));
    connect(ui->SafeInFile, SIGNAL(clicked(bool)), QSniff, SLOT(safe_in_file(bool)));
    connect(QSniff, SIGNAL(set_graph_data(quint8, quint32, quint64)),this,SLOT(add_graph_data(quint8, quint32, quint64)));
    connect(timer,SIGNAL(timeout()),this,SLOT(graph_replot()));
    connect(ui->FindDevice,SIGNAL(clicked()), QSniff, SLOT(find_device()));
    connect(QSniff, SIGNAL(device_ready(bool)), this, SLOT(device_ready(bool)));
    connect(this, SIGNAL(graph_ready(bool)), QSniff, SLOT(set_ready_graph(bool)));
    connect(this, SIGNAL(log_ready(bool)), QSniff, SLOT(set_ready_log(bool)));

    emit log_ready(true);

    set_graphplot_setting();

     emit graph_ready(true);

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

/*void MainWindow::data_graph_overwriting()
{
   Graph_Data.remove(0, MAX_COUNT_PACKET_IN_GRAPH / 2);
   ui->qplot->graph(0)->data().clear();
   ui->qplot->graph(1)->data().clear();
   ui->qplot->graph(2)->data().clear();

   for(size_t i = 0; i < Graph_Data.size(); ++i)
   {
      ui->qplot->graph(Graph_Data.at(i).graph_number)->addData(Graph_Data.at(i).time,Graph_Data.at(i).size);
   }
}*/


void MainWindow::on_StartSniff_clicked()
{
    emit run_sniff();
    timer->start(500); //500 ms

}

void MainWindow::add_String_to_Listen(QString new_string)
{
    if(counter_log >= MAX_COUNT_PACKET_IN_LOG / 2)
    {
        Log_Date += new_string;
    }
    if(counter_log >= MAX_COUNT_PACKET_IN_LOG){
        //emit log_ready(false);
        ui->logtrace->clear();
        ui->logtrace->append(Log_Date);
        Log_Date.clear();
        counter_log = MAX_COUNT_PACKET_IN_LOG / 2;
        //emit log_ready(true);
    } else {
        ui->logtrace->append(new_string);
    }
}

void MainWindow::graph_replot()
{

    ui->qplot->rescaleAxes();      // Масштабируем график по данным
    ui->qplot->replot();
}

void MainWindow::add_graph_data(quint8 protocol, quint32 size, quint64 time)
{
    CGraphData graph_data;
    time -= Time_zero_plot;
   /*if(Graph_Data.size() >= MAX_COUNT_PACKET_IN_GRAPH)
    {
       emit graph_ready(false);
        data_graph_overwriting();
        emit graph_ready(true);
    }*/
     graph_data.time = time;
     graph_data.size = size;

    switch (protocol) {
    case ID_TCP:
    {
        graph_data.graph_number = 0;
        break;
    }
    case ID_UDP:
    {
        graph_data.graph_number = 1;
        break;
    }
    default:
    {
        graph_data.graph_number = 2;
        break;
    }
    }

    ui->qplot->graph(graph_data.graph_number)->addData(graph_data.time,graph_data.size);
   //Graph_Data.append(graph_data);
}

void MainWindow::device_ready(bool flag)
{
    if ( flag == true)
    {
        ui->indDevice->setStyleSheet("background-color: rgb(0, 255, 0)");
        ui->StartSniff->setEnabled(true);

    } else {
        ui->indDevice->setStyleSheet("background-color: rgb(255, 0, 0)");
        ui->StartSniff->setEnabled(false);
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
        emit set_filter("icmp");
    }
}
