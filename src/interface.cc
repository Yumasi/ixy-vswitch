#include "interface.hh"

Interface::Interface(char* pci_addr) { device = ixy_init(pci_addr, 1, 1); }
