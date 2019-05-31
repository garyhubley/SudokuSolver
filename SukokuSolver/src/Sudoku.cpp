
#include "Sudoku.h"
#include <sstream> 
#include "Utilities.h"

Sudoku::Sudoku( const std::string& str ) {
	ToSudoku( str );
}

Sudoku::Sudoku() {

}

Sudoku::~Sudoku() {

}

bool Sudoku::isValidRow( RowNum rowNum ) {
	bool rowNumbersPresent[ 9 ]{ false };
	int *row = _puzzle + ( 9 * static_cast< int >( rowNum ) );

	for( int element = 0; element < ROWSIZE; ++element ) {
		int elementValue = row[ element ];
		if( elementValue != 0 && rowNumbersPresent[ elementValue - 1 ] == true ) {
			// duplicate row element. return false;
			DEBUG_PRINT( "Duplicate element in row" );
			return false;
		}
		rowNumbersPresent[ elementValue - 1 ] = true;
	}

	// check if all numbers were found
	for( int element = 0; element < ROWSIZE; ++element ) {
		if( rowNumbersPresent[ element ] == false ) {
			// missing a number in a row. return false;
			return false;
		}
	}

	return true;
}

bool Sudoku::isValidCol( ColNum colNum ) {
	//bool rowNumbersPresent[ 9 ]{ false };
	//int *row = _puzzle + ( 9 * static_cast< int >( rowNum ) );

	//for( int element = 0; element < ROWSIZE; ++element ) {
	//	int elementValue = row[ element ];
	//	if( elementValue != 0 && rowNumbersPresent[ elementValue - 1 ] == true ) {
	//		// duplicate row element. return false;
	//		DEBUG_PRINT( "Duplicate element in row" );
	//		return false;
	//	}
	//	rowNumbersPresent[ elementValue - 1 ] = true;
	//}

	//// check if all numbers were found
	//for( int element = 0; element < ROWSIZE; ++element ) {
	//	if( rowNumbersPresent[ element ] == false ) {
	//		// missing a number in a row. return false;
	//		return false;
	//	}
	//}

	return true;
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


