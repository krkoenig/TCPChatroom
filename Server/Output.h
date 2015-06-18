#pragma once

#include <iostream>
#include <string>
#include <mutex>

static void output(std::string s)
{
	static std::mutex coutMutex;

	coutMutex.lock();
	std::cout << s << std::endl;
	coutMutex.unlock();
}