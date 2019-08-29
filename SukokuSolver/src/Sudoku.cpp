#include "Sudoku.h"
#include "Utilities.h"

#include <sstream> 

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
	for( int element = 0; element < NUMCELLVALUES; ++element ) {
		int elementValue = set[ element ];
		int offByOneValue = elementValue - 1;

		if( elementValue != 0 ) {
			if( missingValues[ offByOneValue ] == false ) {
				// duplicate element
				//DEBUG_PRINT( "  Duplicate value " << elementValue );
				return DUPLICATEVALUE;
			}
			missingValues[ offByOneValue ] = false;
		}
	}

	for( int element = 0; element < NUMCELLVALUES; ++element ) {
		if( missingValues[ element ] ) {
			//DEBUG_PRINT( "  Missing at least one value." );
			return MISSINGVALUE;
		}
	}

	return VALID;
}

Sudoku::Sudoku( const std::string& str ) {
	ToSudoku( str );
}

Sudoku::~Sudoku() {
	// No memory management. 
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

	//DEBUG_PRINT_BOX( box );
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

int Sudoku::possibleCellValues( int cell, int *values ) {
	if( _puzzle[ cell ] != 0 ) {
		return 0;
	}
	int numValidValues = 0;

	for( int value = 1; value <= NUMCELLVALUES; ++value ) {
		if( isValuePossible( cell, value ) ) {
			values[ numValidValues ] = value;
			++numValidValues;
		}
	}
	return numValidValues;
}

bool Sudoku::isValuePossible( int cell, int value ) {

	_puzzle[ cell ] = value;

	bool result =
		isValidRow( cellToRow( cell ) ) != DUPLICATEVALUE &&
		isValidCol( cellToCol( cell ) ) != DUPLICATEVALUE &&
		isValidBox( cellToBox( cell ) ) != DUPLICATEVALUE;

	_puzzle[ cell ] = 0;

	return result;
}

/*void Sudoku::Possibilities() {
	std::vector<int>
	for( int cellnum = 0; cellnum < PUZZLESIZE; cellnum++ ) {
		if( _puzzle[ cellnum ] != 0 ) {
			// cell has been filled - no possibilities
			_cellPossibilities[ cellnum ][ 0 ] = 0;
		}
		auto box = cellToBox( cellnum );
		auto row = cellToRow( cellnum );
		auto col = cellToCol( cellnum );

		if( isValidBox( box ) == VALID &&
			isValidRow( row ) == VALID &&
			isValidCol( col ) == VALID ) {
			// cell filled.
		}


	}
}*/

bool Sudoku::backtrackSolve( int cell ) {

	if( cell >= PUZZLESIZE ) {
		std::cout << "SUDOKU SOLVED!!!" << std::endl;
		return true;
	}

	while( _puzzle[ cell ] != 0 ) {
		cell++;
	}

	for( int value = 1; value <= NUMCELLVALUES; ++value ) {
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

void Sudoku::penAndPaperSolve() {
	int sizeCellValues[ 81 ];
	int possibleValues[ 81 ][ 9 ];
	for( int i = 0; i < 81; ++i ) {
		for( int j = 0; j < 9; ++j ) {
			possibleValues[ i ][ j ] = 0;
		}
	}

	for( int cell = 0; cell < Sudoku::PUZZLESIZE; ++cell ) {
		sizeCellValues[ cell ] = possibleCellValues( cell, possibleValues[ cell ] );
	}

	for( int cell = 0; cell < Sudoku::PUZZLESIZE; ++cell ) {
		if( sizeCellValues[ cell ] == 1 ) {
			_puzzle[ cell ] = possibleValues[ cell ][ 0 ];
			possibleValues[ cell ][ 0 ] = 0;
			sizeCellValues[ cell ] = 0;

			//updateRowPossibilities( cellToRow( cell ) );
			int row = static_cast< int >( cellToRow( cell ) );
			int *rowPtr = possibleValues[ 9 * row ];

			for( int rowElement = 0; rowElement < NUMCELLVALUES; rowElement+=9 ) {
				rowPtr[ rowElement ];
			}

			// updateColPossibilities()
			// updateBoxPossibilities()
			cell = 0;
		}

	}

	for( int cell = 0; cell < Sudoku::PUZZLESIZE; ++cell ) {
		std::cout << "R" << cellToRow( cell ) << "C" << cellToCol( cell ) << ": \n  " <<
			sizeCellValues[ cell ] << ": ";

		for( int i = 0; i < sizeCellValues[ cell ]; ++i ) {
			std::cout << possibleValues[ cell ][ i ] << " ";
		}
		std::cout << "\n\n";
	}
}

std::ostream& operator<<( std::ostream& out, const Sudoku& sudoku ) {
	// The magic numbers in this function have been tested to work. Please don't change them.
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

