/*	
	A client holds and represents all relevant information 
	pertaining to a single client. 
*/

#pragma once

#include "Output.h"

#include <SFML\Network.hpp>
#include <queue>
#include <memory>
#include <list>

class Client
{
public:
	Client(std::unique_ptr<sf::TcpSocket> s);
	~Client();

	void receive(std::queue<sf::Packet>& packetQueue);
	void send(sf::Packet out);

	bool ping();

private:
	// The TCP socket the client has connected from.
	std::unique_ptr<sf::TcpSocket> socket;

	// The handle the client goes by.
	std::string username;
};

