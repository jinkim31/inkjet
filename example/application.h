#ifndef INKJET_APPLICATION_H
#define INKJET_APPLICATION_H

#include <inkjet/inkjet.h>
#include <siglot/observer.h>

class Application : public siglot::Object
{
public:
    Application();
    ~Application();
    void Render();
private:
    siglot::Thread mThread;
};


#endif
