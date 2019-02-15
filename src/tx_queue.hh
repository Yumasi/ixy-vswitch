#pragma once

#include <deque>

#include "action.hh"
#include "interface.hh"
#include "spinlock.hh"

class TxQueue {
public:
    TxQueue() = default;
    TxQueue(const TxQueue&) = delete;
    TxQueue(const TxQueue&&) = delete;

    ~TxQueue() = default;

    void push(Interface* interface, pkt_buf* bufs[BATCH_SIZE]);
    void pop();

private:
    std::deque<TxAction> tx_actions;
    Spinlock lock;
};
