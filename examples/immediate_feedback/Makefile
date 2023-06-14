CC=zig cc

CFLAGS=-fno-sanitize=undefined -Iinclude
LFLAGS=lib/raylibdll.lib

exe:
	$(CC) main.c HotDylib.c $(CFLAGS) $(LFLAGS)

dll:
	$(CC) -shared -o lib.dll -fPIC lib.c $(CFLAGS) $(LFLAGS)

autodll:
	$(CC) -o auto_build.exe auto_build.c HotDylibEx.c -fno-sanitize=undefined