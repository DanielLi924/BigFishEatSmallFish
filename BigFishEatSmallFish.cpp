#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "MSIMG32.LIB")
#define COUNTER 0
#define PLAYER 0

struct Fish //单个鱼的属性
{
	int x;
	int y;
	int dir;			//鱼的方向
	int type;		//鱼的类型
	double rate;
	int w;
	int h;
	IMAGE picture;
	int level;
	int score;
};
struct Fish fishs[21];
IMAGE fishIMG[21][2];


typedef struct User //结构体用来存储用户数据
{
	char* username;
	char* password;
	int score;
};

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
void initfish(int type);
bool UserData(char* username, char* password, bool check);
void initfishrole();
void initfish(int type);
void Fishload();
void FishPut(int level);
void control();

struct User* users = NULL;
int num_users = 0;

//游戏模块
int starting();
int game();
int History();

//----------------------------------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------------------------------

int main()//主函数
{
	initgraph(1920, 1080);//画布尺寸
	while (1)
	{
		int situation = 0;//状态函数

		situation = starting();
		if (situation == 1)
		{
			game();
		}
		else if (situation == 2)
		{
			int s = situation;
		}

	}
	return 0;
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
				if (LoginClicked)//登录界面
				{
					char Account[20];  // 用于存储输入的用户名
					char Password[20]; //用于存储输入的密码
					InputBox(Account, 20, "Your Accunt:(小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定)", "Account", "\0", 0, 0, true);//获取用户账户
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定", "Password", "\0", 0, 0, true);//获取用户密码

					}
					if (UserData(Account, Password, true))
					{
						situation = 1;
						return situation;
					}
					else
					{
						situation = 2;
						return situation;
					}

				}
				else if (SignUpClicked)//注册界面
				{
					char Account[20];
					char Password[20];
					InputBox(Account, 20, "Your Accunt:(小于10个字符，请不要输入空格，且如果不需要输入账户，则不要在输入框中输入任何内容直接点击确定)", "Account", "\0", 0, 0, true);//获取用户账户
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "Your Password:(In less than 10 character)", "Password", "\0", 0, 0, false);//获取用户密码
						if (UserData(Account, Password, false))
						{
							situation = 2;
							return situation;
						}
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

int game()
{
	void setrate();
	IMAGE background;
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	// Display the image
	Fishload();
	BeginBatchDraw(); // 开始双缓冲绘图
	while (1)
	{
		
		putimage(0, 0, &background, SRCCOPY);// 在虚拟画布上绘制背景
		FishPut(1);
		FlushBatchDraw(); // 刷新缓冲区，将图像一次性绘制到屏幕上
		control();

	}
	closegraph(); // 关闭图形窗口
}

//-----------------------------------------------------------------------------------------------------------------------------------------


void Fishload()
{
	char filename[100] = { "" };
	for (int i = 0; i < 21; i++)
	{
		initfish(i);
		for (int j = 0; j < 2; j++)
		{
			switch (j)
			{
			case 0:
				sprintf(filename, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish%deft.png", i+1);
				break;
			case 1:
				sprintf(filename, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish%dright.png", i+1);
				break;
			}
			loadimage(&fishIMG[i][j], filename, fishs[i].w, fishs[i].h, true);				//载入缩放图片

		}
	}
}
void initfish(int type)					//后续还要修改这个函数加上
{
	MOUSEMSG msg = GetMouseMsg();
	if (type == 0)
	{
		fishs[type].x = msg.x;
		fishs[type].y = msg.y;
		fishs[type].dir = 0; // 左
		fishs[type].type = 0;
		fishs[type].w = (100 + 30);
		fishs[type].h = (int)(fishs[type].w / fishs[type].rate);
	}
	else
	{
		fishs[type].type = rand() % (21 - 1) + 1;
		int dir = rand() % 10 > 5 ? 0 : 1; //0 表示左，1表示右
		fishs[type].dir = dir;
		fishs[type].y = rand() % 90 * 10 + 50;
		fishs[type].x = dir == 0 ? rand() % 400 + 1920 : -1 * rand() % 400; // 400 是边界判断
		fishs[type].w = 100 + 20 * type;
		fishs[type].h = (int)(fishs[type].w / fishs[type].rate);
	}
}


void control()
{
	MOUSEMSG msg = GetMouseMsg();
	fishs[0].x = msg.x;
	fishs[0].y = msg.y;
}
void FishPut(int level)
{
	for (int i = 0; i < level + 3; i++)						//后期加上分数机制后添加等级
	{
		transparentimage3(NULL, fishs[i].x, fishs[i].y, &fishIMG[i][1]);
	}
}

void setrate()
{
	fishs[0].rate = 2.45;
	fishs[1].rate = 2.60;
	fishs[2].rate = 1.03;
	fishs[3].rate = 1.12;
	fishs[4].rate = 0.58;
	fishs[5].rate = 3.36;
	fishs[6].rate = 1.65;
	fishs[7].rate = 2.08;
	fishs[8].rate = 1.08;
	fishs[9].rate = 1.68;
	fishs[10].rate = 3.45;
	fishs[11].rate = 3.84;
	fishs[12].rate = 2.51;
	fishs[13].rate = 2.92;
	fishs[14].rate = 1.13;
	fishs[15].rate = 2.34;
	fishs[16].rate = 1.58;
	fishs[17].rate = 2.26;
	fishs[18].rate = 2.26;
	fishs[19].rate = 1;
	fishs[20].rate = 1;

}

//---------------------------------------------------------------------------------------------------------------------------------------------//

bool UserData(char* username, char* password, bool check)
{
	if (check)
	{
		// 进行账号密码检查的代码
		for (int i = 0; i < num_users; i++) {
			if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
				return true;
			}
		}
		return false;
	}
	else {
		// 添加新用户数据
		num_users++; // 增加用户数量
		// 重新分配内存以容纳新的用户数据
		struct User* temp = (struct User*)realloc(users, num_users * sizeof(struct User));
		if (temp == NULL) {
			// 内存分配失败
			printf("Memory allocation failed.\n");
			return false;
		}
		// 更新 users 指针
		users = temp;
		// 为新用户的 username 和 password 分配内存并复制字符串
		users[num_users - 1].username = (char*)malloc(strlen(username) + 1);
		if (users[num_users - 1].username == NULL) {
			printf("Memory allocation failed.\n");
			return false;
		}
		strcpy(users[num_users - 1].username, username);
		users[num_users - 1].password = (char*)malloc(strlen(password) + 1);
		if (users[num_users - 1].password == NULL) {
			printf("Memory allocation failed.\n");
			// 可以选择释放之前分配的内存
			free(users[num_users - 1].username);
			return false;
		}
		strcpy(users[num_users - 1].password, password);
		users[num_users - 1].score = 0; // 假设初始分数为 0
		printf("User data stored successfully!\n");
		return true;
	}
}