#include <gameboy/cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* memory specific */
uint8 m_peek8(CPU *u, int n)
{
    return u->mem.content[n];
}

uint8 m_consume8(CPU *u)
{
    return u->mem.content[u->mem.ptr++];
}

uint16 m_peek16(CPU *u, int n)
{
    /* https://stackoverflow.com/a/1935457 */
    return m_peek8(u, n) + (m_peek8(u, n + 1) << 8);
}

uint16 m_consume16(CPU *u)
{
    return m_consume8(u) + (m_consume8(u) << 8);
}

/* stack specific */
void s_push8(Stack *s, uint8 n) /* TODO(keyehzy): check for errors */
{
    s->content[s->ptr++] = n;
}

uint8 s_pop8(Stack *s) /* TODO(keyezy) check for errors */
{
    return s->content[--s->ptr];
}

uint8 s_peek8(Stack *s, uint8 n) /* TODO(keyehzy) check for errors */
{
    return s->content[s->ptr - n - 1];
}

void s_push16(Stack *s, uint16 n)
{
    s_push8(s, n >> 8);
    s_push8(s, n);
}

uint16 s_pop16(Stack *s)
{
    return s_pop8(s) + (s_pop8(s) << 8);
}

uint16 s_peek16(Stack *s, uint8 n)
{
    return s_peek8(s, 2 * n) + (s_peek8(s, 2 * n + 1) << 8);
}

uint8 reg(CPU *u, char REG)
{
    switch (REG)
    {
    case 'A':
        return u->reg.AF & 0x0F;
    case 'B':
        return u->reg.BC & 0x0F;
    case 'D':
        return u->reg.DE & 0x0F;
    case 'H':
        return u->reg.HL & 0x0F;
    case 'F':
        return u->reg.AF >> 4;
    case 'C':
        return u->reg.BC >> 4;
    case 'E':
        return u->reg.DE >> 4;
    case 'L':
        return u->reg.HL >> 4;
    default:
        exit(1);
    }
}

uint16 reg_combine(uint8 high, uint8 low)
{
    return high + (low << 8);
}

uint8 get_flag(CPU *u, char FLAG)
{
    uint8 F = reg(u, 'F');
    switch (FLAG)
    {
    case 'Z':
        return (F >> 7) & 0x01;
    case 'N':
        return (F >> 6) & 0x01;
    case 'H':
        return (F >> 5) & 0x01;
    case 'C':
        return (F >> 4) & 0x01;
    default:
        exit(1);
    }
}

void set_flag(CPU *u, char FLAG)
{
    /* TODO(keyehzy): We can do better than this */
    uint8 F = reg(u, 'F');
    switch (FLAG)
    {
    case 'Z':
        F = F | (1 << 7);
        break;
    case 'N':
        F = F | (1 << 6);
        break;
    case 'H':
        F = F | (1 << 5);
        break;
    case 'C':
        F = F | (1 << 4);
        break;
    default:
        exit(1);
    }
    u->reg.AF = reg_combine(reg(u, 'A'), F);
}

void reset_flag(CPU *u, char FLAG)
{
    /* TODO(keyehzy): We can do better than this */
    uint8 F = reg(u, 'F');
    switch (FLAG)
    {
    case 'Z':
        F = F & ~(1 << 7);
        break;
    case 'N':
        F = F & ~(1 << 6);
        break;
    case 'H':
        F = F & ~(1 << 5);
        break;
    case 'C':
        F = F & ~(1 << 4);
        break;
    default:
        exit(1);
    }
    u->reg.AF = reg_combine(reg(u, 'A'), F);
}

int load_rom(CPU *u, char *path)
{
    FILE *f = fopen(path, "rb");

    /* See:
     * https://medium.com/@raphaelstaebler/building-a-gameboy-from-scratch-part-2-the-cpu-d6986a5c6c74
     */
    if (f)
    {
        /* fseek(f, 0x0100, SEEK_CUR); */
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
        exit(1); /* ERROR */
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
    return 0;
}
