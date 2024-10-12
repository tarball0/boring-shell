/*
 * the boring-shell, a random sunday project :)
 * I know this is nothing special (quite boring), although I am slowly escaping
 * tutorial hell. also, inline assembly is fun
 */

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "boring.h"

/* Escape Sequence that clears the terminal */
#define clear() printf("\033[H\033[J")


/* main :D */
int main(int argc, char *argv[]) {
	char prompt[256];
    char *commandarr[32];
    char command[2048] = "";
    char *command_buf = "";
    char exe[32], pwd[64], userhost[128];
	getuserandhost(userhost);
    while (strcmp(exe, "exit") != 0) {
        getpwd(pwd);
		sprintf(prompt, "%s %s $ ", userhost, pwd);
        if ((command_buf = readline(prompt)) == NULL) {
            printf("error reading from stdin");
            return 1;
        }
        add_history(command_buf);
        strcpy(command, command_buf);
        free(command_buf);

        if (strcmp(command, "clear") == 0) {
            clear();
        }

        getArgs(command, commandarr);
        strcpy(exe, commandarr[0]);
        if (strcmp(exe, "cd") == 0) {
            changedir(commandarr[1]);
        }

        else if (strcmp(command, "exit") != 0) {
            execute(exe, commandarr);
        }

    }
    return 0;
}
