#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <time.h>
#include <chrono> // ���ͷ�ļ���ʹ��ʱ���
#pragma comment(lib, "MSIMG32.LIB")
#define LEVEL 5
#define PLAYER 0
#define LEFT -1
#define RIGHT 1
#define FISH_MAX_NUMS 10
#define TIMER_MAX 10

struct Fish //�����������
{
	int x;
	int y;
	int dir;		//��ķ���
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
struct msg
{
	USHORT message;					// ��Ϣ��ʶ
	union
	{
		// �����Ϣ������
		struct
		{
			bool ctrl : 1;		// Ctrl ���Ƿ���
			bool shift : 1;		// Shift ���Ƿ���
			bool lbutton : 1;		// �������Ƿ���
			bool mbutton : 1;		// ����м��Ƿ���
			bool rbutton : 1;		// ����Ҽ�
			short x;				// ���� x ����
			short y;				// ���� y ����
			short wheel;			// �����ֹ���ֵ��Ϊ 120 �ı���
		};

		// ������Ϣ������
		struct
		{
			BYTE vkcode;			// �������������
			BYTE scancode;			// ������ɨ���루������ OEM��
			bool extended : 1;		// �����Ƿ�����չ��
			bool prevdown : 1;		// ������ǰһ��״̬�Ƿ���
		};

		// �ַ���Ϣ������
		TCHAR ch;

		// ������Ϣ������
		struct
		{
			WPARAM wParam;
			LPARAM lParam;
		};
	};
};


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
	IMAGE background,text;
	
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	loadimage(&text, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/text.png", 800, 40, true);
	// Display the image
	putimage(0, 0, &background);
	putimage(550, 150, &text);
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
				else if (SignUpClicked)//ע�����
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
		BeginBatchDraw(); // ��ʼ˫�����ͼ
		putimage(0, 0, &background, SRCCOPY);// �����⻭���ϻ��Ʊ���

		FishPut(LEVEL);
		transparentimage3(NULL, fishs[0].x, fishs[0].y, &fishIMG[0][0]);

		FlushBatchDraw(); // ˢ�»���������ͼ��һ���Ի��Ƶ���Ļ��
		control();
		if (ontimer(10, 0))
		{
			fishmove();
		}
		//resetothers();

	}
	closegraph(); // �ر�ͼ�δ���
}

//-----------------------------------------------------------------------------------------------------------------------------------------


void Fishload()//����ȫ�����ͼƬ���ŵ��ڴ��
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
			fishs[type].dir = LEFT; // ��
			fishs[type].type = 0;
			fishs[type].w = (LEVEL * 100);
			fishs[type].h = (int)(fishs[type].w / fishs[type].rate);

		}
		else
		{
			fishs[type].type = rand() % (21 - 1) + 1;  // ����һ��1��20֮�������������ڱ�ʾ�������
			int dir = rand() % 10 > 5 ? LEFT : RIGHT;  // ����һ���������������5��dirΪ0����ʾ�󣩣�����Ϊ1����ʾ�ң�
			fishs[type].dir = dir;  // ��������ɵķ���ֵ����Ӧ��ķ�������
			fishs[type].y = rand() % 90 * 10 + 50;  // ����һ��50��950֮�������������ڱ�ʾ���y����
			fishs[type].x = dir == 0 ? rand() % 400 + 1920 : -1 * rand() % 400;  // ��dirΪ0������1920��2320֮������x���ꣻ�����ڸ�400��0֮������x���꣬�����ж������߻����ұ߳���
			fishs[type].w = 100 + 20 * type;  // ����������ͼ�����Ŀ�ȣ�������������Ӷ�����
			fishs[type].h = (int)(fishs[type].w / fishs[type].rate);  // ������Ŀ�߱ȼ�����ĸ߶�
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
			loadimage(&fishIMG[i][j], filename, fishs[i].w, fishs[i].h, true); //��������ͼƬ

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

void fishmove()					//������Ҫ�޸������������
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
	if (!peekmessage(&msg, EX_MOUSE))  // ���û�������Ϣ
	{
		return;  // ֱ����������
	}

	// �������Ϣ��������Ϣ
	fishs[0].x = msg.x;
	fishs[0].y = msg.y;
}


void FishPut(int level)
{
	for (int i = 1; i < level + 3; i++)						//���ڼ��Ϸ������ƺ���ӵȼ�
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

bool AccountInput(char* Account, char* Password, bool check)
{
	IMAGE background1;
	loadimage(&background1, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	char log[] = "Username";
	LOGFONT Log{};
	settextcolor(GREEN);
	Log.lfQuality = ANTIALIASED_QUALITY;
	Log.lfHeight = 80;
	strcpy(Log.lfFaceName, "����� б��");
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
			if (index > 0) // ����Ƿ�����������
				break;
		}
		else if (ch == 8) // ����Ƿ�Ϊ�˸��
		{
			if (index > 0)
			{
				index--;
				username[index] = '\0';
				cleardevice(); // �����Ļ�ϵ�����
				putimage(0, 0, &background1); // ���»��Ʊ���
				outtextxy(100, 270, log); // ��������û���
				outtextxy(100, 570, pas); // �����������
				outtextxy(100, 420, username); // ������º���û���
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

	index = 0; // ���������Խ�����������

	while (1)
	{
		char ch = _getch();
		if (ch == '\r' || ch == '\n')
		{
			if (index > 0) // ����Ƿ�����������
				break;
		}
		else if (ch == 8) // ����Ƿ�Ϊ�˸��
		{
			if (index > 0)
			{
				index--;
				password[index] = '\0';
				cleardevice(); // �����Ļ�ϵ�����
				putimage(0, 0, &background1); // ���»��Ʊ���
				outtextxy(100, 270, log); // ��������û���
				outtextxy(100, 570, pas); // �����������
				outtextxy(100, 420, username); // ������º���û���
				outtextxy(100, 670, password); // ������º������
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







