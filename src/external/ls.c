#include <stdio.h>
#include <dirent.h>
#include <string.h>

void main(int argc, char **argv) {
    int i = 1;
    int aflag = 0;
    int rflag = 0;
    for( ; argv[i] != NULL && argv[i][0] == '-' ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        if(strcmp(argv[i], "-a") == 0) {
            aflag = 1;
        }
        else if(strcmp(argv[i], "-r") == 0) {
            rflag = 1;
        }
        else {
            printf("Argument not supported. Refer to readme.\n");
            return;
        }
    }
    if(argv[i] == NULL) {
        DIR *d = opendir(".");
        struct dirent *dir;
        int indx = 0;
        char *arr[1024];
        while((dir = readdir(d)) != NULL) {
            if(!aflag && dir->d_name[0] == '.') {
                continue;
            }
            arr[indx++] = dir->d_name;
        }
        char t[1024];
        int i, j;
        for (i = 1; i < indx; i++) {
            for (j = 1; j < indx; j++) {
                if (rflag == 0) {
                    if ( strcasecmp(arr[j - 1], arr[j]) > 0 ) {
                        strcpy(t, arr[j - 1]);
                        strcpy(arr[j - 1], arr[j]);
                        strcpy(arr[j], t);
                    }
                }
                else {
                    if (strcasecmp(arr[j - 1], arr[j]) < 0) {
                        strcpy(t, arr[j - 1]);
                        strcpy(arr[j - 1], arr[j]);
                        strcpy(arr[j], t);
                    }
                }
            }
        }
        for( indx = 0 ; arr[indx] != NULL ; indx++ ) {
            printf("%s    ", arr[indx]);
        }
        printf("\n");
        closedir(d);
    }
    else if(argv[i+1] == NULL) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        DIR *d = opendir(argv[i]);
        if( d == NULL ) {
            printf("Directory not found. Error!\n");
            return;
        }
        struct dirent *dir;
        int indx = 0;
        char *arr[1024];
        while((dir = readdir(d)) != NULL) {
            if(!aflag && dir->d_name[0] == '.') {
                continue;
            }
            arr[indx++] = dir->d_name;
        }
        char t[256];
        int i, j;
        for (i = 1; i < indx; i++) {
            for (j = 1; j < indx; j++) {
                if (rflag == 0) {
                    if ( strcasecmp(arr[j - 1], arr[j]) > 0 ) {
                        strcpy(t, arr[j - 1]);
                        strcpy(arr[j - 1], arr[j]);
                        strcpy(arr[j], t);
                    }
                }
                else {
                    if (strcasecmp(arr[j - 1], arr[j]) < 0) {
                        strcpy(t, arr[j - 1]);
                        strcpy(arr[j - 1], arr[j]);
                        strcpy(arr[j], t);
                    }
                }
            }
        }
        for( indx = 0 ; arr[indx] != NULL ; indx++ ) {
            printf("%s    ", arr[indx]);
        }
        printf("\n");
        closedir(d);
    }
    else for( ; argv[i] != NULL ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        DIR *d = opendir(argv[i]);
        if( d == NULL ) {
            printf("Directory not found.\n");
            return;
        }
        printf("%s\n", argv[i]);
        struct dirent *dir;
        int indx = 0;
        char *arr[1024];
        while((dir = readdir(d)) != NULL) {
            if(!aflag && dir->d_name[0] == '.') {
                continue;
            }
            arr[indx++] = dir->d_name;
        }
        char t[1024];
        int i, j;
        for (i = 1; i < indx; i++) {
            for (j = 1; j < indx; j++) {
                if (rflag == 0) {
                    if ( strcasecmp(arr[j - 1], arr[j]) > 0 ) {
                        strcpy(t, arr[j - 1]);
                        strcpy(arr[j - 1], arr[j]);
                        strcpy(arr[j], t);
                    }
                }
                else {
                    if (strcasecmp(arr[j - 1], arr[j]) < 0) {
                        strcpy(t, arr[j - 1]);
                        strcpy(arr[j - 1], arr[j]);
                        strcpy(arr[j], t);
                    }
                }
            }
        }
        for( indx = 0 ; arr[indx] != NULL ; indx++ ) {
            printf("%s    ", arr[indx]);
        }
        printf("\n");
        closedir(d);
    }
}