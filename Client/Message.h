#pragma once

#include <SFML\Network.hpp>

// A message constitutes a single text response sent from the client to 
// other members of the chat room. 
// TODO: Hold time of message being sent.
struct Message
{
public:
	std::string text;
	std::string username;

	Message();
	~Message();
};

// Operators for how to store a Message into a packet.
sf::Packet& operator << (sf::Packet& packet, const Message& message);
sf::Packet& operator >> (sf::Packet& packet, Message& message);