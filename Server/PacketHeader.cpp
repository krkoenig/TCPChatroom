#include "PacketHeader.h"

PacketHeader::PacketHeader()
{
}

PacketHeader::~PacketHeader()
{
}

sf::Packet& operator << (sf::Packet& packet, const PacketHeader& header)
{
	return packet << header.numMessage << header.numEvent;
}

sf::Packet& operator >> (sf::Packet& packet, PacketHeader& header)
{
	return packet >> header.numMessage >> header.numEvent;
}