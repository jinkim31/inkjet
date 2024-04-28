#ifndef NETWIRE_VIEW_SOCKET_H
#define NETWIRE_VIEW_SOCKET_H

#include "../comm.h"
#include <Poco/Net/Net.h>
#include <Poco/Net/NetworkInterface.h>

namespace inkjet
{

class Socket : public Comm
{
public:
    struct NetworkAdapter
    {
        std::string displayName, ipString, subnetMaskString;
    };

    static std::vector<NetworkAdapter> listNetworkAdapters();
};

}
#endif
