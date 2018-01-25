#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void main(int argc, char **argv) {
    int i = 1;
    int pflag = 0;
    int vflag = 0;
    for( ; argv[i] != NULL && argv[i][0] == '-' ; i++) {
        if(strcmp(argv[i], "-p") == 0) {
            pflag = 1;
        }
        else if(strcmp(argv[i], "-v") == 0) {
            vflag = 1;
        }
        else {
            printf("Syntax error. Refer to readme.\n");
            return;
        }
    }
    if(argv[i] == NULL) {
        printf("Not enough arguments\n");
        return;
    }
    for( ; argv[i] != NULL ; i++) {
        if (argv[i+1] == NULL) {
            argv[i][strlen(argv[i])-1] == 0;
        }
        if(pflag) {
            struct stat st = {0};
            if (stat(argv[i], &st) == 0) {
                printf("Directory %s already exists.\n", argv[i]);
            }
            else if (stat(argv[i], &st) == -1) {
                char *p;
                for(p = argv[i] + 1; *p; p++) {
                    if(*p == '/') {
                        *p = 0;
                        mkdir(argv[i], 0777);
                        *p = '/';
                    }
                    mkdir(argv[i], 0777);
                }
                if(vflag) {
                    printf("Created directory : %s\n", argv[i]);
                }
            }
            else {
                printf("Cannot create directory. Error!\n");
            }
            continue;
        }
        struct stat st = {0};
        if (stat(argv[i], &st) == 0) {
            printf("Directory %s already exists.\n", argv[i]);
        }
        else if (stat(argv[i], &st) == -1) {
            if(mkdir(argv[i], 0777) != 0) {
                printf("Use -p to recursively create directories.\n");
                continue;
            }
            if(vflag) {
                printf("Created directory : %s\n", argv[i]);
            }
        }
        else {
            printf("Cannot create directory. Error!\n");
        }
    }
}