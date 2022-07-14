#define _CRT_SECURE_NO_WARNINGS							//Issues:
#include <stdio.h>										//Typing beyond the window width which switches lines can cause bugs.
#include <Windows.h>									//When in mouse-select-curcor mode, upon hitting Esc, said feature will not work until F12 twice

main()
{
Start:
	system("cls");
	char key;
	unsigned int PosX = 0, PosY = 0, EscCount = 0, KeyCount = 0;
	BOOL QuickEditFlag = FALSE;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
	SetConsoleTitle("Type Anywhere! Arrow key to move, tap Esc to clear, hold Esc to exit. F12 to toggle quick edit mode.");
	gotoxy(PosX, PosY);
	CONSOLE_CURSOR_INFO CsrInfo;	//Set cursor parameters
	INPUT_RECORD InRecord;									//Event structure
#define MousePos InRecord.Event.MouseEvent.dwMousePosition	//Save myself some time
	LPDWORD EvntNum;
	CsrInfo.bVisible = 1;
	CsrInfo.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CsrInfo);

	while (TRUE)	//Main loop
	{
		if (EscCount > 0)	EscCount--;	//Works together with Hold to exit part, user can't easily fuck this up now.
		while (TRUE)
		{
			ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InRecord, 1, &EvntNum);	//Scan for input
			if (InRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)	//LMB. Also accepts mouse moving
			{
				PosX = MousePos.X; PosY = MousePos.Y;	//Mouse click position = cursor position
				gotoxy(PosX, PosY);
			}
			if (key = InRecord.Event.KeyEvent.wVirtualKeyCode)	//Helps with "Shift" capital letter
			{
				if (InRecord.Event.KeyEvent.bKeyDown == FALSE)	continue;	//Ignore key release event
				break;
			}
		}
		switch (key)
		{
		case VK_ESCAPE:
			system("cls");	//Clear
			PosX = 0;
			PosY = 0;
			if (KeyCount >= 0)	KeyCount--;	//Ignore keycount
			EscCount++;		//EscCount+2
			if (++EscCount > 5)	goto Exit;	//Hold to exit
			break;
		case VK_TAB:
			putchar('\t');
			unsigned int TabIndent = PosX % 8;
			PosX += 8 - TabIndent;
			if (KeyCount >= 0)	KeyCount--;
			break;
		case VK_RETURN:
			putchar('\n');
			PosX = 0;
			PosY++;
			if (KeyCount >= 0)	KeyCount--;
			break;
		case VK_BACK:
			if (!PosX)	break;	//Prevent going negative
			printf("\b ");	//'\b' to go back one block
			PosX--;
			if (KeyCount >= 0)	KeyCount--;
			break;
		case VK_UP:
			if (KeyCount >= 0)	KeyCount--;
			if (!PosY)	break;
			PosY--;
			break;
		case VK_DOWN:
			if (KeyCount >= 0)	KeyCount--;
			PosY++;
			break;
		case VK_LEFT:
			if (KeyCount >= 0)	KeyCount--;
			if (!PosX)	break;
			PosX--;
			break;
		case VK_RIGHT:
			if (KeyCount >= 0)	KeyCount--;
			PosX++;
			break;
		case VK_DELETE:
			if (KeyCount >= 0)	KeyCount--;
			if (!PosX)	break;
			printf("\b ");
			PosX--;
			break;
		case VK_F12:	//Toggle quick edit mode
			if (KeyCount >= 0)	KeyCount--;
			if (QuickEditFlag == TRUE)			//Enable
			{
				SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
				QuickEditFlag = FALSE;
			}
			else if (QuickEditFlag == FALSE)	//Disable
			{
				SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
				QuickEditFlag = TRUE;
			}
			break;
		//Ignore list
		case VK_SHIFT:
		case VK_CONTROL:
		case VK_MENU:
		case VK_CAPITAL:
			break;
		default:
			putchar(InRecord.Event.KeyEvent.uChar.AsciiChar);
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