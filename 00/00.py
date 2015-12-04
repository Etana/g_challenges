import sys

"""
00: Given an IPv4 address and a subnet mask, compute the network, broadcast and
    first/last host addresses
"""

def num_to_ip(num):
    tokens = []
    for _ in range(4):
        tokens.insert(0, num & 255)
        num = num >> 8
    return '.'.join(map(str, tokens))

def ip_to_num(ip):
    num = 0
    for octet in map(int, ip.split('.')):
        num = num * 256 + octet
    return num

if len(sys.argv) != 2:
    print('need one and only one argument', file=sys.stderr)
    sys.exit(1)

address, _, subnet = sys.argv[1].partition('/')
subnet = int(subnet)
num = ip_to_num(address)

if not (0 <= subnet < 33 and address == num_to_ip(num)):
    print('ip argument does not respect [0-255].[0-255].[0-255].[0-255]/[0-32] format', file=sys.stderr)
    sys.exit(2)

mask_host = (1 << (32 - subnet)) - 1
mask_subnet = (((1 << 32) - 1) ^ mask_host)

network = num & mask_subnet
broadcast = num | mask_host

print('ip:\t\t{}/{}'.format(address, subnet))
print('network:\t{}/{}'.format(num_to_ip(network), subnet))
print('broadcast:\t{}/{}'.format(num_to_ip(broadcast), subnet))

if 30 < subnet:
    print('no host')
else:
    first_host = num_to_ip(network + 1)
    last_host = num_to_ip(broadcast - 1)
    print('hosts:\t\t{}/{} <-> {}/{}'.format(first_host, subnet, last_host, subnet))
