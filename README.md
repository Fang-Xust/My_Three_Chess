# My_Three_Chess


main.c


#define _CRT_SECURE_NO_WARNINGS 1
#include"Three_Chess.h"

int main()
{
	int select = 0;
	int quit = 0;
	while (!quit) 
	{
		ShowUI();              //此处调用ShowUI()函数打印菜单
		scanf("%d", &select);
		switch (select)
		{
		case 1:               //选择1玩游戏
			Game();
			break;            //选择2退出游戏
		case 2:
			quit = 1;       //当quit为1时，下次循环判断为0，不进循环
			printf("ByeBye!\n");
			break;
		default:
			printf("Please Enter Again!\n");
			break;
		}
	}
	system("pause");
	return 0;
}  


Three_Chess.h


#pragma once
#ifndef _THREE_CHESS_H_
#define _THREE_CHESS_H_

#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<time.h>

#define ROW 3
#define COL 3

void ShowUI();
void Game();
void ComputerMove(char board[][COL], int row, int col);
void PlayerMove(char board[][COL], int row, int col);
void ShowBoard(char board[][COL], int row, int col);
char Judge(char board[][COL], int row, int col);

#endif


Three_Chess.c


#define _CRT_SECURE_NO_WARNINGS 1
#include"Three_Chess.h"

void ShowUI()
{
	printf("*******************************\n");
	printf("*    1、GAME       2、EXIT    *\n");
	printf("*******************************\n");
	printf("Please select:\n");
}

void ComputerMove(char board[][COL], int row, int col)
{
	while (1)
	{                   //调用rand()函数生成两个随机数作为下标
		int x = rand() % row;      //这里分别对row和col取模
		int y = rand() % col;
		if (board[x][y] == ' ')     //判断此位置是否为空，如果为空就赋值'O'表示电脑走在此位置
		{
			board[x][y] = 'O';
			break;                   //退出循环
		}
	}
}


void PlayerMove(char board[][COL], int row, int col)
{
	int x, y;
	while (1)
	{
		printf("Please enter position->x y:\n");
		scanf("%d %d", &x, &y);           //提示用户输入坐标
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{                            //判断输入的坐标是否满足条件
			if (board[x-1][y-1] == ' ')    //用户输入的下标是从1开始的，而数组下标是从0开始的，所以这里要对x和y减1
			{
				board[x-1][y-1] = 'X';     //在此位置放入'X'，表示用户下在这里
				break;
			}
			else
			{
				printf("Your place is taken,Try Again:\n");
			}
		}
		else
		{
			printf("Enter error,Try Again:\n");
		}
	}
}


char Judge(char board[][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)       //判断每一行row是否相等且不能为空
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
		{
			return board[i][0];
		}
	}
	for (i = 0; i < col; i++)       //判断每一列col是否相等且不能为空
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] != ' ')
		{
			return board[0][i];
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
	{                          //判断左对角线是否都相等且不为空
		return board[0][0];
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != ' ')
	{                          //判断右对角线是否都相等且不为空
		return board[0][2];
	}
	//如果上面集中情况即行、列、对角线都没有一样的，下面就要判断是否棋盘放满了
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 'N';           //如果棋盘上有空的，说明没满，返回'N'继续
			}
		}
	}
	//如果走到这，说明只有一种可能，那就是平局
	return 'E';                //返回'E'，表示平局
}


void ShowBoard(char board[][COL], int row, int col)
{
	system("cls");               //显示棋盘之前每次实现一次清屏
	printf("    1   2   3\n");    //打印第一行的数字列号
	printf("---------------\n");   //打印横线
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)   
	{ 
		printf("%d |",i + 1);    //打印行号，这里i+1表示从1开始而不是0
		for (j = 0; j < col; j++)
		{
			printf(" %c |",board[i][j]);
		}
		printf("\n---------------\n");
	}
	printf("\n");
}


void Game()
{
	char board[ROW][COL];                 //定义数组棋盘
	memset(board, ' ', sizeof(board));    //实现数组置空
	char result = 'N';
	srand((unsigned long)time(NULL));       //布置随机数种子，在ComputerMove()函数中用到，头文件#include<time.h>
	while (1)
	{
		ComputerMove(board, ROW, COL);
		ShowBoard(board, ROW, COL);
		result = Judge(board, ROW, COL);
		if (result != 'N')   //X玩家赢，O电脑赢，E平局，N继续
		{
			break;
		}
		PlayerMove(board, ROW, COL);
		ShowBoard(board, ROW, COL);
		result = Judge(board, ROW, COL);
		if (result != 'N')   //X玩家赢，O电脑赢，E平局，N继续
		{
			break;
		}
	} 
	switch (result)
	{
	case 'X':
		printf("Congratulations!You Win!\n");
		break;
	case 'O':
		printf("Damn!You Lose！\n");
		break;
	case 'E':
		printf("Dogfall!\n");
		break;
	default:
		break;
	}
}
