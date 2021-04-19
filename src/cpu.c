#include <gameboy/cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* memory specific */
void MEMORY_CONTROL(uint16_t n)
{
    if (n < 0x800)
    {
        puts("Writing to readonly memory.");
        exit(1);
    }
    if ((n >= 0xFEA0) && (n < 0xFEFF))
    {
        puts("Writing to non-usable part of memory.");
        exit(1);
    }
}

void ECHO_RAM(CPU *u, uint16_t n, uint8_t val)
{
    if ((n >= 0xc000) && (n < 0xde00))
    {
        u->mem.content[n + 0x2000] = val;
    }
    else if ((n >= 0xe000) && (n < 0xfe00))
    {
        u->mem.content[n - 0x2000] = val;
    }
}

uint8_t m_peek8(CPU *u)
{
    return u->mem.content[u->mem.ptr];
}
uint8_t m_get8(CPU *u, uint16_t n)
{
    return u->mem.content[n];
}

void m_set8(CPU *u, uint16_t n, uint8_t val)
{
    MEMORY_CONTROL(n);
    ECHO_RAM(u, n, val);
    u->mem.content[n] = val;
}

uint8_t m_read8(CPU *u)
{
    return u->mem.content[u->mem.ptr++];
}

uint16_t m_peek16(CPU *u)
{
    /* https://stackoverflow.com/a/1935457 */
    return m_get8(u, u->mem.ptr) + (m_get8(u, u->mem.ptr + 1) << 8);
}

uint16_t m_get16(CPU *u, uint16_t n)
{
    /* https://stackoverflow.com/a/1935457 */
    return m_get8(u, n) + (m_get8(u, n + 1) << 8);
}

void m_set16(CPU *u, uint16_t n, uint16_t val)
{
    m_set8(u, n, val >> 8);
    m_set8(u, n + 1, val);
}

uint16_t m_read16(CPU *u)
{
    return m_read8(u) + (m_read8(u) << 8);
}

/* stack specific */
void s_push8(CPU *u, uint8_t n) /* TODO(keyehzy): check for errors */
{
    u->st->content[u->st->ptr++] = n;
}

uint8_t s_pop8(CPU *u) /* TODO(keyezy): check for errors */
{
    return u->st->content[--u->st->ptr];
}

uint8_t s_peek8(CPU *u, uint16_t n) /* TODO(keyehzy): check for errors */
{
    return u->st->content[u->st->ptr - n - 1];
}

void s_push16(CPU *u, uint16_t n)
{
    s_push8(u, n >> 8);
    s_push8(u, n);
}

uint16_t s_pop16(CPU *u)
{
    return s_pop8(u) + (s_pop8(u) << 8);
}

uint16_t s_peek16(CPU *u, uint16_t n)
{
    return s_peek8(u, 2 * n) + (s_peek8(u, 2 * n + 1) << 8);
}

char *rom_type(uint8_t byte)
{
    switch (byte)
    {
    case 0x0:
        return "ROM ONLY";
    case 0x1:
        return "ROM+MBC";
    case 0x2:
        return "ROM+MBC1+RAM";
    case 0x3:
        return "ROM+MBC1+RAM+BATT";
    case 0x5:
        return "ROM+MBC2";
    case 0x6:
        return "ROM+MBC2+BATTERY";
    case 0x8:
        return "ROM+RAM";
    case 0x9:
        return "ROM+RAM+BATTERY";
    case 0xB:
        return "ROM+MMM01";
    case 0xC:
        return "ROM+MMM01+SRAM";
    case 0xD:
        return "ROM+MMM01+SRAM+BATT";
    case 0xF:
        return "ROM+MBC3+TIMER+BATT";
    case 0x10:
        return "ROM+MBC3+TIMER+RAM+BATT";
    case 0x11:
        return "ROM+MBC3";
    case 0x12:
        return "ROM+MBC3+RAM";
    case 0x13:
        return "ROM+MBC3+RAM+BATT";
    case 0x19:
        return "ROM+MBC5";
    case 0x1A:
        return "ROM+MBC5+RAM";
    case 0x1B:
        return "ROM+MBC5+RAM+BATT";
    case 0x1C:
        return "ROM+MBC5+RUMBLE";
    case 0x1D:
        return "ROM+MBC5+RUMBLE+SRAM";
    case 0x1E:
        return "ROM+MBC5+RUMBLE+SRAM+BATT";
    case 0x1F:
        return "Pocket Camera";
    case 0xFD:
        return "Bandai TAMA5";
    case 0xFE:
        return "Hudson HuC-3";
    case 0xFF:
        return "Hudson HuC-1";
    default:
        return "Unknown";
    }
}

char *rom_size(uint8_t byte)
{
    switch (byte)
    {
    case 0x0:
        return "32KByte";
    case 0x1:
        return "64KByte";
    case 0x2:
        return "128KByte";
    case 0x3:
        return "256KByte";
    case 0x4:
        return "512KByte";
    case 0x5:
        return "1MByte";
    case 0x6:
        return "2MByte";
    case 0x52:
        return "1.1MByte";
    case 0x53:
        return "1.2MByte";
    case 0x54:
        return "1.5MByte";
    default:
        return "Unknown";
    }
}

char *ram_size(uint8_t byte)
{
    switch (byte)
    {
    case 0x0:
        return "None";
    case 0x1:
        return "2kB";
    case 0x2:
        return "8kB";
    case 0x3:
        return "32kB";
    case 0x4:
        return "128kB";
    default:
        return "Unknown";
    }
}

GameInfo rom_info(CPU *u)
{
    GameInfo info;

    for (int i = 0; i < 16; i++)
    {
        info.title[i] = m_get8(u, 0x0134 + i);
    }

    info.gb_color = m_get8(u, 0x143) == 0x80;
    info.license[0] = m_get8(u, 0x144);
    info.license[1] = m_get8(u, 0x145);
    info.gb_sgb_indicator = m_get8(u, 0x146);
    info.cartridge_type = m_get8(u, 0x147);
    info.rom_size = m_get8(u, 0x148);
    info.ram_size = m_get8(u, 0x149);
    info.destintion = m_get8(u, 0x14a);
    info.license[2] = m_get8(u, 0x14b);

    return info;
}

void dump_info(GameInfo info)
{
    printf("Game Title: %s\n", info.title);
    printf("Color GB: %s\n", info.gb_color ? "Color" : "No Color");

    if (info.gb_sgb_indicator == 0)
    {
        printf("Mode: GameBoy\n");
    }
    else if (info.gb_sgb_indicator == 3)
    {
        printf("Mode: Super GameBoy\n");
    }

    printf("Catridge Type: %s\n", rom_type(info.cartridge_type));
    printf("ROM Size: %s\n", rom_size(info.cartridge_type));
    printf("RAM Size: %s\n", ram_size(info.cartridge_type));
    printf("Destination: %s\n", info.destintion ? "Non-Japanese" : "Japanese");

    switch (info.license[2])
    {
    case 0x33:
        printf("License code: %02x %02x\n", info.license[1], info.license[2]);
        break;
    case 0x79:
        puts("Accolade");
        break;
    case 0xA4:
        puts("Konami");
        break;
    default:
        printf("License code: %02x %02x\n", info.license[1], info.license[2]);
        break;
    }
}

int load_rom(CPU *u, char *path, int flag)
{
    FILE *f = fopen(path, "rb");

    if (f)
    {
        if (fread(u->mem.content, 0x8000, 1, f) == 0)
        { /* allocate 0x000 - 0x8000 to rom */
            fprintf(stderr, "Could not allocate rom into memory.\n");
            exit(1);
        }
        printf("ROM loaded: %s \n", path);
    }
    else
    {
        printf("Could not find ROM in path: %s\n", path);
        exit(1);
    }

    u->info = rom_info(u);

    if (flag)
    {
        dump_info(u->info);
    }
    return 0;
}

int boot_cpu(CPU *u, int debug_flag)
{
    memset(u, 0, sizeof(*u));
    if (!u)
    {
        puts("Failed to boot.");
        exit(1);
    }

    u->debug = debug_flag;
    u->st = (Stack *)malloc(sizeof(Stack));

    /* http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html */
    u->reg.AF = 0x01B0;
    u->reg.BC = 0x0013;
    u->reg.DE = 0x00D8;
    u->reg.HL = 0x014D;
    u->st->ptr = 0xFFFE; /* SP */
    u->mem.ptr = 0x100;  /* PC */
    u->mem.content[0xFF05] = 0x00;
    u->mem.content[0xFF06] = 0x00;
    u->mem.content[0xFF07] = 0x00;
    u->mem.content[0xFF10] = 0x80;
    u->mem.content[0xFF11] = 0xBF;
    u->mem.content[0xFF12] = 0xF3;
    u->mem.content[0xFF14] = 0xBF;
    u->mem.content[0xFF16] = 0x3F;
    u->mem.content[0xFF17] = 0x00;
    u->mem.content[0xFF19] = 0xBF;
    u->mem.content[0xFF1A] = 0x7F;
    u->mem.content[0xFF1B] = 0xFF;
    u->mem.content[0xFF1C] = 0x9F;
    u->mem.content[0xFF1E] = 0xBF;
    u->mem.content[0xFF20] = 0xFF;
    u->mem.content[0xFF21] = 0x00;
    u->mem.content[0xFF22] = 0x00;
    u->mem.content[0xFF23] = 0xBF;
    u->mem.content[0xFF24] = 0x77;
    u->mem.content[0xFF25] = 0xF3;
    u->mem.content[0xFF26] = 0xF1;
    u->mem.content[0xFF40] = 0x91;
    u->mem.content[0xFF42] = 0x00;
    u->mem.content[0xFF43] = 0x00;
    u->mem.content[0xFF45] = 0x00;
    u->mem.content[0xFF47] = 0xFC;
    u->mem.content[0xFF48] = 0xFF;
    u->mem.content[0xFF49] = 0xFF;
    u->mem.content[0xFF4A] = 0x00;
    u->mem.content[0xFF4B] = 0x00;
    u->mem.content[0xFFFF] = 0x00;
    return 0;
}
