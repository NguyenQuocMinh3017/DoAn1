#include"Common.h"

void _Common::gotoXY(int pX, int pY) {
	COORD coord;
	coord.X = pX;
	coord.Y = pY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void _Common::fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void _Common::setColor(int k)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}

void _Common::ReSet()
{
	setColor(15);
	system("CLS");
}

void _Common::Khung(int x, int y, int a, int b)
{

	for (int i = y; i < y + b; i++)
	{
		gotoXY(x, i); putchar(204);
		gotoXY(x + a, i); putchar(185);
	}
	for (int i = x; i < x + a; i++)
	{
		gotoXY(i, y); putchar(203);
		gotoXY(i, y + b); putchar(202);
	}
	gotoXY(x, y); putchar(201);
	gotoXY(a + x, y); putchar(187);
	gotoXY(x, b + y); putchar(200);
	gotoXY(a + x, b + y); putchar(188);
}

void _Common::TrangChu()
{
	FILE *f = fopen("TrangChu.txt", "rt");
	if (f == NULL)
	{
		printf("Loi Do Hoa!\n");
		return;
	}
	setColor(9);
	char a;
	while (!feof(f))
	{
		a = fgetc(f);
		if (a == -37)
			setColor(14);
		putchar(a);
	}
}

int _Common::Menu(char S[][20], int first, int last)
{
	ReSet();
	TrangChu();

	int chon = first, cl;
	unsigned char ch;
	setColor(14);
	Khung(19, 13, 17, last - first + 2);
	do
	{
		for (int i = first; i <= last; i++)
		{
			cl = (chon == i ? 240 : 15);
			setColor(cl);
			gotoXY(20, i - first + 14);
			printf(S[i]);
		}
		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			if (ch == 80)
				chon == last ? chon = first : chon++;
			if (ch == 72)
				chon == first ? chon = last : chon--;
		}
		Sleep(100);
	} while (ch != '\r');
	setColor(15);
	return chon;
}