#ifndef BORING_H
#define BORING_H

// asm-functions.c
int changedir(const char *);
int getpwd(char *);

// shell-utils.c
int replaceWithTilde(char *);
int getuserandhost(char *);
int execute(char *, char **);
int getArgs(char *, char **);

#endif // !BORING_H
