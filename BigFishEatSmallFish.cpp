#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "MSIMG32.LIB")



// 功能模块
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //实现透明图片输出
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom); //鼠标检测模块
void DrawButten(int left, int top, int right, int bottom, const char* text); //创建游戏标准按钮
void PlayerFish(int x, int y);
void EatenFish(int x, int y, int level);
bool LoginCheck(char* username, char* password);
void UserData(char* username, char* password);

struct User //结构体
{
	char username[20];
	char password[20];
	int score;
};

struct User UserGroups[1];

struct User** users = NULL;
int num_users = 0;

//游戏模块
int starting();
int game();
//int History();


int main()//主函数
{
	int situation;//状态函数
	initgraph(1920, 1080);//画布尺寸

	situation = starting();//进入程序界面
	if (situation == 1)
	{

		game();
	}
	else if (situation == 2)
	{
		situation = starting();//进入程序界面
		return 0;
	}
}

int starting()
{
	int situation;
	IMAGE img;
	loadimage(&img, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	// Display the image
	putimage(0, 0, &img);
	int LoginLeft = 860, LoginTop = 290, LoginRight = 1060, LoginDown = 390; //Login按钮参数
	int SignUpLeft = 860, SignUpTop = 490, SignUpRight = 1060, SignUpDown = 590;//SignUp按钮参数
	int ExitLeft = 860, ExitTop = 690, ExitRight = 1060, ExitDown = 790;//退出按钮参数
	DrawButten(LoginLeft, LoginTop, LoginRight, LoginDown, "login"); //绘制登录按钮
	DrawButten(SignUpLeft, SignUpTop, SignUpRight, SignUpDown, "SignUp"); //绘制注册按钮
	DrawButten(ExitLeft, ExitTop, ExitRight, ExitDown, "Exit"); //绘制退出图标
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
					InputBox(Account, 20, "Your Accunt:(小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定)", "Account", "\0", 0, 0, true);//获取用户账户
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定", "Password", "\0", 0, 0, true);//获取用户密码

					}
					if (LoginCheck(Account, Password))
					{
						situation = 1;
						return situation;
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
						UserData(Account, Password);
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

int game()
{
	IMAGE background;
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	// Display the image
	putimage(0, 0, &background);
	while (1)
	{
		MOUSEMSG msg = GetMouseMsg();
		int x, y;
		x = msg.x;
		y = msg.y;

		BeginBatchDraw(); // 开始双缓冲绘图

		putimage(0, 0, &background, SRCCOPY);// 在虚拟画布上绘制背景

		PlayerFish(x, y);

		FlushBatchDraw(); // 刷新缓冲区，将图像一次性绘制到屏幕上
	}

	closegraph(); // 关闭图形窗口
}

void PlayerFish(int x, int y)
{

	IMAGE PlayerFish;
	loadimage(&PlayerFish, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/PlayerFish.png", 100, 100, true); // 在虚拟画布上绘制小鱼
	transparentimage3(NULL, x, y, &PlayerFish);

}
/*
void EatenFish(int x, int y,int level)
{
	IMAGE fish[19]; //创建20个鱼作为被玩家吃的对象
	int random_x, random_y; //作为每次生成鱼的坐标
	while (1)
	{
		while (random_x == x)
		{
			srand(time(NULL));
			random_x = rand() % 1920;
		}
		while (random_y == y)
		{
			srand(time(NULL));
			random_x = rand() % 1080;
		}
		for (int i = 0; i < 19; i++)
		{
			srand(time(NULL));
			int random_fish;
			random_fish = rand() % (i + 2);
			loadimage(&fish[random_fish], "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/PlayerFish.png", true);
		}



	}
}
*/
bool LoginCheck(char* username, char* password) {
	// 在这里进行用户账号密码的验证
	for (int i = 0; i < num_users; i++) {
		if (strcmp(users[i]->username, username) == 0 && strcmp(users[i]->password, password) == 0) {
			return true;
		}
	}

	// 循环结束后输出错误信息
	printf("Login failed: Invalid username or password.\n");
	return false; // 验证失败
}
void UserData(char* username, char* password) {
	// 检查是否已经存在相同的用户名
	for (int i = 0; i < num_users; i++) {
		if (strcmp(users[i]->username, username) == 0) {
			printf("Username already exists.\n");
			return;
		}
	}

	// 动态分配内存并添加用户
	struct User* new_user = (struct User*)malloc(sizeof(struct User));
	strcpy_s(new_user->username, username);
	strcpy_s(new_user->password, password);

	// 扩展用户数组大小并添加新用户指针
	num_users++;
	users = (struct User**)realloc(users, num_users * sizeof(struct User*));
	users[num_users - 1] = new_user;

	printf("User registered successfully!\n");
}
