#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __linux__
const char *platform = "linux";
#else
const char *platform = "windows";
#endif

// Optinal arguments
bool silent = false;

// Entry
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Error: No project name provided.\n");
        printf("Usage: cinit <name>\n");
        exit(1);
    }
    else if (argc > 2)
    {
        for (int i = 1; i < argc - 1; i++)
        {
            if (strcmp(argv[i], " -s") || strcmp(argv[i], "-s"))
                silent = true;
            else
            {
                printf("Error: Unknown argument `%s`.\n", argv[i]);
                exit(1);
            }
        }
    }

    if (!silent)
        printf("Creating project `%s`...\n", argv[argc - 1]);

    if (platform == "windows")
    {
        char *mainFileData = "echo #include \"common.h\" >> main.c && echo. >> main.c && echo int main(int argc, char *argv) { >> main.c && echo. >> main.c && echo return 0; >> main.c && echo } >> main.c";
        char commonFileData[512] = "";
        snprintf(commonFileData, sizeof(commonFileData), "echo #ifndef %s_common_h >> common.h && echo #define %s_common_h >> common.h && echo. >> common.h && echo #endif >> common.h", argv[argc - 1], argv[argc - 1]);
        char command[1024] = "";
        snprintf(command, sizeof(command), "mkdir %s && cd %s && mkdir src && cd src && type nul > main.c && type nul > common.h && %s && %s", argv[argc - 1], argv[argc - 1], mainFileData, commonFileData);
        if (!silent)
            printf("%s\n", command);
        system(command);
    }
    else
    {
        char *mainFileData = "echo #include \"common.h\" >> main.c && echo. >> main.c && echo int main(int argc, char *argv) { >> main.c && echo. >> main.c && echo return 0; >> main.c && echo } >> main.c";
        char commonFileData[512] = "";
        snprintf(commonFileData, sizeof(commonFileData), "echo #ifndef %s_common_h >> common.h && echo #define %s_common_h >> common.h && echo. >> common.h && echo #endif >> common.h", argv[argc - 1], argv[argc - 1]);
        char command[1024] = "";
        snprintf(command, sizeof(command), "mkdir %s && cd %s && mkdir src && cd src && touch main.c && touch common.h && %s && %s", argv[argc - 1], argv[argc - 1], mainFileData, commonFileData);
        if (!silent)
            printf("%s\n", command);
        system(command);
    }

    if (!silent)
        printf("Completed.\n");
    return 0;
}
