#pragma once

#include "interface.hh"

#define BATCH_SIZE (32)

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
