#ifndef INKJET_APPLICATION_H
#define INKJET_APPLICATION_H

#include "inkjet.h"
#include <siglot/observer.h>

class Application : public siglot::Object
{
public:
    Application();
    ~Application();
    void Render();
    void SLOT slot();
private:
    siglot::Thread mThread;
    siglot::Observer mObserver;
};


#endif
