#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "Json.h"

#ifdef _WIN32
#include <windows.h>
#include <sys/stat.h>
#define stat _stat
#define PATH_SEP "\\"
#define EXE_EXT ".exe"
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#include <sys/stat.h>
#define PATH_SEP "/"
#define EXE_EXT ""
#define CLEAR_SCREEN "clear"
#endif


#define CONFIG_FILE         "config.json"
#define SOURCE_FILE         "main.c"
#define OUTPUT_FILE         "main"
#define DEFAULT_COMPILER    "clang"


typedef struct 
{
    char    compiler[256];
    char    flags[1024];

    int     watchInterval;
    int     clearScreen;
} Config;


int LoadConfig(Config* config) 
{
    // Default config
    
    strcpy(config->compiler, DEFAULT_COMPILER);
    strcpy(config->flags, "");
    config->watchInterval = 2;
    config->clearScreen = 1;

    // Read config from file

    FILE* configFile = fopen(CONFIG_FILE, "r");
    if (!configFile)
    {
        return 0;
    }

    fseek(configFile, 0, SEEK_END);
    uint32_t configFileLength = (uint32_t)ftell(configFile);
    fseek(configFile, 0, SEEK_SET);

    char* configFileContent = malloc(configFileLength * 3);
    configFileContent[configFileLength] = 0;

    fread(configFileContent, 1, configFileLength, configFile);
    fclose(configFile);

    uint8_t* buffer = (uint8_t*)configFileContent + configFileLength;

    Json root;
    JsonResult parseResult = JsonParse(CONFIG_FILE, configFileLength, JsonParseFlags_SupportComment, buffer, configFileLength * 2, &root);
    if (parseResult.error != JsonError_None) 
    {
        fprintf(stderr, "Error loading config file: %s\n", parseResult.message);
        return 0;
    }
    
    Json jsonCompiler;
    if (!JsonFindWithType(root, "compiler", JsonType_String, &jsonCompiler))
    {
        return 0;
    }
    
    Json jsonFlags;
    if (!JsonFindWithType(root, "flags", JsonType_String, &jsonFlags))
    {
        return 0;
    }
    
    Json jsonWatchInterval;
    if (!JsonFindWithType(root, "watchInterval", JsonType_Number, &jsonFlags))
    {
        return 0;
    }
    
    Json jsonClearScreen;
    if (!JsonFindWithType(root, "jsonClearScreen", JsonType_Boolean, &jsonFlags))
    {
        return 0;
    }

    memcpy(config->flags, jsonFlags.string, jsonFlags.length + 1);
    memcpy(config->compiler, jsonCompiler.string, jsonCompiler.length + 1);
    
    config->watchInterval = (int)jsonWatchInterval.number;
    config->clearScreen = (int)jsonWatchInterval.boolean;

    free(configFileContent);
    return 1;
}


time_t GetFileModTime(const char* filename) 
{
    struct stat st;
    if (stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_mtime;
}


int Compile(const Config* config) 
{
    char command[2048];
    snprintf(command, sizeof(command), "%s %s -o %s%s %s", 
             config->compiler, config->flags, OUTPUT_FILE, EXE_EXT, SOURCE_FILE);
    
    printf("Compiling: %s\n", command);
    
    #ifdef _WIN32
    int result = system(command);
    #else
    int result = system(command);
    #endif
    
    if (result != 0) 
    {
        fprintf(stderr, "Compilation failed\n");
        return 0;
    }
    
    return 1;
}


void RunProgram() 
{
    printf("Running program:\n");
    printf("----------------------------------------\n");
    
    char run_cmd[256];
    snprintf(run_cmd, sizeof(run_cmd), "%s%s", OUTPUT_FILE, EXE_EXT);
    int result = system(run_cmd);
    
    printf("----------------------------------------\n");
    printf("Program exited with status %d\n", result);
}


void ClearScreenIfEnabled(const Config* config) 
{
    if (config->clearScreen) 
    {
        system(CLEAR_SCREEN);
    }
}


#ifdef _WIN32
DWORD WINAPI WatchThread(LPVOID lpParam) 
{
    Config *config = (Config *)lpParam;
    time_t lastModTime = 0;
    
    while (1) 
    {
        time_t currentModTime = GetFileModTime(SOURCE_FILE);
        
        if (currentModTime != lastModTime) 
        {
            if (currentModTime == 0) 
            {
                fprintf(stderr, "Error: Could not access %s\n", SOURCE_FILE);
                break;
            }
            
            lastModTime = currentModTime;
            
            ClearScreenIfEnabled(config);
            if (Compile(config)) 
            {
                RunProgram();
            }
        }
        
        Sleep(config->watchInterval * 1000);
    }

    return 0;
}
#else
void WatchLoop(const Config *config) 
{
    time_t last_mtime = 0;
    
    while (1) 
    {
        time_t current_mtime = get_file_mtime(SOURCE_FILE);
        
        if (current_mtime != last_mtime) 
        {
            if (current_mtime == 0) 
            {
                fprintf(stderr, "Error: Could not access %s\n", SOURCE_FILE);
                break;
            }
            
            last_mtime = current_mtime;
            
            clear_screen_if_enabled(config);
            if (compile_file(config)) 
            {
                run_program();
            }
        }
        
        sleep(config->watch_interval);
    }
}
#endif

int main() 
{
    Config config;
    
    if (!LoadConfig(&config)) 
    {
        printf("Using default configuration\n");
    }
    
    printf("Auto-Compiler Configuration:\n");
    printf("  Compiler: %s\n", config.compiler);
    printf("  Flags: %s\n", config.flags);
    printf("  Watch Interval: %d seconds\n", config.watchInterval);
    printf("  Clear Screen: %s\n", config.clearScreen ? "Yes" : "No");
    
    ClearScreenIfEnabled(&config);
    if (Compile(&config)) 
    {
        RunProgram();
    }
    
    #ifdef _WIN32
    printf("Watching %s for changes... (Interval: %d seconds)\n", SOURCE_FILE, config.watchInterval);
    printf("Press Ctrl+C to exit\n");
    
    HANDLE thread = CreateThread(NULL, 0, WatchThread, &config, 0, NULL);
    if (thread == NULL) 
    {
        fprintf(stderr, "Error creating watch thread\n");
        return 1;
    }
    
    // Wait for Ctrl+C
    while (1) 
    {
        Sleep(1000);
    }
    #else
    printf("Watching %s for changes... (Interval: %d seconds)\n", SOURCE_FILE, config.watch_interval);
    printf("Press Ctrl+C to exit\n");
    WatchLoop(&config);
    #endif
    
    return 0;
}