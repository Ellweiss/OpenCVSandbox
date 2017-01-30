#pragma once

#include <iostream>

namespace Sandbox
{

inline bool Error(const char* msg)
{
	std::cerr << "Error: " << msg << std::endl;

	return false;
}

}