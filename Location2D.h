#pragma once 
#include <stdio.h>
struct Location2D {
	int  row;
	int  col;
	Location2D(int r = 0, int c = 0) { row = r; col = c; }
	bool isNeighbor(Location2D& p) {//자기 이웃이 p인지 검사
		return ((row == p.row && (col == p.col - 1 || col == p.col + 1))
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1)));
	}
	bool operator==(Location2D& p) { return row == p.row && col == p.col; }//연산자오버로딩을 사용하여 p와 자기자신이 같은위치인지 검사.
	void print() { printf("(%2d,%2d) ", row, col); }
};