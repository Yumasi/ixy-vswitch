#!/usr/bin/env python

from scapy.all import *


sendp(Ether(dst='ff:ff:ff:ff:ff:ff')/IP(ttl=(1,20)), iface="vswitch_net1", inter=0.1)
