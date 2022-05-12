#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>

main()
{
	int i = 0, ClickScore = 0, CsrPosX = 44, CsrPosY = 12;
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD InRecord;
	LPDWORD EvntNum;
	CONSOLE_CURSOR_INFO CsrInfo;
	srand((unsigned)time(NULL));		//Set random seed
#define MousePos InRecord.Event.MouseEvent.dwMousePosition		//Stupid visual studio
	SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);	//Enable all the modes
	CsrInfo.bVisible = 0;	CsrInfo.dwSize = 100;
	SetConsoleCursorInfo(hOut, &CsrInfo);
	SetConsoleTitle(TEXT("Click the Cursor!"));
	puts("Click the middle cursor to begin!");
	CreateBox(45, 23);		//Playfield Restriction:(1,2)~(43,22)	don't forget X*2
	GotoXY(44, 12);			//Middle Position
	CsrInfo.bVisible = 1;	SetConsoleCursorInfo(hOut, &CsrInfo);

	while (TRUE)
	{
		ReadConsoleInput(hIn, &InRecord, 1, &EvntNum);
		if (InRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if (InRecord.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)	continue;	//Stop spamming from mousemove event
			if (MousePos.X == CsrPosX && MousePos.Y == CsrPosY)
			{
				CsrInfo.bVisible = 0;	SetConsoleCursorInfo(hOut, &CsrInfo);
				GotoXY(0, 0);	printf("                                 \rScore: %d", ++ClickScore);
				CsrInfo.bVisible = 1;	SetConsoleCursorInfo(hOut, &CsrInfo);
				GotoXY(CsrPosX = GetRndNumRange(1 * 2, 43 * 2), CsrPosY = GetRndNumRange(2, 22));
			}
			else
			{
				GotoXY(0, 0);	printf("                                 \rYou Failed!");
				CsrInfo.dwSize = 1;	SetConsoleCursorInfo(hOut, &CsrInfo);
				Sleep(2000);
				break;
			}
		}
	}
	system("cls");
	return 0;
}

int CreateBox(unsigned int WndW, unsigned int WndH)	//from my functions collection
{
	int j = 0;
	for (int i = 0; i < WndW * 2 + 2; i++)
	{
		putchar('-');
	}
	putchar('\n');
	while (j < WndH)
	{
		putchar('|');
		for (int i = 0; i < WndW; i++)
		{
			putchar(' ');	putchar(' ');
		}
		putchar('|');	putchar('\n');
		j++;
	}
	for (int i = 0; i < WndW * 2 + 2; i++)
	{
		putchar('-');
	}
	putchar('\n');
	return 1;
}
int GotoXY(int x, int y)	//In console, go to the corresponding cursor position.
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 1;
}
int GetRndNumRange(int a, int b)
{
	return rand() % (b - a + 1) + a;
}