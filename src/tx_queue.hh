#pragma once

#include <deque>

#include "interface.hh"
#include "spinlock.hh"

#define BATCH_SIZE (32)

class TxQueue {
    class TxAction
    {
    public:
        TxAction(Interface* interface, pkt_buf* bufs[BATCH_SIZE]);
        TxAction(const TxAction&) = delete;
        TxAction(const TxAction&&) = delete;
        ~TxAction() = default;

    private:
        Interface* interface_;
        pkt_buf *bufs_[BATCH_SIZE];
    };

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
