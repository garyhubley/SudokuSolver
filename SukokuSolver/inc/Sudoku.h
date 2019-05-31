#pragma once

#include <string>

class Sudoku {
public:
	static const int ROWSIZE = 9;
	static const int COLSIZE = 9;
	static const int PUZZLESIZE = 81;
	enum class RowNum:int { R1, R2, R3, R4, R5, R6, R7, R8, R9 };
	enum class ColNum:int { C1, C2, C3, C4, C5, C6, C7, C8, C9 };
private:
	int _puzzle[ PUZZLESIZE ];

	void ToSudoku( const std::string &str );
public:
	Sudoku( const std::string &str );
	Sudoku();
	~Sudoku();

	bool isValidRow( RowNum rowNum );
	bool isValidCol( ColNum colNum );

	friend std::ostream &operator << ( std::ostream &out, const Sudoku &sudoku );
};

