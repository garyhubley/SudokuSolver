#include "Sudoku.h"

#include <iostream>
#include <random>
#include <fstream>
#include <string> 
#include <sstream>

int main() {
	int level;
	//std::cout << "Select level (0-5): ";
	//std::cin >> level;
	std::ifstream puzzleFile;

	// Open file relative to the project directory
	puzzleFile.open( "Sudokus/Level0.txt" );
	if( !puzzleFile.is_open() ) {
		std::cerr << "Failed to open puzzle file. :(" << std::endl;
		std::cin.get();
		return 0;
	}

	std::random_device r;
	std::default_random_engine randomEngine( r() );
	std::uniform_int_distribution<int> uniform_dist( 1, 10000 );

	int puzzleNum = uniform_dist( randomEngine );
	std::cout << "PuzzNum: " << puzzleNum << std::endl;
	std::string line;
	for( int lineNum = 0; lineNum < puzzleNum; ++lineNum ) {
		puzzleFile >> line;
	}
	
	Sudoku puzzle( line );
	std::cout << "Puzz: " << std::endl << puzzle << std::endl;
	puzzle.isValidBox( Sudoku::BoxNum::B1 );
	for (int num = 0; num < Sudoku::ROWSIZE; num++ )
	{
		std::cout << "Row" << num + 1 << " is "
			<< ( puzzle.isValidRow( static_cast< Sudoku::RowNum >( num ) ) ? "valid.\n" : "invalid\n" );
		std::cout << "Col" << num + 1 << " is "
			<< ( puzzle.isValidCol( static_cast< Sudoku::ColNum >( num ) ) ? "valid.\n" : "invalid\n" );
	}
	std::cin.clear();
	std::cin.get();
}


