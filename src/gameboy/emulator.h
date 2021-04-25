#ifndef EMULATOR_H
#define EMULATOR_H
#include <gameboy/cpu.h>
#include <stdint.h>

#define CLOCK_SPEED 4194304
#define UPDATES_PER_SECOND 60
#define DEFAULT_FREQ 4096
#define MAX_CYCLES_PER_SECOND (int)(CLOCK_SPEED / UPDATES_PER_SECOND)

int emulate_rom(CPU *u);
void execute_interupts(CPU *u);
void update_timers(CPU *u, int cycles);
void update_graphics(CPU *u, int cycles);

#endif
