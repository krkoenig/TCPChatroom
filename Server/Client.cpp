#include "Client.h"

#include <thread>
#include <chrono>

Client::Client(std::unique_ptr<sf::TcpSocket> s)
{
	socket = std::move(s);
	socket->setBlocking(false);

	output("New Connection at " + socket->getRemoteAddress().toString() + ":" + std::to_string(socket->getLocalPort()));
}

Client::~Client()
{
	output("Disconnection at " + socket->getRemoteAddress().toString() + ":" + std::to_string(socket->getLocalPort()));
	socket->disconnect();
}

void Client::receive(std::queue<sf::Packet>& packetQueue)
{
		sf::Packet p;
		if (socket->receive(p) == sf::Socket::Done)
		{
			packetQueue.push(p);
		}
		else
		{
			// error
		}
}

void Client::send(sf::Packet out)
{
	if (socket->send(out) != sf::Socket::Done)
	{
		// error
	}
}

bool Client::ping()
{
	sf::Packet ping;
	ping << "ping";
	return socket->send(ping) == sf::Socket::Done;
}
