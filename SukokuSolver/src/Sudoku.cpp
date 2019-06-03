
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

		if( elementValue != 0 ) {
			if( rowNumbersPresent[ elementValue - 1 ] == true ) {
			// duplicate row element. return false;
				DEBUG_PRINT( "Duplicate element in row" );
				return false;
			}
			rowNumbersPresent[ elementValue - 1 ] = true;
		}
	}

	// check if all numbers were found
	for( int element = 0; element < ROWSIZE; ++element ) {
		if( rowNumbersPresent[ element ] == false ) {
			// missing a number in a row. return false;
			DEBUG_PRINT( "Missing element in row" );
			return false;
		}
	}

	return true;
}

bool Sudoku::isValidCol( ColNum colNum ) {
	bool colNumbersPresent[ 9 ]{ false };
	int *col = _puzzle + static_cast< int >( colNum );

	for( int element = 0; element < COLSIZE; ++element ) {
		int elementValue = col[ element * 9 ];
		if( elementValue != 0 ) {
			if( colNumbersPresent[ elementValue - 1 ] == true ) {
			// duplicate col element. return false;
				DEBUG_PRINT( "Duplicate element in col" );
				return false;
			}
			colNumbersPresent[ elementValue - 1 ] = true;
		}
	}

	// check if all numbers were found
	for( int element = 0; element < ROWSIZE; ++element ) {
		if( colNumbersPresent[ element ] == false ) {
			// missing a number in a row. return false;
			DEBUG_PRINT( "Missing element in col" );
			return false;
		}
	}

	return true;
}

bool Sudoku::isValidBox( BoxNum boxNum ) {
	bool boxNumbersPresent[ 9 ]{ false };
	int *box = _puzzle;// +static_cast< int >( colNum );

	for( int i = 0; i < 9; i++ ) {
		int idx = ( i / 3 ) * 27 + ( i % 3 ) * 3;
		std::cout << "index: " << idx << "\nElement: " << *( box + idx ) << std::endl;
	}
	//for( int element = 0; element < COLSIZE; ++element ) {
	//	int elementValue = col[ element * 9 ];
	//	if( elementValue != 0 ) {
	//		if( colNumbersPresent[ elementValue - 1 ] == true ) {
	//		// duplicate col element. return false;
	//			DEBUG_PRINT( "Duplicate element in col" );
	//			return false;
	//		}
	//		colNumbersPresent[ elementValue - 1 ] = true;
	//	}
	//}

	//// check if all numbers were found
	//for( int element = 0; element < ROWSIZE; ++element ) {
	//	if( colNumbersPresent[ element ] == false ) {
	//		// missing a number in a row. return false;
	//		DEBUG_PRINT( "Missing element in col" );
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


