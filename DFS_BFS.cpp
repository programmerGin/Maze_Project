#include "Maze.h"
void main()
{
	system("mode con cols=120 lines=40");
	int num;
	Maze maze;

	while (1) {
		printf("=================================\n");
		printf("1. 연결리스트 스택으로 미로찾기\n");
		printf("2. 연결리스트 큐로 미로찾기\n");
		printf("3. 연결리스트 큐로 미로찾기 게임하기\n");
		printf("4. 연결리스트 스택, 큐로 비교하기\n");
		printf("========그 외 번호는 종료==========\n");
		printf("번호 입력: ");
		scanf("%d", &num);

		if (num == 1)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<Linked Stack Maze> Start!!\n-> 동작을 위해 엔터를 누르세요!");
			maze.stack_Search();
			maze.printDFS();
			printf("\n");

		}
		else if (num == 2)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<LinkedQueueMaze> Start!!\n-> 동작을 위해 엔터를 누르세요!");
			maze.queue_SearchExit();
			maze.printBFS();
			printf("\n");
		}
		else if (num == 3)
		{
			maze.roadMap("Maze.txt", num);
			system("cls");
			printf("<LinkedQueueMaze> Start!!\n-> 동작을 위해 방향키를 누르세요!");
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
			printf("프로그램을 종료합니다.\n");
			break;
		}
	}

}