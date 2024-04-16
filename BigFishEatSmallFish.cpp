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
#include <chrono> // ���ͷ�ļ���ʹ��ʱ���
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
	int gamelevel;
	int score;
};

struct Fish fishs[22];

IMAGE fishIMG[22][2];

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

typedef struct Node {
	char username[20]; // �����û�����󳤶�Ϊ19������һ��������'\0'
	int score;
	struct Node* next;
} Node;

// ȫ�ֱ�������Ϊ�����ͷ�ڵ�
Node* head = NULL;
 // �����ͷָ��

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




//��Ϸģ��
int starting();
void game();
void History();
void supertoolinit();

//----------------------------------------------------------------------------------------------------------------------------------------

void DrawButten(int left, int top, int right, int bottom, const char* text) //���Ʊ�׼��ť
{
	setfillcolor(LIGHTGRAY);
	solidroundrect(left, top, right, bottom, 10, 10); //��ʽ�ʹ�С
	setbkmode(TRANSPARENT);
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
	int HistoryLeft = 860, HistoryTop = 590, HistoryRight = 1060, HistoryDown = 690;
	LOGFONT Log{};
	settextcolor(GREEN);
	Log.lfQuality = ANTIALIASED_QUALITY;
	Log.lfHeight = 50;
	strcpy(Log.lfFaceName, "����� б��");
	settextstyle(&Log);
	DrawButten(LoginLeft, LoginTop, LoginRight, LoginDown, "login"); //���Ƶ�¼��ť
	DrawButten(SignUpLeft, SignUpTop, SignUpRight, SignUpDown, "SignUp"); //����ע�ᰴť
	DrawButten(ExitLeft, ExitTop, ExitRight, ExitDown, "Exit"); //�����˳�ͼ��
	DrawButten(HistoryLeft, HistoryTop, HistoryRight, HistoryDown, "History");
	bool LoginClicked = false; //���õ�¼��ťΪfalse
	bool SignUpClicked = false; //����ע�ᰴťΪfalse
	bool ExitClicked = false; //�����˳���ťΪfalse
	bool HistoryClicked = false;
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
				else if (isPointInsideRectangle(x, y, HistoryLeft, HistoryTop, HistoryRight, HistoryDown))
				{
					LoginClicked = false; //���õ�¼��ťΪfalse
					SignUpClicked = false; //����ע�ᰴťΪfalse
					ExitClicked = false; //�����˳���ťΪfalse
					HistoryClicked = true;
				}

			}
			else if (msg.uMsg == WM_LBUTTONUP) //����������Ƿ�̧��
			{
				if (LoginClicked)//��¼����
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
				else if (SignUpClicked)//ע�����
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
	strcpy(Log.lfFaceName, "����� б��");
	settextstyle(&Log);

	while (1)
	{
		
		char add[] = "��";
		char scoretext[100];
		_itoa(fishs[0].score, scoretext, 10);
		strcat(scoretext, add);
		BeginBatchDraw(); // ��ʼ˫�����ͼ
		putimage(0, 0, &background, SRCCOPY);// �����⻭���ϻ��Ʊ���
		transparentimage3(NULL, 1700, 50, &countinue);
		transparentimage3(NULL, fishs[0].x, fishs[0].y, &fishIMG[0][fishs[0].dir]);
		FishPut(fishs[0].gamelevel);
		//pause();
		outtextxy(1500, 50, scoretext);
		FlushBatchDraw(); // ˢ�»���������ͼ��һ���Ի��Ƶ���Ļ��

		control();
		if (ontimer(10, 0))
		{
			fishmove();
		}
		resetothers();
		if (gameover() == 1)
		{
			EndBatchDraw(); // ����˫�����ͼ
			addScore(Account, fishs[0].score); // ��ӷ��������� // ��ʾ��ʷ��¼
			break;
		}
	}
	//closegraph(); // �ر�ͼ�δ���
}

void addScore(char* Account, int score)
{
	// �����½ڵ�
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		// �ڴ����ʧ��
		fprintf(stderr, "Memory allocation failed.\n");
		return;
	}

	// �����û������½ڵ�
	strncpy(newNode->username, Account, sizeof(newNode->username) - 1);
	newNode->username[sizeof(newNode->username) - 1] = '\0'; // ȷ���ַ�������

	// ���÷���
	newNode->score = score;

	// ���½ڵ��nextָ��ָ��ǰ������β�ڵ�
	newNode->next = NULL;

	// �������Ϊ�գ��½ڵ㼴Ϊͷ�ڵ�
	if (head == NULL) {
		head = newNode;
	}
	else {
		// ���򣬱�������ĩβ�����½ڵ���ӵ�ĩβ
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
	const int borderWidth = 100; // ������Ļ��Ե�ı߽���

	if (type == ROLE) // ��ҽ�ɫ��ʼ��
	{
		fishs[type].x = BKWIDTH / 2 - 60; // ��ʼλ������Ļ����
		fishs[type].y = BKHIGH / 2 - 60;
		fishs[type].dir = RIGHT; // ��ʼ��������
		fishs[type].type = ROLE;
		fishs[type].w = FISH_MIN_W + 30; // ��ҽ�ɫ�Ŀ��
		fishs[type].h = (int)(fishs[type].w / fishs[type].rate); // ���ݱ������ø߶�
	}
	else // ������ĳ�ʼ��
	{
		// ���ѡ�����ɷ�������ң�
		int spawnSide = rand() % 2 == 0 ? LEFT : RIGHT;
		fishs[type].dir = spawnSide;

		// �������ɷ������ó�ʼλ�ã�����Ļ��
		if (spawnSide == LEFT)
		{
			fishs[type].x = -fishs[type].w; // �����Ļ��
		}
		else
		{
			fishs[type].x = BKWIDTH; // �Ҳ���Ļ��
		}
		fishs[type].y = borderWidth + rand() % (BKHIGH - 2 * borderWidth); // ��������ڶ����߽����������

		// �������������ͺʹ�С
		fishs[type].type = rand() % (FISH_MAX_NUMS - 1) + 1;
		fishs[type].w = FISH_MIN_W + 20 * type;
		fishs[type].h = (int)(fishs[type].w / fishs[type].rate);
		fishs[type].gamelevel = type;
	}
}

// �ƶ���
void fishmove()
{
	const int borderWidth = 100; // ������Ļ��Ե�ı߽���

	for (int i = 1; i < FISH_MAX_NUMS; i++)
	{
		switch (fishs[i].dir)
		{
		case LEFT:
			fishs[i].x -= 2; // �����ƶ�
			// ����Ƿ��Ƴ���Ļ���
			if (fishs[i].x + fishs[i].w < 0)
			{
				// ������Ƴ�����Ļ��࣬�������·�������Ļ�Ҳ�
				fishs[i].x = BKWIDTH;
				fishs[i].y = borderWidth + rand() % (BKHIGH - 2 * borderWidth);
			}
			break;
		case RIGHT:
			fishs[i].x += 2; // �����ƶ�
			// ����Ƿ��Ƴ���Ļ�Ҳ�
			if (fishs[i].x > BKWIDTH)
			{
				// ������Ƴ�����Ļ�Ҳ࣬�������·�������Ļ���
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
			loadimage(&fishIMG[i][j], filename, fishs[i].w, fishs[i].h, true);				//��������ͼƬ

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
	if (!peekmessage(&msg, EX_MOUSE))  // ���û�������Ϣ
	{
		return;  // ֱ����������
	}

	// �������Ϣ��������Ϣ
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

} //���ű���//����

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
}//�߽���

int eatfish(int type)
{
	//���������ཻ
	//���Ͻ������ֵ

	int minx = max(fishs[ROLE].x, fishs[type].x);
	int miny = max(fishs[ROLE].y, fishs[type].y);
	//���½�����Сֵ
	int maxx = min(fishs[ROLE].x + fishs[ROLE].w, fishs[type].x + fishs[type].w);
	int maxy = min(fishs[ROLE].y + fishs[ROLE].h, fishs[type].y + fishs[type].h);

	if (minx > maxx || miny > maxy)
	{
		return 0;			//���ཻ
	}
	else
	{
		//ʹ�õȼ��ж�
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
			return 0;							//��һ�����ƻ����ƶ�ʱ��ӻ���
		}
		else
		{
			return 1;
		}
	}

}

int gameover()
{
	for (int i = 1; i < fishs[0].gamelevel + 3; i++)//����Դ��i < FISH_MAX_NUMS)
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
	Log.lfQuality = PROOF_QUALITY;
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
			strcpy(Account,username);
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
