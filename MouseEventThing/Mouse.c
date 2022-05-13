#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>

main()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);			//Specify handles
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD InRecord;									//Event structure
#define MousePos InRecord.Event.MouseEvent.dwMousePosition	//Save myself some time
	LPDWORD EvntNum;										//This is useless but needed anyway
	CONSOLE_CURSOR_INFO CsrInfo;
	SetConsoleTitle(TEXT("Click the Cursor!"));
	short int ClickScore, CsrPosX, CsrPosY, RestartFlag, BoxSizeX, BoxSizeY;

	putchar('\n');
	puts("1 - Tiny   5 * 5");
	puts("2 - Easy   17* 9");
	puts("3 - Medium 33*17");
	puts("4 - Hard   43*21");
	puts("Other - Exit");
	GotoXY(0, 0);
	printf("Welcome! Please pick a difficulty: [_\b");
	char Diff = getchar();
	system("color 0F");
	switch (Diff)
	{
	case '1':
		system("cls");
		puts("Sike! Tiny is not working yet! Tiny man!");
		system("timeout /t 4");
		return 0;
	case '2':
		system("mode con cols=40 lines=15");
		BoxSizeX = 19, BoxSizeY = 11;
		break;
	case '3':
		system("mode con cols=72 lines=23");
		BoxSizeX = 35, BoxSizeY = 19;
		break;
	case '4':
		system("mode con cols=92 lines=27");		//Set the correct window size
		BoxSizeX = 45, BoxSizeY = 23;		//Playfield Restriction:(1,2)~(43,22)	don't forget X*2
		break;
	default:
		return 0;
	}
Start:
	RestartFlag = 0, ClickScore = 0;
	CsrPosX = BoxSizeX - 1, CsrPosY = BoxSizeY / 2 + 2;			//Middle Position
	srand((unsigned)time(NULL));								//Set random seed
	SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);	//Enable all the modes
	CsrInfo.bVisible = 0;	CsrInfo.dwSize = 100;				//Preset Cursor info
	SetConsoleCursorInfo(hOut, &CsrInfo);
	puts("Click the middle cursor to begin!");
	CreateBox(BoxSizeX, BoxSizeY);
	GotoXY(CsrPosX, CsrPosY);	//Middle Position
	CsrInfo.bVisible = 1;	SetConsoleCursorInfo(hOut, &CsrInfo);

	while (TRUE)
	{
		ReadConsoleInput(hIn, &InRecord, 1, &EvntNum);			//Scan for input
		if (InRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)	//LMB Press
		{
			if (InRecord.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)	continue;		//Block mousemove event
			if (RestartFlag == 1)	break;
			if (MousePos.X == CsrPosX && MousePos.Y == CsrPosY)
			{
				CsrInfo.bVisible = 0;	SetConsoleCursorInfo(hOut, &CsrInfo);
				GotoXY(0, 0);	printf("                                 \rScore: %d", ++ClickScore);
				CsrInfo.bVisible = 1;	SetConsoleCursorInfo(hOut, &CsrInfo);
				GotoXY(CsrPosX = GetRndNumRange(1 * 2, (BoxSizeX - 2) * 2), CsrPosY = GetRndNumRange(2, BoxSizeY - 1));
			}
			else
			{
				GotoXY(0, 0);	printf("                                 \rYou Failed! Score: %d", ClickScore);
				CsrInfo.dwSize = 1;	CsrInfo.bVisible = 0; SetConsoleCursorInfo(hOut, &CsrInfo);
				GotoXY(BoxSizeX - 12, BoxSizeY / 2 + 2);				//Middle Pos
				printf("Click again to restart.");	RestartFlag = 1;	//Next event restart
			}
		}
	}
	system("cls");
	goto Start;
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