
#include "Sudoku.h"
#include <sstream> 

Sudoku::Sudoku( const std::string& str ) {
	ToSudoku( str );
}

Sudoku::Sudoku() {

}

Sudoku::~Sudoku() {

}

void Sudoku::ToSudoku( const std::string &str ) {
	size_t len = str.length();
	
	for( size_t i = 0; i < len; ++i ) {
		std::stringstream converter; 
		converter << str[ i ];
		converter >> _puzzle[ i ];
	}

}

std::ostream& operator<<( std::ostream& out, const Sudoku& sudoku ) {
	for( int i = 0; i < Sudoku::COLSIZE; ++i ) {
		for( int j = 0; j < 3; ++j ) {
			out << sudoku._puzzle[ i * 9 + j ] << " ";
		}
		out << "| ";
		for( int j = 3; j < 6; ++j ) {
			out << sudoku._puzzle[ i * 9 + j ] << " ";
		}
		out << "| ";
		for( int j = 6; j < 9; ++j ) {
			out << sudoku._puzzle[ i * 9 + j ] << " ";
		}
		out << std::endl;
		if( i != 8 && i % 3 == 2 ) {
			for( int j = 0; j < 21; ++j ) {
				out << "-";
			}

			out << std::endl;
		}
	}
	return out;
}


