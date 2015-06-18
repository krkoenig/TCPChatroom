#include "ClientManager.h"

#include <thread>
#include <chrono>

ClientManager::ClientManager()
{
	output("Client Manager constructed...");

	std::thread(&ClientManager::listen, this).detach();
	std::thread(&ClientManager::receive, this).detach();
	std::thread(&ClientManager::ping, this).detach();
}


ClientManager::~ClientManager()
{
}

void ClientManager::listen()
{
	sf::TcpListener listener;
	unsigned short port = 10993;

	output("Listening...");

	if (listener.listen(port) != sf::Socket::Done)
	{
		//  error...
	}

	while (true)
	{
		std::unique_ptr<sf::TcpSocket> newSocket(new sf::TcpSocket);
		if (listener.accept(*newSocket) != sf::Socket::Done)
		{
			// error...
		}

		// Create a new client and add him to the list of clients.
		std::unique_ptr<Client> newClient(new Client(std::move(newSocket)));

		clientMutex.lock();
		clients.push_back(std::move(newClient));
		clientMutex.unlock();
	}
}

void ClientManager::receive()
{
	while (true)
	{
		clientMutex.lock();
		for (std::list<std::unique_ptr<Client>>::iterator it = clients.begin(); it != clients.end(); it++)
		{	
			packetMutex.lock();
			(*it)->receive(packetQueue);
			packetMutex.unlock();
		}
		clientMutex.unlock();

	}
}

void ClientManager::broadcast(sf::Packet out)
{
	clientMutex.lock();
	for (std::list<std::unique_ptr<Client>>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		(*it)->send(out);
	}
	clientMutex.unlock();
}

sf::Packet ClientManager::popPacket()
{
	packetMutex.lock();
	sf::Packet p = packetQueue.front();
	packetQueue.pop();
	packetMutex.unlock();

	return p;
}

void ClientManager::ping()
{
	while (true)
	{
		std::list<std::unique_ptr<Client>>::iterator it = clients.begin();
		clientMutex.lock();
		// Check if there are no clients
		while (it != clients.end())
		{
			if (!(*it)->ping())
			{
				it = clients.erase(it);
			}
			else
			{
				it++;
			}
		}
		clientMutex.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

bool ClientManager::hasPackets()
{
	return !packetQueue.empty();
}