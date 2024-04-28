#include "socket.h"

std::vector<inkjet::Socket::NetworkAdapter> inkjet::Socket::listNetworkAdapters()
{
    std::vector<NetworkAdapter> adapters;
    for(const auto& pocoAdapter : Poco::Net::NetworkInterface::list())
    {
        if(!pocoAdapter.supportsIPv4())
            continue;

        NetworkAdapter adapter;
        adapter.displayName = pocoAdapter.displayName();
        adapter.subnetMaskString = pocoAdapter.subnetMask().toString();
        adapter.ipString = pocoAdapter.address().toString();
        adapters.push_back(std::move(adapter));
    }

    return adapters;
}
