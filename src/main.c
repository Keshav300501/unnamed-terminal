#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

void unnamed_prompt() {
    struct passwd *pw;
    pw = getpwuid(geteuid());
    char *user = NULL;
    if (pw)
        user = pw->pw_name;
    else {
        fprintf(stdout, "Error in getting user.\n");
        return;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stdout, "Error in getting current path.\n");
        return;
    }
    printf("<%s %s> $ ",user,cwd);
}

char *unnamed_read(void) {
        char *resp = malloc(sizeof(char)*1024);
        fgets(resp, 1024, stdin);
        if(resp == NULL) {
            char *str = "Error in getting user input from terminal.";
            return str;
        }
        return resp;
}

char **unnamed_split(char *line) {
    char **args = malloc(sizeof(char*)*1024);
    char *argx = strtok(line, " \n\t\a");
    int pos = 0;
    while(argx != NULL) {
        args[pos] = argx;
        argx = strtok(NULL, " ");
        pos++;
    }
    args[pos] = NULL;
    return args;
}

void add_history(char **args);
void unnamed_cd(char **args);
void unnamed_echo(char **args);
void unnamed_pwd(char **args);
void unnamed_history(char **args);
void unnamed_exit(char **args);

void unnamed_exec(char **args) {
    if(args[0] == NULL) {
        return;
    }
    if(strcmp(args[0], "cd") == 0) {
        unnamed_cd(args);
        add_history(args);
        return;
    }
    if(strcmp(args[0], "echo") == 0) {
        unnamed_echo(args);
        add_history(args);
        return;
    }
    if(strcmp(args[0], "pwd") == 0) {
        unnamed_pwd(args);
        add_history(args);
        return;
    }
    if(strcmp(args[0], "history") == 0) {
        unnamed_history(args);
        add_history(args);
        return;
    }
    if(strcmp(args[0], "exit") == 0) {
        unnamed_exit(args);
        add_history(args);
        return;
    }
    return external_call(args);
}

void add_history(char **args) {
    FILE *fw = fopen("/home/tank/Documents/unnamed-terminal/out/history","a");
    int i;
    for( i = 0 ; args[i] != NULL ; i++ ) {
        fprintf(fw, "%s ", args[i]);    
    }
    fprintf(fw, "\n");
    fclose(fw);
}

void unnamed_cd(char **args) {
    int len = -1;
    while (args[++len] != NULL) {}
    if(len > 2) {
        printf("Syntax error. Too many arguments. Refer to readme.\n");
        return;
    }
    if(args[1] == NULL) {
        chdir(getenv("HOME"));
        return;
    }
    args[1][strlen(args[1])-1] = 0;
    if(strcmp(args[1], "~") == 0) {
        chdir(getenv("HOME"));
        return;
    }
    if(args[1][0] == '-') {
        printf("CD doesn't support this argument. Refer to readme.\n");
    }
    if(chdir(args[1]) != 0) {
        printf("Directory not found. Refer to readme.\n");
    }
    return;
}

void unnamed_echo(char **args) {
    int i = 1;
    int nflag = 0;
    for( ; args[i] != NULL && args[i][0] == '-' ; i++) {
        if(args[i][strlen(args[i])-1] == '\n') {
            args[i][strlen(args[i])-1] = 0;
        }
        if(strcmp(args[i], "-n") == 0) {
            nflag = 1;
        }
        else {
            printf("Argument not supported. Refer to readme.\n");
            return;
        }
    }
    if(args[i] == NULL) {
        printf("\n");
        return;
    }
    if(args[i][strlen(args[i])-1] == '\n' && nflag == 1) {
        args[i][strlen(args[i])-1] = 0;
    }
    printf("%s", args[i++]);
    for( ; args[i] != NULL ; i++) {
        if(args[i][strlen(args[i])-1] == '\n' && nflag == 1) {
            args[i][strlen(args[i])-1] = 0;
        }
        printf(" %s", args[i]);
    }
}

void unnamed_pwd(char **args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stdout, "Error in getting current path.\n");
        return;
    }
    int i = 1;
    for( ; args[i] != NULL && args[i][0] == '-' ; i++) {
        printf("Argument not supported. Refer to readme.\n");
        return;
    }
    fprintf(stdout, "%s\n", cwd);
}

void unnamed_history(char **args) {
    int i = 1;
    for( ; args[i] != NULL && args[i][0] == '-' ; i++) {
        if(args[i+1] == NULL) {
            args[i][strlen(args[i])-1] = 0;
        }
        if(strcmp(args[i], "-c") == 0) {
            FILE *fr = fopen("/home/tank/Documents/unnamed-terminal/out/history","w");
            fclose(fr);
            return;
        }
        else if(strcmp(args[i], "-w") == 0) {
            if(args[i+1] == NULL) {
                printf("Missing argument to save history in. Refer to readme.\n");
                return;
            }
            if(args[i+2] == NULL) {
                args[i+1][strlen(args[i+1])-1] = 0;
            }
            FILE *fw = fopen(args[i+1],"w");
            FILE *fr = fopen("/home/tank/Documents/unnamed-terminal/out/history","r+");
            int ind = 0;
            char ent[128];
            while (fgets(ent, 128, fr) != NULL) {
                ind++;
                fprintf(fw, "%d\t%s", ind, ent);
            }
            fclose(fw);
            fclose(fr);
            return;
        }
        else {
            printf("Argument not supported. Refer to readme.\n");
            return;
        }
    }
    FILE *fr = fopen("/home/tank/Documents/unnamed-terminal/out/history","r+");
    int ind = 0;
    char ent[128];
    while (fgets(ent, 128, fr) != NULL) {
        ind++;
        fprintf(stdout, "%d\t%s", ind, ent);
    }
    fclose(fr);
}

void unnamed_exit(char **args) {
    exit(0);
}

void external_call(char **args) {
    if(strcmp(args[0], "cat") == 0) {
        if(fork() == 0) {
            execvp("/home/tank/Documents/unnamed-terminal/out/external/cat", args++);
        }
        else {
            wait(NULL);
        }
        add_history(args);
        return;
    }
    if(strcmp(args[0], "date") == 0) {
        if(fork() == 0) {
            execvp("/home/tank/Documents/unnamed-terminal/out/external/date", args++);
        }
        else {
            wait(NULL);
        }
        add_history(args);
        return;
    }
    if(strcmp(args[0], "ls") == 0) {
        if(fork() == 0) {
            execvp("/home/tank/Documents/unnamed-terminal/out/external/ls", args++);
        }
        else {
            wait(NULL);
        }
        add_history(args);
        return;
    }
    if(strcmp(args[0], "mkdir") == 0) {
        if(fork() == 0) {
            execvp("/home/tank/Documents/unnamed-terminal/out/external/mkdir", args++);
        }
        else {
            wait(NULL);
        }
        add_history(args);
        return;
    }
    if(strcmp(args[0], "rm") == 0) {
        if(fork() == 0) {
            execvp("/home/tank/Documents/unnamed-terminal/out/external/rm", args++);
        }
        else {
            wait(NULL);
        }
        add_history(args);
        return;
    }
    printf("Command not found.\n");
}

void unnamed_loop(void) {
    char *line;
    char **args;

    do {
        unnamed_prompt();
        line = unnamed_read();
        args = unnamed_split(line);
        unnamed_exec(args);
    } 
    while ( 1 );
}

int main(int argc, char **argv) {
    unnamed_loop();
}