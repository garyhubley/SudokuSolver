#pragma once

#include <sstream>
#include <iostream>

inline void DEBUG_PRINT( const std::string &str )
{
#ifdef _DEBUG
	std::cerr << str << std::endl;
#endif

}