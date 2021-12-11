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

	//�񱳸� ���� ��
	char** stackMap = NULL;
	char** queueMap = NULL;

	//��ġ ť,���� ��ü ����
	LinkedQueue locQueue;
	LinkedStack stack;

public:

	Maze() { init(0, 0); }
	~Maze() { reset(); }

	void init(int w, int h) //map ������ �迭�� �������� �Ҵ�
	{
		map = new char* [h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}

	void reset() //�̷� �� maze�� �������� ����
	{
		for (int i = 0; i < height; i++)
			delete[]map[i];
		delete[]map;
	}

	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r >= height || c >= width) return false;
		else return map[r][c] == '0' || map[r][c] == 'x';
	}



	void roadMap(const char* filename, int num)
	{
		char c;
		ifstream fp(filename);
		if (fp.fail())
			printf("Error: ������ �������� �ʽ��ϴ�.");

		//�̷� ũ�� ���
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

		//map �������迭 �������� �Ҵ�
		init(width, height);

		//map �������迭�� �̷� ����
		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				fp >> c;
				map[i][z] = c;

				//ť�� �Ա� ��ġ ����
				if (map[i][z] == 'e')
				{
					Location2D entry(i, z);
					if (num == 1)
						stack.push(new Node(i, z)); //���� �Ա�!
					else if (num == 2 || num == 3)
						locQueue.enqueue(new Node(i, z));
					else if (num == 4)
					{
						stack.push(new Node(i, z));
						locQueue.enqueue(new Node(i, z));
					}
				}
			}
		}
		fp.close();
	}

	//�̷� ȭ�鿡 ���
	void printMap() {
		//printf("��ü �̷��� ũ�� = %d X %d \n", width, height);
		printf("\n\n  [ Map ]\n\n");
		for (int i = 0; i < height; i++)
		{
			for (int z = 0; z < width; z++)
			{
				if (map[i][z] == '0') //��
				{
					cout << "  ";
				}
				else if (map[i][z] == '1') //��
				{
					cout << "��";
				}
				else if (map[i][z] == 'e') //�Ա�
				{
					cout << "o ";
				}
				else if (map[i][z] == 'x') //�ⱸ
				{
					cout << "x ";
				}
				else if (map[i][z] == '.') //������ ��
				{
					cout << "* ";
				}

			}
			cout << endl;
		}
		cout << endl;
	}

	int get_Enterkey()
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
		roadMap("Maze.txt", 1);
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
		roadMap("Maze.txt", 2);
		printf("BFS~\n");
		while (locQueue.isEmpty() == false) {
			Location2D* here = locQueue.peek();
			locQueue.dequeue();
			int r = here->row;
			int c = here->col;
			printf("(%d,%d)-> ", r, c);
			if (map[r][c] == 'x') {
				return;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locQueue.enqueue(new Node(r - 1, c));
				if (isValidLoc(r + 1, c)) locQueue.enqueue(new Node(r + 1, c));
				if (isValidLoc(r, c - 1)) locQueue.enqueue(new Node(r, c - 1));
				if (isValidLoc(r, c + 1)) locQueue.enqueue(new Node(r, c + 1));
			}
		}
	}
	//==================��ġ���================================
	void queue_SearchExit()
	{
		int count = 0;
		while (locQueue.isEmpty() == false) //ť�� ������� �ʴ� ����
		{
			printMap();
			if (get_Enterkey() == 13)
			{
				system("cls");

				Location2D* here = locQueue.peek(); //ť�� ��� front ��ü ����
				locQueue.dequeue(); //ť ��� ��ü ����
				count++;
				int r = here->row;
				int c = here->col;

				printf("������ġ: (%d,%d) \n", r, c);

				if (map[r][c] == 'x') { //�ⱸ�̸� ����
					system("cls");
					printf("!Ž�� ����!\n");
					printf("dequeue %d�� \n", count);
					printf("=====[ Result ]=====\n");
					printMap();
					return;
				}
				else if (map[r][c] != '.')
				{
					map[r][c] = '.';
					if (isValidLoc(r - 1, c)) locQueue.enqueue(new Node(r - 1, c));
					if (isValidLoc(r + 1, c)) locQueue.enqueue(new Node(r + 1, c));
					if (isValidLoc(r, c - 1)) locQueue.enqueue(new Node(r, c - 1));
					if (isValidLoc(r, c + 1)) locQueue.enqueue(new Node(r, c + 1));
				}
			}
		}
		printf("�̷� Ž�� ����\n");
	}

	

	
	void stack_Search()	//���� �κ�
	{
		int count=0;
		while (stack.isEmpty() == false) {	//���� ������� ���� ���
			printMap();
			if (get_Enterkey() == 13) {
				system("cls");
				Node* here = stack.peek();
				stack.pop();

				int r = here->row;
				int c = here->col;
				count++;
				printf("������ġ: (%d,%d) ", r, c);

				if (map[r][c] == 'x')
				{
					system("cls");
					printf("\n!Ž�� ����!\n");
					printf("pop %d�� \n", count);
					printf("=====[ Result ]=====\n");
					
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
		printf("�̷� Ž�� ����\n");
	}


	//=================================================================


	void QueueMazeGame()
	{
		int count = 0;
		while (locQueue.isEmpty() == false) //ť�� ������� �ʴ� ����
		{
			Location2D* here = locQueue.peek(); //ť�� ��� front ��ü ����
			int r = here->row;
			int c = here->col;

			int key = get_Enterkey();

			switch (key)
			{
			case 72: //��
				if (map[r - 1][c] == 'x') //���� ��ġ�� �ⱸ�̸� ����
				{
					map[r][c] = '0';
					map[r - 1][c] = '.';  //�̵��� ��ġ
					locQueue.dequeue(); //ť ��� ��ü ����
					locQueue.enqueue(new Node(r - 1, c)); //�̵��� ��ġ ť�� ����
					locQueue.dequeue(); //ť ��� ��ü ����
					count++;
					system("cls");
					printf("\n!Ž�� ����!\n");
					printf("=====[ Result ]=====\n");
					printf("�̵� %d�� ", count);
					printMap();
					return;
				}
				else if (isValidLoc(r - 1, c) && map[r - 1][c] != '1') //�� �� �ִ� ��ġ�̰�, ���� �ƴϸ�
				{
					system("cls");
					map[r][c] = '0'; //���� ��ġ ��� ����
					map[r - 1][c] = '.';  //�̵��� ��ġ
					locQueue.dequeue(); //ť ��� ��ü ����
					locQueue.enqueue(new Node(r - 1, c)); //�̵��� ��ġ ť�� ����
					printMap();
					count++;
				}
				break;
			case 80: //��
				if (map[r + 1][c] == 'x')
				{
					map[r][c] = '0';
					map[r + 1][c] = '.';
					locQueue.dequeue(); //ť ��� ��ü ����
					locQueue.enqueue(new Node(r + 1, c)); //�̵��� ��ġ ť�� ����
					locQueue.dequeue(); //ť ��� ��ü ����
					count++;
					system("cls");
					printf("\n!Ž�� ����!\n");
					printf("=====[ Result ]=====\n");
					printf("�̵� %d�� ", count);
					printMap();
					return;
				}
				else if (isValidLoc(r + 1, c) && map[r + 1][c] != '1')
				{
					system("cls");

					map[r][c] = '0';
					map[r + 1][c] = '.';
					locQueue.dequeue(); //ť ��� ��ü ����
					locQueue.enqueue(new Node(r + 1, c));
					printMap();
					count++;
				}
				break;
			case 75: //��
				if (map[r][c - 1] == 'x')
				{
					map[r][c] = '0';
					map[r][c - 1] = '.';
					locQueue.dequeue(); //ť ��� ��ü ����
					locQueue.enqueue(new Node(r, c - 1)); //�̵��� ��ġ ť�� ����
					locQueue.dequeue(); //ť ��� ��ü ����
					count++;
					system("cls");
					printf("\n!Ž�� ����!\n");
					printf("=====[ Result ]=====\n");
					printf("�̵� %d�� ", count);
					printMap();
					return;
				}
				else if (isValidLoc(r, c - 1) && map[r][c - 1] != '1')
				{
					system("cls");
					map[r][c] = '0';
					map[r][c - 1] = '.';

					locQueue.dequeue(); //ť ��� ��ü ����

					locQueue.enqueue(new Node(r, c - 1));
					printMap();
					count++;
				}
				break;
			case 77: //��
				if (map[r][c + 1] == 'x')
				{
					map[r][c] = '0';
					map[r][c + 1] = '.';
					locQueue.dequeue(); //ť ��� ��ü ����
					locQueue.enqueue(new Node(r, c + 1)); //�̵��� ��ġ ť�� ����
					locQueue.dequeue(); //ť ��� ��ü ����
					count++;
					system("cls");
					printf("\n!Ž�� ����!\n");
					printf("=====[ Result ]=====\n");
					printf("�̵� %d�� ", count);
					printMap();
					return;
				}
				else if (isValidLoc(r, c + 1) && map[r][c + 1] != '1')
				{
					system("cls");

					map[r][c] = '0';
					map[r][c + 1] = '.';

					locQueue.dequeue(); //ť ��� ��ü ����
					locQueue.enqueue(new Node(r, c + 1));
					printMap();
					count++;
				}
				break;
			default:
				printf("����Ű�� �Է����ּ���.\n");
				break;
			}
		}
	}

	//__________________________________________________________________________________________________

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
			printf("Error: ������ �������� �ʽ��ϴ�.");

		//�̷� ũ�� ���
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

				if (queueMap[i][z] == 'e') //�Ա� ��ġ
				{
					stack.push(new Node(i, z));
					locQueue.enqueue(new Node(i, z));
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
				if (stackMap[i][z] == '0') //��
				{
					cout << "  ";
				}
				else if (stackMap[i][z] == '1') //��
				{
					cout << "��";
				}
				else if (stackMap[i][z] == 'e') //�Ա�
				{
					cout << "o ";
				}
				else if (stackMap[i][z] == 'x') //�ⱸ
				{
					cout << "x ";
				}
				else if (stackMap[i][z] == '.') //������ ��
				{
					cout << "* ";
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
				if (queueMap[i][z] == '0') //��
				{
					cout << "  ";
				}
				else if (queueMap[i][z] == '1') //��
				{
					cout << "��";
				}
				else if (queueMap[i][z] == 'e') //�Ա�
				{
					cout << "o ";
				}
				else if (queueMap[i][z] == 'x') //�ⱸ
				{
					cout << "x ";
				}
				else if (queueMap[i][z] == '.') //������ ��
				{
					cout << "* ";
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
			Sleep(100);
			//system("cls");

			if (locQueue.isEmpty() == true && stack.isEmpty() == true)
			{
				printf("\n!Ž�� ����!\n");
				printf("=====[ Result ]=====\n");
				printf("���� Ž�� %dȸ, ť Ž�� %dȸ \n", stackCount, queueCount);
				if (stackCount > queueCount)
					printf("ť(���� �켱 Ž��)�� �� �����ϴ�.\n");
				else if (stackCount < queueCount)
					printf("����(�ʺ� �켱 Ž��)�� �� �����ϴ�.\n");
				else if (stackCount == queueCount)
					printf("���ð� ť�� Ž�� Ƚ���� �����մϴ�.\n");

				
				return;
			}

			if (stack.isEmpty() == false)
			{
				Node* hereStack = stack.peek();
				stack.pop();
				int sr = hereStack->row;
				int sc = hereStack->col;
				stackCount++;

				//printf("Stack Now Position: (%d,%d) \n", sr, sc);

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
			if (locQueue.isEmpty() == false)
			{
				Location2D* hereQueue = locQueue.peek();
				locQueue.dequeue();
				int qr = hereQueue->row;
				int qc = hereQueue->col;
				queueCount++;
				//printf("Queue Now Position: (%d,%d) \n", qr, qc);

				if (queueMap[qr][qc] == 'x')
				{
					while (locQueue.isEmpty() == false)
						locQueue.dequeue();
				}
				else if (queueMap[qr][qc] != '.')
				{
					queueMap[qr][qc] = '.';
					if (queue_isValidLoc(qr - 1, qc)) locQueue.enqueue(new Node(qr - 1, qc));
					if (queue_isValidLoc(qr + 1, qc)) locQueue.enqueue(new Node(qr + 1, qc));
					if (queue_isValidLoc(qr, qc - 1)) locQueue.enqueue(new Node(qr, qc - 1));
					if (queue_isValidLoc(qr, qc + 1)) locQueue.enqueue(new Node(qr, qc + 1));
				}
			}
		
		}
		printf("�̷� Ž�� ����\n");
	}
};