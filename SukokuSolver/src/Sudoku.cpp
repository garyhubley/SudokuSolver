
#include "Sudoku.h"
#include <sstream> 
#include "Utilities.h"

void Sudoku::ToSudoku( const std::string &str ) {
	size_t len = str.length();

	for( size_t i = 0; i < len; ++i ) {
		std::stringstream converter;
		converter << str[ i ];
		converter >> _puzzle[ i ];
	}

}

int Sudoku::isValid( int *set ) {

	bool missingValues[ NUMCELLVALUES ] = { true, true, true, true, true, true, true, true, true };


	// check if all numbers were found
	for( int element = 0; element < Sudoku::NUMCELLVALUES; ++element ) {
		int elementValue = set[ element ];
		int offByOneValue = elementValue - 1;

		if( elementValue != 0 ) {
			if( missingValues[ offByOneValue ] == false ) {
				// duplicate element
				DEBUG_PRINT( "  Duplicate value " << elementValue );
				return DUPLICATEVALUE;
			}
			missingValues[ offByOneValue ] = false;
		}
	}

	for( int element = 0; element < Sudoku::NUMCELLVALUES; ++element ) {
		if( missingValues[ element ] ) {
			DEBUG_PRINT( "  Missing at least one value." );
			return MISSINGVALUE;
		}
	}

	return VALID;
}

Sudoku::Sudoku( const std::string& str ) {
	ToSudoku( str );
}

Sudoku::Sudoku() {

}

Sudoku::~Sudoku() {

}

Sudoku::RowNum Sudoku::cellToRow( int cell ) {
	return static_cast< Sudoku::RowNum >( cell / 9 );
}

Sudoku::ColNum Sudoku::cellToCol( int cell ) {
	return static_cast< Sudoku::ColNum >( cell % 9 );
}

Sudoku::BoxNum Sudoku::cellToBox( int cell ) {
	return static_cast< Sudoku::BoxNum >( cell / 3 % 3 + cell / 27 * 3 );
}

///Rows are labeled 0-8 starting at the top
void Sudoku::getRow( RowNum rowNum, int *row ) {
	int *rowPtr = _puzzle + ( 9 * static_cast< int >( rowNum ) );

	for( int i = 0; i < NUMCELLVALUES; i++ ) {
		row[ i ] = rowPtr[ i ];
	}
}

///Cols are labeled 0-8 starting at the left
void Sudoku::getCol( ColNum colNum, int *col ) {
	int *colPtr = _puzzle + static_cast< int >( colNum );

	for( int i = 0; i < NUMCELLVALUES; i++ ) {
		col[ i ] = colPtr[ 9 * i ];
	}
}

///Boxes are labeled 0-8 starting at the top left
/// 0 | 1 | 2 
///-----------
/// 3 | 4 | 5
///-----------
/// 6 | 7 | 8
void Sudoku::getBox( BoxNum boxNum, int *box ) {
	// Arithmetic to get the first number in the box (top left corner)
	int *boxPtr = _puzzle + ( static_cast< int >( boxNum ) / 3 ) * 27 + ( static_cast< int >( boxNum ) % 3 ) * 3;

	// Arithmetic to get the values from the box.
	/********************************************/
	// This takes advantage of the floor property of integer math. DO NOT CHANGE!
	auto elementToCellNumber = []( int e ) { return ( e / 3 ) * 9 + e % 3; };

	for( int i = 0; i < COLSIZE; ++i ) {
		box[ i ] = boxPtr[ elementToCellNumber( i ) ];
	}

	DEBUG_PRINT_BOX( box );
}

int Sudoku::isValidRow( RowNum rowNum ) {
	int row[ NUMCELLVALUES ];
	getRow( rowNum, row );

	return isValid( row );
}

int Sudoku::isValidCol( ColNum colNum ) {
	int col[ NUMCELLVALUES ];
	getCol( colNum, col );

	return isValid( col );
}

int Sudoku::isValidBox( BoxNum boxNum ) {
	int box[ NUMCELLVALUES ];
	getBox( boxNum, box );

	return isValid( box );
}

/*      DEAD CODE           */
//void Sudoku::Possibilities() {
//
//	for( int cellnum = 0; cellnum < PUZZLESIZE; cellnum++ ) {
//		if( _puzzle[ cellnum ] != 0 ) {
//			// cell has been filled - no possibilities
//			_cellPossibilities[ cellnum ][ 0 ] = 0;
//		}
//		auto box = cellToBox( cellnum );
//		auto row = cellToRow( cellnum );
//		auto col = cellToCol( cellnum );
//
//		if( isValidBox( box ) == VALID &&
//			isValidRow( row ) == VALID &&
//			isValidCol( col ) == VALID ) {
//			// cell filled.
//		}
//
//
//	}
//}

bool Sudoku::backtrackSolve( int cell ) {

	if( cell >= PUZZLESIZE ) {
		std::cout << "SUDOKU SOLVED!!!" << std::endl;
		return true;
	}

	while( _puzzle[ cell ] != 0 ) {
		cell++;
	}

	for( int value = 1; value <= 9; ++value ) {
		_puzzle[ cell ] = value;

		DEBUG_PRINT( "\n\n" << *this );

		int validBox = isValidBox( cellToBox( cell ) );
		int validRow = isValidRow( cellToRow( cell ) );
		int validCol = isValidCol( cellToCol( cell ) );

		if( ( validBox == VALID || validBox == MISSINGVALUE ) &&
			( validRow == VALID || validRow == MISSINGVALUE ) &&
			( validCol == VALID || validCol == MISSINGVALUE ) ) {
			if( backtrackSolve( cell + 1 ) ) {
				return true;
			}
		}
	}
	_puzzle[ cell ] = 0;
	return false;
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

std::ostream &operator << ( std::ostream &out, const Sudoku::RowNum &num ) {
	return out << static_cast< int >( num );
}

std::ostream &operator << ( std::ostream &out, const Sudoku::ColNum &num ) {
	return out << static_cast< int >( num );
}

std::ostream &operator << ( std::ostream &out, const Sudoku::BoxNum &num ) {
	return out << static_cast< int >( num );
}
