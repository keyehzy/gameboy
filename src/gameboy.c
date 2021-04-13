#include "gameboy/cpu.h"
#include "gameboy/disassembler.h"

int main(int argc, char **argv)
{
    CPU u;
    boot_cpu(&u);
    load_rom(&u, "roms/tetris.gb");
    disassemble_rom(&u);

    return 0;
}
