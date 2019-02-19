#include <functional>
#include <iostream>
#include <vector>

#include "conditional_iterator.hxx"
#include "interface.hh"

#define BATCH_SIZE (32)

static void flooding(std::vector<Interface>& interfaces)
{
    for (Interface& i : interfaces) {
        pkt_buf* bufs[BATCH_SIZE];
        uint32_t num_rx = ixy_rx_batch(i.device, 0, bufs, BATCH_SIZE);

        if (num_rx > 0) {
            std::cout << "Received: " << num_rx << " packets" << std::endl;
            for (uint32_t i = 0; i < num_rx; ++i)
                bufs[i]->ref_count = interfaces.size() - 1;

            auto condition = [&](Interface& other) { return other != i; };
            ConditionalIterator it(interfaces.begin(), interfaces.end(),
                                   std::ref(condition));

            for (; it.itr != it.end; ++it) {
                uint32_t num_tx = ixy_tx_batch(it->device, 0, bufs, num_rx);
                std::cout << "Sent: " << num_tx << " packets" << std::endl;
                for (uint32_t i = num_tx; i < num_rx; ++i) {
                    bufs[i]->ref_count = 1;
                    pkt_buf_free(bufs[i]);
                }
            }
        }
    }
}

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
