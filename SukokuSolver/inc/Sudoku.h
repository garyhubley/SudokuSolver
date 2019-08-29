#pragma once

#include <string>

class Sudoku {
public:
	static const int NUMCELLVALUES = 9;
	static const int ROWSIZE = 9;
	static const int COLSIZE = 9;
	static const int PUZZLESIZE = 81;
	enum class RowNum:int { R1, R2, R3, R4, R5, R6, R7, R8, R9 };
	enum class ColNum:int { C1, C2, C3, C4, C5, C6, C7, C8, C9 };
	enum class BoxNum:int { B1, B2, B3, B4, B5, B6, B7, B8, B9 };
	enum Validation { VALID = 0, MISSINGVALUE, DUPLICATEVALUE };

private:
	int _puzzle[ PUZZLESIZE ];
	int _cellPossibilities[ PUZZLESIZE ][ 9 ] = { 0 };

	void ToSudoku( const std::string &str );

	int isValid( int *set );

public:
	Sudoku( const std::string &str );
	Sudoku();
	~Sudoku();

	static Sudoku::RowNum cellToRow( int cell );
	static Sudoku::ColNum cellToCol( int cell );
	static Sudoku::BoxNum cellToBox( int cell );

	void getRow( RowNum rowNum, int *row );
	void getCol( ColNum colNum, int *col );
	void getBox( BoxNum boxNum, int *box );

	int isValidRow( RowNum rowNum );
	int isValidCol( ColNum colNum );
	int isValidBox( BoxNum boxNum );
	void Possibilities();
	bool backtrackSolve( int cell );

	friend std::ostream &operator << ( std::ostream &out, const Sudoku &sudoku );
	friend std::ostream &operator << ( std::ostream &out, const RowNum &num );
	friend std::ostream &operator << ( std::ostream &out, const ColNum &num );
	friend std::ostream &operator << ( std::ostream &out, const BoxNum &num );
};

