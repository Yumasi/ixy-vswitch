#include <iostream>
#include <vector>

#include "interface.hh"

#define BATCH_SIZE (32)

static void forward(Interface& int_1, Interface& int_2)
{
    pkt_buf* bufs[BATCH_SIZE];
    uint32_t num_rx = ixy_rx_batch(int_1.device, 0, bufs, BATCH_SIZE);
    if (num_rx > 0) {
        uint32_t num_tx = ixy_tx_batch(int_2.device, 0, bufs, num_rx);
        for (uint32_t i = num_tx; i < num_rx; ++i) {
            pkt_buf_free(bufs[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cerr << "Too few arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " <managed interfaces pci id lists>"
                  << std::endl;

        return 1;
    }

    std::vector<Interface> interfaces;
    interfaces.push_back(Interface(argv[1]));
    interfaces.push_back(Interface(argv[2]));

    return 0;
}
