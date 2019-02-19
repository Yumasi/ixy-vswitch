#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>

#include "conditional_iterator.hxx"
#include "interface.hh"

static constexpr size_t BATCH_SIZE = 32;

using u32 = std::uint32_t;
using byte = std::byte;

using mac_addr = std::array<byte, 6>;

static std::vector<Interface> interfaces;
// FIXME: what if there is more than one interface with a MAC ? (Can it happen
// ?)
static std::map<mac_addr, Interface&> fib;

struct eth_frame {
    byte dst_mac[6];
    byte src_mac[6];
    byte ether_type[2];
};

void add_interface(char* pci_addr) { interfaces.emplace_back(pci_addr); }
std::vector<Interface>& get_interfaces() { return interfaces; }

static void flood(pkt_buf* packet)
{
    for (Interface& i : interfaces) {
        packet->ref_count = interfaces.size() - 1;

        auto condition = [&](Interface& other) { return other != i; };
        ConditionalIterator it(interfaces.begin(), interfaces.end(),
                               std::ref(condition));

        for (; it.itr != it.end; ++it) {
            uint32_t num_tx = ixy_tx_batch(it->device, 0, &packet, 1);
            if (!num_tx)
                pkt_buf_free(packet);
        }
    }
}

static inline void forward(Interface& i)
{
    pkt_buf* bufs[BATCH_SIZE];
    u32 num_rx = ixy_rx_batch(i.device, 0, bufs, BATCH_SIZE);

    for (u32 pkt_idx = 0; pkt_idx < num_rx; ++pkt_idx) {
        eth_frame* frame = reinterpret_cast<eth_frame*>(bufs[pkt_idx]->data);
        mac_addr src_addr;
        std::copy(frame->src_mac, frame->src_mac + 6, src_addr.begin());
        fib.try_emplace(src_addr, i);

        auto condition = [&](std::pair<mac_addr, Interface&> other) {
            return !std::memcmp(other.first.data(), frame->dst_mac, 6);
        };

        auto dest = std::find_if(fib.begin(), fib.end(), condition);

        if (dest == fib.end()) {
            flood(bufs[pkt_idx]);
            return;
        }

        // TODO: use tx_batch for actual batches
        ixy_tx_batch(dest->second.device, 0, &bufs[pkt_idx], 1);
        pkt_buf_free(bufs[pkt_idx]);
    }
}

void start_forwarding()
{
    while (true) {
        for (Interface& i : interfaces)
            forward(i);
    }
}
