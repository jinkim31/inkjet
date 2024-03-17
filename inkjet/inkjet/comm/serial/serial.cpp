#include "serial.h"

inkjet::Serial::Serial()
{
    mPort = NULL;
}

inkjet::Serial::~Serial()
{
    if(mPort != NULL)
        sp_free_port(mPort);
}

void inkjet::Serial::onMove(siglot::Thread &thread)
{
    mObserver.move(thread);
}

void inkjet::Serial::onRemove()
{
    mObserver.remove();
}

std::vector<std::string> inkjet::Serial::getPortNames()
{
    sp_port** ports;
    if(sp_list_ports(&ports) < 0)
        return {};

    std::vector<std::string> names;
    for(int i=0; ; i++)
    {
        if(ports[i]==NULL)
            break;
       names.emplace_back(sp_get_port_name(ports[i]));
    }

    sp_free_port_list(ports);
    return names;
}
