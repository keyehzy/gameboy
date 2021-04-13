#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <gameboy/cpu.h>
typedef struct
{
    char *mnemoic;
} Instruction;

int disassemble_rom(CPU *u);
#endif
