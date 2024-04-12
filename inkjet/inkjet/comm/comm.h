#ifndef NETWIRE_VIEW_COMM_H
#define NETWIRE_VIEW_COMM_H

#include <siglot/object.h>
#include <siglot/observer.h>

namespace inkjet
{

class Comm : public siglot::Object
{
public:
protected:
    void onMove(siglot::Thread &thread) override;
    void onRemove() override;
public:
    Comm();
    virtual bool open()=0;
    SIGLOT_ADD_FROM_FUNC(bool, Comm, open);
    virtual bool close()=0;
    SIGLOT_ADD_FROM_FUNC(bool, Comm, close);
    virtual bool write(std::vector<uint8_t>&& data)=0;
    SIGLOT_ADD_FROM_FUNC_1(bool, Comm, write, std::vector<uint8_t>, data);
    virtual bool writeString(std::string&& data)=0;
    SIGLOT_ADD_FROM_FUNC_1(bool, Comm, writeString, std::string, data);
    virtual SIGNAL SIGNAL_ReadReady(std::vector<uint8_t>&& data)=0;
    virtual SIGNAL SIGNAL_ReadLineReady(std::string&& data)=0;
protected:
    virtual SLOT SLOT_observerCallback(){};
    siglot::Observer mObserver;
};

}
#endif
