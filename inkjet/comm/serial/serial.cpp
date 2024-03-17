//
// Created by Jin Kim on 2024/02/16.
//

#include "serial.h"

Serial::Serial()
{
    mIsOpen = false;
    mPortName = "";
}

Serial::~Serial()
{

}

void Serial::onMove(siglot::Thread &thread)
{
    Object::onMove(thread);
}

void Serial::onRemove()
{
    Object::onRemove();
}
