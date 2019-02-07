#pragma once

#include <atomic>

class Spinlock {
  public:
    Spinlock() = default;
    Spinlock(const Spinlock&) = delete;
    Spinlock(const Spinlock&&) = delete;

    ~Spinlock() = default;

    void lock() {
        while (lock_.test_and_set(std::memory_order_acquire))
            continue;
    }

    void release() { lock_.clear(std::memory_order_release); }

  private:
    std::atomic_flag lock_ = ATOMIC_FLAG_INIT;
};
