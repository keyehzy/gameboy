#include <gameboy/cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* memory specific */
uint8_t m_peek8(CPU *u)
{
    return u->mem.content[u->mem.ptr];
}

uint8_t m_get8(CPU *u, uint16_t n)
{
    return u->mem.content[n];
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

uint16_t m_read16(CPU *u)
{
    return m_read8(u) + (m_read8(u) << 8);
}

/* stack specific */
void s_push8(Stack *s, uint8_t n) /* TODO(keyehzy): check for errors */
{
    s->content[s->ptr++] = n;
}

uint8_t s_pop8(Stack *s) /* TODO(keyezy): check for errors */
{
    return s->content[--s->ptr];
}

uint8_t s_peek8(Stack *s, uint16_t n) /* TODO(keyehzy): check for errors */
{
    return s->content[s->ptr - n - 1];
}

void s_push16(Stack *s, uint16_t n)
{
    s_push8(s, n >> 8);
    s_push8(s, n);
}

uint16_t s_pop16(Stack *s)
{
    return s_pop8(s) + (s_pop8(s) << 8);
}

uint16_t s_peek16(Stack *s, uint16_t n)
{
    return s_peek8(s, 2 * n) + (s_peek8(s, 2 * n + 1) << 8);
}

int load_rom(CPU *u, char *path)
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
    return 0;
}

int boot_cpu(CPU *u)
{
    memset(u, 0, sizeof(*u));
    if (!u)
    {
        puts("Failed to boot.");
        exit(1);
    }

    /* http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html */
    u->reg.AF=0x01B0;
    u->reg.BC=0x0013;
    u->reg.DE=0x00D8;
    u->reg.HL=0x014D;
    /* u->st->ptr=0xFFFE; */
    u->mem.ptr = 0x100;
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
