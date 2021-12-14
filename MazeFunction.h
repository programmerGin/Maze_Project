#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Link.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Maze
{ 
	char** map = NULL;
	int width;
	int height;
	char** stackMap = NULL;
	char** queueMap = NULL;


	LinkedQueue queue;
	LinkedStack stack;

public:

	Maze() { init(0, 0); }
	~Maze() { reset(); }

	void init(int w, int h) 
	{
		map = new char* [h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}

	void reset()
	{
		for (int i = 0; i < height; i++)
			delete[]map[i];
		delete[]map;
	}

	bool isValidLoc(int r, int c)
	{//r,c가 0보다 작거나 height, width보다 값이 크면 false
		if (r < 0 || c < 0 || r >= height || c >= width) return false;
		else return map[r][c] == '0' || map[r][c] == 'x';
	}



	void roadFile(const char* filename, int num)
	{
		char c;
		ifstream fp(filename);
		if (fp.fail())
			printf("Error: 파일이 존재하지 않습니다.");

		FILE* fd = fopen(filename, "r");
		int word = 0;
		height = 1;
		width = 0;
		while ((c = getc(fd)) != EOF) {
			if (c == '\n') height++;
			if (c == '0' || c == '1' || c == 'e' || c == 'x')
			{
				word++;
			}
		}
		width = word / height;
		init(width, height);

		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				fp >> c;
				map[i][z] = c;

				
				if (map[i][z] == 'e')//e는 시작
				{//entry 입구
					Location2D entry(i, z);
					if (num == 1)
						stack.push(new Node(i, z)); //입구 push
					else if (num == 2 || num == 3)
						queue.enqueue(new Node(i, z));
					else if (num == 4)
					{
						stack.push(new Node(i, z));
						queue.enqueue(new Node(i, z));
					}
				}
			}
		}
		fp.close();
	}
	// ==================파일로 맵 가져오기=============================================
	
	//미로 화면에 출력
	void printMap() {
		printf("\n\n  [ Map ]\n\n");
		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				if (map[i][z] == '0') //미로
				{
					cout << "  ";
				}
				else if (map[i][z] == '1') //벽
				{
					cout << "▣";
				}
				else if (map[i][z] == 'e') //입구
				{
					cout << "☞";
				}
				else if (map[i][z] == 'x') //출구
				{
					cout << "♨";
				}
				else if (map[i][z] == '.') //방문했던곳
				{
					cout << "♪";
				}

			}
			cout << endl;
		}
		cout << endl;
	}

	int E_key()
	{
		int key;
		key = _getch();
		if (key == 13)
		{
			return key;
		}
		else if (key == 224)
		{
			return _getch();
		}
		return 0;
	}

	void printDFS()
	{
		roadFile("Maze.txt", 1);
		printf("DFS~\n");
		while (stack.isEmpty() == false) {
			Location2D* here = stack.peek();
			stack.pop();
			int r = here->row;
			int c = here->col;
			printf("(%d,%d)-> ", r, c);
			if (map[r][c] == 'x') {
				return;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) stack.push(new Node(r - 1, c));
				if (isValidLoc(r + 1, c)) stack.push(new Node(r + 1, c));
				if (isValidLoc(r, c - 1)) stack.push(new Node(r, c - 1));
				if (isValidLoc(r, c + 1)) stack.push(new Node(r, c + 1));
			}
		}
	}
	void printBFS()
	{
		roadFile("Maze.txt", 2);
		printf("BFS~\n");
		while (queue.isEmpty() == false) {
			Location2D* here = queue.peek();
			queue.dequeue();
			int r = here->row;
			int c = here->col;
			printf("(%d,%d)-> ", r, c);
			if (map[r][c] == 'x') {
				return;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) queue.enqueue(new Node(r - 1, c));
				if (isValidLoc(r + 1, c)) queue.enqueue(new Node(r + 1, c));
				if (isValidLoc(r, c - 1)) queue.enqueue(new Node(r, c - 1));
				if (isValidLoc(r, c + 1)) queue.enqueue(new Node(r, c + 1));
			}
		}
	}
	//==================위치출력================================
	void queue_SearchExit()//BFS 너비우선탐색
	{
		int count = 0;
		while (queue.isEmpty() == false) 
		{
			printMap();
			if (E_key() == 13)
			{
				system("cls");

				Location2D* here = queue.peek(); 
				queue.dequeue(); 
				count++;
				int r = here->row;
				int c = here->col;

				printf("현재위치: (%d,%d) \n", r, c);

				if (map[r][c] == 'x') { 
					system("cls");
					printf("\n>>>탐색완료.>>> \n");
					printf("=====[ 결과]=====\n");
					printf("dequeue %d번 \n", count);
					
					printMap();
					return;
				}
				else if (map[r][c] != '.')
				{
					map[r][c] = '.';
					if (isValidLoc(r - 1, c)) queue.enqueue(new Node(r - 1, c));
					if (isValidLoc(r + 1, c)) queue.enqueue(new Node(r + 1, c));
					if (isValidLoc(r, c - 1)) queue.enqueue(new Node(r, c - 1));
					if (isValidLoc(r, c + 1)) queue.enqueue(new Node(r, c + 1));
				}
			}
		}
		printf("미로 탐색 실패\n");
	}

	

	
	void stack_Search()	//DFS 깊이우선 탐색
	{
		int count=0;
		while (stack.isEmpty() == false) {	
			printMap();
			if (E_key() == 13) {
				system("cls");
				Node* here = stack.peek();
				stack.pop();

				int r = here->row;
				int c = here->col;
				count++;
				printf("현재위치: (%d,%d) ", r, c);

				if (map[r][c] == 'x')
				{
					system("cls");
					printf("\n>>>탐색완료.>>> \n");
					printf("=====[ 결과]=====\n");
					printf("pop %d번 \n", count);
					
					
					printMap();
					return;
				}
				else {
					map[r][c] = '.';
					if (isValidLoc(r - 1, c)) stack.push(new Node(r - 1, c));
					if (isValidLoc(r + 1, c)) stack.push(new Node(r + 1, c));
					if (isValidLoc(r, c - 1)) stack.push(new Node(r, c - 1));
					if (isValidLoc(r, c + 1)) stack.push(new Node(r, c + 1));
				}
			}
		}
		printf("미로 탐색 실패\n");
	}

//=======================비교하기==========================================

void compare_init(int w, int h)
{
	stackMap = new char* [h];
	queueMap = new char* [h];
	for (int i = 0; i < h; i++)
	{
		stackMap[i] = new char[w];
		queueMap[i] = new char[w];
	}
}

void compare_reset()
{
	for (int i = 0; i < height; i++)
	{
		delete[]stackMap[i];
		delete[]queueMap[i];
	}
	delete[]stackMap;
	delete[]queueMap;
}

bool stack_isValidLoc(int sr, int sc)
{
	if (sr < 0 || sc < 0 || sr >= height || sc >= width) return false;
	else return stackMap[sr][sc] == '0' || stackMap[sr][sc] == 'x';
}

bool queue_isValidLoc(int qr, int qc)
{
	if (qr < 0 || qc < 0 || qr >= height || qc >= width) return false;
	else return queueMap[qr][qc] == '0' || queueMap[qr][qc] == 'x';
}

void compare_roadMap(const char* filename)
{
	char c;
	ifstream fp(filename);
	if (fp.fail())
		printf("Error: 파일이 존재하지 않습니다.");

	//미로 크기 계산
	FILE* fd = fopen(filename, "r");
	int word = 0;
	height = 1;
	width = 0;
	while ((c = getc(fd)) != EOF) {
		if (c == '\n') height++;
		if (c == '0' || c == '1' || c == 'e' || c == 'x')
		{
			word++;
		}
	}
	width = word / height;

	compare_init(width, height);

	for (int i = 0; i < height; i++)
	{
		for (int z = 0; z < width; z++)
		{
			fp >> c;
			queueMap[i][z] = c;
			stackMap[i][z] = c;

			if (queueMap[i][z] == 'e') //입구 위치
			{
				stack.push(new Node(i, z));
				queue.enqueue(new Node(i, z));
			}
		}
	}
	fp.close();
}
void comparePrintMap() {
	printf("\n\n  [ StackMap ]\n\n");
	for (int i = 0; i < height; i++)
	{
		for (int z = 0; z < width; z++)
		{
			if (stackMap[i][z] == '0') //미로
			{
				cout << "  ";
			}
			else if (stackMap[i][z] == '1') //벽
			{
				cout << "▣";
			}
			else if (stackMap[i][z] == 'e') //입구
			{
				cout << "☞";
			}
			else if (stackMap[i][z] == 'x') //출구
			{
				cout << "♨";
			}
			else if (stackMap[i][z] == '.') //방문했던 곳
			{
				cout << "♪";
			}

		}
		cout << endl;
	}
	cout << endl;
	printf("\n\n  [ QueueMap ]\n\n");
	for (int i = 0; i < height; i++)
	{
		for (int z = 0; z < width; z++)
		{
			if (queueMap[i][z] == '0') //미로
			{
				cout << "  ";
			}
			else if (queueMap[i][z] == '1') //벽
			{
				cout << "▣";
			}
			else if (queueMap[i][z] == 'e') //입구
			{
				cout << "☞";
			}
			else if (queueMap[i][z] == 'x') //출구
			{
				cout << "♨ ";
			}
			else if (queueMap[i][z] == '.') //방문했던곳
			{
				cout << "♪";
			}

		}
		cout << endl;
	}
	cout << endl;
}
void compare()
{
	int stackCount = 0;
	int queueCount = 0;
	while (1)
	{
		comparePrintMap();
		Sleep(100);//속도

		if (queue.isEmpty() == true && stack.isEmpty() == true)
		{
			printf("\n>>>탐색완료.>>> \n");
			printf("=====[ 결과]=====\n");
			printf("POP %d회, DEQUEUE %d회 \n", stackCount, queueCount);
			if (stackCount > queueCount)
				printf("BFS가 더 빠릅니다.\n");
			else if (stackCount < queueCount)
				printf("DFS가 더 빠릅니다.\n");
			else if (stackCount == queueCount)
				printf("DFS와 BFS가 동시에 도착했습니다.\n");


			return;
		}

		if (stack.isEmpty() == false)
		{
			Location2D* hereStack = stack.peek();
			stack.pop();
			int sr = hereStack->row;
			int sc = hereStack->col;
			stackCount++;

			if (stackMap[sr][sc] == 'x')
			{
				while (stack.isEmpty() == false)
					stack.pop();
			}
			else if (stackMap[sr][sc] != '.')
			{
				stackMap[sr][sc] = '.';
				if (stack_isValidLoc(sr - 1, sc)) stack.push(new Node(sr - 1, sc));
				if (stack_isValidLoc(sr + 1, sc)) stack.push(new Node(sr + 1, sc));
				if (stack_isValidLoc(sr, sc - 1)) stack.push(new Node(sr, sc - 1));
				if (stack_isValidLoc(sr, sc + 1)) stack.push(new Node(sr, sc + 1));
			}
		}
		if (queue.isEmpty() == false)
		{
			Location2D* hereQueue = queue.peek();
			queue.dequeue();
			int qr = hereQueue->row;
			int qc = hereQueue->col;
			queueCount++;


			if (queueMap[qr][qc] == 'x')
			{
				while (queue.isEmpty() == false)
					queue.dequeue();
			}
			else if (queueMap[qr][qc] != '.')
			{
				queueMap[qr][qc] = '.';
				if (queue_isValidLoc(qr - 1, qc)) queue.enqueue(new Node(qr - 1, qc));
				if (queue_isValidLoc(qr + 1, qc)) queue.enqueue(new Node(qr + 1, qc));
				if (queue_isValidLoc(qr, qc - 1)) queue.enqueue(new Node(qr, qc - 1));
				if (queue_isValidLoc(qr, qc + 1)) queue.enqueue(new Node(qr, qc + 1));
			}
		}

	}
	printf("미로 탐색 실패\n");




}




};