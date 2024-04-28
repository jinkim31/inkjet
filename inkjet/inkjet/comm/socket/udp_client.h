#ifndef NETWIRE_VIEW_UDP_CLIENT_H
#define NETWIRE_VIEW_UDP_CLIENT_H

#include "socket.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::asio;

namespace inkjet
{

class UDPClient : public Socket
{

public:
    UDPClient();
    bool open() override;
    bool close() override;
    bool write(std::vector<uint8_t> &&data) override;
    bool writeString(std::string &&data) override;
    void SIGNAL_ReadReady(std::vector<uint8_t> &&data) override;
    void SIGNAL_ReadLineReady(std::string &&data) override;
protected:
    void SLOT_observerCallback() override;
private:
};

}

#endif
