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

struct Fish //�����������
{
	int x;
	int y;
	int dir;			//��ķ���
	int type;		//�������
	double rate;
	int w;
	int h;
	IMAGE picture;
	int level;
	int score;
};
struct Fish fishs[21];
IMAGE fishIMG[21][2];


typedef struct User //�ṹ�������洢�û�����
{
	char* username;
	char* password;
	int score;
};

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
void initfish(int type);
bool UserData(char* username, char* password, bool check);
void initfishrole();
void initfish(int type);
void Fishload();
void FishPut(int level);
void control();

struct User* users = NULL;
int num_users = 0;

//��Ϸģ��
int starting();
int game();
int History();

//----------------------------------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------------------------------

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

int game()
{
	void setrate();
	IMAGE background;
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	// Display the image
	Fishload();
	BeginBatchDraw(); // ��ʼ˫�����ͼ
	while (1)
	{
		
		putimage(0, 0, &background, SRCCOPY);// �����⻭���ϻ��Ʊ���
		FishPut(1);
		FlushBatchDraw(); // ˢ�»���������ͼ��һ���Ի��Ƶ���Ļ��
		control();

	}
	closegraph(); // �ر�ͼ�δ���
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
			loadimage(&fishIMG[i][j], filename, fishs[i].w, fishs[i].h, true);				//��������ͼƬ

		}
	}
}
void initfish(int type)					//������Ҫ�޸������������
{
	MOUSEMSG msg = GetMouseMsg();
	if (type == 0)
	{
		fishs[type].x = msg.x;
		fishs[type].y = msg.y;
		fishs[type].dir = 0; // ��
		fishs[type].type = 0;
		fishs[type].w = (100 + 30);
		fishs[type].h = (int)(fishs[type].w / fishs[type].rate);
	}
	else
	{
		fishs[type].type = rand() % (21 - 1) + 1;
		int dir = rand() % 10 > 5 ? 0 : 1; //0 ��ʾ��1��ʾ��
		fishs[type].dir = dir;
		fishs[type].y = rand() % 90 * 10 + 50;
		fishs[type].x = dir == 0 ? rand() % 400 + 1920 : -1 * rand() % 400; // 400 �Ǳ߽��ж�
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
	for (int i = 0; i < level + 3; i++)						//���ڼ��Ϸ������ƺ���ӵȼ�
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