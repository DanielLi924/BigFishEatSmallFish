#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "MSIMG32.LIB")
#pragma warning(disable:4996)
#define GAME_WIDTH = 1920;
#define GAME_HEIGHT = 1080;


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
void Eatenfish();
bool UserData(char* username, char* password, bool check);
int randomRange(int min, int max);
void runFishAnimation();

typedef struct User //结构体用来存储用户数据
{
	char* username;
	char* password;
	int score;
};
struct User* users = NULL;
int num_users = 0;


//游戏模块
int starting();
int game();
//int History();


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
		while (1)
		{
			MOUSEMSG msg = GetMouseMsg();
			int x, y;
			x = msg.x;
			y = msg.y;

			BeginBatchDraw(); // 开始双缓冲绘图

			putimage(0, 0, &background, SRCCOPY);// 在虚拟画布上绘制背景

			PlayerFish(x, y);
	                                     		runFishAnimation();

			FlushBatchDraw(); // 刷新缓冲区，将图像一次性绘制到屏幕上
		}
	}
	

	closegraph(); // 关闭图形窗口
}

void PlayerFish(int x, int y)
{

	IMAGE PlayerFish;
	loadimage(&PlayerFish, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/PlayerFish.png", 100, 100, true); // 在虚拟画布上绘制小鱼
	transparentimage3(NULL, x, y, &PlayerFish);

}

typedef struct {
	int x;
	int y;
} Fish;

// Function to generate a random number within a range
int randomRange(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Function to generate a new fish
Fish generateFish() {
	Fish newFish;
	newFish.x = randomRange(0, 1919); // Generate random x-coordinate within game width
	newFish.y = randomRange(0, 1079); // Generate random y-coordinate within game height
	return newFish;
}

// Function to move the fish
void moveFish(Fish* fish) {
	// Example: Random movement
	fish->x += randomRange(-1, 1); // Move fish randomly in x-direction
	fish->y += randomRange(-1, 1); // Move fish randomly in y-direction

	// Ensure fish stays within game boundaries
	fish->x = (fish->x +1920) % 1920; // Wrap fish around if it goes out of screen horizontally
	fish->y = (fish->y + 1080) % 1080; // Wrap fish around if it goes out of screen vertically
}

// Function to run the fish animation
void runFishAnimation() 
{
	srand(time(NULL)); // Seed the random number generator

	IMAGE EatenFish;
	loadimage(&EatenFish, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/eatenfish1.png", 100, 100, true); // Load the fish image

	// Create two fish
	Fish fish1 = generateFish(); // Generate the first fish
	Fish fish2 = generateFish(); // Generate the second fish

	int i;
	for (i = 0; i < 100; i++) { // Run animation loop
		moveFish(&fish1); // Move the first fish
		moveFish(&fish2); // Move the second fish

		// Display fish positions
		transparentimage3(NULL, fish1.x, fish1.y, &EatenFish); // Display the first fish
		transparentimage3(NULL, fish2.x, fish2.y, &EatenFish); // Display the second fish

		// Simulate game loop delay
		Sleep(100); // Adjust sleep duration as needed for your game

		// Clear the screen
		cleardevice(); // Clear the graphics window
	}

	closegraph(); // Close graphics window
}


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

