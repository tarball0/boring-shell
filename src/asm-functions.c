#include "boring.h"

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
