#ifndef NETWIRE_VIEW_UDP_CLIENT_H
#define NETWIRE_VIEW_UDP_CLIENT_H

#include "../comm.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::asio;

namespace inkjet
{

class UDPClient : public Comm
{

public:
    static std::vector<std::string> getAdapterIPs();
    UDPClient();
    bool setEndpoint(std::string&& ip, uint16_t&& port);
    bool open() override;
    bool close() override;
    bool write(std::vector<uint8_t> &&data) override;
    bool writeString(std::string &&data) override;
    void SIGNAL_ReadReady(std::vector<uint8_t> &&data) override;
    void SIGNAL_ReadLineReady(std::string &&data) override;
protected:
    void SLOT_observerCallback() override;
private:
    std::string mIpString;
    uint16_t mPort;
    bool mIsOpen;
    io_service mIoService;
    ip::udp::resolver resolver{mIoService};
    ip::udp::socket mSocket{mIoService};
    ip::udp::endpoint mEndpoint;
};

}

#endif
