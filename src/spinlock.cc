#include "spinlock.hh"

void Spinlock::lock()
{
    while (lock_.test_and_set(std::memory_order_acquire))
        continue;
}

void Spinlock::release()
{
    lock_.clear(std::memory_order_release);
}
