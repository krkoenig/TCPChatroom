#pragma once

#include <iostream>
#include <string>
#include <mutex>

// Outputs the given string to the console while using a static lock
// in order to prevent multiple threads from trying to access the cout
// stream at the same time.

static void output(std::string s)
{
	// Creates a single mutex to be used for every instance 
	// that this function is called.
	static std::mutex coutMutex;

	coutMutex.lock();
	std::cout << s;
	coutMutex.unlock();
}