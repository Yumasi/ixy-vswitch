#pragma once

#include <vector>

extern "C" {
#include "driver/device.h"
#include "stats.h"
}

struct Interface {
    ixy_device* device;
    device_stats stats;

  public:
    Interface(char* pci_addr) { device = ixy_init(pci_addr, 1, 1); }
    ~Interface() = default;

    bool operator==(const Interface& other) { return other.device == device; }
    bool operator!=(const Interface& other) { return other.device != device; }
};

void add_interface(char* pci_addr);
std::vector<Interface>& get_interfaces();
