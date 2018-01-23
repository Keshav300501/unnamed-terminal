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
        //fprintf(stdout, "%d\n", sizeof(resp));
        fgets(resp, 1024, stdin);
        if(resp == NULL) {
            char *str = "Error in getting user input from terminal.";
            return str;
        }
        //fprintf(stdout, "%s\n", resp);
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

void add_history(char *line);
void unnamed_cd(char **args);
void unnamed_echo(char **args);
void unnamed_pwd(char **args);
void unnamed_history(char **args);
void unnamed_exit(char **args);

void unnamed_exec(char *line, char **args) {
    if(args[0] == NULL) {
        return;
    }
    if(strcmp(args[0], "cd") == 0) {
        unnamed_cd(args);
        add_history(line);
        return;
    }
    if(strcmp(args[0], "echo") == 0) {
        unnamed_echo(args);
        add_history(line);
        return;
    }
    if(strcmp(args[0], "pwd") == 0) {
        unnamed_pwd(args);
        add_history(line);
        return;
    }
    if(strcmp(args[0], "history") == 0) {
        unnamed_history(args);
        add_history(line);
        return;
    }
    if(strcmp(args[0], "exit") == 0) {
        unnamed_exit(args);
        add_history(line);
        return;
    }
    //return external_call(args);
}

void add_history(char *line) {
    FILE *fw = fopen("history","a");
    fprintf(fw, "%s\n", line);
    fclose(fw);
}

void unnamed_cd(char **args) {
    // printf("cd has been called\n");
    int len = -1;
    while (args[++len] != NULL) {}
    if(len > 2) {
        printf("Syntax error. Too many arguments. Refer to readme.\n");
        return;
    }
    if(args[1] == NULL) {
        chdir("/home/tank/Documents/unnamed-terminal");
        return;
    }
    args[1][strlen(args[1])-1] = 0;
    if(strcmp(args[1], "~") == 0) {
        chdir("/home/tank/Documents/unnamed-terminal");
        return;
    }
    chdir(args[1]);
    return;
}

void unnamed_echo(char **args) {
    // printf("echo has been called\n");
    int i = 1;
    int nflag = 0;
    for( ; args[i] != NULL && args[i][0] == '-' ; i++) {
        if(strcmp(args[i], "-n") == 0) {
            nflag = 1;
        }
        else {
            printf("Syntax error. Refer to readme.\n");
            return;
        }
    }
    if(args[i] == NULL) {
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
    // printf("pwd has been called\n");
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stdout, "Error in getting current path.\n");
        return;
    }
    fprintf(stdout, "%s\n", cwd);
}

void unnamed_history(char **args) {
    // printf("history has been called\n");
    int i = 1;
    for( ; args[i] != NULL && args[i][0] == '-' ; i++) {
        if(args[i+1] == NULL) {
            args[i][strlen(args[i])-1] = 0;
        }
        if(strcmp(args[i], "-c") == 0) {
            FILE *fr = fopen("history","w");
            fclose(fr);
            return;
        }
        if(strcmp(args[i], "-w") == 0) {
            if(args[i+1] == NULL) {
                printf("Missing argument to save history in. Refer to readme.\n");
                return;
            }
            if(args[i+2] == NULL) {
                args[i+1][strlen(args[i+1])-1] = 0;
            }
            FILE *fw = fopen(args[i+1],"w");
            FILE *fr = fopen("history","r+");
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
            printf("Syntax error. Refer to readme.\n");
            return;
        }
    }
    FILE *fr = fopen("history","r+");
    int ind = 0;
    char ent[128];
    while (fgets(ent, 128, fr) != NULL) {
        ind++;
        fprintf(stdout, "%d\t%s", ind, ent);
    }
    fclose(fr);
}

void unnamed_exit(char **args) {
    // printf("exit has been called\n");
    exit(0);
}

void unnamed_loop(void) {
    char *line;
    char **args;

    do {
        unnamed_prompt();
        line = unnamed_read();
        args = unnamed_split(line);
        // fprintf(stdout, "%s", line);
        // int pos = 0;
        // while(args[pos] != NULL) {
        //     printf("%s\n", args[pos]);
        //     pos++;
        // }
        unnamed_exec(line, args);
    } 
    while ( 1 );
}

int main(int argc, char **argv) {
    unnamed_loop();
}