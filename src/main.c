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
    char command[2048] = "";
    char *command_buf = "";
    char pwd[64], userhost[128], prompt[256];
	getuserandhost(userhost);
    while (strcmp(command, "exit") != 0) {
        getpwd(pwd);
		replaceWithTilde(pwd);
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
        } else {
			execute(command);
		}

    }
    return 0;
}
