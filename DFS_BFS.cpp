#include "MazeFunction.h"
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <mciapi.h>
#pragma comment(lib,"winmm.lib")

	
	
void main()
{
	//PlaySound("���ϰ��", 0, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
	PlaySound(TEXT("bgm.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP); //���� ���
	_getch();




	system("mode con cols=150 lines=40");
	int num;
	Maze maze;
	


	while (1) {
		printf("=======   8�� �̷�ã�� ������Ʈ ==========\n");
		printf("\n");
		printf("=========   �޴��� �������ּ���  ========== \n");
		printf("1. DFS��� �̷�ã�� \n");
		printf("2. BFS���  �̷�ã�� \n");
		printf("3. DFS, BFS ���ϱ� \n");
		printf("=========== �� �� ��ȣ�� ����=================\n");

		printf("��ȣ �Է�: ");
		scanf("%d", &num);
		maze.roadFile("Maze.txt", num);

		if (num == 1)
		{
			system("cls");
			maze.stack_Search();
			maze.printDFS();
			printf("\n");

		}
		else if (num == 2)
		{

			system("cls");
			maze.queue_SearchExit();
			maze.printBFS();
			printf("\n");
		}
		else if (num == 3)
		{
			maze.compare_roadMap("Maze.txt");
			system("cls");
			maze.compare();
		}
		else
		{
			printf("���α׷��� �����մϴ�.\n");
			break;
		}
	}

}