#ifndef INKJET_APPLICATION_H
#define INKJET_APPLICATION_H

#include "inkjet.h"

class Application : public Object
{
public:
    Application();
    ~Application();
    void Render();
private:
    Thread mThread;
};


#endif
