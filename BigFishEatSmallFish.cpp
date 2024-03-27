#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "MSIMG32.LIB")

#define BKWIDTH 1920; // �������
#define BKHIGH  1080; // 



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
void EatenFish();
void initfish(int type);
bool UserData(char* username, char* password, bool check);
typedef struct User //�ṹ�������洢�û�����
{
	char* username;
	char* password;
	int score;
};

struct Fish
{
	int x;
	int y;
	int dir;			//��ķ���
	int type;			//�������
	double rate;
	int w;
	int h;
};
const int FISH_MAX_NUMS = 20;
struct Fish fish[FISH_MAX_NUMS];
IMAGE fishIMG[20][2];

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
			
			
		BeginBatchDraw(); // ��ʼ˫�����ͼ

		putimage(0, 0, &background, SRCCOPY);// �����⻭���ϻ��Ʊ���

			
			
		MOUSEMSG msg = GetMouseMsg();
		int x, y;
		x = msg.x;
		y = msg.y;
		PlayerFish(x, y);
		EatenFish();
		FlushBatchDraw(); // ˢ�»���������ͼ��һ���Ի��Ƶ���Ļ��
	}
	

	closegraph(); // �ر�ͼ�δ���
}

void PlayerFish(int x, int y)
{

	IMAGE PlayerFish;
	loadimage(&PlayerFish, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/PlayerFish.png", 100, 100, true); // �����⻭���ϻ���С��
	transparentimage3(NULL, x, y, &PlayerFish);

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
void initfish(int type)
{
	if (type == ROLE)
	{
		fish[type].x = BKWIDTH / 2 - 60;
		fish[type].y = BKHIGH / 2 - 60;
		fish[type].dir = ASPECT_RIGHT;
		fish[type].type = ROLE;
		fish[type].w = (FISH_MIN_W + 30);
		fish[type].h = (int)(fish[type].w / fish[type].rate);
	}
	else
	{
		fish[type].type = rand() % (FISH_MAX_NUMS - 1) + 1;
		int dir = rand() % 10 > 5 ? ASPECT_LEFT : ASPECT_RIGHT;		//Ӣ��ð��
		fish[type].dir = dir;
		fish[type].y = rand() % 90 * 10 + 50;
		fish[type].x = dir == ASPECT_LEFT ? rand() % BOARD + BKWIDTH : -1 * rand() % BOARD;
		fish[type].w = FISH_MIN_W + 20 * type;
		fish[type].h = (int)(fish[type].w / fish[type].rate);
	}
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
				sprintf(filename, _T("E:/designprogramme/Cprogramme/BigfishEatSmallfish/image/fish%dleft.png"), i);
				break;
			case 1:
				sprintf(filename, _T("E:/designprogramme/Cprogramme/BigfishEatSmallfish/image/fish%dright.png"), i);
				break;
			}
			loadimage(&fishIMG[i][j], filename, fish[i].w, fish[i].h, true);				//��������ͼƬ

		}
	}
}

void Drawfish()
{
	for (int i = 0; i < rolegrade + 3; i++)						//���ڼ��Ϸ������ƺ���ӵȼ�
	{
		transparentimage3(NULL, fish[i].x, fish[i].y, &fishIMG[i][fish[i].dir]);
	}
}

void moveothers()
{
	for (int i = 1; i < FISH_MAX_NUMS; i++)
	{
		switch (fish[i].dir)
		{
		case ASPECT_LEFT:
			fish[i].x -= 5;
			break;
		case ASPECT_RIGHT:
			fish[i].x += 5;
			break;
		}
	}
}