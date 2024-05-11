#ifndef NETWIRE_VIEW_UDP_CLIENT_H
#define NETWIRE_VIEW_UDP_CLIENT_H

#include "socket.h"
#include <Poco/Net/Net.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Timespan.h>

namespace inkjet
{

class UDPClient : public Socket
{

public:
    UDPClient();
    bool open(const std::string&& ipString, unsigned short&& port);
    bool close();
    void write(std::string&& data);
    void write(std::vector<uint8_t>&& data);
    std::vector<uint8_t> read();
    size_t readMem(uint8_t* buffer, const size_t& bufferSize);
    size_t available();
    SIGNAL SIGNAL_available(){};
protected:
    void SLOT_observerCallback() override;
private:
    Poco::Net::DatagramSocket mSocket;
    std::vector<uint8_t> mReadBuffer;
    size_t poll();
};

}

#endif
