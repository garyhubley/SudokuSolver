#pragma once

#include <sstream>
#include <iostream>

#ifdef _DEBUG
#define DEBUG_PRINT( x ) std::cerr << x << std::endl;
#define DEBUG_PRINT_BOX( box )                           \
	for( int row = 0; row < 3; ++row ) {                 \
		for( int col = 0; col < 3; ++col ) {             \
			std::cerr << boxPtr[ col + row * 3 ] << " "; \
		}                                                \
	std::cerr << std::endl;                              \
	}

#else
#define DEBUG_PRINT( x ) do {} while(0);
#define DEBUG_PRINT_BOX( box ) do {} while(0);          

#endif // _DEBUG

