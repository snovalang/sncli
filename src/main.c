/* main.c — snl: Snovalang Unified CLI & Toolchain Orchestrator */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  #include <process.h>
  #define EXE_EXT ".exe"
#else
  #include <unistd.h>
  #include <sys/wait.h>
  #define EXE_EXT ""
#endif

#define SNCLI_VERSION "0.1.0"

static void setup_environment(void) {
    if (!getenv("SNOVA_STD_PATH")) {
        const char *candidates[] = {
            "snova-std/src",
            "../snova-std/src",
            "../../snova-std/src",
            NULL
        };
        for (int i = 0; candidates[i]; i++) {
#ifdef _WIN32
            DWORD attrs = GetFileAttributesA(candidates[i]);
            if (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY)) {
                _putenv_s("SNOVA_STD_PATH", candidates[i]);
                break;
            }
#else
            FILE *f = fopen(candidates[i], "r");
            if (f) {
                fclose(f);
                setenv("SNOVA_STD_PATH", candidates[i], 1);
                break;
            }
#endif
        }
    }
}

static int run_compiler_command(int argc, char **argv) {
    char comp_path[1024] = {0};

    const char *candidates[] = {
        "snovac/build/snl" EXE_EXT,
        "../snovac/build/snl" EXE_EXT,
        "../../snovac/build/snl" EXE_EXT,
        "snovac/build/sncli" EXE_EXT,
        "../snovac/build/sncli" EXE_EXT,
        "../../snovac/build/sncli" EXE_EXT,
        "snovac/build/snovac" EXE_EXT,
        "../snovac/build/snovac" EXE_EXT,
        NULL
    };

    int found = 0;
    for (int i = 0; candidates[i]; i++) {
        FILE *f = fopen(candidates[i], "rb");
        if (f) {
            fclose(f);
            strncpy(comp_path, candidates[i], sizeof(comp_path) - 1);
            found = 1;
            break;
        }
    }

    if (!found) {
        strncpy(comp_path, "snl" EXE_EXT, sizeof(comp_path) - 1);
    }

    /* Build argument array */
    char **child_argv = (char **)malloc((size_t)(argc + 1) * sizeof(char *));
    child_argv[0] = comp_path;
    for (int i = 1; i < argc; i++) {
        child_argv[i] = argv[i];
    }
    child_argv[argc] = NULL;

#ifdef _WIN32
    intptr_t ret = _spawnvp(_P_WAIT, comp_path, (const char *const *)child_argv);
    free(child_argv);
    return (int)ret;
#else
    pid_t pid = fork();
    if (pid == 0) {
        execvp(comp_path, child_argv);
        exit(1);
    }
    free(child_argv);
    int status = 0;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
#endif
}

int main(int argc, char **argv) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setup_environment();

    if (argc < 2) {
        printf("snl %s - Snovalang Unified CLI\n\n", SNCLI_VERSION);
        printf("Usage:\n");
        printf("  snl run   <file.snova|--project>   Execute Snovalang code with integrated runtime\n");
        printf("  snl build <file.snova|--project>   Compile to native standalone executable\n");
        printf("  snl check <file.snova|--project>   Validate types, syntax and architecture\n");
        printf("  snl get   [url]                    Manage and download dependencies\n");
        printf("  snl tidy                           Sync modules and dependencies in mod.sno\n");
        printf("  snl --version                      Show snl version\n");
        return 0;
    }

    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0) {
        printf("snl %s (Snovalang Toolchain & CLI)\n", SNCLI_VERSION);
        return 0;
    }

    return run_compiler_command(argc, argv);
}
