#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

class Casino
{
private:
	wchar_t s[3][3];
	int balance;
public:
	Casino()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				s[i][j] = rand() % 4 + 49;
			}
		}
		balance = 1000;
	}
	void setBalance(int n)
	{
		balance += n;
	}
	int win()
	{
		if (s[0][1] == '1' and s[1][1] == '1' and s[2][1] == '1')
		{
			return 1;
		}
		else if (s[0][1] == '2' and s[1][1] == '2' and s[2][1] == '2')
		{
			return 2;
		}
		else if (s[0][1] == '3' and s[1][1] == '3' and s[2][1] == '3')
		{
			return 3;
		}
		else if (s[0][1] == '4' and s[1][1] == '4' and s[2][1] == '4')
		{
			return 4;
		}
		else
		{
			return 0;
		}
	}
	void spin(int i)
	{
		if (i < 10)
		{
			s[0][2] = s[0][1];
			s[0][1] = s[0][0];
			s[0][0] = rand() % 4 + 49;
			Sleep(i * 5);
		}
		if (i < 15)
		{
			s[1][2] = s[1][1];
			s[1][1] = s[1][0];
			s[1][0] = rand() % 4 + 49;
		}
		if (i < 30)
		{
			s[2][2] = s[2][1];
			s[2][1] = s[2][0];
			s[2][0] = rand() % 4 + 49;
		}
	}
	void window(int width, wchar_t* screen)
	{
		wstring gameName = { L"╔══════════════════════════╗║>><< ОДНОРУКИЙ БАНДИТ >><<║╚══════════════════════════╝" };
		wstring gameS = { L"╔═══════════╗║    │ │    ║║>>  │ │  <<║║    │ │    ║╚═══════════╝" };
		wstring gameB = { L"БАЛАНС:" };
		for (int i = 0; i < 74; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				screen[i + j * width] = ' ';
			}
		}
		screen[74 + 24 * width] = L'╝';
		screen[0 + 24 * width] = L'╚';
		screen[74 + 0 * width] = L'╗';
		screen[0 + 0 * width] = L'╔';
		for (int i = 1; i < 74; i++)
		{
			screen[i + 0 * width] = L'═';
			screen[i + 24 * width] = L'═';
		}
		for (int i = 1; i < 24; i++)
		{
			screen[0 + i * width] = L'║';
			screen[74 + i * width] = L'║';
		}
		int j = 1;
		int i = 24;
		for (int n = 0; n < 84; n++, i++)
		{
			if (n == 28 or n == 56)
			{
				j++;
				i = 24;
			}
			screen[i + j * width] = gameName[n];
		}
		j = 10;
		i = 31;
		for (int n = 0; n < 65; n++, i++)
		{
			if (n == 13 or n == 26 or n == 39 or n == 52)
			{
				j++;
				i = 31;
			}
			screen[i + j * width] = gameS[n];
		}
		i = 32;
		for (int n = 0; n < 7; n++, i++)
		{
			screen[i + 18 * width] = gameB[n];
		}
		string strB = to_string(balance);
		i = 40;
		for (int n = 0; n < size(strB); n++, i++)
		{
			screen[i + 18 * width] = strB[n];
		}
		int a = 35, b = 11;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				screen[a + b * width] = s[i][j];
				b++;
			}
			a += 2;
			b = 11;
		}
		wstring lever = { L"  ▇  ║  ║  ║══╝" };
		for (int j = 8, n = 0; j < 14 and n < 15; j++)
		{
			for (i = 44; i < 47; i++, n++)
			{
				screen[i + j * width] = lever[n];
			}
		}
	}
	void lever(int width, wchar_t* screen, HANDLE hConsole, DWORD dwBytesWritten, int height)
	{
		wstring lever0 = { L"  ▇  ║  ║  ║══╝" };
		wstring lever1 = { L"        ▇  ║══╝" };
		wstring lever2 = { L"            ══▇" };
		int i, j;
		for (int j = 8, n = 0; j < 14 and n < 15; j++)
		{
			for (i = 44; i < 47; i++, n++)
			{
				screen[i + j * width] = lever0[n];
			}
		}
		WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
		Sleep(100);
		for (int j = 8, n = 0; j < 14 and n < 15; j++)
		{
			for (i = 44; i < 47; i++, n++)
			{
				screen[i + j * width] = lever1[n];
			}
		}
		WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
		Sleep(100);
		for (int j = 8, n = 0; j < 14 and n < 15; j++)
		{
			for (i = 44; i < 47; i++, n++)
			{
				screen[i + j * width] = lever2[n];
			}
		}
		WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
		Sleep(100);
		for (int j = 8, n = 0; j < 14 and n < 15; j++)
		{
			for (i = 44; i < 47; i++, n++)
			{
				screen[i + j * width] = lever1[n];
			}
		}
		WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
		Sleep(100);
	}
	void winPrint(int n, int width, wchar_t* screen)
	{
		string strWin = to_string(n);
		screen[36 + 7 * width] = '+';
		int i = 37;
		for (int n = 0; n < size(strWin); n++, i++)
		{
			screen[i + 7 * width] = strWin[n];
		}
	}
};

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	int width = 75;
	int height = 25;
	SetWindow(width, height);
	wchar_t* screen = new wchar_t[width * height];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	Casino c;
	srand(time(NULL));
	int key;
	c.window(width, screen);
	WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);

	do
	{
		if (_kbhit())
		{
			key = _getch_nolock();
			if (key == 13)
			{
				c.lever(width, screen, hConsole, dwBytesWritten, height);
				c.setBalance(-10);
				for (int i = 0; i < 20; i++)
				{
					c.spin(i);
					c.window(width, screen);
					WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
					Sleep(i * 20);
				}
				if (c.win() == 1)
				{
					c.setBalance(100);
					c.winPrint(100, width, screen);
					WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
				}
				else if (c.win() == 2)
				{
					c.setBalance(200);
					c.winPrint(200, width, screen);
					WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
				}
				else if (c.win() == 3)
				{
					c.setBalance(300);
					c.winPrint(300, width, screen);
					WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
				}
				else if (c.win() == 4)
				{
					c.setBalance(400);
					c.winPrint(400, width, screen);
					WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
				}
			}
			else if (key == 27)
			{
				break;
			}
		}
	} while (true);
	return 0;
}
