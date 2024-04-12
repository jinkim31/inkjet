#include "comm.h"

inkjet::Comm::Comm()
{
    connect(mObserver, SIGLOT(siglot::Observer::SIGNAL_observed), *this, SIGLOT(Comm::SLOT_observerCallback));
}

void inkjet::Comm::onMove(siglot::Thread &thread)
{
    mObserver.move(thread);
}

void inkjet::Comm::onRemove()
{
    mObserver.remove();
}
