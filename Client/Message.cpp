#include "Message.h"

Message::Message()
{
}

Message::~Message()
{
}

sf::Packet& operator << (sf::Packet& packet, const Message& message)
{
	return packet << message.username << message.text;
}

sf::Packet& operator >> (sf::Packet& packet, Message& message)
{
	return packet >> message.username >> message.text;
}