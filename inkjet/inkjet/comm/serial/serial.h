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
    void start();
    void stop();
private:
    siglot::Observer mObserver;
    sp_port* mPort;
    void onMove(siglot::Thread &thread) override;
    void onRemove() override;
};

}
#endif
