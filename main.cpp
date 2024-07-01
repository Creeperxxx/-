#include <iostream>
#define _USE_MATH_DEFINES
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
using namespace std; 

#define RADIUS 15
#define WIDTH 800
#define HEIGHT 600
#define PERIOD 7
#define RIGHT_EDGE WIDTH*3/4
#define BLT 1
#define BAFFLE_WIDTH RADIUS*8
#define BAFFLE_HEIGHT RADIUS*1/2
#define BALL_PATH RADIUS


void test01();
bool test02();

void ballnext(int &x, int &y, double &radians,int b_x,int b_y,bool& flag2);
void putboard(int x, int y, int width, int height);
void putball(int x, int y);
int mousemove(int& pre_x,ExMessage& msg);
int keymove();
void puttext(int x, int y, int h, char *c);

int main()
{
	initgraph(WIDTH,HEIGHT);
	int x = WIDTH / 2;
	int y = RADIUS;
	int b_x = RIGHT_EDGE / 2 - 4 * RADIUS;
	int b_y = HEIGHT - BLT - BAFFLE_HEIGHT;
	int b_h = BAFFLE_HEIGHT;
	int b_w = BAFFLE_WIDTH;
	setfillcolor(WHITE);
	setlinecolor(BLACK);

	srand((unsigned int)time(NULL));
	double radians = ((rand() % 91 + 45) / 1.0) * M_PI / 180.0;
	
	/*int mouse_prex = 0;*/
	int count = 0;
	while (true)
	{
		BeginBatchDraw();
		cleardevice();
		setbkcolor(WHITE);

		/*b_x = b_x + mousemove(mouse_prex, msg);
		if (b_x + BLT < 0)
		{
			b_x = BLT + 0;
		}
		if (b_x + BAFFLE_WIDTH + BLT > WIDTH)
		{
			b_x = WIDTH - BLT - BAFFLE_WIDTH;
		}*/

		/*ExMessage m;
		int distance = 0;
		if (peekmessage(&m,EX_MOUSE)&&(m.message == WM_MOUSEMOVE))
		{
			if (mouse_prex == 0)
			{
				mouse_prex = m.x;
			}
			if (mouse_prex < m.x)
			{
				distance = 5;
			}
			else
			{
				distance = -5;
			}
		}*/
		
		int distance = keymove();
		b_x = b_x + distance;
		if (b_x + BLT < 0)
		{
			b_x = BLT + 0;
		}
		if (b_x + BAFFLE_WIDTH + BLT > RIGHT_EDGE)
		{
			b_x = RIGHT_EDGE - BLT - BAFFLE_WIDTH;
		}
		
		bool flag2 = true;
		ballnext(x, y, radians,b_x,b_y,flag2);
		if (!flag2)
		{
			x = WIDTH / 2;
			y = RADIUS;
			radians = ((rand() % 91 + 45) / 1.0) * M_PI / 180.0;
			count++;
			cout << count << " ";

		}
		putball(x, y);
		putboard(RIGHT_EDGE, BLT, RADIUS / 2,HEIGHT - 2 * BLT);
		putboard(b_x, b_y, b_w, b_h);

		Sleep(PERIOD);
		FlushBatchDraw();

		if (test02())
		{
			break;
		}
	}
	EndBatchDraw();
	return 0;
}

void ballnext(int& x, int& y, double& radians,int b_x,int b_y,bool &flag2)
{
	int f_x = (int)(x + BALL_PATH * cos(radians));
	int f_y = (int)(y + BALL_PATH * sin(radians));

	bool flag1 = true;
	while (true)
	{
		bool flag = true;
		if (f_x > RIGHT_EDGE- RADIUS)
		{
			f_x = 2 * (RIGHT_EDGE - RADIUS) - f_x;
			radians = M_PI - radians;
		}
		if (f_x < RADIUS)
		{
			f_x = 2 * RADIUS - f_x;
			radians = M_PI - radians;
		}
		if (f_y < RADIUS)
		{
			f_y = 2 * RADIUS - f_y;
			radians = -radians;
		}
		if (f_y > HEIGHT - RADIUS)
		{
			f_y = 2 * (HEIGHT - RADIUS) - f_y;
			radians = -radians;
			flag2 = false;
		}
		if ( f_x>=b_x&&f_x <= b_x + BAFFLE_WIDTH && f_y >= HEIGHT - 2 * BLT - BAFFLE_HEIGHT-RADIUS)
		{
			f_y = 2 * (HEIGHT - 2 * BLT - BAFFLE_HEIGHT - RADIUS) - f_y;
			radians = -radians;
			flag2 = true;
		}
		if (f_x > b_x + BAFFLE_WIDTH+BLT &&
			pow(f_x - (b_x + BLT + BAFFLE_WIDTH), 2) + pow(f_y - b_y-BLT, 2) <= RADIUS * RADIUS)
		{
			if (flag1)
			{
				radians += 4 * M_PI;
				while (radians >= 2 * M_PI)
				{
					radians -= M_PI_2;
				}
				flag1 = false;
			}
			f_x = (int)(x + 1/4*BALL_PATH * cos(radians));
			f_y = (int)(y + 1/4*BALL_PATH * sin(radians));
			flag = false;
			flag2 = true;
		}
		if (f_x < b_x + BLT && pow(f_x - (b_x - BLT), 2) + pow(f_y - b_y - BLT, 2) <= RADIUS * RADIUS)
		{
			radians += 4 * M_PI;
			while (radians >= 3 / 2 * M_PI)
			{
				radians -= M_PI_2;
			}
			f_x = (int)(x + 1 / 4 * RADIUS * cos(radians));
			f_y = (int)(y + 1 / 4 * RADIUS * sin(radians));
			flag = false;
			flag2 = true;
		}
		if (f_x >= RADIUS && f_x <= RIGHT_EDGE - RADIUS && f_y >= RADIUS && f_y <= HEIGHT - RADIUS&&flag)
		{
			x = f_x;
			y = f_y;
			break;
		}
	}
}

void test01()
{
	double ra;
	int count = 0;
	double max = 90.0;
	double min = 90.0;
	double sum = 0.0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++)
	{
		ra = (rand() % 91 + 45) / 1.0;
		if (ra < min)
		{
			min = ra;
		}
		if (ra > max)
		{
			max = ra;
		}
		sum += ra;
		cout << ra << " ";
		count++;
		if (count % 10 == 0)
		{
			cout << endl;
		}
	}
	cout << "最大：" << max << endl;
	cout << "最小：" << min << endl;
	cout << "平均：" << sum / 100.0 << endl;
	double test = 50.123456;
	cout << test << endl;
}

bool test02()
{
	ExMessage msg;
	peekmessage(&msg, EM_MOUSE);
	if (msg.message == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;
}

void putboard(int x, int y, int width, int height)
{
	setfillcolor(RGB(0, 191, 255));
	setlinestyle(PS_SOLID, BLT);
	
	fillrectangle(x, y, x + width, y + height);
}

void putball(int x, int y)
{
	setfillcolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	fillcircle(x, y, RADIUS);
}

int mousemove(int &pre_x,ExMessage& msg)
{
	if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_MOUSEMOVE)
	{
		if (pre_x == 0)
		{
			pre_x = msg.x;
			return 0;
		} 
		else if (pre_x > msg.x)
		{
			pre_x = msg.x;
			return -10*RADIUS;
		}
		else
		{
			pre_x = msg.x;
			return 10*RADIUS;
		}
	}
	return 0;
}

int keymove()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		return -RADIUS;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		return RADIUS;
	}
	return 0;
}

void puttext(int x, int y, int h, char*  c)
{
	settextcolor(BLACK);
	settextstyle(16, 0, _T("黑体"));
	LOGFONT l;
	gettextstyle(&l);
	l.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&l);
}