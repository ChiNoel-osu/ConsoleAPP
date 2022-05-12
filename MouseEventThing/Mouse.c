#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

main()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD InRecd;
	LPDWORD EvntNum;
	while (TRUE)
	{
		ReadConsoleInput(hIn, &InRecd, 1, &EvntNum);
	}

	system("pause");
	return 0;

}