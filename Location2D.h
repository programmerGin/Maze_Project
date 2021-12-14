#pragma once 
#include <stdio.h>
struct Location2D {
	int  row;
	int  col;
	Location2D(int r = 0, int c = 0) { row = r; col = c; }
	bool isNeighbor(Location2D& p) {//�ڱ� �̿��� p���� �˻�
		return ((row == p.row && (col == p.col - 1 || col == p.col + 1))
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1)));
	}
	bool operator==(Location2D& p) { return row == p.row && col == p.col; }//�����ڿ����ε��� ����Ͽ� p�� �ڱ��ڽ��� ������ġ���� �˻�.
	void print() { printf("(%2d,%2d) ", row, col); }
};