#include "Maze.h"
void main()
{
	system("mode con cols=120 lines=40");
	int num;
	Maze maze;

	while (1) {
		printf("=================================\n");
		printf("1. ���Ḯ��Ʈ �������� �̷�ã��\n");
		printf("2. ���Ḯ��Ʈ ť�� �̷�ã��\n");
		printf("3. ���Ḯ��Ʈ ť�� �̷�ã�� �����ϱ�\n");
		printf("4. ���Ḯ��Ʈ ����, ť�� ���ϱ�\n");
		printf("=================================\n");
		printf("��ȣ �Է�, ��ȣ �� �� ���� : ");
		scanf("%d", &num);

		if (num == 1)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<Linked Stack Maze> Start!!\n-> Enter and Show Miro Program");
			maze.stack_Search();
		}
		else if (num == 2)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<LinkedQueueMaze> Start!!\n-> Enter and Show Miro Program");
			maze.queue_SearchExit();
		}
		else if (num == 3)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<LinkedQueueMaze> Start!!\n-> Enter and Show Miro Program");
			maze.printMap();
			maze.QueueMazeGame();
		}
		else if (num == 4)
		{
			maze.compare_roadMap("Maze.txt");
			system("cls");
			printf("<Compare Stack & Queue> Start!!\n");
			maze.compare();
		}
		else
		{
			printf("���α׷��� �����մϴ�.\n");
			break;
		}
	}

}