#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Tkucha {
	int amount; //���������� ���������� ���������
	int number; //����� ����
};
struct Tgame {
	int iname; //���������� ����� �������� ������
	int ak;    //���������� ���
};
enum ConsoleColor
{
	White = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED,
	Red = BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
	Green = BACKGROUND_GREEN | FOREGROUND_BLUE,
	Blue = BACKGROUND_BLUE,
};
void SetCursorVisibility(bool isVisible)
{
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = isVisible;
	ci.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}
void SetColor(HANDLE hStdout, WORD wColor)
{
	SetConsoleTextAttribute(hStdout, wColor);
}
void fpp(int x, int y, int S, HANDLE hStdout, WORD wColor)
{
	DWORD cWritten;
	COORD coord;
	coord.X = x;            // ������ � ������ ������
	coord.Y = y;            //   ������ ������
	CHAR chFillChar = ' ';

	if (!FillConsoleOutputCharacter(
		hStdout,          // ���������� ��������� ������
		chFillChar,       // ���������� ���������
		S,                // ����� ����� ��� ����������
		coord,            // ������ ������ ��� ������
		&cWritten))       // ����������� ����� �������)
		cout << "FillConsoleOutputCharacter";

	if (!FillConsoleOutputAttribute(
		hStdout,          // ���������� ��������� ������
		wColor,           // ���� ��� ����������
		S,            // ����� ����������� �����
		coord,            // ������ ������ ��� ������
		&cWritten))       // ����������� ����� ������� )
		cout << "FillConsoleOutputAttribute";

}
void ClearScreen(HANDLE hStdout)
{
	int x = 0; int y = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
	{
		cout << "Error! FillConsoleOutputCharacter " << endl;
		return;
	}
	int S = csbi.dwSize.X *csbi.dwSize.Y;
	WORD wColor = White;
	fpp(x, y, S, hStdout, wColor);
	COORD coord = { x, y };
	if (!SetConsoleCursorPosition(hStdout, coord))
	{
		cout << "Error! FillConsoleOutputCharacter " << endl;
		return;
	}
}
void fpn(HANDLE hOutput, int x, int y, WCHAR ct[])
{
	COORD pos;
	pos.X = x; pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
	DWORD  dw;

	WriteConsoleW(hOutput, ct, lstrlenW(ct), &dw, NULL);
}
void fpn1(HANDLE hOutput, int x, int y, DWORD iname, WCHAR ct[])
{
	COORD pos;
	pos.X = x; pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
	DWORD  dw;
	WCHAR  snum[16];
	wsprintfW(snum, ct, iname);
	WriteConsoleW(hOutput, snum, lstrlenW(snum), &dw, NULL);
}
void robot(Tkucha *A[5], int kol, int &sumg)
{
	int nmax;
	int maxel = 0;
	int sum = 0;
	for (int i = 0; i<kol; i++)
	{
		sum = sum ^ (A[i]->amount);
		if (maxel<(A[i]->amount))
		{
			nmax = i;
			maxel = A[i]->amount;
		}
	}
	if (sum != 0)
	{
		sum = 0;
		for (int i = 0; i<kol; i++)
			if (i != nmax)
				sum = sum ^ (A[i]->amount);
		while (A[nmax]->amount != 0 && (sum ^ (A[nmax]->amount)) != 0)
		{
			(A[nmax]->amount)--;
			sumg--;
		}
	}
	else
	{
		(A[nmax]->amount)--;
		sumg--;
	}
}
int game(HANDLE hOutput)
{

	Tgame game;
	int c;
	int lastk;
	int firstk;
	WORD wColor;

	Tkucha *A[5];

	int sum = 0;
	int knumber;
	int x = 0; int y = 0;
	int flag = 0;
	int flagpl;


	fpn(hOutput, 32, 5, L"�������� ����� ����");
	fpn(hOutput, 5, 20, L"��� ���������� ����������� ������� �����-����, ��� ������ ������� ENTER");
	fpn(hOutput, 35, 10, L"����� - �����");
	fpn(hOutput, 35, 12, L"����� - ���������");
	y = 10;
	wColor = Red; // BACKGROUND_RED;
	fpp(32, y, 2, hOutput, wColor);
	do {
		c = NULL;
		if (_kbhit())
		{
			c = _getch();
			if (c == 72 || c == 80)
			{
				if (y == 10)
				{
					wColor = White; //BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED;
					fpp(31, y, 3, hOutput, wColor);
					y += 2;
					wColor = Red; //BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
					fpp(32, y, 2, hOutput, wColor);
				}
				else
				{
					wColor = White; // BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED;
					fpp(31, y, 3, hOutput, wColor);
					y -= 2;
					wColor = Red; //BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
					fpp(32, y, 2, hOutput, wColor);

				}
			}
		}
	} while (c != 13);

	if (y == 10)
		flagpl = 1;   //������� ����
	else flagpl = 2;

	ClearScreen(hOutput);
	fpn(hOutput, 5, 20, L"��� ���������� ����������� ������� �����-����, ��� ������ ������� ENTER");
	fpn(hOutput, 23, 5, L"�������� ���������� ��� ��� ����:");
	fpn(hOutput, 35, 10, L"���");
	fpn(hOutput, 35, 12, L"������");
	fpn(hOutput, 35, 14, L"����");
	wColor = Red; // BACKGROUND_RED;
	fpp(32, y, 2, hOutput, wColor);
	do {
		c = NULL;
		if (_kbhit())
		{
			c = _getch();
			if (c == 72 || c == 80)
			{
				switch (c)
				{
				case 72:
					if (y>10)
					{
						wColor = White; //BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED;
						fpp(31, y, 3, hOutput, wColor);
						y -= 2;
						wColor = Red; //BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
						fpp(32, y, 2, hOutput, wColor);
					}
					else cout << '\a' << '\a';
					break;
				case 80:
					if (y<14)
					{
						wColor = White; //BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED;
						fpp(31, y, 3, hOutput, wColor);
						y += 2;
						wColor = Red; //BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
						fpp(32, y, 2, hOutput, wColor);
					}
					else cout << '\a' << '\a';
					break;
				}
			}
		}
	} while (c != 13);
	if (y == 10)
		game.ak = 3;
	else {
		if (y == 12)
			game.ak = 4;
		else game.ak = 5;
	}
	c = 0;
	ClearScreen(hOutput);

	int hk = 3;
	for (int i = 0; i<game.ak; i++)
	{
		A[i] = new Tkucha;
		A[i]->number = i;
		A[i]->amount = hk;
		hk += 2;
	}
	if (flagpl == 1)
	{
		if (rand() <= 16383)
			game.iname = 1;
		else game.iname = 2;
	}
	else game.iname = 1;
	for (int i = 0; i<game.ak; i++)
		sum += A[i]->amount;
	wColor = Green;
	int j = 0;
	for (y = 6; y<(2 * game.ak) + 6; y += 2)
	{
		for (x = 18; x<4 * (A[j]->amount) + 18; x += 4)
			fpp(x, y, 2, hOutput, wColor);
		j++;
	}
	y = 6;
	for (int i = 1; i <= game.ak; i++)
	{
		x = 5;
		fpn1(hOutput, x, y, i, L"����: %d");
		y += 2;
	}
	while (sum)
	{
		if (game.iname == 3)  game.iname = 1;
		fpn1(hOutput, 30, 2, game.iname, L"����� �����: %d");
		fpn(hOutput, 31, 4, L"����� ����");
		fpn(hOutput, 5, 20, L"��� ���������� ����������� ������� �����-����, ��� ������ ������� ENTER");
		y = 6; x = 18;
		for (int i = 0; A[i]->amount <= 0; i++, y += 2);
		do {
			wColor = Blue;
			fpp(x, y, 2, hOutput, wColor);
			if (_kbhit())
			{
				c = _getch();
				if (c == 72 || c == 80)
				{
					switch (c)
					{
					case 72:
						firstk = 0;
						while (A[firstk]->amount == 0) firstk++;
						if (y>6 + firstk * 2)
						{
							wColor = Green;
							fpp(x, y, 2, hOutput, wColor);
							do {
								y -= 2;
							} while (A[y / 2 - 3]->amount == 0);
							wColor = Blue;
							fpp(x, y, 2, hOutput, wColor);
						}
						else cout << '\a' << '\a';
						break;
					case 80:
						for (int j = 0; j<game.ak; j++)
						{
							if (A[j]->amount != 0)
								lastk = j + 1;
						}
						if (y<6 + 2 * (lastk - 1))
						{
							wColor = Green;
							fpp(x, y, 2, hOutput, wColor);
							do {
								y += 2;
							} while (A[y / 2 - 3]->amount == 0);
							wColor = Blue;
							fpp(x, y, 2, hOutput, wColor);
						}
						else cout << '\a' << '\a';
						break;
					}
				}
			}
		} while (c != 13);
		knumber = (y / 2) - 3;
		fpn(hOutput, 31, 4, L"�������� ��������� ");
		fpn(hOutput, 2, 20, L"��� �������� ������� ������� Del,��� ��������� �������� ������� End ��� Enter ");
		fpn(hOutput, 7, 22, L"**��������! ������ �������� �������� ����������.");

		wColor = Green;
		fpp(x, y, 2, hOutput, wColor);

		do {
			x = 18 + (A[knumber]->amount - 1) * 4;
			wColor = Blue;
			fpp(x, y, 2, hOutput, wColor);
			if (_kbhit())
			{
				c = _getch();
				if (c == 83)
				{
					A[knumber]->amount--;
					sum--;
					flag = 1;
					wColor = Red;
					fpp(x, y, 2, hOutput, wColor);
					if (x>18)
					{
						x -= 4;
						wColor = Blue;
						fpp(x, y, 2, hOutput, wColor);
					}
					else cout << '\a';
				}
			}
		} while (c != 79 && c != 13 && A[knumber]->amount != 0 || !flag);
		flag = 0;
		if (flagpl == 1)
		{
			if (game.iname == 1)
				game.iname = 2;
			else
				game.iname = 1;
		}
		else {
			if (sum>0)
			{
				robot(A, game.ak, sum);
				game.iname = 3;
			}
		}
		ClearScreen(hOutput);
		wColor = Green; //BACKGROUND_GREEN ;
		int j = 0;
		for (y = 6; y<(2 * game.ak) + 6; y += 2)
		{
			for (x = 18; x<4 * (A[j]->amount) + 18; x += 4)
				fpp(x, y, 2, hOutput, wColor);
			j++;
		}
		y = 6;
		for (int i = 1; i <= game.ak; i++)
		{
			x = 5;
			fpn1(hOutput, x, y, i, L"����: %d");
			y += 2;
		}
	}
	ClearScreen(hOutput);
	if (flagpl == 1)
	{
		if (game.iname == 1)  return 2;
		else return 1;
	}
	else {
		if (game.iname == 3) return 3;
		else return 1;
	}
}
int main()
{

	setlocale(LC_ALL, "rus");


	SetCursorVisibility(false);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE)
		return 1;
	ClearScreen(h);


	WORD wColor = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

	SetColor(h, wColor);
	cout << endl << endl;
	cout << "                      :.    .�(   .::.  .��:                           " << endl;
	cout << "                  .��08:    �8�   088� .888:       .��.                " << endl;
	cout << "                  :8880    .08�  :888: :888:      :088:                " << endl;
	cout << "                  :8880.   .88:  0880. :8880    .08880                 " << endl;
	cout << "                  �88880   .88:  088(  �88880..�00�88(                 " << endl;
	cout << "                  080088.  :88.  �88.  �80088000(.080.                 " << endl;
	cout << "                 .88:.080. �80   080  .88�.:��:. .88:                  " << endl;
	cout << "                 �80  .080:08�   88�  :88:       (80                   " << endl;
	cout << "                 08.   .08888.  :88(  :88.       �8(                   " << endl;
	cout << "                :80     .080(   .88�  �80       .��.                   " << endl;
	cout << "                (�.      .:.     .:.  .:.                              " << endl;
	cout << endl;
	wColor = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
	SetColor(h, wColor);
	cout << "                          ������� ���� :  " << endl;
	cout << "     ��� � �������������� ����, � ������� ��� ������ �� ������� ����� ��������," << endl;
	cout << "  ����������� �� ��������� �����. ����� ���������� ��������� � ������ ����� " << endl;
	cout << "  ����������� �����. �� ���� ��� ����� ���� ����� ����� ���������� ���������  " << endl;
	cout << "  (������� ����) �� ����� �����. ���������� �����, ������� ��������� �������." << endl;
	cout << endl << endl;
	cout << "                ��� ������ ���� ������� ������� ENTER" << endl;

	unsigned char passkey = 0;
	while (passkey != 13) passkey = _getch();
	while (passkey == 13)
	{
		ClearScreen(h);
		switch (game(h))
		{
		case 1: fpn(h, 29, 10, L"������� ������ �����");
			break;
		case 2: fpn(h, 29, 10, L"������� ������ �����");
			break;
		case 3: fpn(h, 29, 10, L"�� ��������� ");
			break;
		default:cout << "Error !" << endl;
		}
		fpn(h, 29, 25, L"����� ���� - Enter, ����� - ����� ������ �������");
		passkey = _getch();
	}
	return 0;
}
