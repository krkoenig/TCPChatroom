#pragma once

#include <SFML\Network.hpp>

struct Message
{
public:
	std::string text;
	std::string username;

	Message();
	~Message();
};

sf::Packet& operator << (sf::Packet& packet, const Message& message);

sf::Packet& operator >> (sf::Packet& packet, Message& message);