#ifndef INKJET_SERIAL_H
#define INKJET_SERIAL_H

#include <siglot/object.h>
#include <siglot/observer.h>
#include <serial/serial.h>

namespace inkjet
{

class Serial : public siglot::Object
{
public:
    Serial();
    ~Serial();
    static std::vector<std::string> getPortNames();
    void setPortName(std::string&& portName);   SIGLOT_ADD_FROM_VOID_FUNC_1(Serial, setPortName, std::string, portName)
    void setBaudRate(int&& baudRate);           SIGLOT_ADD_FROM_VOID_FUNC_1(Serial, setBaudRate, int, baudRate)
    bool open();    SIGLOT_ADD_FROM_FUNC(bool, Serial, open);
    bool close();   SIGLOT_ADD_FROM_FUNC(bool, Serial, close);
    bool write(std::vector<uint8_t>&& data); SIGLOT_ADD_FROM_FUNC_1(bool, Serial, write, std::vector<uint8_t>, data);
    bool writeString(std::string&& data); SIGLOT_ADD_FROM_FUNC_1(bool, Serial, writeString, std::string, data);
    size_t readMem(uint8_t* buffer, size_t bufferSize);
    void flush(){ mPort.flush();}

    SIGNAL SIGNAL_RxReady(std::vector<uint8_t>&& data){}
    SIGNAL SIGNAL_RxLineReady(std::string&& data){}

    std::string blockingReadLine(int timeoutMs);
private:
    void SLOT_observerCallback();
    serial::Serial mPort;
    std::string mPortName;
    std::string mRxLine;
    uint8_t mRxBuffer[1024];
    void onMove(siglot::Thread &thread) override;
    void onRemove() override;
};

}
#endif
