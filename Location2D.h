#pragma once
#pragma
struct Location2D {
	//행 번호
	int row;
	//열 번호
	int col;

	//생성자, 디폴트 매개변수를 사용함, 좌표 객체의 초기화
	Location2D(int r = 0, int c = 0) { row = r; col = c; }

	/*  '위치 p'가 자신의 이웃인지 검사하는 함수
	true를 반환하면 이웃, false를 반환하면 이웃X  */
	bool isNeighbor(Location2D& p) {
		return (row == p.row && (col == p.col - 1 || col == p.col + 1))
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1));
	}

	//연산자 오버로딩을 사용해서 '위치p'가 자신과 같은 위치인지를 검사하는 함수
	bool operator==(Location2D& p) { return row == p.row && col == p.col; }
};