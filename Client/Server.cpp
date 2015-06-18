#include "Server.h"
#include "Output.h"
#include <iostream>
#include <thread>

Server::Server() :
socket(new sf::TcpSocket())
{
	sf::Socket::Status status = socket->connect("127.0.0.1", 10993);
	if (status == sf::Socket::Done)
	{
		std::thread(&Server::receive, this).detach();
	}
	else
	{
		output("Unable to connect");
	}
}

Server::~Server()
{
	socket->disconnect();
}

void Server::receive()
{
	while (true)
	{
		sf::Packet in;
		if (socket->receive(in) != sf::Socket::Done)
		{
			// error...
		}

		pManage.pushPacket(in);
	}
}

void Server::send(sf::Packet out)
{
	socket->send(out);
}