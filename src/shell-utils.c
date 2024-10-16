#include <stdio.h>
#include <string.h>
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

int execute(char *command, char **opts_arr) {
    int exec_status;

    if (fork() == 0) {
        exec_status = execvp(command, opts_arr);

        if (exec_status == -1) {
            printf("could not execute\n");
            return 1;
        }
    } else {
        wait(NULL);
    }
    printf("\n");
    return 0;
}

int replaceWithTilde(char *pwd) {
    int uname_size, pwd_size;
    char uname[128];
    char homedir[256];
    pwd_size = strlen(pwd);
    getlogin_r(uname, 128);
	sprintf(homedir, "/home/%s", uname);

	if (strncmp(homedir, pwd, strlen(homedir)) == 0){
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
