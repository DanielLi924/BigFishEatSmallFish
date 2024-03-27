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


// ����ģ��
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //ʵ��͸��ͼƬ���
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom); //�����ģ��
void DrawButten(int left, int top, int right, int bottom, const char* text); //������Ϸ��׼��ť
void PlayerFish(int x, int y);
void Eatenfish();
bool UserData(char* username, char* password, bool check);
int randomRange(int min, int max);
void runFishAnimation();

typedef struct User //�ṹ�������洢�û�����
{
	char* username;
	char* password;
	int score;
};
struct User* users = NULL;
int num_users = 0;


//��Ϸģ��
int starting();
int game();
//int History();


int main()//������
{
	initgraph(1920, 1080);//�����ߴ�
	while (1)
	{
		int situation = 0;//״̬����

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
	int LoginLeft = 860, LoginTop = 290, LoginRight = 1060, LoginDown = 390; //Login��ť����
	int SignUpLeft = 860, SignUpTop = 490, SignUpRight = 1060, SignUpDown = 590;//SignUp��ť����
	int ExitLeft = 860, ExitTop = 690, ExitRight = 1060, ExitDown = 790;//�˳���ť����
	DrawButten(LoginLeft, LoginTop, LoginRight, LoginDown, "login"); //���Ƶ�¼��ť
	DrawButten(SignUpLeft, SignUpTop, SignUpRight, SignUpDown, "SignUp"); //����ע�ᰴť
	DrawButten(ExitLeft, ExitTop, ExitRight, ExitDown, "Exit"); //�����˳�ͼ��
	bool LoginClicked = false; //���õ�¼��ťΪfalse
	bool SignUpClicked = false; //����ע�ᰴťΪfalse
	bool ExitClicked = false; //�����˳���ťΪfalse
	while (1)
	{

		if (MouseHit) //�������Ƿ��л�¼�
		{
			MOUSEMSG msg = GetMouseMsg(); //����Ϣ����msg
			int x = msg.x; //��ȡ��� x ����
			int y = msg.y; //��ȡ��� y ����

			if (msg.uMsg == WM_LBUTTONDOWN) //�ж�����Ϊ�������������
			{
				if (isPointInsideRectangle(x, y, LoginLeft, LoginTop, LoginRight, LoginDown))
				{
					LoginClicked = true; //���õ�¼��ťΪtrue
					SignUpClicked = false; //����ע�ᰴťΪfalse
					ExitClicked = false; //�����˳���ťΪfalse
				}
				else if (isPointInsideRectangle(x, y, SignUpLeft, SignUpTop, SignUpRight, SignUpDown))
				{
					LoginClicked = false; //���õ�¼��ťΪfalse
					SignUpClicked = true; //����ע�ᰴťΪtrue
					ExitClicked = false; //�����˳���ťΪfalse
				}
				else if (isPointInsideRectangle(x, y, ExitLeft, ExitTop, ExitRight, ExitDown))
				{
					LoginClicked = false; //���õ�¼��ťΪfalse
					SignUpClicked = false; //����ע�ᰴťΪfalse
					ExitClicked = true; //�����˳���ťΪtrue
				}
			}
			else if (msg.uMsg == WM_LBUTTONUP) //����������Ƿ�̧��
			{
				if (LoginClicked)//��¼����
				{
					char Account[20];  // ���ڴ洢������û���
					char Password[20]; //���ڴ洢���������
					InputBox(Account, 20, "Your Accunt:(С��10���ַ����벻Ҫ����ո����������Ҫ�����˻�����Ҫ��������������κ�����ֱ�ӵ��ȷ��)", "Account", "\0", 0, 0, true);//��ȡ�û��˻�
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "С��10���ַ����벻Ҫ����ո����������Ҫ�����˻�����Ҫ��������������κ�����ֱ�ӵ��ȷ��", "Password", "\0", 0, 0, true);//��ȡ�û�����

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
				else if (SignUpClicked)//ע�����
				{
					char Account[20];
					char Password[20];
					InputBox(Account, 20, "Your Accunt:(С��10���ַ����벻Ҫ����ո����������Ҫ�����˻�����Ҫ��������������κ�����ֱ�ӵ��ȷ��)", "Account", "\0", 0, 0, true);//��ȡ�û��˻�
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "Your Password:(In less than 10 character)", "Password", "\0", 0, 0, false);//��ȡ�û�����
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

void DrawButten(int left, int top, int right, int bottom, const char* text) //���Ʊ�׼��ť
{
	setfillcolor(LIGHTGRAY);
	solidroundrect(left, top, right, bottom, 10, 10); //��ʽ�ʹ�С
	outtextxy(left + 10, top + 10, text);//�������
}

bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom)
{
	return (x >= left && x <= right && y >= top && y <= bottom); //�ж��Ƿ��ڰ�ť��
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

			BeginBatchDraw(); // ��ʼ˫�����ͼ

			putimage(0, 0, &background, SRCCOPY);// �����⻭���ϻ��Ʊ���

			PlayerFish(x, y);
	                                     		runFishAnimation();

			FlushBatchDraw(); // ˢ�»���������ͼ��һ���Ի��Ƶ���Ļ��
		}
	}
	

	closegraph(); // �ر�ͼ�δ���
}

void PlayerFish(int x, int y)
{

	IMAGE PlayerFish;
	loadimage(&PlayerFish, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/PlayerFish.png", 100, 100, true); // �����⻭���ϻ���С��
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
		// �����˺�������Ĵ���
		for (int i = 0; i < num_users; i++) {
			if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
				return true;
			}
		}
		return false;
	}
	else {
		// ������û�����
		num_users++; // �����û�����
		// ���·����ڴ��������µ��û�����
		struct User* temp = (struct User*)realloc(users, num_users * sizeof(struct User));
		if (temp == NULL) {
			// �ڴ����ʧ��
			printf("Memory allocation failed.\n");
			return false;
		}
		// ���� users ָ��
		users = temp;
		// Ϊ���û��� username �� password �����ڴ沢�����ַ���
		users[num_users - 1].username = (char*)malloc(strlen(username) + 1);
		if (users[num_users - 1].username == NULL) {
			printf("Memory allocation failed.\n");
			return false;
		}
		strcpy(users[num_users - 1].username, username);
		users[num_users - 1].password = (char*)malloc(strlen(password) + 1);
		if (users[num_users - 1].password == NULL) {
			printf("Memory allocation failed.\n");
			// ����ѡ���ͷ�֮ǰ������ڴ�
			free(users[num_users - 1].username);
			return false;
		}
		strcpy(users[num_users - 1].password, password);
		users[num_users - 1].score = 0; // �����ʼ����Ϊ 0
		printf("User data stored successfully!\n");
		return true;
	}
}

