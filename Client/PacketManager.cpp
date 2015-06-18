#include "PacketManager.h"
#include "Output.h"

#include <thread>

PacketManager::PacketManager()
{
	std::thread(&PacketManager::handlePackets, this).detach();
}


PacketManager::~PacketManager()
{
}

void PacketManager::handlePackets()
{
	while (true)
	{
		if (!packetQueue.empty())
		{
			sf::Packet in = popPacket();
			std::string type;
			in >> type;

			if (type == "message")
			{
				Message m = unpackMessPack(in);
				output(m.username + ": " + m.text);
			}
		}
	}
}

void PacketManager::pushPacket(sf::Packet p)
{
	packetMutex.lock();
	packetQueue.push(p);
	packetMutex.unlock();
}

sf::Packet PacketManager::popPacket()
{
	sf::Packet p;
	packetMutex.lock();
	p = packetQueue.front();
	packetQueue.pop();
	packetMutex.unlock();

	return p;
}

Message PacketManager::unpackMessPack(sf::Packet& in)
{
	Message mess;
	in >> mess;
	return mess;
}
