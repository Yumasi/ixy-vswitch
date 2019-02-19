#include <array>
#include <cstddef>

#include "interface.hh"

using byte = std::byte;

using mac_addr = std::array<byte, 6>;

static std::vector<Interface> interfaces;

void add_interface(char* pci_addr) { interfaces.emplace_back(pci_addr); }
std::vector<Interface>& get_interfaces() { return interfaces; }
void start_forwarding()
{
}
