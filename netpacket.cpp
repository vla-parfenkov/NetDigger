#include "netpacket.h"
#include <netinet/ether.h>
#include <netinet/in.h>
#include <QDebug>


//structure ip packets
struct iphdr{
    quint8 ver_len;
    quint8 type_service;
    quint16 size;
    quint16 id;
    quint16 flag_offset;
    quint8 time_live;
    quint8 protocol;
    quint16 chek_summ;
    quint8 saddr[SIZE_IPv4];
    quint8 daddr[SIZE_IPv4];
};

//structure ip6 packets
struct ip6_hdr{
    quint32 ver_trafic_label;
    quint16 lenght;
    quint8 protocol;
    quint8 time_live;
    quint16 saddr[SIZE_IPv6];
    quint16 daddr[SIZE_IPv6];
};


CEthernetFrame::CEthernetFrame()
{
    packet = NULL;
    packet_size = 0;
}

CEthernetFrame::CEthernetFrame(const u_char *payload_in, size_t size)
{
    packet = payload_in;
    packet_size = size;
}

CEthernetFrame::~CEthernetFrame()
{
    //
}


QString CEthernetFrame::get_dest_mac()
{
    const ether_header *eth = reinterpret_cast<const ether_header *>(packet);
    const ether_addr *res = reinterpret_cast<const ether_addr *>(&eth->ether_dhost);

    return QString::fromLatin1(ether_ntoa(res));

}

QString CEthernetFrame::get_source_mac()
{
    const ether_header *eth = reinterpret_cast<const ether_header *>(packet);
    const ether_addr *res = reinterpret_cast<const ether_addr *>(&eth->ether_shost);

    return QString::fromLatin1(ether_ntoa(res));
}

quint16 CEthernetFrame::get_e_type()
{
    const ether_header *eth = reinterpret_cast<const ether_header *>(packet);
    return ntohs(eth->ether_type);
}

const u_char *CEthernetFrame::get_packet()
{
    return packet;
}

size_t CEthernetFrame::size()
{
    return packet_size;
}

CPacket* CEthernetFrame::parse_frame(CVisitor* visitor)
{
    return visitor->visit(this);
}




CIPPacket::CIPPacket()
{
    ip_packet = NULL;
    eth_frame = NULL;
}

CIPPacket::CIPPacket(const u_char *payload, size_t size)
{
    eth_frame = new CEthernetFrame(payload, size);
    ip_packet = payload + sizeof(ether_header);
    const iphdr *ip = reinterpret_cast<const iphdr *>(ip_packet);
    ip_version = ((ip->ver_len & 0b11110000) >> 4);
    if (ip_version == 4){
       ip_lenght = (ip->ver_len & 0b00001111);
    } else {
        const ip6_hdr *ip6 = reinterpret_cast<const ip6_hdr *>(ip_packet);
        ip_lenght = ip6->lenght;
    }
}

CIPPacket::~CIPPacket()
{
    delete eth_frame;
}

QString CIPPacket::get_dest_mac()
{
    return eth_frame->get_dest_mac();
}

QString CIPPacket::get_source_mac()
{
    return eth_frame->get_source_mac();
}

quint16 CIPPacket::get_e_type()
{
    return eth_frame->get_e_type();
}

const u_char *CIPPacket::get_packet()
{
    return eth_frame->get_packet();
}

size_t CIPPacket::size()
{
    return eth_frame->size();
}


QString CIPPacket::get_source_ip()
{
    QString str("");
    if (ip_version == 4)
    {
        const iphdr *ip = reinterpret_cast<const iphdr *>(ip_packet);
        for (size_t i = 0; i < SIZE_IPv4; ++i ){
             str += QString::number(ip->saddr[i]);
             if(i < SIZE_IPv4 - 1){
                 str += ".";
             }
        }
    } else{
        const ip6_hdr *ip = reinterpret_cast<const ip6_hdr *>(ip_packet);
        for (size_t i = 0; i < SIZE_IPv6; ++i ){
             str += QString::number(ip->saddr[i],16);
             if(i < SIZE_IPv6 - 1){
                 str += ":";
             }
        }
    }
    return str;
}

QString CIPPacket::get_dest_ip()
{
    QString str("");
    if (ip_version == 4)
    {
        const iphdr *ip = reinterpret_cast<const iphdr *>(ip_packet);
        for (size_t i = 0; i < SIZE_IPv4; ++i ){
             str += QString::number(ip->daddr[i]);
             if(i < SIZE_IPv4 - 1){
                 str += ".";
             }
        }
    } else{
        const ip6_hdr *ip = reinterpret_cast<const ip6_hdr *>(ip_packet);
        for (size_t i = 0; i < SIZE_IPv6;++i ){
             str += QString::number(ip->daddr[i],16);
             if(i < SIZE_IPv6 - 1){
                 str += ":";
             }
        }
    }
    return str;
}

quint8 CIPPacket::get_protocol()
{
    if (ip_version == 4)
    {
        const iphdr *ip = reinterpret_cast<const iphdr *>(ip_packet);
        return ip->protocol;
    } else {
        const ip6_hdr *ip = reinterpret_cast<const ip6_hdr *>(ip_packet);
        return  ip->protocol;
    }
}

quint8 CIPPacket::get_version()
{
    return ip_version;
}

quint8 CIPPacket::get_lenght()
{
    return ip_lenght * 4;
}

CEthernetFrame* CIPPacket::get_eth_header()
{
    return eth_frame;
}

CPacket* CIPPacket::parse_frame(CVisitor* visitor)
{
    return visitor->visit(this);
}


//-----------------------------------------------------------//
CTCPPacket::CTCPPacket()
{
    tcp_packet = NULL;
    ip_pck = NULL;

}

CTCPPacket::CTCPPacket(const u_char *payload, size_t size)
{
    ip_pck = new CIPPacket(payload, size);
   tcp_packet = payload  + sizeof(ether_header) + ip_pck->get_lenght();
}

CTCPPacket::~CTCPPacket()
{
    delete ip_pck;
}

QString CTCPPacket::get_dest_mac()
{
    return ip_pck->get_dest_mac();
}

QString CTCPPacket::get_source_mac()
{
    return ip_pck->get_source_mac();
}

quint16 CTCPPacket::get_e_type()
{
    return ip_pck->get_e_type();
}

const u_char *CTCPPacket::get_packet()
{
    return ip_pck->get_packet();
}

size_t CTCPPacket::size()
{
    return ip_pck->size();
}

QString CTCPPacket::get_source_ip()
{
    return ip_pck->get_source_ip();
}

QString CTCPPacket::get_dest_ip()
{
    return ip_pck->get_dest_ip();
}

quint8 CTCPPacket::get_protocol()
{
    return ip_pck->get_protocol();
}

quint8 CTCPPacket::get_version()
{
    return ip_pck->get_version();
}

quint8 CTCPPacket::get_lenght()
{
    return ip_pck->get_lenght();
}

quint16 CTCPPacket::get_source_port()
{
    const quint8 *tcp_port = reinterpret_cast<const quint8 *>(tcp_packet);
    quint16 port = (tcp_port[0] << (sizeof(tcp_port[0]) * CHAR_BIT) | tcp_port[1] );
    return port;
}

quint16 CTCPPacket::get_dest_port()
{
    const quint8 *tcp_port = reinterpret_cast<const quint8 *>(tcp_packet + sizeof(quint8[2]));
    quint16 port = (tcp_port[0] << (sizeof(tcp_port[0]) * CHAR_BIT) | tcp_port[1] );
    return port;
}

CIPPacket *CTCPPacket::get_ip_header()
{
    return ip_pck;
}

CPacket* CTCPPacket::parse_frame(CVisitor* visitor)
{
    return visitor->visit(this);
}

//-------------------------------------------------------///



CPacket* CPacketVisitor::visit(CEthernetFrame* eth_frame)
{
    if ((eth_frame->get_e_type() == IPv4_E_TYPE) || (eth_frame->get_e_type() == IPv6_E_Type) )
    {
        CPacket *packet = new CIPPacket(eth_frame->get_packet(), eth_frame->size());
        delete eth_frame;
        packet->parse_frame(this);
    } else
    {
        return eth_frame;
    }
}

CPacket* CPacketVisitor::visit(CIPPacket* ip_pck)
{
    CPacket *packet = NULL;
    switch (ip_pck->get_protocol()) {
    case ID_TCP:
    {
        packet = new CTCPPacket(ip_pck->get_packet(), ip_pck->size());
        delete ip_pck;
        packet->parse_frame(this);
        break;
    }
    case ID_UDP:
    {
        packet = new CUDPPacket(ip_pck->get_packet(), ip_pck->size());
        delete ip_pck;
        packet->parse_frame(this);
        break;
    }
    default:
        return ip_pck;
}

    return packet;
}



CPacket* CPacketVisitor::visit(CTCPPacket* tcp_pck)
{
    return tcp_pck;
}

CPacket *CPacketVisitor::visit(CUDPPacket *udp_pck)
{
    return udp_pck;
}

//---------------------------------------------------------------////

CUDPPacket::CUDPPacket()
{
    udp_packet = NULL;
}

CUDPPacket::CUDPPacket(const u_char *payload, size_t size)
{
    ip_pck = new CIPPacket(payload, size);
    udp_packet = payload  + sizeof(ether_header) + ip_pck->get_lenght();
}

CUDPPacket::~CUDPPacket()
{
   //
}

quint16 CUDPPacket::get_source_port()
{
    const quint8 *udp_port = reinterpret_cast<const quint8 *>(udp_packet);
    quint16 port = (udp_port[0] << (sizeof(udp_port[0]) * CHAR_BIT) | udp_port[1] );
    return port;
}

quint16 CUDPPacket::get_dest_port()
{
    const quint8 *udp_port = reinterpret_cast<const quint8 *>(udp_packet + sizeof(quint8[2]));
    quint16 port = (udp_port[0] << (sizeof(udp_port[0]) * CHAR_BIT) | udp_port[1] );
    return port;
}

CPacket *CUDPPacket::parse_frame(CVisitor *visitor)
{
    return visitor->visit(this);
}





