#ifndef INKJET_SERIAL_H
#define INKJET_SERIAL_H

#include <siglot/object.h>
#include <siglot/observer.h>

class Serial : public siglot::Object
{
public:
    Serial();
    ~Serial();
    void setPort(const std::string& portName);
private:
    siglot::Observer mObserver;
    std::string mPortName;
    bool mIsOpen;
    unsigned int mBaudRate;
    void onMove(siglot::Thread &thread) override;
    void onRemove() override;
};

#endif
