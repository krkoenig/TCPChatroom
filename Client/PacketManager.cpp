#include "PacketManager.h"
#include "Output.h"

#include <thread>

PacketManager::PacketManager(const bool& c):
connected(c)
{
}


PacketManager::~PacketManager()
{
}

void PacketManager::start()
{
	std::thread(&PacketManager::handlePackets, this).detach();
}

void PacketManager::handlePackets()
{
	while (connected)
	{
		if (!packetQueue.empty())
		{
			// Process the first packet in the queue if there is one
			sf::Packet in = popPacket();
			std::string type;
			in >> type;

			// Perform the appropriate function for each
			// type of message.
			if (type == "message")
			{
				messPack(in);
				
			}
		}
	}
}

void PacketManager::pushPacket(sf::Packet p)
{
	// Only one thread can access the packetqueue
	// at a time.
	packetMutex.lock();
	packetQueue.push(p);
	packetMutex.unlock();
}

sf::Packet PacketManager::popPacket()
{
	sf::Packet p;

	// Only one thread can access the packetqueue
	// at a time.
	packetMutex.lock();
	p = packetQueue.front();
	packetQueue.pop();
	packetMutex.unlock();

	return p;
}

void PacketManager::messPack(sf::Packet& in)
{
	Message mess;
	in >> mess;

	output(mess.username + ": " + mess.text + "\n");
}
