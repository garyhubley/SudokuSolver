
#include "Sudoku.h"

bool isValidRow( Sudoku puzzle, RowNum rowNum ) {
	bool rowNumbersPresent[ 9 ]{ false };
	int *row = puzzle + ( 9 * static_cast< int >( rowNum ) );

	
	for( int element = 0; element < ROWSIZE; ++element ) {
		if( rowNumbersPresent[ row[element] ] == true ) {
			// duplicate row element. return false;
			return false;
		}
		rowNumbersPresent[ element ] = true;
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