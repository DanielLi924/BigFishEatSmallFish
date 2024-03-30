#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <time.h>
#include <chrono> // 添加头文件以使用时间库
#pragma comment(lib, "MSIMG32.LIB")
#define LEVEL 5
#define PLAYER 0
#define LEFT -1
#define RIGHT 1
#define FISH_MAX_NUMS 10
#define TIMER_MAX 10

struct Fish //单个鱼的属性
{
	int x;
	int y;
	int dir;		//鱼的方向
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
struct msg
{
	USHORT message;					// 消息标识
	union
	{
		// 鼠标消息的数据
		struct
		{
			bool ctrl : 1;		// Ctrl 键是否按下
			bool shift : 1;		// Shift 键是否按下
			bool lbutton : 1;		// 鼠标左键是否按下
			bool mbutton : 1;		// 鼠标中键是否按下
			bool rbutton : 1;		// 鼠标右键
			short x;				// 鼠标的 x 坐标
			short y;				// 鼠标的 y 坐标
			short wheel;			// 鼠标滚轮滚动值，为 120 的倍数
		};

		// 按键消息的数据
		struct
		{
			BYTE vkcode;			// 按键的虚拟键码
			BYTE scancode;			// 按键的扫描码（依赖于 OEM）
			bool extended : 1;		// 按键是否是扩展键
			bool prevdown : 1;		// 按键的前一个状态是否按下
		};

		// 字符消息的数据
		TCHAR ch;

		// 窗口消息的数据
		struct
		{
			WPARAM wParam;
			LPARAM lParam;
		};
	};
};


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
void fishmove();
void Fishload();
void FishPut(int level);
void control();
void setrate();
int ontimer(int duration, int id);
bool AccountInput(char *Account, char *Password, bool situation);
void beginword();
void printUser(char* Username);

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
	IMAGE background,text;
	
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	loadimage(&text, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/text.png", 800, 40, true);
	// Display the image
	putimage(0, 0, &background);
	putimage(550, 150, &text);
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
					char Account[20];
					char Password[20];
					bool s = AccountInput(Account, Password, true);
					if (s)
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
					bool s1 = AccountInput(Account, Password, false);
					if(s1)
					{
						situation = 2;
						return situation;
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
	setrate();
	IMAGE background;
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	// Display the image
	Fishload();

	while (1)
	{
		BeginBatchDraw(); // 开始双缓冲绘图
		putimage(0, 0, &background, SRCCOPY);// 在虚拟画布上绘制背景

		FishPut(LEVEL);
		transparentimage3(NULL, fishs[0].x, fishs[0].y, &fishIMG[0][0]);

		FlushBatchDraw(); // 刷新缓冲区，将图像一次性绘制到屏幕上
		control();
		if (ontimer(10, 0))
		{
			fishmove();
		}
		//resetothers();

	}
	closegraph(); // 关闭图形窗口
}

//-----------------------------------------------------------------------------------------------------------------------------------------


void Fishload()//加载全部鱼的图片（放到内存里）
{
	MOUSEMSG msg = GetMouseMsg();
	for (int i = 0; i < 21; i++)
	{
		char filename[100] = { "" };
		int type = i;
		if (type == 0)
		{
			fishs[type].x = msg.x;
			fishs[type].y = msg.y;
			fishs[type].dir = LEFT; // 左
			fishs[type].type = 0;
			fishs[type].w = (LEVEL * 100);
			fishs[type].h = (int)(fishs[type].w / fishs[type].rate);

		}
		else
		{
			fishs[type].type = rand() % (21 - 1) + 1;  // 生成一个1到20之间的随机数，用于表示鱼的类型
			int dir = rand() % 10 > 5 ? LEFT : RIGHT;  // 生成一个随机数，若大于5则dir为0（表示左），否则为1（表示右）
			fishs[type].dir = dir;  // 将随机生成的方向赋值给对应鱼的方向属性
			fishs[type].y = rand() % 90 * 10 + 50;  // 生成一个50到950之间的随机数，用于表示鱼的y坐标
			fishs[type].x = dir == 0 ? rand() % 400 + 1920 : -1 * rand() % 400;  // 若dir为0，则在1920到2320之间生成x坐标；否则在负400到0之间生成x坐标，用来判断鱼从左边还是右边出来
			fishs[type].w = 100 + 20 * type;  // 根据鱼的类型计算鱼的宽度，宽度随类型增加而增加
			fishs[type].h = (int)(fishs[type].w / fishs[type].rate);  // 根据鱼的宽高比计算鱼的高度
		}
		for (int j = 0; j < 2; j++)
		{
			switch (j)
			{
			case 0:
				sprintf(filename, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish%dleft.png", i);
				break;
			case 1:
				sprintf(filename, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish%dright.png", i);
				break;
			}
			loadimage(&fishIMG[i][j], filename, fishs[i].w, fishs[i].h, true); //载入缩放图片

		}
	}
	
} 

int ontimer(int duration, int id)
{
	static int starttime[TIMER_MAX];
	int endtime = clock();
	if (endtime - starttime[id] >= duration)
	{
		starttime[id] = endtime;
		return 1;
	}
	return 0;
}

void fishmove()					//后续还要修改这个函数加上
{
	for (int i = 1; i < FISH_MAX_NUMS; i++)
	{
		switch (fishs[i].dir)
		{
		case LEFT:
			fishs[i].x -= 1;
			break;
		case RIGHT:
			fishs[i].x += 1;
			break;
		}
	}
}

void control()
{
	ExMessage msg;
	if (!peekmessage(&msg, EX_MOUSE))  // 如果没有鼠标消息
	{
		return;  // 直接跳出函数
	}

	// 有鼠标消息，则处理消息
	fishs[0].x = msg.x;
	fishs[0].y = msg.y;
}


void FishPut(int level)
{
	for (int i = 1; i < level + 3; i++)						//后期加上分数机制后添加等级
	{
		transparentimage3(NULL, fishs[i].x, fishs[i].y, &fishIMG[i][0]);
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

bool AccountInput(char* Account, char* Password, bool check)
{
	IMAGE background1;
	loadimage(&background1, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	char log[] = "Username";
	LOGFONT Log{};
	settextcolor(GREEN);
	Log.lfQuality = ANTIALIASED_QUALITY;
	Log.lfHeight = 80;
	strcpy(Log.lfFaceName, "得意黑 斜体");
	settextstyle(&Log);
	char pas[] = "Password";
	char username[100];
	char password[100];
	int index = 0;

	putimage(0, 0, &background1);
	outtextxy(100, 270, log);
	outtextxy(100, 570, pas);

	while (1)
	{
		char ch = _getch();
		if (ch == '\r' || ch == '\n')
		{
			if (index > 0) // 检查是否输入了密码
				break;
		}
		else if (ch == 8) // 检测是否为退格键
		{
			if (index > 0)
			{
				index--;
				username[index] = '\0';
				cleardevice(); // 清除屏幕上的内容
				putimage(0, 0, &background1); // 重新绘制背景
				outtextxy(100, 270, log); // 重新输出用户名
				outtextxy(100, 570, pas); // 重新输出密码
				outtextxy(100, 420, username); // 输出更新后的用户名
			}
		}
		else
		{
			username[index++] = ch;
			username[index] = '\0';
			putimage(0, 0, &background1);
			outtextxy(100, 270, log);
			outtextxy(100, 570, pas);
			outtextxy(100, 420, username);
		}
	}

	index = 0; // 重置索引以接收密码输入

	while (1)
	{
		char ch = _getch();
		if (ch == '\r' || ch == '\n')
		{
			if (index > 0) // 检查是否输入了密码
				break;
		}
		else if (ch == 8) // 检测是否为退格键
		{
			if (index > 0)
			{
				index--;
				password[index] = '\0';
				cleardevice(); // 清除屏幕上的内容
				putimage(0, 0, &background1); // 重新绘制背景
				outtextxy(100, 270, log); // 重新输出用户名
				outtextxy(100, 570, pas); // 重新输出密码
				outtextxy(100, 420, username); // 输出更新后的用户名
				outtextxy(100, 670, password); // 输出更新后的密码
			}
		}
		else
		{
			password[index++] = ch;
			password[index] = '\0';
			putimage(0, 0, &background1);
			outtextxy(100, 270, log);
			outtextxy(100, 570, pas);
			outtextxy(100, 420, username);
			outtextxy(100, 670, password);
		}
	}
	if (check)
	{
		bool situation = UserData(username, password, true);
		return situation;
	}
	else
	{
		bool situation = UserData(username, password, false);
		return situation;
	}

}







