/*
	The ClientManager handles all connections and listens for 
	new ones and terminates old ones.
*/

#pragma once

#include <list>
#include <mutex>
#include <memory>
#include <queue>

#include "Client.h"

#include "Output.h"

class ClientManager
{
public:
	ClientManager();
	~ClientManager();

	sf::Packet popPacket();

	// Sends a packet to all clients
	void broadcast(sf::Packet out);

	bool hasPackets();

private:
	// A list of all connected clients
	std::list<std::unique_ptr<Client>> clients;
	// Locks client to prevent client disconnection and connections from
	// interfering with one another from across threads.
	std::mutex clientMutex;

	std::queue<sf::Packet> packetQueue;
	std::mutex packetMutex;
	
	// Listens for new connections
	void listen();

	void receive();

	void ping();	
};

