#pragma once

#include <atomic>

class Spinlock
{
public:
    Spinlock() = default;
    Spinlock(const Spinlock&) = delete;
    Spinlock(const Spinlock&&) = delete;

    ~Spinlock() = default;

    void lock();
    void release();
private:

    std::atomic_flag lock_ = ATOMIC_FLAG_INIT;
};
