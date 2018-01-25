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
        printf("%s\n", asctime(local));
        return;
    }
    for( ; argv[i] != NULL && argv[i][0] == '-' ; i++) {
        if(strcmp(argv[i], "-u") == 0) {
            local = gmtime(&t);
            printf("%s\n", asctime(local));
            return;
        }
        else {
            printf("Syntax error. Refer to readme.\n");
            return;
        }
    }
}