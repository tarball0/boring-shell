boring: src/main.c src/asm-functions.c src/shell-utils.c
	gcc -Wall src/main.c src/shell-utils.c src/asm-functions.c -o /usr/local/bin/boring -lreadline
