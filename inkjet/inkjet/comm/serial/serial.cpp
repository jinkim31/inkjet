#include "serial.h"

inkjet::Serial::Serial()
{
    mPort = NULL;
    setName("serial");
    connect(mObserver, SIGLOT(siglot::Observer::SIGNAL_observed), *this, SIGLOT(Serial::SLOT_observerCallback));
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

bool inkjet::Serial::open()
{
    sp_port* port;
    if(sp_get_port_by_name(mPortName.c_str(), &port)<0)
        return false;

    if(sp_open(port, SP_MODE_READ_WRITE)<0)
    {
        sp_free_port(port);
        return false;
    }

    sp_set_baudrate(port, 115200);
    sp_set_bits(port, 8);

    mPort = port;
    mObserver.start();
    return true;
}

bool inkjet::Serial::close()
{
    if(mPort==NULL)
        return false;

    if(sp_close(mPort)<0)
        return false;

    mObserver.stop();
    sp_free_port(mPort);
    mPort = NULL;
    return true;
}

void inkjet::Serial::SLOT_observerCallback()
{
    if(mPort==NULL)
        return;

    if(sp_input_waiting(mPort)<=0)
        return;
    static uint8_t buffer[1024];
    int n = sp_blocking_read_next(mPort, buffer, 1024, 100);

    std::vector<uint8_t> rx;
    rx.reserve(n);
    for(int i=0; i<n; i++)
        rx.push_back(buffer[i]);
    emit(SIGLOT(Serial::SIGNAL_RxReady), std::move(rx));
}

void inkjet::Serial::setPortName(std::string &&portName)
{
    mPortName = std::move(portName);
}

bool inkjet::Serial::write(std::vector<uint8_t> &&data)
{
    if(sp_blocking_write(mPort, data.data(), data.size(), 100) == data.size())
    {
        std::cout<<"written "<<data.size()<<" bytes"<<std::endl;
        return true;
    }
    else
        return false;
}