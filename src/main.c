/*
 * the boring-shell, a random sunday project :)
 * I know this is nothing special (quite boring), although I am slowly escaping tutorial hell.
 * also, inline assembly is fun
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Escape Sequence that clears the terminal */
#define clear() printf("\033[H\033[J")

/* Function Declarations */
int getArgs(char *, char **);
int changedir(const char *);
int getpwd(char *);
int execute(char *, char **);

/* main :D */
int main(int argc, char *argv[]) {
    char prompt[] = ">>> ";
    char *commandarr[32];
    char command[2048];
    char exe[32], pwd[64];
    int len;
    while (strcmp(command, "exit") != 0) {
        if (strcmp(command, "clear") == 0) {
            clear();
        }
        getpwd(pwd);
        printf("%s %s", pwd, prompt);
        if (fgets(command, sizeof(command), stdin) == 0) {
            printf("error reading from stdin");
            return 1;
        }
        command[strcspn(command, "\n")] = '\0';
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

/* Function definitions */
int getArgs(char line_in[], char *charray_out[]) {
    char *in_ptr = line_in;
    int i = 0;
    while (i < 32 && (charray_out[i] = strsep(&in_ptr, " ")) != NULL) {
		i++;
	}
	charray_out[i+1] = NULL;

    return i;
}

/* Messing around with extended inline asm
 * this is what it's supposed to be:
 *
 *        asm ( assembler template
 *          : output operands
 *          : input operands
 *          : list of clobbered registers
 *          );
 */

int changedir(const char path[]) {
    int result;
    asm("syscall" : "=a"(result) : "a"(80), "D"(path) : "rcx", "r11", "memory");
    /* rcx and r11 are always clobbered by the syscall
     * The syscall instruction uses rcx to store the address of the next
     * instruction to return to, and r11 to save the value of the rflags
     * register. These values will then be restored by the sysret instruction.
     */
    return result;
}

int getpwd(char *pwd) {
    asm("syscall" : : "a"(79), "D"(pwd), "S"(64) : "rcx", "r11", "memory");
    return 0;
}

int execute (char *command, char **opts_arr){
	int exec_status;
	
	if (fork() == 0) {
		exec_status = execvp(command, opts_arr);

		if (exec_status == -1) {
			printf("could not execute\n");
			return 1;
		}
	}
	else {
		wait(NULL);
	}
	printf("\n");
	return 0;
}
