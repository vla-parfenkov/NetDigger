#include "sniffer.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>



CBaseSniffer* CBaseSniffer::_BaseSniff = NULL;

CBaseSniffer::CBaseSniffer(): handle(0), mask(0), net(0) {}

CBaseSniffer* CBaseSniffer::init_sniffer()
{
    if (_BaseSniff == NULL) {
        _BaseSniff = new CBaseSniffer;
    }
    return _BaseSniff;

}

CBaseSniffer::~CBaseSniffer()
{
    if (handle){
        pcap_close(handle);
    }
}

void CBaseSniffer::set_pcap_handle(pcap_t *pcap_handle)
{
    handle = pcap_handle;
}

pcap_t* CBaseSniffer::get_pcap_handle()
{
    return handle;
}

const pcap_t* CBaseSniffer::get_pcap_handle() const
{
    return handle;
}


void CBaseSniffer::sniff_loop(pcap_handler function, size_t max_packets)
{
    pcap_loop(handle, max_packets , function, NULL);

}

bool CBaseSniffer::set_filter(const QString &filter)
{
    bpf_program filter_prog;
    if ( pcap_compile(handle, &filter_prog, qPrintable(filter), 0, net) == -1) {
        return false;
    }
    size_t result = pcap_setfilter(handle, &filter_prog);
    pcap_freecode(&filter_prog);
    if (result == -1)
    {
        return false;
    } else{
        return true;
    }

}

void CBaseSniffer::set_mask(bpf_u_int32 netmask)
{
    mask = netmask;
}

void CBaseSniffer::set_net(bpf_u_int32 netip)
{
    net = netip;
}

void CBaseSniffer::stop_loop()
{
    pcap_breakloop(handle);
}

bool CBaseSniffer::found_device()
{

    char errbuf[PCAP_ERRBUF_SIZE];
    QString device(pcap_lookupdev(errbuf));
    if(device == NULL)
    {
        return false;
    } else
    {
       return set_device(device);
    }

}

const u_char *CBaseSniffer::get_packet(pcap_pkthdr *header)
{
    return pcap_next(handle,header);
}

bool CBaseSniffer::set_device(const QString &device)
{
    const char* dev = qPrintable(device);
    pcap_t *newhandler = NULL;
    char error_buffer[PCAP_ERRBUF_SIZE];
    bpf_u_int32 tempmask;
    bpf_u_int32 tempnet;

    //узнать адрес устройства
    pcap_lookupnet(dev, &tempnet, &tempmask, error_buffer);
    //открыть устройство

    newhandler = pcap_open_live( dev, BUFSIZ, true, 0, error_buffer);
    if (newhandler == NULL){
        return false;
    }
    _BaseSniff->set_pcap_handle(newhandler);
    _BaseSniff->set_net(tempnet);
    _BaseSniff->set_mask(tempmask);
    return true;

}



//---------------------------------------------------------//


//void callbackfunc(u_char *args, const pcap_pkthdr *header, const u_char *packet);

CQTSniffer::CQTSniffer()
{
    Sniff = CBaseSniffer::init_sniffer();

}

CQTSniffer::~CQTSniffer()
{
    this->requestInterruption();
    this->wait();
    delete Sniff;
}

void CQTSniffer::safe_packets(CPacket* packet)
{
    QFile fout("out.txt");
    fout.open(QIODevice::Append);
    QTextStream writeStream(&fout);
    writeStream << "len: " << packet->size() << endl;
    writeStream << "dmas: " << packet->get_dest_mac()<< endl;
    writeStream << "smas: " <<packet->get_source_mac()<< endl;
    writeStream << "e_type: " << hex << packet->get_e_type() << endl;
    writeStream << "sip: " << packet->get_source_ip() << endl;
    writeStream << "dip: " << packet->get_dest_ip() << endl;
    writeStream << "id_protocol: " <<dec <<packet->get_protocol() << endl;
    writeStream << "sport: " << packet->get_source_port() << endl;
    writeStream << "dport: " << packet->get_dest_port() << endl;
    for (size_t i = 0; i < packet->size(); ++i )
    {
        if(i % 8 == 0)
        {
            writeStream << endl;
        }
        //вывод побитово
      for (qint8 j = (sizeof(packet->get_packet()[i]) * CHAR_BIT) - 1; j >=0; --j)
      {
        writeStream << ((packet->get_packet()[i] >> j) & 1) ;
      }
    }
    writeStream << endl;
    fout.close();
    return;
}

void CQTSniffer::start_sniff()
{
   this->start();

}

void CQTSniffer::stop_sniff()
{
    this->requestInterruption();
}

void CQTSniffer::set_filter(QString filter)
{
    Sniff->set_filter(filter);
}

void CQTSniffer::safe_in_file(bool safe)
{
    safeinfile = safe;
}

void CQTSniffer::find_device()
{
    emit device_ready(Sniff->found_device());
}

void CQTSniffer::set_ready_graph(bool flag)
{
    safeingraph = flag;
}

void CQTSniffer::set_ready_log(bool flag)
{
    safeinlog = flag;
}

void CQTSniffer::run()
{

    forever{ 
        QString packet_data;
        pcap_pkthdr packet_header;
        const u_char* packet_body = Sniff->get_packet(&packet_header);
        CPacket *Packet = new CEthernetFrame(packet_body, packet_header.len);
        CVisitor *Visitor = new CPacketVisitor();
        Packet = Packet->parse_frame(Visitor);

        // строка для записи в list
        packet_data += Packet->get_source_ip() + " > " + Packet->get_dest_ip();
        packet_data += " protocol num: " + QString::number(Packet->get_protocol());
        packet_data += " Lenght packet: " + QString::number(Packet->size()) + "\n";

        if (safeinfile == true)
        {
            safe_packets(Packet);
        }
        if( safeingraph == true){
            quint64 time_ms = (packet_header.ts.tv_sec * (quint64)1000) + (packet_header.ts.tv_usec / 1000);
            emit set_graph_data(Packet->get_protocol(), Packet->size(), time_ms);
        }
        if  (safeinlog == true)
        {
            //вызов сигнала записи в list
            emit packet_ready(packet_data);
        }

        delete Packet;
        delete Visitor;
        if(isInterruptionRequested()){
            return;
    }
    }
}




/*void callbackfunc(u_char *args, const  pcap_pkthdr *packet_header, const u_char *packet_body)
{

    QFile fout("out.txt");
    CTCPPacket packet(packet_body);
    fout.open(QIODevice::Append);
    QTextStream writeStream(&fout);
    writeStream << packet_header->caplen << "\n";
    writeStream << packet_header->len << "\n";
    writeStream << packet.get_dest_mac()<< "\n";
    writeStream << packet.get_source_mac()<< "\n";
    writeStream << hex << packet.get_e_type() << "\n";
    writeStream << packet.get_source_ip() << "\n";
    writeStream << packet.get_dest_ip() << "\n";
    writeStream << dec <<packet.get_protocol() << "\n";
    writeStream << packet.get_source_port() << "\n";
    writeStream << packet.get_dest_port() << "\n";
    for (size_t i = 0; i < packet.get_packet_size(); ++i )
    {
       // writeStream << packet.get_packet().toHex();
    }
    writeStream << "\n";
    fout.close();
    return;
}*/
//--------------------------------------------------------------------------//

