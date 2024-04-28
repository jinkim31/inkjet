#include "udp_client.h"

inkjet::UDPClient::UDPClient()
{

}

bool inkjet::UDPClient::open()
{

}

bool inkjet::UDPClient::close()
{
}

bool inkjet::UDPClient::write(std::vector<uint8_t> &&data)
{
    return false;
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
