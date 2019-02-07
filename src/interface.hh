#pragma once

#include <array>
#include <cstddef>
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
    std::array<std::byte, 6> mac_addr;

    Interface(char* pci_addr);
    ~Interface() = default;

    bool operator==(const Interface& other) { return other.device == device; }
    bool operator!=(const Interface& other) { return other.device != device; }
};
