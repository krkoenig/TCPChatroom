#pragma once

#include <SFML\Network.hpp>

struct PacketHeader
{
public:
	int numMessage;
	int numEvent;

	PacketHeader();
	~PacketHeader();
};

sf::Packet& operator << (sf::Packet& packet, const PacketHeader& header);

sf::Packet& operator >> (sf::Packet& packet, PacketHeader& header);