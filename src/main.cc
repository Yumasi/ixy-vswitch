#include <iostream>

#include "interface.hh"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Too few arguments." << std::endl;
        std::cerr << "Usage: " << argv[0]
                  << " <managed interfaces pci id lists>" << std::endl;

        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        add_interface(argv[i]);
    }

    start_forwarding();

    return 0;
}
