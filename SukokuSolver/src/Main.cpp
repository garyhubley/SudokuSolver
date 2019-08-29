#include "Sudoku.h"
#include "Utilities.h"

#include <iostream>
#include <fstream>
#include <string> 

int main( int argc, char **argv ) {

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
	// Open file relative to the project directory
	std::ifstream puzzleFile( fileName );

	if( !puzzleFile.is_open() ) {
		std::cerr << "Failed to open puzzle file. :(" << std::endl;
		std::cin.get();
		return 0;
	}

	int puzzleNum = randomIntUniform( 0, 9999 );

	std::cout << "Puzzle " << puzzleNum << " selected from " << fileName << std::endl;

	Sudoku puzzle( getPuzzleString( puzzleFile, puzzleNum ) );

	std::cout << "Puzz: " << std::endl << puzzle << std::endl;

	if( puzzle.backtrackSolve( 0 ) ) {
		std::cout << std::endl << puzzle;
	} else {
		std::cout << std::endl << "This puzzle is unsolvable :(";
	}
	
	std::cout << std::endl << "Goodbye!";
	
	puzzleFile.close();

	std::cin.clear();
	std::cin.get();
}


