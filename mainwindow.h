#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sniffer.h"
#include "qcustomplot.h"
#include <QTimer>

#define MAX_COUNT_PACKET_IN_LOG 128
#define MAX_COUNT_PACKET_IN_GRAPH 128
#define COUNT_GRAPH 3

namespace Ui {
class MainWindow;
}

struct CGraphData
{
    quint8 graph_number;
    quint32 size;
    quint64 time;

    CGraphData():graph_number(COUNT_GRAPH - 1),size(0),time(0){}
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    CQTSniffer *QSniff;
    void set_graphplot_setting(); //настройка графического полотна
    QTimer* timer;
    quint64 Time_zero_plot; //время запуска программы
    //QVector<CGraphData> Graph_Data;
    QString Log_Date;
    quint16 counter_log;
    void data_graph_overwriting();
    void data_log_overwriting();



public slots:
    void on_StartSniff_clicked();
    void add_String_to_Listen(QString new_string);
    void graph_replot();
    void add_graph_data(quint8 protocol, quint32 size, quint64 time);
    void device_ready(bool flag);
signals:
    void run_sniff();
    void set_filter(QString filter);
    void graph_ready(bool flag);
    void log_ready(bool flag);
private slots:
    void on_buttonAll_clicked();
    void on_buttonTCP_clicked();
    void on_buttonUDP_clicked();
    void on_buttonIGMP_clicked();

};

#endif // MAINWINDOW_H
