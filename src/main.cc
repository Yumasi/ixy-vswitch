#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cerr << "Too few arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " <managed interfaces pci id lists>"
                  << std::endl;

        return 1;
    }

    return 0;
}
