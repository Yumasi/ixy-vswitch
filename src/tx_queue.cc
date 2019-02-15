#include "tx_queue.hh"

void TxQueue::push(Interface *interface, pkt_buf* bufs[BATCH_SIZE])
{
    lock.lock();
    tx_actions.emplace_front(interface, bufs);
    lock.release();
}

void TxQueue::pop()
{
    lock.lock();
    tx_actions.pop_back();
    lock.release();
}
