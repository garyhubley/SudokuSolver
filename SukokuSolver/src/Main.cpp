#include "Sudoku.h"

#include <iostream>
#include <random>
#include <fstream>
#include <string> 
#include <sstream>

Sudoku stringToSudoku( const std::string &str, Sudoku puzzle );

int main() {
	int level;
	int puzzle[81];
	//std::cout << "Select level (0-5): ";
	//std::cin >> level;
	std::ifstream puzzleFile;
	
	// Open file relative to the project directory
	puzzleFile.open( "Sudokus/Solved.txt" );
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
	std::cout << "Puzz: " << line << std::endl;
	stringToSudoku( line, puzzle );

	std::cout << "Printing as int: " << std::endl;
	for( int i = 0; i < 81; i++ ) {
		std::cout << puzzle[ i ];
	}
	std::cin.clear();
	std::cin.get();
}

Sudoku stringToSudoku( const std::string &str, Sudoku puzzle ) {
	size_t len = str.length();
	std::stringstream converter;
	
	for( size_t i = 0; i < len; ++i ) {
		converter << str[ i ];
		converter >> puzzle[ i ];
	}
	return puzzle;
}

void SudokuPrint