#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>
#include "HotDylibEx.h"

int main(int argc, const char* argv[])
{
	printf("Auto build DLL v1.0\n");
	printf("-------------------\n");

	int useGMake = 0;
	if (argc > 1 && strcmp(argv[1], "make") == 0)
	{
		printf("Select gmake alternative to build_dll.bat\n");
		useGMake = 1;
	}

	HotDylibFileTime dir = { 0, "lib.c" };
 	HotDylibWatchFiles(&dir, 1); // Initialize

	while (1)
	{
		if (HotDylibWatchFiles(&dir, 1))
		{	
			printf("Find lib.c changed, recompile dll...\n");
			if (useGMake)
			{
				system("make dll");
			}
			else
			{
				system("build_dll.bat");
			}

			// Ignore further changed
			HotDylibWatchFiles(&dir, 1); 
		}

		Sleep(16);
	}

	return 0;
}
