#pragma once

#include <iostream>
#include <string>
#include <mutex>

static std::mutex coutMutex;

static void output(std::string s)
{
	coutMutex.lock();
	std::cout << s << std::endl;
	coutMutex.unlock();
}