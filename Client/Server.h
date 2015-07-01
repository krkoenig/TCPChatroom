#pragma once

#include <memory>
#include <SFML\Network.hpp>

#include "PacketManager.h"

// A server object represents a connection to an external server. Packets
// can be sent to the server and packets can be received from the server.
// A server contains a thread that constantly waits to receive from the
// server.

class Server
{
public:
	// A server must be located somewhere.
	Server(std::string ip);
	~Server();

	// Sends the server the given packet.
	void send(sf::Packet out);

	// Lets the program know if the server is connected to anything.
	bool isConnected() { return connected; };

private:
	// The TCP socket the client has connected from.
	std::unique_ptr<sf::TcpSocket> socket;

	// Handles input from the server.
	void receive();

	// Handles any packets received from the server.
	PacketManager pManage;

	// True if connected to server.
	bool connected;
};

