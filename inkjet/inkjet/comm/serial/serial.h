#ifndef INKJET_SERIAL_H
#define INKJET_SERIAL_H

#include <siglot/object.h>
#include <siglot/observer.h>
#include <libserialport/libserialport.h>

namespace inkjet
{

class Serial : public siglot::Object
{
public:
    Serial();
    ~Serial();
    std::vector<std::string> getPortNames();
    void setPortName(std::string&& portName);   SIGLOT_ADD_FROM_VOID_FUNC_1(Serial, setPortName, std::string, portName)
    bool open();    SIGLOT_ADD_FROM_FUNC(bool, Serial, open);
    bool close();   SIGLOT_ADD_FROM_FUNC(bool, Serial, close);
    bool write(std::vector<uint8_t>&& data); SIGLOT_ADD_FROM_FUNC_1(bool, Serial, write, std::vector<uint8_t>, data);
    void SIGNAL_RxReady(std::vector<uint8_t>&& data){}
private:
    void SLOT_observerCallback();
    siglot::Observer mObserver;
    sp_port* mPort;
    std::string mPortName;
    void onMove(siglot::Thread &thread) override;
    void onRemove() override;
};

}
#endif
