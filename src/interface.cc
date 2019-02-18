#include "interface.hh"

static std::vector<Interface> interfaces;

void add_interface(char* pci_addr) { interfaces.emplace_back(pci_addr); }
std::vector<Interface>& get_interfaces() { return interfaces; }
