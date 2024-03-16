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

void Serial::setPort(const std::string portName)
{
    mPortName = portName;
}

void Serial::setBaudRate(unsigned int baudRate)
{
    mBaudRate = baudRate;
}
