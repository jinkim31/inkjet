#include "udp_client.h"

inkjet::UDPClient::UDPClient()
{
    mIsOpen = false;
}

bool inkjet::UDPClient::setEndpoint(std::string &&ip, uint16_t &&port)
{
    mIpString = ip;
    mPort = port;

    ip::udp::resolver::query query(ip::udp::v4(), mIpString, std::to_string(mPort));
    mEndpoint = *resolver.resolve(query);

    return true;
}

bool inkjet::UDPClient::open()
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

bool inkjet::UDPClient::close()
{
    if(!mIsOpen)
        return false;
    mSocket.close();
    return true;
}

bool inkjet::UDPClient::write(std::vector<uint8_t> &&data)
{
    return false;
}

std::vector<std::string> inkjet::UDPClient::getAdapterIPs()
{
    boost::asio::io_service io;
    boost::asio::ip::tcp::resolver resolver(io);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name() + ".local", "");
    boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    std::vector<std::string> IPs;

    while(iter != end) {
        std::cout<<iter->endpoint().address().to_string()<<std::endl;
        //if(iter->endpoint().address().is_v4()
        //&& std::find(IPs.begin(), IPs.end(),iter->endpoint().address().to_string()) == IPs.end())
            IPs.push_back(std::move(iter->endpoint().address().to_string()));
        ++iter;
    }
    return IPs;
}

bool inkjet::UDPClient::writeString(std::string &&data)
{
    return false;
}

void inkjet::UDPClient::SIGNAL_ReadReady(std::vector<uint8_t> &&data)
{

}

void inkjet::UDPClient::SIGNAL_ReadLineReady(std::string &&data)
{

}

void inkjet::UDPClient::SLOT_observerCallback()
{
    Comm::SLOT_observerCallback();
}
