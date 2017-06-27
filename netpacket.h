#ifndef NETPACKET_H
#define NETPACKET_H

#include <QApplication>
#include <QString>


#define SIZE_IPv4 4
#define SIZE_IPv6 8
#define IPv4_E_TYPE 0x0800
#define IPv6_E_Type 0x86DD
#define ID_TCP 6
#define ID_UDP 17

class CPacket;
class CEthernetFrame;
class CIPPacket;
class CTCPPacket;
class CUDPPacket;

//pattern visitor
class CVisitor : public QObject
{
    Q_OBJECT
public:
    virtual CPacket* visit(CEthernetFrame* eth_frame) {}
    virtual CPacket* visit(CIPPacket* ip_pck) {}
    virtual CPacket* visit(CTCPPacket* tcp_pck) {}
    virtual CPacket* visit(CUDPPacket* udp_pck) {}
};

class CPacketVisitor : public CVisitor
{

public:
    CPacket* visit(CEthernetFrame* eth_frame);
    CPacket* visit(CIPPacket* ip_pck);
    CPacket* visit(CTCPPacket* tcp_pck);
    CPacket* visit(CUDPPacket* udp_pck);
};

//packet interface
class CPacket : public  QObject
{
    Q_OBJECT
public:
    virtual QString get_dest_mac() {return "";}
    virtual QString get_source_mac() {return "";}
    virtual quint16 get_e_type() { return 0;}
    virtual const u_char* get_packet() {return NULL;}
    virtual size_t size() { return 0;}
    virtual QString get_source_ip() { return "";}
    virtual QString get_dest_ip() {return "";}
    virtual quint8 get_protocol() {return 0;}
    virtual quint8 get_version() {return 0;}
    virtual quint8 get_lenght() {return 0;}
    virtual quint16 get_source_port() {return 0;}
    virtual quint16 get_dest_port() {return 0;}
    virtual CPacket* parse_frame(CVisitor* visitor) {return NULL;}
};


class CEthernetFrame : public CPacket
{
public:

    CEthernetFrame();
    explicit CEthernetFrame(const u_char* payload_in, size_t size);
    ~CEthernetFrame();
    QString get_dest_mac();
    QString get_source_mac();
    quint16 get_e_type();
    const u_char* get_packet();
    size_t size();

protected:
    const u_char* packet;
    size_t packet_size;

    // CPacket interface
public:
    CPacket* parse_frame(CVisitor* visitor);
};

class CIPPacket : public CPacket
{
public:
    CIPPacket();
    CIPPacket(const u_char* payload, size_t size);
    ~CIPPacket();
    QString get_dest_mac();
    QString get_source_mac();
    quint16 get_e_type();
    const u_char* get_packet();
    size_t size();
    QString get_source_ip();
    QString get_dest_ip();
    quint8 get_protocol();
    quint8 get_version();
    quint8 get_lenght();
    CEthernetFrame* get_eth_header();

protected:
    const u_char* ip_packet;
private:
    CEthernetFrame* eth_frame;
    quint8 ip_version;
    quint8 ip_lenght;


    // CPacket interface
public:
    CPacket* parse_frame(CVisitor* visitor);
};


class CTCPPacket : public CPacket
{
public:
    CTCPPacket();
    explicit CTCPPacket(const u_char* payload, size_t size);
    ~CTCPPacket();

    QString get_dest_mac();
    QString get_source_mac();
    quint16 get_e_type();
    const u_char* get_packet();
    size_t size();
    QString get_source_ip();
    QString get_dest_ip();
    quint8 get_protocol();
    quint8 get_version();
    quint8 get_lenght();
    quint16 get_source_port();
    quint16 get_dest_port();
    CIPPacket* get_ip_header();
protected:

CIPPacket* ip_pck;
private:

    const u_char* tcp_packet;

    // CPacket interface
public:
    CPacket* parse_frame(CVisitor* visitor);
};



class CUDPPacket : public CTCPPacket
{

public:
    CUDPPacket();
    explicit CUDPPacket(const u_char* payload, size_t size);
    ~CUDPPacket();


    quint16 get_source_port();
    quint16 get_dest_port();


private:
    const u_char* udp_packet;

    // CPacket interface
public:
    CPacket *parse_frame(CVisitor *visitor);
};


#endif // NETPACKET_H
