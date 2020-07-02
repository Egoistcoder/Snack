#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>
#include"snake.h"

//随机产生食物
void inItFood()
{
	food[0] = rand() % WIDE;
	food[1] = rand() % HIGH;
}

 //蛇的初始化坐标        
void inItSnake()
{
	snake.size = 2;
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;
	snake.body[1].X = WIDE / 2 - 1;
	snake.body[1].Y = HIGH / 2;
}

//蛇和食物界面上的初始化
void ShowUI()
{
	COORD coord;
	//COORD是Windows.h提供的结构体函数 有两个参数

	//在蛇的最后一节身体前进后在此位置打印空格
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf(" ");

	//显示蛇的位置
	for (int i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}
	//显示食物的位置
	coord.X = food[0];
	coord.Y = food[1];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);         //设置控制台光标位置（固定字符，coord）
	putchar('#');
	//getchar();
}

//游戏开始
void PlayGame()
{
	char key = 'd';
	
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE  
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)
	{
		//显示界面
		ShowUI();


		//方向控制
		while (_kbhit())
		{
			key = _getch();
		}
		switch (key)
		{
			case 'D': case'd': dx = 1; dy = 0; break;
			case 'A': case'a': dx = -1; dy = 0; break;
			case 'W': case'w': dx = 0; dy = -1; break;
			case 'S': case's': dx = 0; dy = 1; break;

		}
		
		
		//是否与自身碰撞
		for (int i = 1; i < snake.size; i++)
		{
			if (snake.body[i].X == snake.body[0].X && snake.body[i].Y == snake.body[0].Y)
			{
				return;
			}
		}

		//和食物碰撞
		if (snake.body[0].X == food[0] && snake.body[1].Y == food[1])
		{
			//随机生成食物
			inItFood();
			//蛇的长度增长
			snake.size++;
			//分数增加
			score += 10;
			//关卡 障碍物 速度
		}

		//蛇坐标更新（蛇头更新 + 蛇身体更新）
		lx = snake.body[snake.size - 1].X;
		ly = snake.body[snake.size - 1].Y;

		for (int i = snake.size -1 ; i > 0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X += dx;
		snake.body[0].Y += dy;

		Sleep(400);
		//system("cls");
	}
}

//设置墙体
void inItWall()
{
	for (int i = 0; i <= HIGH; i++)
	{
		for (int j = 0; j <= WIDE; j++)
		{
			if (i == HIGH)
				putchar('=');
			else if (j == WIDE)
				putchar('=');
			else
				putchar(' ');
		}
			printf("\n");
	}
}


int main()
{
	srand((size_t)time(NULL));        //随机数种子
	//system("color f2");
	//去掉光标
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	inItWall();
	inItFood();
	inItSnake();
	ShowUI();
	PlayGame();
	return EXIT_SUCCESS;
}
