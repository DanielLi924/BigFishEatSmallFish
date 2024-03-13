#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#pragma comment(lib, "MSIMG32.LIB")

void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg -> getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	A
}

// ����ģ��
bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom); //�����ģ��
void DrawButten(int left, int top, int right, int bottom, const char* text); //������Ϸ��׼��ť
void PlayerFish(int x,int y);
void EatedFish(int x,int y);
//��Ϸģ��
int starting();
int game();
int History();


int main()//������
{
	int situation;//״̬����
	initgraph(1920, 1080);//�����ߴ�
	
	situation = starting();//����������
	if (situation == 1)
	{
		
		cleardevice();
		game();
	}
	else if (situation == 2)
	{
		cleardevice();
		return 0;
	}
}

int starting()
{
	initgraph(1920, 1080);
	int situation;
	IMAGE img;
	loadimage(&img, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);
	// Display the image
	putimage(0, 0, &img);
	int LoginLeft = 860, LoginTop = 290, LoginRight = 1060, LoginDown = 390; //Login��ť����
	int SignUpLeft = 860, SignUpTop = 490, SignUpRight = 1060, SignUpDown = 590;//SignUp��ť����
	int ExitLeft = 860, ExitTop = 690, ExitRight = 1060, ExitDown = 790;//�˳���ť����
	DrawButten(LoginLeft,LoginTop, LoginRight, LoginDown, "login"); //���Ƶ�¼��ť
	DrawButten(SignUpLeft, SignUpTop, SignUpRight, SignUpDown, "SignUp"); //����ע�ᰴť
	DrawButten(ExitLeft, ExitTop, ExitRight,ExitDown, "Exit"); //�����˳�ͼ��
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
				if (LoginClicked) 
				{
					char Account[20];  // ���ڴ洢������û���
					char Password[20]; //���ڴ洢���������
					InputBox(Account,20, "Your Accunt:(С��10���ַ����벻Ҫ����ո����������Ҫ�����˻�����Ҫ��������������κ�����ֱ�ӵ��ȷ��)","Account","\0",0,0,true);//��ȡ�û��˻�
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "С��10���ַ����벻Ҫ����ո����������Ҫ�����˻�����Ҫ��������������κ�����ֱ�ӵ��ȷ��", "Password", "\0", 0, 0,true);//��ȡ�û�����
						situation = 1; 
						return situation;
					}
					else
					{
						
					}
					
					
				}
				else if (SignUpClicked)
				{
					char Account[20];
					char Password[20];
					InputBox(Account, 20, "Your Accunt:(С��10���ַ����벻Ҫ����ո����������Ҫ�����˻�����Ҫ��������������κ�����ֱ�ӵ��ȷ��)", "Account", "\0", 0, 0, true);//��ȡ�û��˻�
					if (Account[0] != '\0')
					{
						InputBox(Password, 20, "Your Password:(In less than 10 character)", "Password", "\0", 0, 0, false);//��ȡ�û�����
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
	initgraph(1920, 1080); // ��ʼ��ͼ�δ���

	IMAGE background;
	loadimage(&background, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg", 1920, 1080, true);

	while (1)
	{
		MOUSEMSG msg = GetMouseMsg();
		int x, y;
		x = msg.x;
		y = msg.y;

		BeginBatchDraw(); // ��ʼ˫�����ͼ

		putimage(0, 0, &background, SRCCOPY);// �����⻭���ϻ��Ʊ���

		PlayerFish(x, y);
		EatenFish(x,y,level);
		FlushBatchDraw(); // ˢ�»���������ͼ��һ���Ի��Ƶ���Ļ��
	}

	closegraph(); // �ر�ͼ�δ���
}

void PlayerFish(int x,int y)
{
	
	IMAGE PlayerFish;
	loadimage(&PlayerFish, "C:/Users/Cheng/Desktop/test.jpg", 20, 20, true); // �����⻭���ϻ���С��
	putimage(x, y, &PlayerFish);
}

void EatenFish(int x, int y,int level)
{
	IMAGE fish[19];
	int random_x, random_y;
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
			loadimage(&fish[random_fish], "", true);
		}


		
	}
}