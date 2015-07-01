#include "PacketManager.h"
#include "PacketHeader.h"
#include "Message.h"

#include <thread>

PacketManager::PacketManager()
{

}


PacketManager::~PacketManager()
{
}

void PacketManager::handlePacket(ClientManager& c)
{
	if (c.hasPackets())
	{
		sf::Packet in = c.popPacket();
		std::string type;
		in >> type;

		if (type == "message")
		{
			c.broadcast(compMessPack(in));
		}
	}
}

sf::Packet PacketManager::compMessPack(sf::Packet in)
{
	Message mess;
	in >> mess;

	output(mess.username + ": " + mess.text + "\n");

	sf::Packet out;
	out << "message" << mess;
	return out;
}