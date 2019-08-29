#include "Sudoku.h"

#include <iostream>
#include <random>
#include <fstream>
#include <string> 
#include <sstream>
#include <iomanip>

int main(int argc, char **argv) {
	int level;
	//std::cout << "Select level (0-5): ";
	//std::cin >> level;
	std::ifstream puzzleFile;

	// Open file relative to the project directory
	
	
	// TODO: Create argument parser
	std::string fileName;

#ifdef _DEBUG
	fileName = "Sudokus/Level0.txt";
#else
	if( argc < 2 ) {
		std::cout << "No file provided, default file opened\n";
		fileName = "Sudokus/Level0.txt";
	} else {
		fileName = argv[ 1 ];
	}
#endif
	puzzleFile.open( fileName );

	if( !puzzleFile.is_open() ) {
		std::cerr << "Failed to open puzzle file. :(" << std::endl;
		std::cin.get();
		return 0;
	}

	std::random_device r;
	std::default_random_engine randomEngine( r() );
	std::uniform_int_distribution<int> uniform_dist( 1, 10000 );

	int puzzleNum = uniform_dist( randomEngine );
	std::cout << "Puzzle " << puzzleNum << " selected from " << fileName << std::endl;
	
	std::string line;
	for( int lineNum = 0; lineNum < puzzleNum; ++lineNum ) {
		puzzleFile >> line;
	}

	Sudoku puzzle( line );

	std::cout << "Puzz: " << std::endl << puzzle << std::endl;
	puzzle.backtrackSolve( 0 );
	std::cout << std::endl << puzzle << std::endl << "Goodbye!";

	std::cin.clear();
	std::cin.get();
}


