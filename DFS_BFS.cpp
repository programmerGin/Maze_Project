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
		printf("=================================\n");
		printf("번호 입력, 번호 외 값 종료 : ");
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
			printf("프로그램을 종료합니다.\n");
			break;
		}
	}

}