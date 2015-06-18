/*	
	Chatroom using TCP and SFML
	Kyle Koenig
*/

#include "ClientManager.h"
#include "PacketManager.h"
#include "Output.h"

#include <string>
#include <thread>
#include <chrono>

int main()
{
	ClientManager clients;
	PacketManager packets;

	while (true)
	{
		packets.handlePacket(clients);
	}

	return 0;
}