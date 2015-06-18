#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#include "Server.h"
#include "Output.h"

void input(Server& server)
{
		std::string s;
		std::getline(std::cin, s);
		Message m;
		m.username = "XXX";
		m.text = s;
		sf::Packet p;
		p << "message" << m;
		server.send(p);
}

int main()
{
	Server server;

	while (true)
	{
		input(server);
	}

	return 0;
}

