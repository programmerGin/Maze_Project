#pragma once
#pragma
struct Location2D {
	//�� ��ȣ
	int row;
	//�� ��ȣ
	int col;

	//������, ����Ʈ �Ű������� �����, ��ǥ ��ü�� �ʱ�ȭ
	Location2D(int r = 0, int c = 0) { row = r; col = c; }

	/*  '��ġ p'�� �ڽ��� �̿����� �˻��ϴ� �Լ�
	true�� ��ȯ�ϸ� �̿�, false�� ��ȯ�ϸ� �̿�X  */
	bool isNeighbor(Location2D& p) {
		return (row == p.row && (col == p.col - 1 || col == p.col + 1))
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1));
	}

	//������ �����ε��� ����ؼ� '��ġp'�� �ڽŰ� ���� ��ġ������ �˻��ϴ� �Լ�
	bool operator==(Location2D& p) { return row == p.row && col == p.col; }
};