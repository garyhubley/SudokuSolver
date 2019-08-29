#include "Utilities.h"

#include <string> 
#include <random>
#include <fstream>

static const int charsPerLine = 83;

int randomIntUniform( int low, int high ) {
	std::random_device r;
	std::default_random_engine randomEngine( r() );
	std::uniform_int_distribution<int> uniform_dist( low, high );

	return uniform_dist( randomEngine );
}

std::string getPuzzleString( std::ifstream &puzzleFile, int puzzleNumber ) {

	std::string line;
	puzzleFile.seekg( charsPerLine * puzzleNumber );

	puzzleFile >> line;
	return line;
}