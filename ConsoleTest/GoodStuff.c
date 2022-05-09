#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>		//Needed for kbhit()

main()
{
	unsigned int WndW, WndH;
	char* TitleSet[32], * UserName = getenv("USERNAME")/*Get Environment Variable*/, i;
	printf("Hello! %s. Please enter the title: ", UserName);
	if (!scanf("%[^\n]", TitleSet))
	{
		puts("Your title will not be changed.");
		goto BoxSetting;
	}
	printf("Your new title is: %s\n", TitleSet);
	SetConsoleTitle(TitleSet);
BoxSetting:
	ClearBuffer();
	putchar('\n');
	printf("Please enter the width:");
	if (scanf("%d", &WndW) != 1)	//Check valid
	{
		puts("You fucked up!");
		goto BoxSetting;
	}
	ClearBuffer();
	printf("Please enter the height:");
	if (scanf("%d", &WndH) != 1)	//Check valid
	{
		puts("You fucked up!");
		goto BoxSetting;
	}
	printf("Your box will be %d*%d\n\n", WndW, WndH);
	puts("Create Box? 'Y' to confirm.");
	ClearBuffer();
	if ((i = getch()) == 'Y' || i == 'y')
	{
		//HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);	//Alternately, use this to simplify handle
		CONSOLE_CURSOR_INFO CsrInfo;	//Preset cursor parameters
		CsrInfo.bVisible = 0;
		CsrInfo.dwSize = 1;
		CreateBox(WndW, WndH);
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CsrInfo);	//Set cursor parameters
		unsigned int f = 0;							//Loading animation frame number
		const char Anim[4] = { '\\','|','/','-' };	//The loading animation
		while (1)
		{
			if (kbhit())
			{
				if ((i = getch()) == 13)	//ASCII code 13 for '\n'
				{
					CsrInfo.bVisible = 1;
					CsrInfo.dwSize = 1;
					SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CsrInfo);
					break;
				}
			}
			gotoxy(WndW, WndH / 2);		//Goto The Center of the BOX
			putchar(Anim[f]);
			f++;
			if (f > 3)	f = 0;
			Sleep(100);
		}
		gotoxy(0, WndH + 1);	putchar('\n');	//Linebreak to avoid overwrite
	}
	else puts("The box will not be created.");

	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	system("pause");
	return 0;
}

int CreateBox(int WndW, int WndH)
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);		//Maximize the console window
	system("cls");
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
int gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 1;
}
int ClearBuffer()
{
	char BloodyBuffer;
	while ((BloodyBuffer = getchar()) != EOF && BloodyBuffer != '\n');
	return 1;
}