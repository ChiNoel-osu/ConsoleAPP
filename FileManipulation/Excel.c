#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>

main()
{
	FILE* NewFile = fopen("TestFile.xls", "w");
	UINT Row = 1, Column = 1, charCnt = 0;
	INPUT_RECORD IpRec;
	char key, actualKey, Typing[10];
	LPDWORD EvntNum;
	BOOL newCell = FALSE;
	puts("Type to begin! Starting at R1C1.");
	while (TRUE)
	{
		while (TRUE)
		{
			ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &IpRec, 1, &EvntNum);	//Scan for input
			actualKey = IpRec.Event.KeyEvent.uChar.AsciiChar;
			if (key = IpRec.Event.KeyEvent.wVirtualKeyCode)	//Helps with "Shift" capital letter
			{
				if (IpRec.Event.KeyEvent.bKeyDown == FALSE)	continue;	//Ignore key release event
				break;
			}
		}
		switch (key)
		{
		case VK_ESCAPE:
			goto Exit;
		case VK_TAB:
			fprintf(NewFile, "\t");
			Column++;
			charCnt = 0;	//Clear counter
			break;
		case VK_RETURN:
			fprintf(NewFile, "\n");
			Row++;
			charCnt = 0;
			break;
		case VK_SHIFT:
		case VK_CONTROL:
		case VK_MENU:
		case VK_CAPITAL:
			break;
		default:
			fprintf(NewFile, "%c", actualKey);
			charCnt++;
			break;
		}
		system("cls");
		Typing[charCnt-1] = actualKey;
		printf("At Row %d|Col %d\nTyping in: %c\nThe cell's got: ", Row, Column, actualKey);
		for (short i = 0; i < charCnt; i++)
		{
			printf("%c", Typing[i]);
		}
	}
Exit:
	fclose(NewFile);

	system("pause");
	return 0;
}