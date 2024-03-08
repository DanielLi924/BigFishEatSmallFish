#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define return_value //关键返回值

// 功能模块
bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom); //鼠标检测模块
void DrawButten(int left, int top, int right, int bottom, const char* text); //创建游戏标准按钮
//游戏模块
int starting();


int main()//主函数
{
	initgraph(1920, 1080);//画布尺寸
	starting(); //进入程序界面
	return 0;
}

int starting()
{
	int LoginLeft = 900, LoginTop = 530, LoginRight = 990, LoginDown = 550;
	int SignUpLeft = 900, SignUpTop = 560, SignUpRight = 990, SignUpDown = 570;
	int ExitLeft = 900, ExitTop = 580, ExitRight = 990, ExitDown = 600;
	DrawButten(LoginLeft,LoginTop, LoginRight, LoginDown, "login"); //绘制登录按钮
	DrawButten(SignUpLeft, SignUpTop, SignUpRight, SignUpDown, "SignUp"); //绘制注册按钮
	DrawButten(ExitLeft, ExitTop, ExitRight,ExitDown, "Exit"); //绘制退出图标
	bool LoginClicked = false; //设置登录按钮为false
	bool SignUpClicked = false; //设置注册按钮为false
	bool ExitClicked = false; //设置退出按钮为false
	while (1)
	{

		if (MouseHit) //检测鼠标是否有活动事件
		{
			MOUSEMSG msg = GetMouseMsg(); //将信息存入msg
			int x = msg.x; //获取鼠标 x 坐标
			int y = msg.y; //获取鼠标 y 坐标

			if (msg.uMsg == WM_LBUTTONDOWN) //判断条件为如果鼠标左键按下
			{
				if (isPointInsideRectangle(x, y, LoginLeft, LoginTop, LoginRight, LoginDown))
				{
					LoginClicked = true; //设置登录按钮为true
					SignUpClicked = false; //设置注册按钮为false
					ExitClicked = false; //设置退出按钮为false
				}
				else if (isPointInsideRectangle(x, y, SignUpLeft, SignUpTop, SignUpRight, SignUpDown))
				{
					LoginClicked = false; //设置登录按钮为false
					SignUpClicked = true; //设置注册按钮为true
					ExitClicked = false; //设置退出按钮为false
				}
				else if (isPointInsideRectangle(x, y, ExitLeft, ExitTop, ExitRight, ExitDown))
				{
					LoginClicked = false; //设置登录按钮为false
					SignUpClicked = false; //设置注册按钮为false
					ExitClicked = true; //设置退出按钮为true
				}
			}
			else if (msg.uMsg == WM_LBUTTONUP) //检测鼠标左键是否抬起
			{
				if (LoginClicked) 
				{
					char Account[20];  // 用于存储输入的用户名
					char Password[20]; //用于存储输入的密码
					InputBox(Account,20, "Your Accunt:(In less than 10 character)","Account","Your Account",500,500,false);
					InputBox(Password, 20, "Your Password:(In less than 10 character)");
				}
				else if (SignUpClicked)
				{

				}

			}
		}
	}
}

void DrawButten(int left, int top, int right, int bottom, const char* text) //绘制标准按钮
{
	setfillcolor(LIGHTGRAY);
	solidroundrect(left, top, right, bottom, 50, 50); //样式和大小
	outtextxy(left + 10, top + 10, text);//输出文字
}

bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom)
{
	return (x >= left && x <= right && y >= top && y <= bottom); //判断是否在按钮内
}
