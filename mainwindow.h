#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sniffer.h"
#include "qcustomplot.h"
#include <QTimer>



namespace Ui {
class MainWindow;
}

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



public slots:
    void on_StartSniff_clicked();
    void add_String_to_Listen(QString new_string);
    void graph_replot();
    void add_graph_data(quint8 protocol, quint32 size, quint64 time);
signals:
    void run_sniff();
    void set_filter(QString filter);
private slots:
    void on_buttonAll_clicked();
    void on_buttonTCP_clicked();
    void on_buttonUDP_clicked();
    void on_buttonIGMP_clicked();

};

#endif // MAINWINDOW_H
