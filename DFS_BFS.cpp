#include "Maze.h"
void main()
{
	system("mode con cols=150 lines=40");
	int num;
	Maze maze;

	while (1) {
		printf("=======�޴��� �������ּ���==========\n");
		printf("1. DFS��� �̷�ã��\n");
		printf("2. BFS���  �̷�ã��\n");
		printf("3. DFS, BFS ���ϱ�\n");
		printf("===========�׿� ��ȣ�� ����=================\n");
		printf("��ȣ �Է�: ");
		scanf("%d", &num);

		if (num == 1)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("������ ���� ���͸� ��������!");
			maze.stack_Search();
			maze.printDFS();
			printf("\n");

		}
		else if (num == 2)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("������ ���� ���͸� ��������!");
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