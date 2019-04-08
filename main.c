# My_Three_Chess

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
