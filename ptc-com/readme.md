# Protocol communication

This source to packet data before send out

# Format

| HEADER | LENGTH | DATA[n] | TRAILER | CHECKSUM |
|--------|--------|---------|---------|----------|

HEADER: Start of packet.

LENGTH: Data length, number of byte.

DATA: Data, byte array

TRAILDER: End of packet.

CHECKSUM: validate packet.

