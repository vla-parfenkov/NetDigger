#ifndef SNIFFER_H
#define SNIFFER_H

#include <pcap.h>
#include <QObject>
#include <QString>
#include <QThread>
#include <QVector>
#include "netpacket.h"



/* Объект данного класса занимается прослушкой сетевого устройства*/
//use singleton
class CBaseSniffer  {
public:

    static CBaseSniffer* init_sniffer ();
    ~CBaseSniffer();
    pcap_t * get_pcap_handle ();
    const pcap_t * get_pcap_handle () const;
    bool set_filter (const QString &filter);
    void set_device (const QString &device);
    void sniff_loop (pcap_handler function, size_t max_packets);
    void stop_loop ();
    void found_device();
    const u_char* get_packet(pcap_pkthdr* header);

protected:

    CBaseSniffer();
    void set_pcap_handle (pcap_t *pcap_handle);
    void set_net (bpf_u_int32 netip);
    void set_mask (bpf_u_int32 netmask);


private:

    static CBaseSniffer* _BaseSniff;
    pcap_t *handle;
    const u_char* packet_data;
    bpf_u_int32 mask;
    bpf_u_int32 net;




};

//---------------------------------------------------------//
//Start sniffing thread
class CQTSniffer : public QThread
{
    Q_OBJECT
public:
    CQTSniffer();
    ~CQTSniffer();
    //onFile
    void safe_packets(CPacket* packet);
private:
    CBaseSniffer *Sniff;
    bool safeinfile = false;

public slots:
    void start_sniff();
    void stop_sniff();
    void set_filter(QString filter);
    void safe_in_file(bool safe);
signals:
    void stop_loop();
    void packet_ready(QString packet_data);
    void set_graph_data(quint8 protocol, quint32 size, quint64 time);

    // QThread interface
protected:
    void run();
};

//----------------------------------------------------------//

/*class CDataGraph : public QObject
{
    Q_OBJECT
public:
private:

};*/

#endif // SNIFFER_H
