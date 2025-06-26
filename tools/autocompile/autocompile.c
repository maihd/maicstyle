#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <errno.h>

#include "Json.h"


#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   include <sys/stat.h>

#   define stat             _stat
#   define PATH_SEP         "\\"
#   define EXE_EXT          ".exe"
#   define CLEAR_SCREEN_CMD "cls"
#else
#   include <unistd.h>
#   include <sys/stat.h>

#   define PATH_SEP         "/"
#   define EXE_EXT          ""
#   define CLEAR_SCREEN_CMD "clear"
#endif


#define CONFIG_FILE         "config.json"
#define SOURCE_FILE         "main.c"
#define OUTPUT_FILE         "main"
#define DEFAULT_COMPILER    "clang"


typedef struct 
{
    char    compiler[256];
    char    flags[1024];
    char    runParams[1024];

    int32_t watchInterval;
    bool    clearScreen;
} Config;


typedef enum LoadResult
{
    LoadResult_Success,
    LoadResult_Failure,
    LoadResult_UseDefault
} LoadResult;


LoadResult LoadConfig(const char* filePath, Config* outConfig) 
{
    // Default config
    
    memcpy(outConfig->compiler, DEFAULT_COMPILER, sizeof(DEFAULT_COMPILER));
    memcpy(outConfig->flags, "", 1);
    memcpy(outConfig->runParams, "", 1);

    outConfig->watchInterval = 2;
    outConfig->clearScreen = true;

    // Read config from file
    FILE* configFile;
    errno_t ferr = fopen_s(&configFile, filePath, "rb");
    if (ferr != 0 && ferr != EEXIST)
    {
        char errmsg[1024];
        strerror_s(errmsg, sizeof(errmsg), ferr);

        fprintf(stderr, "Failed to open file `%s`: %s\n", filePath, errmsg);
        return LoadResult_UseDefault;
    }

    if (!configFile)
    {
        return LoadResult_UseDefault;
    }

    fseek(configFile, 0, SEEK_END);
    const uint32_t configFileLength = (uint32_t)ftell(configFile);
    fseek(configFile, 0, SEEK_SET);

    const size_t allocationSize = configFileLength * 3 + 1 > 4096 
        ? configFileLength * 3 + 1
        : 4096;

    void* allocationBuffer = malloc(allocationSize);

    char* configFileContent = allocationBuffer;
    configFileContent[configFileLength] = 0;

    fread(configFileContent, 1, configFileLength, configFile);
    fclose(configFile);

    void* parseBuffer = (uint8_t*)allocationBuffer + configFileLength + 1;
    const uint32_t parseBufferSize = allocationSize - configFileLength - 1;

    Json root;
    JsonResult parseResult = JsonParse(configFileContent, configFileLength, JsonParseFlags_Default, parseBuffer, parseBufferSize, &root);
    if (parseResult.error != JsonError_None) 
    {
        fprintf(stderr, "Error loading config file: %s\n", parseResult.message);
        free(allocationBuffer);
        return LoadResult_UseDefault;
    }

    // Apply config fields
    
    Json jsonCompiler;
    if (JsonFindWithType(root, "compiler", JsonType_String, &jsonCompiler) == JsonError_None)
    {
        memcpy(outConfig->compiler, jsonCompiler.string, jsonCompiler.length + 1);
    }
    
    Json jsonFlags;
    if (JsonFindWithType(root, "flags", JsonType_String, &jsonFlags) == JsonError_None)
    {
        memcpy(outConfig->flags, jsonFlags.string, jsonFlags.length + 1);
    }
    
    Json jsonRunParams;
    if (JsonFindWithType(root, "runParams", JsonType_String, &jsonRunParams) == JsonError_None)
    {
        memcpy(outConfig->runParams, jsonRunParams.string, jsonRunParams.length);
    }
    
    Json jsonWatchInterval;
    if (JsonFindWithType(root, "watchInterval", JsonType_Number, &jsonWatchInterval) == JsonError_None)
    {
        outConfig->watchInterval = (int32_t)jsonWatchInterval.number;
    }
    
    Json jsonClearScreen;
    if (JsonFindWithType(root, "clearScreen", JsonType_Boolean, &jsonClearScreen) == JsonError_None)
    {
        printf("jsonClearScreen: %d\n", jsonClearScreen.boolean);
        outConfig->clearScreen = jsonClearScreen.boolean;
    }

    free(allocationBuffer);
    return LoadResult_Success;
}


time_t GetFileModTime(const char* filename) 
{
    struct stat st;
    if (stat(filename, &st) != 0) 
    {
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
    
    int result = system(command);
    if (result != 0) 
    {
        fprintf(stderr, "Compilation failed\n");
        return 0;
    }
    
    return 1;
}


void RunProgram(const Config* config) 
{
    char run_exe[256];
    snprintf(run_exe, sizeof(run_exe), "%s%s", OUTPUT_FILE, EXE_EXT);
    
    char run_cmd[2048];
    snprintf(run_cmd, sizeof(run_cmd), "%s %s", run_exe, config->runParams);

    printf("Running program: %s\n", run_cmd);
    printf("----------------------------------------\n");
    
    int result = system(run_cmd);
    
    printf("----------------------------------------\n");
    printf("Program exited with status %d\n", result);
}


void ClearScreenIfEnabled(const Config* config) 
{
    if (config->clearScreen) 
    {
        system(CLEAR_SCREEN_CMD);
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
                RunProgram(config);
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


int main(int argc, const char* argv[]) 
{
    Config* config = malloc(sizeof(Config));

    const char* configFilePath = CONFIG_FILE;
    if (argc > 1)
    {
        configFilePath = argv[1];
    }

    if (LoadConfig(configFilePath, config) == LoadResult_UseDefault) 
    {
        printf("Using default configuration\n");
    }
    
    printf("Auto-Compiler Configuration:\n");
    printf("  Compiler: %s\n", config->compiler);
    printf("  Flags: %s\n", config->flags);
    printf("  Run params: %s\n", config->runParams);
    printf("  Watch Interval: %d seconds\n", config->watchInterval);
    printf("  Clear Screen: %s\n", config->clearScreen ? "Yes" : "No");

    // Run program as launch time
    
    ClearScreenIfEnabled(config);
    if (Compile(config)) 
    {
        RunProgram(config);
    }
    
#ifdef _WIN32
    printf("Watching %s for changes... (Interval: %d seconds)\n", SOURCE_FILE, config->watchInterval);
    printf("Press Ctrl+C to exit\n");
    
    HANDLE threadHandle = CreateThread(NULL, 0, WatchThread, &config, 0, NULL);
    if (threadHandle == NULL) 
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

//! EOF
