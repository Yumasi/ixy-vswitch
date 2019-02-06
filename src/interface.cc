#include "interface.hh"

std::vector<Interface*> Interface::interfaces;

Interface::Interface(char* pci_addr)
{
    device = ixy_init(pci_addr, 1, 1);

    interfaces.push_back(this);
}
