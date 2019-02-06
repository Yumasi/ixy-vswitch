#pragma once

#include <memory>
#include <string>
#include <vector>

extern "C" {
#include "driver/device.h"
#include "stats.h"
}

struct Interface
{
    static std::vector<Interface*> interfaces;

    ixy_device* device;
    device_stats stats;

    Interface(char* pci_addr);
    ~Interface() = default;

    bool operator==(const Interface& other) { return other.device == device; }
    bool operator!=(const Interface& other) { return other.device != device; }
};
