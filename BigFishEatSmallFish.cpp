#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define return_value; //关键返回值

// 功能模块
bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom); //鼠标检测模块
void DrawButten(int left, int top, int right, int bottom, const char* text); //创建游戏标准按钮
//游戏模块
int starting();


void main()//主函数
{
	initgraph(1920, 1080);
	starting(); //进入程序界面
	
}

int starting()
{
	DrawButten(945, 530, 975, 550, "login");
	DrawButten(945, 560, 975, 570, "SignUp");
	DrawButten(int left, int top, int right, int bottom, const char* text);
	
	
	while (1)
	{
		if (MouseHit)
		{
			MOUSEMSG msg = GetMouseMsg();
			int x = msg.x;
			int y = msg.y;

			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if(isP)
			}

		}
	}
}

void DrawButten(int left, int top, int right, int bottom,const char* text)
{
	solidroundrect(left, top, right, bottom, 50, 50);
	outtextxy(left + 10, top + 10, text);
}

bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom)
{
	return (x >= left && x <= right && y >= top && y <= bottom); //判断是否在按钮内
}
