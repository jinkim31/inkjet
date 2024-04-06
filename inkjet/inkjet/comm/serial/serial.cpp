#include "serial.h"

InkJet::Serial::Serial()
{
    mPort = NULL;
    setName("serial");
    connect(mObserver, SIGLOT(siglot::Observer::SIGNAL_observed), *this, SIGLOT(Serial::SLOT_observerCallback));
}

InkJet::Serial::~Serial()
{
    if(mPort != NULL)
        sp_free_port(mPort);
}

void InkJet::Serial::onMove(siglot::Thread &thread)
{
    mObserver.move(thread);
}

void InkJet::Serial::onRemove()
{
    mObserver.remove();
}

std::vector<std::string> InkJet::Serial::getPortNames()
{
    sp_port** ports;
    int ret = sp_list_ports(&ports);
    if(ret < 0)
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

bool InkJet::Serial::open()
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
    //mObserver.start();
    return true;
}

bool InkJet::Serial::close()
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

void InkJet::Serial::SLOT_observerCallback()
{
    if(mPort==NULL)
        return;

    if(sp_input_waiting(mPort)<=0)
        return;
    int n = sp_blocking_read_next(mPort, mRxBuffer, 1024, 100);

    std::vector<uint8_t> rx;
    rx.reserve(n);
    for(int i=0; i<n; i++)
    {
        rx.push_back(mRxBuffer[i]);
        mRxLine.append(1, mRxBuffer[i]);
        if(mRxBuffer[i] == '\0' || mRxBuffer[i] == '\n')
        {
            emit(SIGLOT(Serial::SIGNAL_RxLineReady), std::move(mRxLine));
            mRxLine = "";
        }
    }
    emit(SIGLOT(Serial::SIGNAL_RxReady), std::move(rx));
}

void InkJet::Serial::setPortName(std::string &&portName)
{
    mPortName = std::move(portName);
}

bool InkJet::Serial::write(std::vector<uint8_t> &&data)
{
    if(sp_blocking_write(mPort, data.data(), data.size(), 100) == data.size())
        return true;
    else
        return false;
}

bool InkJet::Serial::writeString(std::string &&data)
{
    if(sp_blocking_write(mPort, data.data(), data.size(), 100) == data.size())
        return true;
    else
        return false;
}

std::string InkJet::Serial::blockingReadLine(int timeoutMs)
{
    std::string res;
    while(true)
    {
        int n = sp_blocking_read_next(mPort, mRxBuffer, 1024, timeoutMs);
        if(n <= 0)
            return "";

        for(int i=0; i<n; i++)
        {
            res.append(1, (char)mRxBuffer[i]);
            if(mRxBuffer[i] == '\n')
            {
                return res;
            }
        }
    }
}
