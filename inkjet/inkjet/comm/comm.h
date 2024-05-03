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
protected:
    virtual SLOT SLOT_observerCallback(){};
    siglot::Observer mObserver;
};

}
#endif
