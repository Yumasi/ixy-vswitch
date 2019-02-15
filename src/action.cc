#include <cstring>

#include "action.hh"

TxAction::TxAction(Interface* interface, pkt_buf* bufs[BATCH_SIZE])
{
    interface_ = interface;
    std::memcpy(bufs_, bufs, sizeof(pkt_buf*) * BATCH_SIZE);
}
