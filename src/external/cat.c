#include <stdio.h>
#include <string.h>

void main(int argc, char **argv) {
    int i = 1;
    int eflag = 0;
    int nflag = 0;
    for( ; argv[i] != NULL && argv[i][0] == '-' ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        if(strcmp(argv[i], "-E") == 0) {
            eflag = 1;
        }
        else if(strcmp(argv[i], "-n") == 0) {
            nflag = 1;
        }
        else {
            printf("Argument not supported. Refer to readme.\n");
            return;
        }
    }
    if(argv[i] == NULL) {
        char line[1024];
        int ind = 1;
        while( 1 ) {
            fgets(line, 1024, stdin);
            if(nflag) {
                printf("%d ", ind++);
            }
            if(line[strlen(line)-1] == '\n') {
                line[strlen(line)-1] = 0;
            }
            printf("%s", line);
            if(eflag) {
                printf("$");
            }
            printf("\n");
        }
        return;
    }
    int ind = 0;
    for( ; argv[i] != NULL ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        FILE *fr = fopen(argv[i], "r");
        if(fr == NULL) {
            printf("File does not exist.\n");
            return;
        }
        char line[1024];
        while (fgets(line, 1024, fr) != NULL) {
            ind++;
            if(eflag) {
                if(line[strlen(line)-1] == '\n') {
                    line[strlen(line)-1] = '$';
                }
            }
            else {
                if(line[strlen(line)-1] == '\n') {
                    line[strlen(line)-1] = 0;
                }
            }
            if(nflag) {
                fprintf(stdout, "%d %s\n", ind, line);
            }
            else {
                fprintf(stdout, "%s\n", line);
            }
        }
        fclose(fr);
    }
}