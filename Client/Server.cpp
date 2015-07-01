#include "Server.h"
#include "Output.h"
#include <thread>

Server::Server(std::string ip) :
socket(new sf::TcpSocket()),
pManage(connected)
{
	// By default the program uses port 10993.
	// TODO: Make a port number be part of the input.
	sf::Socket::Status status = socket->connect(ip, 10993);

	//  If the socket successfully connected, start waiting to
	// receive from the server.
	if (status == sf::Socket::Done)
	{
		connected = true;
		
		// Start the receiving thread and the packet handling threads.
		std::thread(&Server::receive, this).detach();
		pManage.start();
	}
	else
	{
		connected = false;
		output("Unable to connect\n");
	}
}

Server::~Server()
{
	// When the program ends, or a server disconnects.
	socket->disconnect();
}

void Server::receive()
{
	// The thread ends if the server stops being connected.
	while (isConnected())
	{
		sf::Packet in;
		if (socket->receive(in) != sf::Socket::Done)
		{
			// The server has disconnected.
			connected = false;
		}
		else 
		{
			// Add the received packet to be handled by the packet manager.
			pManage.pushPacket(in);
		}
	}
}

void Server::send(sf::Packet out)
{
	if (socket->send(out) != sf::Socket::Done)
	{
		// The server has disconnected.
		connected = false;
	}
}