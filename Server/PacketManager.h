#pragma once

#include "ClientManager.h"

#include <mutex>
#include <queue>
#include <SFML\Network.hpp>

class PacketManager
{
public:
	PacketManager();
	~PacketManager();

	void handlePacket(ClientManager& c);
private:
	sf::Packet compMessPack(sf::Packet in);
};

