#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <gameboy/cpu.h>

typedef struct
{
    uint16_t breakpoint;
} Debugger;

typedef struct
{
    char *name;
    int (*func)(CPU *, char *arg);
    char *doc;
} CMD;

int debugger(CPU *u);
#endif
