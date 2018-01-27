#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void main(int argc, char **argv) {
    int i = 1;
    int iflag = 0;
    int dflag = 0;
    for( ; argv[i] != NULL && argv[i][0] == '-' ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        if(strcmp(argv[i], "-i") == 0) {
            iflag = 1;
        }
        else if(strcmp(argv[i], "-d") == 0) {
            dflag = 1;
        }
        else {
            printf("Argument not supported. Refer to readme.\n");
            return;
        }
    }
    if(argv[i] == NULL) {
        printf("Not enough arguments\n");
        return;
    }
    for( ; argv[i] != NULL ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        if(iflag) {
            printf("Are you sure you want to remove %s? ", argv[i]);
            char str[50];
            gets(str);
            if(strcasecmp(str, "y") != 0) {
                return;
            }
        }
        DIR *dir = opendir(argv[i]);
        if(dir == NULL) {
            FILE *fr = fopen(argv[i], "r");
            if(fr == NULL) {
                printf("File does not exist.\n");
                return;
            }
            remove(argv[i]);
            fclose(fr);
            continue;
        }
        if(dflag == 0) {
            printf("Cannot perform rm on directories.\n");
            closedir(dir);
            return;
        }
        if(rmdir(argv[i]) == 0) {
            closedir(dir);
            continue;
        }
        printf("Non empty directory. Cannot perform rm.\n");
        closedir(dir);
        return;
    }
}