#pragma once

#include <memory>
#include <SFML\Network.hpp>

#include "PacketManager.h"

class Server
{
public:
	Server();
	~Server();

	void send(sf::Packet out);

private:
	// The TCP socket the client has connected from.
	std::unique_ptr<sf::TcpSocket> socket;

	void receive();

	PacketManager pManage;
};

