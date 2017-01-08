#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Tkucha {
	int amount; //количество оставшихся предметов
	int number; //номер кучи
};
struct Tgame {
	int iname; //порядковый номер ходяшего игрока
	int ak;    //количество куч
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
	coord.X = x;            // начнем с первой ячейки
	coord.Y = y;            //   первой строки
	CHAR chFillChar = ' ';

	if (!FillConsoleOutputCharacter(
		hStdout,          // дескриптор экранного буфера
		chFillChar,       // заполнение пробелами
		S,                // число ячеек для заполнения
		coord,            // первая ячейка для записи
		&cWritten))       // фактическое число записей)
		cout << "FillConsoleOutputCharacter";

	if (!FillConsoleOutputAttribute(
		hStdout,          // дескриптор экранного буфера
		wColor,           // цвет для заполнения
		S,            // число заполняемых ячеек
		coord,            // первая ячейка для записи
		&cWritten))       // фактическое число записей )
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


	fpn(hOutput, 32, 5, L"ВЫБЕРЕТЕ РЕЖИМ ИГРЫ");
	fpn(hOutput, 5, 20, L"Для управления используйте клавиши ВВЕРХ-ВНИЗ, для выбора нажмите ENTER");
	fpn(hOutput, 35, 10, L"Игрок - Игрок");
	fpn(hOutput, 35, 12, L"Игрок - Компьютер");
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
		flagpl = 1;   //сделать меню
	else flagpl = 2;

	ClearScreen(hOutput);
	fpn(hOutput, 5, 20, L"Для управления используйте клавиши ВВЕРХ-ВНИЗ, для выбора нажмите ENTER");
	fpn(hOutput, 23, 5, L"ВЫБЕРЕТЕ КОЛИЧЕСТВО КУЧ ДЛЯ ИГРЫ:");
	fpn(hOutput, 35, 10, L"Три");
	fpn(hOutput, 35, 12, L"Четыре");
	fpn(hOutput, 35, 14, L"Пять");
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
		fpn1(hOutput, x, y, i, L"Куча: %d");
		y += 2;
	}
	while (sum)
	{
		if (game.iname == 3)  game.iname = 1;
		fpn1(hOutput, 30, 2, game.iname, L"Ходит игрок: %d");
		fpn(hOutput, 31, 4, L"ВЫБОР КУЧИ");
		fpn(hOutput, 5, 20, L"Для управления используйте клавиши ВВЕРХ-ВНИЗ, для выбора нажмите ENTER");
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
		fpn(hOutput, 31, 4, L"УДАЛЕНИЕ ПРЕДМЕТОВ ");
		fpn(hOutput, 2, 20, L"Для удаления нажмите клавишу Del,для окончания удаления клавишу End или Enter ");
		fpn(hOutput, 7, 22, L"**Внимание! Синний предмент является неудалённым.");

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
			fpn1(hOutput, x, y, i, L"Куча: %d");
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
	cout << "                      :.    .С(   .::.  .СС:                           " << endl;
	cout << "                  .СС08:    С8С   088С .888:       .СС.                " << endl;
	cout << "                  :8880    .08С  :888: :888:      :088:                " << endl;
	cout << "                  :8880.   .88:  0880. :8880    .08880                 " << endl;
	cout << "                  С88880   .88:  088(  С88880..С00С88(                 " << endl;
	cout << "                  080088.  :88.  С88.  С80088000(.080.                 " << endl;
	cout << "                 .88:.080. С80   080  .88С.:СС:. .88:                  " << endl;
	cout << "                 С80  .080:08С   88С  :88:       (80                   " << endl;
	cout << "                 08.   .08888.  :88(  :88.       С8(                   " << endl;
	cout << "                :80     .080(   .88С  С80       .СС.                   " << endl;
	cout << "                (С.      .:.     .:.  .:.                              " << endl;
	cout << endl;
	wColor = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
	SetColor(h, wColor);
	cout << "                          ПРАВИЛА ИГРЫ :  " << endl;
	cout << "     Ним — математическая игра, в которой два игрока по очереди берут предметы," << endl;
	cout << "  разложенные на несколько кучек. Выбор количества предметов в кучках может " << endl;
	cout << "  производить игрок. За один ход может быть взято любое количество предметов  " << endl;
	cout << "  (большее нуля) из одной кучки. Выигрывает игрок, взявший последний предмет." << endl;
	cout << endl << endl;
	cout << "                Для начала игры нажмите клавишу ENTER" << endl;

	unsigned char passkey = 0;
	while (passkey != 13) passkey = _getch();
	while (passkey == 13)
	{
		ClearScreen(h);
		switch (game(h))
		{
		case 1: fpn(h, 29, 10, L"Выиграл первый игрок");
			break;
		case 2: fpn(h, 29, 10, L"Выиграл второй игрок");
			break;
		case 3: fpn(h, 29, 10, L"Вы проиграли ");
			break;
		default:cout << "Error !" << endl;
		}
		fpn(h, 29, 25, L"Новая игра - Enter, Выход - любая другая клавиша");
		passkey = _getch();
	}
	return 0;
}
