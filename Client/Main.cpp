#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <SFML\Network.hpp>
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Widgets.hpp>

#include "Server.h"
#include "Output.h"

std::string username;

void input(Server& server)
{
	std::string s;
	std::getline(std::cin, s);
	Message m;
	m.username = username;
	m.text = s;
	sf::Packet p;
	p << "message" << m;
	server.send(p);
}

int main()
{
	// Create the sfgui object to abstract from SFML

	while (true) {
		// Extract the IP address of the server from the user
		std::string ip;
		output("Enter the IP address of the chat client: ");
		std::cin >> ip;

		// Skip any left over whitespace.
		std::cin.sync();

		Server server(ip);

		output("Enter a username: ");
		std::getline(std::cin, username);

		while (server.isConnected())
		{
			input(server);
		}
		output("\n");
		output("You have disconnected from the server.\n");
	}

	return 0;
}

