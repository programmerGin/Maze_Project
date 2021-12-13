#include "MazeFunction.h"
void main()
{
	system("mode con cols=150 lines=40");
	int num;
	Maze maze;

	while (1) {
		printf("=======   8조 미로찾기 프로젝트 ==========\n");
		printf("\n");
		printf("=========   메뉴를 선택해주세요  ========== \n");
		printf("1. DFS방식 미로찾기 \n");
		printf("2. BFS방식  미로찾기 \n");
		printf("3. DFS, BFS 비교하기 \n");
		printf("=========== 그 외 번호는 종료=================\n");
		printf("\n");

		printf("번호 입력: ");
		scanf("%d", &num);
		maze.roadFile("Maze.txt", num);

		if (num == 1)
		{
			//system("cls");
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
			printf("프로그램을 종료합니다.\n");
			break;
		}
	}

}