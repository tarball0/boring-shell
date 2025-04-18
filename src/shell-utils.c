#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "boring.h"

int getArgs(char line_in[], char *charray_out[]) {
    char *in_ptr = line_in;
    int i = 0;
    while (i < 32 && (charray_out[i] = strsep(&in_ptr, " ")) != NULL) {
        i++;
    }
    charray_out[i + 1] = NULL;

    return i;
}

int execute(char *command) {
    int exec_status;
    char exe[32], *commandarr[32];
    getArgs(command, commandarr);
    strcpy(exe, commandarr[0]);
    if (strcmp(exe, "cd") == 0) {
        changedir(commandarr[1]);
        return 0;
    } else if (strcmp(command, "exit") != 0) {
        pid_t pid = fork();
        if (pid == 0) {
            exec_status = execvp(exe, commandarr);

            if (exec_status == -1) {
                printf("could not execute\n");
                exit(1);
            }
        } else if (pid > 0) {
            wait(NULL);
        } else {
            printf("fork failed\n");
            return 1;
        }
        printf("\n");
    }
	return 0;
}

int replaceWithTilde(char *pwd) {
    int uname_size, pwd_size;
    char uname[128];
    char homedir[256];
    pwd_size = strlen(pwd);
    getlogin_r(uname, 128);
    sprintf(homedir, "/home/%s", uname);

    if (strncmp(homedir, pwd, strlen(homedir)) == 0) {
        uname_size = strlen(uname);
        uname_size += 5;
        memmove(pwd, pwd + uname_size, pwd_size - uname_size + 1);
        pwd[0] = '~';
        return 0;
    }
    return -1;
}

int getuserandhost(char *userathost) {
    char uname[256];
    char hostname[256];
    gethostname(hostname, 256);
    getlogin_r(uname, 256);
    sprintf(userathost, "%s@%s", uname, hostname);
    return 0;
}
