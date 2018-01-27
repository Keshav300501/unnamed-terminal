#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main(int argc, char **argv) {
    time_t t = time(NULL);
    struct tm *local;
    int i = 1;
    if(argv[i] == NULL) {
        local = localtime(&t);
        printf("IST %s", asctime(local));
        return;
    }
    for( ; argv[i] != NULL && argv[i][0] == '-' ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        if(strcmp(argv[i], "-u") == 0) {
            local = gmtime(&t);
            printf("UTC %s", asctime(local));
            return;
        }
        else {
            printf("Argument not supported. Refer to readme.\n");
            return;
        }
    }
}