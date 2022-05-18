#define _CRT_SECURE_NO_WARNINGS							//Issues:
#include <stdio.h>										//Typing beyond the window width which switches lines can cause bugs.
#include <Windows.h>									//
#include <conio.h>										//
														//To Do:
main()													//
{
Start:
	system("cls");
	char key;
	unsigned int PosX = 0, PosY = 0, EscCount = 0, KeyCount = 0;
	BOOL QuickEditFlag = FALSE;
	SetConsoleTitle("Type Anywhere! Arrow key to move, tap Esc to clear, hold Esc to exit. F12 to toggle quick edit mode.");
	gotoxy(PosX, PosY);
	CONSOLE_CURSOR_INFO CsrInfo;	//Set cursor parameters
	CsrInfo.bVisible = 1;
	CsrInfo.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CsrInfo);
	//while (1)
	//{
	//	key = _getch();
	//	printf("%d\n", key);
	//}
	while (TRUE)	//Main loop
	{
		if (EscCount > 0)	EscCount--;	//Works together with Hold to exit part, user can't easily fuck this up now.
		key = _getch();
		switch (key)
		{
		case 27:	//Esc
			system("cls");	//Clear
			PosX = 0;
			PosY = 0;
			if (KeyCount >= 0)	KeyCount--;	//Ignore keycount
			EscCount++;		//EscCount+2
			if (++EscCount > 5)	goto Exit;	//Hold to exit
			break;
		case 9:		//Tab
			putchar('\t');
			unsigned int TabIndent = PosX % 8;
			PosX += 8 - TabIndent;
			if (KeyCount >= 0)	KeyCount--;	//Ignore keycount
			break;
		case 13:	//Enter
			putchar('\n');
			PosX = 0;
			PosY++;
			if (KeyCount >= 0)	KeyCount--;	//Ignore keycount
			break;
		case 8:		//BackSpace
			if (!PosX)	break;	//Prevent going negative
			printf("\b ");	//'\b' to go back one block
			PosX--;
			if (KeyCount >= 0)	KeyCount--;	//Ignore keycount
			break;
		case -32:	//-32 prefix								//	Well this is rather complicate.
			char Minus32 = _getch();							//	You see, when using arrow keys
			switch (Minus32)									//there'll be a '-32' before the actual
			{													//key code, and that key code can
			case 72:	//Up									//conflict with some letters.
				if (!PosY)	break;	//Prevent going negative	//	'-32' is there to differentiate
				PosY--;											//between a funcion key or a normal
				break;											//letter key.
			case 80:	//Down
				PosY++;
				break;
			case 75:	//Left
				if (!PosX)	break;	//Prevent going negative
				PosX--;
				break;
			case 77:	//Right
				PosX++;
				break;
			case 83:	//Delete
				if (!PosX)	break;	//Prevent going negative
				printf("\b ");	//'\b' to go back one block
				PosX--;
				break;
			case -122:	//F12	Toggle quick edit mode & cursor select
				if (QuickEditFlag == TRUE)			//Enable
				{
					SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
					QuickEditFlag = FALSE;
				}
				else if (QuickEditFlag == FALSE)	//Disable
				{
					SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS);
					QuickEditFlag = TRUE;
				}
			default:
				break;
			}
			if (KeyCount >= 0)	KeyCount--;	//Ignore keycount
			break;
		case 0:		//0 prefix
			if (KeyCount >= 0)	KeyCount--;	//Ignore keycount
			break;
		default:
			printf("%c", key);
			PosX++;
			break;
		}
		gotoxy(PosX, PosY);
		KeyCount++;
	}
Exit:
	CsrInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CsrInfo);
	printf("You've typed %d keys.\n", ++KeyCount);
	puts("Press Enter to restart, other keys to exit.");
	while (key = _getch())
	{
		if (key == 27)
		{
			continue;
		}
		else if (key == 13)
		{
			goto Start;
		}
		else
		{
			return 0;
		}
	}
}

int gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 1;
}