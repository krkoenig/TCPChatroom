#pragma once

#include "Message.h"

#include <mutex>
#include <queue>
#include <SFML\Network.hpp>

class PacketManager
{
public:
	PacketManager();
	~PacketManager();

	void pushPacket(sf::Packet p);

private:
	Message unpackMessPack(sf::Packet& in);

	sf::Packet PacketManager::popPacket();

	std::queue<sf::Packet> packetQueue;
	std::mutex packetMutex;

	void handlePackets();
};

