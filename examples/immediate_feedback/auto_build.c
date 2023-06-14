#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>
#include "HotDylibEx.h"

int main()
{
	HotDylibFileTime dir = { 0, "lib.c" };
 	HotDylibWatchFiles(&dir, 1); // Initialize

	while (1)
	{
		if (HotDylibWatchFiles(&dir, 1))
		{	
			printf("Find lib.c changed, recompile dll...\n");
			system("make dll");
			HotDylibWatchFiles(&dir, 1); // Ignore further changed
		}

		Sleep(16);
	}

	return 0;
}
