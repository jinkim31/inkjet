#include "udp_socket.h"


inkjet::UdpSocket::UdpSocket()
{
    mIsOpen = false;
}

bool inkjet::UdpSocket::open()
{
    if(mIsOpen)
        return false;

    try
    {
        mSocket.open(ip::udp::v4());
        mIsOpen = true;
    }
    catch(std::exception& e){return false;}
    return true;
}

bool inkjet::UdpSocket::close()
{
    if(!mIsOpen)
        return false;
    mSocket.close();
    return true;
}

bool inkjet::UdpSocket::write(std::vector<uint8_t> &&data)
{
    return false;
}

bool inkjet::UdpSocket::writeString(std::string &&data)
{
    return false;
}

void inkjet::UdpSocket::SIGNAL_ReadReady(std::vector<uint8_t> &&data)
{

}

void inkjet::UdpSocket::SIGNAL_ReadLineReady(std::string &&data)
{

}

bool inkjet::UdpSocket::setIP(const std::string&& ip)
{
    mIpString = ip;
    try{mEndpoint = ip::udp::endpoint(ip::address::from_string(mIpString), mPort);}
    catch(std::exception& e){return false;}
    return true;
}

bool inkjet::UdpSocket::setPort(const uint16_t&& port)
{
    mPort = port;
    try{mEndpoint = ip::udp::endpoint(ip::address::from_string(mIpString), mPort);}
    catch(std::exception& e){return false;}
    return true;
}

void inkjet::UdpSocket::SLOT_observerCallback()
{
    std::cout<<"observer"<<std::endl;
}
