#ifndef EMULATOR_H
#define EMULATOR_H
#include <gameboy/cpu.h>
#include <stdint.h>

#define CLOCK_SPEED 4194304
#define UPDATES_PER_SECOND 60
#define DEFAULT_FREQ 4096
#define MAX_CYCLES_PER_SECOND (int)(CLOCK_SPEED / UPDATES_PER_SECOND)

#define CASE_CB_SLA                                                            \
    case 0x20:                                                                 \
    case 0x21:                                                                 \
    case 0x22:                                                                 \
    case 0x23:                                                                 \
    case 0x24:                                                                 \
    case 0x25:                                                                 \
    case 0x26:                                                                 \
    case 0x27

#define CASE_CB_SRA                                                            \
    case 0x28:                                                                 \
    case 0x29:                                                                 \
    case 0x2A:                                                                 \
    case 0x2B:                                                                 \
    case 0x2C:                                                                 \
    case 0x2D:                                                                 \
    case 0x2E:                                                                 \
    case 0x2F

#define CASE_CB_SRL                                                            \
    case 0x38:                                                                 \
    case 0x39:                                                                 \
    case 0x3A:                                                                 \
    case 0x3B:                                                                 \
    case 0x3C:                                                                 \
    case 0x3D:                                                                 \
    case 0x3E:                                                                 \
    case 0x3F

#define CASE_CB_BIT                                                            \
    case 0x40:                                                                 \
    case 0x41:                                                                 \
    case 0x42:                                                                 \
    case 0x43:                                                                 \
    case 0x44:                                                                 \
    case 0x45:                                                                 \
    case 0x46:                                                                 \
    case 0x47

#define CASE_CB_SET                                                            \
    case 0xC0:                                                                 \
    case 0xC1:                                                                 \
    case 0xC2:                                                                 \
    case 0xC3:                                                                 \
    case 0xC4:                                                                 \
    case 0xC5:                                                                 \
    case 0xC6:                                                                 \
    case 0xC7

#define CASE_CB_RES                                                            \
    case 0x80:                                                                 \
    case 0x81:                                                                 \
    case 0x82:                                                                 \
    case 0x83:                                                                 \
    case 0x84:                                                                 \
    case 0x85:                                                                 \
    case 0x86:                                                                 \
    case 0x87

int emulate_rom(CPU *u);
int execute_opcode(CPU *u, uint8_t op);

/* Extra registers */

#endif
