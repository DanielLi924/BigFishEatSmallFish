#include <graphics.h>
#include <conio.h>
#include <stdio.h>

// 功能模块
bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom); //鼠标检测模块
void DrawButten(int left, int top, int right, int bottom, const char* text); //创建游戏标准按钮
//游戏模块
int starting();
int game();


int main()//主函数
{
	int situation;//状态函数
	initgraph(1920, 1080);//画布尺寸
	
	situation = starting();//进入程序界面
	if (situation == 1)
	{
		
		cleardevice();
		int LoginLeft = 860, LoginTop = 290, LoginRight = 1060, LoginDown = 390;
		DrawButten(LoginLeft, LoginTop, LoginRight, LoginDown, "login");
		while (1)
		{

		}
	}
	else if (situation == 2)
	{
		cleardevice();
		int LoginLeft = 860, LoginTop = 290, LoginRight = 1060, LoginDown = 390;
		DrawButten(LoginLeft, LoginTop, LoginRight, LoginDown, "signin");
		while (1)
		{

		}
	}
	return 0;
}

int starting()
{
	initgraph(1920, 1080);
	int situation;
	IMAGE img;
	loadimage(&img, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	// Display the image
	putimage(0, 0, &img);
	int LoginLeft = 860, LoginTop = 290, LoginRight = 1060, LoginDown = 390; //Login按钮参数
	int SignUpLeft = 860, SignUpTop = 490, SignUpRight = 1060, SignUpDown = 590;//SignUp按钮参数
	int ExitLeft = 860, ExitTop = 690, ExitRight = 1060, ExitDown = 790;//退出按钮参数
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
					InputBox(Account,20, "Your Accunt:(小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定)","Account","\0",0,0,true);//获取用户账户
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定", "Password", "\0", 0, 0,true);//获取用户密码
						situation = 1;
						return situation;
					}
					else
					{
						
					}
					
					
				}
				else if (SignUpClicked)
				{
					char Account[20];
					char Password[20];
					InputBox(Account, 20, "Your Accunt:(小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定)", "Account", "\0", 0, 0, true);//获取用户账户
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "Your Password:(In less than 10 character)", "Password", "\0", 0, 0, false);//获取用户密码
						situation = 2;
						return situation;
					}
					else
					{

					}
				}
				else if (ExitClicked)
				{
					exit(0);
				}

			}
		}
	}
	
}

void DrawButten(int left, int top, int right, int bottom, const char* text) //绘制标准按钮
{
	setfillcolor(LIGHTGRAY);
	solidroundrect(left, top, right, bottom, 10, 10); //样式和大小
	outtextxy(left + 10, top + 10, text);//输出文字
}

bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom)
{
	return (x >= left && x <= right && y >= top && y <= bottom); //判断是否在按钮内
}
