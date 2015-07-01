#pragma once

#include <mutex>
#include <queue>
#include <SFML\Network.hpp>

#include "Message.h"

// A packetmanager controls all packets received fromt he server.
// Each packet is put into a queue where it is processed and printed.
// The queue processing happens on its own thread to allow input to
// be handled by the main thread.
class PacketManager
{
public:
	PacketManager(const bool& c);
	~PacketManager();

	// Adds a packet to the queue. Called by Server who gives the packets to the 
	// packetmanager.
	void pushPacket(sf::Packet p);

	// Starts the handling of packets.
	void start();

private:
	// Unpacks a message type packet and prints it to screen.
	void messPack(sf::Packet& in);

	// Removes the next packet in the queue when the mutex is unlocked.
	sf::Packet PacketManager::popPacket();

	// The queue where packets are placed and processed.
	// It has its own mutex since the packetmanager thread
	// and the server receiving thread both need to access it.
	std::queue<sf::Packet> packetQueue;
	std::mutex packetMutex;

	// Loops until a packet is available to pop and then calls the corresponding
	// function to handle the packet based on its type.
	void handlePackets();

	// A reference to whether the server is connected. Stop handling packets when the server
	// disconnects. A packetmanager can not change this value.
	const bool& connected;
};

