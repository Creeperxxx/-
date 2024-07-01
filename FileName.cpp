#include <iostream>
#include <easyx.h>
using namespace std;

int main()
{
	initgraph(800, 600);

	while (true)
	{
		ExMessage m;
		m = getmessage(EX_MOUSE);
		if (m.message == WM_MOUSEMOVE)
		{
			putpixel(m.x, m.y, RED);
		}
	}
	return 0;
}