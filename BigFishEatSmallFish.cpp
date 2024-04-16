#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <chrono> // 添加头文件以使用时间库
#pragma comment(lib, "MSIMG32.LIB")
#define PLAYER 0
#define LEFT 0
#define RIGHT 1
#define FISH_MAX_NUMS 21
#define TIMER_MAX 10
#define BOARD 400
#define BKWIDTH 1920
#define BKHIGH 1080
#define ROLE 0
#define FISH_MIN_W 50
char Account[20];

struct User* users = NULL;

int num_users = 0;

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
	int gamelevel;
	int score;
};

struct Fish fishs[22];

IMAGE fishIMG[22][2];

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

typedef struct Node {
	char username[20]; // 假设用户名最大长度为19，加上一个结束符'\0'
	int score;
	struct Node* next;
} Node;

// 全局变量，作为链表的头节点
Node* head = NULL;
 // 链表的头指针

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
bool UserData(char* username, char* password, bool check);
void fishmove();
void FishPut(int gamelevel);
void control();
void setrate();
int ontimer(int duration, int id);
bool AccountInput(char *Account, char *Password, bool situation);
void resetothers();
void initfish(int type);
void loadresource();
int eatfish(int i);
int gameover();
void addScore(char* username, int score);
void pause();




//游戏模块
int starting();
void game();
void History();
void supertoolinit();

//----------------------------------------------------------------------------------------------------------------------------------------

void DrawButten(int left, int top, int right, int bottom, const char* text) //绘制标准按钮
{
	setfillcolor(LIGHTGRAY);
	solidroundrect(left, top, right, bottom, 10, 10); //样式和大小
	setbkmode(TRANSPARENT);
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
	int HistoryLeft = 860, HistoryTop = 590, HistoryRight = 1060, HistoryDown = 690;
	LOGFONT Log{};
	settextcolor(GREEN);
	Log.lfQuality = ANTIALIASED_QUALITY;
	Log.lfHeight = 50;
	strcpy(Log.lfFaceName, "得意黑 斜体");
	settextstyle(&Log);
	DrawButten(LoginLeft, LoginTop, LoginRight, LoginDown, "login"); //绘制登录按钮
	DrawButten(SignUpLeft, SignUpTop, SignUpRight, SignUpDown, "SignUp"); //绘制注册按钮
	DrawButten(ExitLeft, ExitTop, ExitRight, ExitDown, "Exit"); //绘制退出图标
	DrawButten(HistoryLeft, HistoryTop, HistoryRight, HistoryDown, "History");
	bool LoginClicked = false; //设置登录按钮为false
	bool SignUpClicked = false; //设置注册按钮为false
	bool ExitClicked = false; //设置退出按钮为false
	bool HistoryClicked = false;
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
				else if (isPointInsideRectangle(x, y, HistoryLeft, HistoryTop, HistoryRight, HistoryDown))
				{
					LoginClicked = false; //设置登录按钮为false
					SignUpClicked = false; //设置注册按钮为false
					ExitClicked = false; //设置退出按钮为false
					HistoryClicked = true;
				}

			}
			else if (msg.uMsg == WM_LBUTTONUP) //检测鼠标左键是否抬起
			{
				if (LoginClicked)//登录界面
				{
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
				else if (HistoryClicked)
				{
					History();
				}

			}
		}
	}

}

void game()
{
	fishs[0].gamelevel = 1;
	int score = 0;
	setrate();
	IMAGE background;
	IMAGE countinue;
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/game.jpg", 1920, 1080, true);
	loadimage(&countinue, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/continue.png",30,30,true);
	// Display the image
	loadresource();
	LOGFONT Log{}; 
	Log.lfQuality = PROOF_QUALITY;
	Log.lfHeight = 30;
	strcpy(Log.lfFaceName, "得意黑 斜体");
	settextstyle(&Log);

	while (1)
	{
		
		char add[] = "分";
		char scoretext[100];
		_itoa(fishs[0].score, scoretext, 10);
		strcat(scoretext, add);
		BeginBatchDraw(); // 开始双缓冲绘图
		putimage(0, 0, &background, SRCCOPY);// 在虚拟画布上绘制背景
		transparentimage3(NULL, 1700, 50, &countinue);
		transparentimage3(NULL, fishs[0].x, fishs[0].y, &fishIMG[0][fishs[0].dir]);
		FishPut(fishs[0].gamelevel);
		//pause();
		outtextxy(1500, 50, scoretext);
		FlushBatchDraw(); // 刷新缓冲区，将图像一次性绘制到屏幕上

		control();
		if (ontimer(10, 0))
		{
			fishmove();
		}
		resetothers();
		if (gameover() == 1)
		{
			EndBatchDraw(); // 结束双缓冲绘图
			addScore(Account, fishs[0].score); // 添加分数到链表 // 显示历史记录
			break;
		}
	}
	//closegraph(); // 关闭图形窗口
}

void addScore(char* Account, int score)
{
	// 创建新节点
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		// 内存分配失败
		fprintf(stderr, "Memory allocation failed.\n");
		return;
	}

	// 复制用户名到新节点
	strncpy(newNode->username, Account, sizeof(newNode->username) - 1);
	newNode->username[sizeof(newNode->username) - 1] = '\0'; // 确保字符串结束

	// 设置分数
	newNode->score = score;

	// 将新节点的next指针指向当前的链表尾节点
	newNode->next = NULL;

	// 如果链表为空，新节点即为头节点
	if (head == NULL) {
		head = newNode;
	}
	else {
		// 否则，遍历链表到末尾，将新节点添加到末尾
		Node* current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
}

void History()
{
	char message[1024] = "";
	struct Node* current = head;
	while (current != NULL) {
		char record[256];
		snprintf(record, sizeof(record), "Player: %s\nScore: %d\n\n", current->username, current->score);
		strcat(message, record);
		current = current->next;
	}
	HWND hWnd = FindWindow(NULL, "BigFishEatSmallFish");
	MessageBox(hWnd, message, "History Records", MB_OK);
}

/*
void pause()
{
	isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom);
	transparentimage3(NULL, fishs[0].x, fishs[0].y, &fishIMG[0][fishs[0].dir]);
}
*/

void supertoolinit()
{
	IMAGE Shild;
	IMAGE ClearAllFish;
	IMAGE DoubleScore;
	loadimage(&Shild, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/shield.png", 100, 100, true);
	loadimage(&ClearAllFish, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/ClearAllFish.png", 100, 100, true);
	loadimage(&DoubleScore, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish1left.png", 100, 100, true);

}


//-----------------------------------------------------------------------------------------------------------------------------------------

void initfish(int type)
{
	const int borderWidth = 100; // 定义屏幕边缘的边界宽度

	if (type == ROLE) // 玩家角色初始化
	{
		fishs[type].x = BKWIDTH / 2 - 60; // 初始位置在屏幕中央
		fishs[type].y = BKHIGH / 2 - 60;
		fishs[type].dir = RIGHT; // 初始方向向右
		fishs[type].type = ROLE;
		fishs[type].w = FISH_MIN_W + 30; // 玩家角色的宽度
		fishs[type].h = (int)(fishs[type].w / fishs[type].rate); // 根据比例设置高度
	}
	else // 其他鱼的初始化
	{
		// 随机选择生成方向（左或右）
		int spawnSide = rand() % 2 == 0 ? LEFT : RIGHT;
		fishs[type].dir = spawnSide;

		// 根据生成方向设置初始位置，在屏幕外
		if (spawnSide == LEFT)
		{
			fishs[type].x = -fishs[type].w; // 左侧屏幕外
		}
		else
		{
			fishs[type].x = BKWIDTH; // 右侧屏幕外
		}
		fishs[type].y = borderWidth + rand() % (BKHIGH - 2 * borderWidth); // 随机生成在顶部边界宽度外的区域

		// 随机生成鱼的类型和大小
		fishs[type].type = rand() % (FISH_MAX_NUMS - 1) + 1;
		fishs[type].w = FISH_MIN_W + 20 * type;
		fishs[type].h = (int)(fishs[type].w / fishs[type].rate);
		fishs[type].gamelevel = type;
	}
}

// 移动鱼
void fishmove()
{
	const int borderWidth = 100; // 定义屏幕边缘的边界宽度

	for (int i = 1; i < FISH_MAX_NUMS; i++)
	{
		switch (fishs[i].dir)
		{
		case LEFT:
			fishs[i].x -= 2; // 向左移动
			// 检查是否移出屏幕左侧
			if (fishs[i].x + fishs[i].w < 0)
			{
				// 如果鱼移出了屏幕左侧，将其重新放置在屏幕右侧
				fishs[i].x = BKWIDTH;
				fishs[i].y = borderWidth + rand() % (BKHIGH - 2 * borderWidth);
			}
			break;
		case RIGHT:
			fishs[i].x += 2; // 向右移动
			// 检查是否移出屏幕右侧
			if (fishs[i].x > BKWIDTH)
			{
				// 如果鱼移出了屏幕右侧，将其重新放置在屏幕左侧
				fishs[i].x = -fishs[i].w;
				fishs[i].y = borderWidth + rand() % (BKHIGH - 2 * borderWidth);
			}
			break;
		}
	}
}

void initfishrole()
{
	fishs[0].w = FISH_MIN_W + 30 + 20 * fishs[0].gamelevel;
	fishs[0].h = ((int)(fishs[0].w / fishs[0].rate));
	loadimage(&fishIMG[ROLE][0], _T("D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish0left.png"), fishs[ROLE].w, fishs[ROLE].h, true);
	loadimage(&fishIMG[ROLE][1], _T("D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish0right.png"), fishs[ROLE].w, fishs[ROLE].h, true);
}

void loadresource()
{
	char filename[100] = { "" };
	for (int i = 0; i < FISH_MAX_NUMS; i++)
	{
		initfish(i);
		for (int j = 0; j < 2; j++)
		{
			switch (j)
			{
			case 0:
				sprintf(filename,"D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish%dleft.png", i);
				break;
			case 1:
				sprintf(filename,"D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish%dright.png", i);
				break;
			}
			loadimage(&fishIMG[i][j], filename, fishs[i].w, fishs[i].h, true);				//载入缩放图片

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

void control()
{
	ExMessage msg;
	if (!peekmessage(&msg, EX_MOUSE))  // 如果没有鼠标消息
	{
		return;  // 直接跳出函数
	}

	// 有鼠标消息，则处理消息
	if (fishs[0].x <= msg.x)
	{
		fishs[0].dir = 1;
		fishs[0].x = msg.x;
		fishs[0].y = msg.y;
	}
	else
	{
		fishs[0].dir = 0;
		fishs[0].x = msg.x;
		fishs[0].y = msg.y;
	}

	
}

void FishPut(int level)
{
	for (int i = 1; i < fishs[0].gamelevel + 3; i++)
	{
		transparentimage3(NULL, fishs[i].x, fishs[i].y, &fishIMG[i][fishs[i].dir]);
	}
}

void setrate()
{
	fishs[0].rate = 2.45;
	fishs[1].rate = 2.12;
	fishs[2].rate = 2.26;
	fishs[3].rate = 2.62;
	fishs[4].rate = 2.84;
	fishs[5].rate = 1.59;
	fishs[6].rate = 2.50;
	fishs[7].rate = 2.60;
	fishs[8].rate = 1.00;
	fishs[9].rate = 1.12;
	fishs[10].rate = 0.58;
	fishs[11].rate = 3.36;
	fishs[12].rate = 1.65;
	fishs[13].rate = 2.08;
	fishs[14].rate = 1.08;
	fishs[15].rate = 1.68;
	fishs[16].rate = 3.45;
	fishs[17].rate = 3.84;
	fishs[18].rate = 3.29;
	fishs[19].rate = 2.92;
	fishs[20].rate = 1.14;
	fishs[21].rate = 1.56;

} //缩放比例//比例

void resetothers()
{
	for (int i = 1; i < FISH_MAX_NUMS; i++)
	{
		switch (fishs[i].dir)
		{
		case LEFT:
			if (fishs[i].x < -400)
			{
				initfish(i);
			}
			break;
		case RIGHT:
			if (fishs[i].x > 1920 + 400)
			{
				initfish(i);
			}
			break;
		}
	}
}//边界检测

int eatfish(int type)
{
	//两个矩形相交
	//左上角求最大值

	int minx = max(fishs[ROLE].x, fishs[type].x);
	int miny = max(fishs[ROLE].y, fishs[type].y);
	//右下角求最小值
	int maxx = min(fishs[ROLE].x + fishs[ROLE].w, fishs[type].x + fishs[type].w);
	int maxy = min(fishs[ROLE].y + fishs[ROLE].h, fishs[type].y + fishs[type].h);

	if (minx > maxx || miny > maxy)
	{
		return 0;			//不相交
	}
	else
	{
		//使用等级判断
		if (fishs[ROLE].gamelevel >= fishs[type].gamelevel)
		{
			initfish(type);
			fishs[0].score = fishs[0].score + type;
			int result = fishs[0].score / 5;
			if (result >= 1 )
			{
				fishs[0].gamelevel = result;
				initfishrole();
			}
			return 0;							//下一步完善积分制度时添加积分
		}
		else
		{
			return 1;
		}
	}

}

int gameover()
{
	for (int i = 1; i < fishs[0].gamelevel + 3; i++)//问题源（i < FISH_MAX_NUMS)
	{
		if (eatfish(i) == 1)
		{
			return 1;
		}
	}

	return 0;
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
	Log.lfQuality = PROOF_QUALITY;
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
			strcpy(Account,username);
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
			Password = password;
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
