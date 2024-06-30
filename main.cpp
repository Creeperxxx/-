#include <iostream>
#define _USE_MATH_DEFINES
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
using namespace std; 

#define RADIUS 15
#define WIDTH 800
#define HEIGHT 600
#define PERIOD 10
#define RIGHT_EDGE WIDTH*3/4
#define BLT 1
#define BAFFLE_WIDTH RADIUS*8
#define BAFFLE_HEIGHT RADIUS*1/2


void test01();
bool test02();

void ballnext(int &x, int &y, double &radians,int b_x,int b_y);
void putboard(int x, int y, int width, int height);
void putball(int x, int y);

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
	
	BeginBatchDraw();
	while (true)
	{
		cleardevice();
		setbkcolor(WHITE);

		ballnext(x, y, radians,b_x,b_y);
		putball(x, y);
		putboard(RIGHT_EDGE, BLT, RADIUS / 2,HEIGHT - 2 * BLT);
		putboard(b_x, b_y, b_w, b_h);
		FlushBatchDraw();

		Sleep(PERIOD);
		if (test02())
		{
			break;
		}
	}
	EndBatchDraw();
	return 0;
}

void ballnext(int& x, int& y, double& radians,int b_x,int b_y)
{
	int f_x = (int)(x + RADIUS * cos(radians));
	int f_y = (int)(y + RADIUS * sin(radians));

	while (true)
	{
		
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
		}
		if ( f_x>=b_x&&f_x <= b_x + BAFFLE_WIDTH && f_y >= HEIGHT - 2 * BLT - BAFFLE_HEIGHT-RADIUS)
		{
			f_y = 2 * (HEIGHT - 2 * BLT - BAFFLE_HEIGHT - RADIUS) - f_y;
			radians = -radians;
		}
		if (f_x > b_x + BAFFLE_WIDTH+BLT &&
			pow(f_x - (b_x + BLT + BAFFLE_WIDTH), 2) + pow(f_y - b_y-BLT, 2) <= RADIUS * RADIUS)
		{
			radians += 4 * M_PI;
			while (radians >= 2 * M_PI)
			{
				radians -= M_PI_2;
			}
			f_x = (int)(x + 1/4*RADIUS * cos(radians));
			f_y = (int)(y + 1/4*RADIUS * sin(radians));
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
		}
		if (f_x >= RADIUS && f_x <= RIGHT_EDGE - RADIUS && f_y >= RADIUS && f_y <= HEIGHT - RADIUS)
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