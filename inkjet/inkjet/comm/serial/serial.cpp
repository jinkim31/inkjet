#include "serial.h"

inkjet::Serial::Serial()
{
    setSiglotObjectName("serial");
}

inkjet::Serial::~Serial()
{

}

void inkjet::Serial::onMove(siglot::Thread &thread)
{

}

void inkjet::Serial::onRemove()
{

}

std::vector<std::string> inkjet::Serial::getPortNames()
{
    std::vector<std::string> names;
    for(const auto& portInfo : serial::list_ports())
    {
       names.emplace_back(portInfo.port);
    }
    return names;
}

bool inkjet::Serial::open()
{
    mPort.setPort(mPortName);
    mPort.setBaudrate(115200);
    mPort.setBytesize(serial::eightbits);
    mPort.setParity(serial::parity_none);
    mPort.setStopbits(serial::stopbits_one);
    mPort.setFlowcontrol(serial::flowcontrol_none);
    mPort.setTimeout(1,0,0,0,0);

    try
    {
    mPort.open();
    std::this_thread::sleep_for(std::chrono::milliseconds(0));
    mPort.flush();
    }catch(std::exception e)
    {
        return false;
    }

    return true;
}

bool inkjet::Serial::close()
{
    mPort.close();
    return !mPort.isOpen();
}

void inkjet::Serial::SLOT_observerCallback()
{

}

void inkjet::Serial::setPortName(std::string &&portName)
{
    mPortName = std::move(portName);
}

bool inkjet::Serial::write(std::vector<uint8_t> &&data)
{
    mPort.flush();
    size_t n = mPort.write(data);

    if( n!=data.size())
        std::cerr<<"write failed("<<n<<"/"<<data.size()<<")"<<std::endl;
    return n==data.size();
}

bool inkjet::Serial::writeString(std::string &&data)
{
    //std::cout<<"writing "<<data.substr(0, data.length()-2)<<std::endl;
    size_t n = mPort.write(data);

    //std::cerr<<"write string ("<<n<<"/"<<data.size()<<")"<<std::endl;
    return n==data.size();
}

std::string inkjet::Serial::blockingReadLine(int timeoutMs)
{
}

void inkjet::Serial::setBaudRate(int &&baudRate)
{
    mPort.setBaudrate(baudRate);
}

size_t inkjet::Serial::readMem(uint8_t* buffer, size_t bufferSize)
{
    size_t n = 0;
    if(mPort.available())
    {
        n = mPort.read(buffer, bufferSize);
        printf("received: ");
        for(int i=0; i<n; i++)
        {
            if(buffer[i] != '\r')
                printf("%c", buffer[i]);
        }
    }

    return n;
}