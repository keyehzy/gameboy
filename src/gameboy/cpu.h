#ifndef CPU_H
#define CPU_H
#include <stdint.h>

#define Z_FLAG 0x80
#define N_FLAG 0x40
#define H_FLAG 0x20
#define C_FLAG 0x10

typedef struct
{
    uint8_t title[16];
    uint8_t gb_color;
    uint8_t gb_sgb_indicator;
    uint8_t cartridge_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destintion;
    uint8_t license[3];

} GameInfo;

typedef struct
{
    uint16_t ptr;
    uint8_t content[0x10000];
} Stack;

typedef struct
{
    /*
      Memory map notes: 0x0000 - 0x8000 ROM Bank
                        0x8000 - 0xA000 VRAM
                        0xA000 - 0xC000 switchable RAM ban
                        0xC000 - 0xE000 Internal RAM
                        0xE000 - 0xFE00 Echo of 8kB Internal RAM
                        0xFE00 - 0xFEA0 Sprite Attrib Memory (OAM)
                        0xFEA0 - 0xFF00 Empty but unusable for I/O
                        0xFF00 - 0xFF4C I/O ports
                        0xFF4C - 0xFF80 Empty but unusable for I/O
                        0xFF80 - 0xFFFF Internal RAM
                        0xFFFF - 0xFFFF Interrupt Enable Register

    */
    uint16_t ptr;
    uint8_t content[0x10000]; /* 64kB */
} Memory;

typedef struct
{
    GameInfo info;
    int debug;
    Memory mem;
    Stack *st;
    struct
    {
        union
        {
            struct
            {
                uint8_t A;
                uint8_t F;
            };

            uint16_t AF;
        };

        union
        {
            struct
            {
                uint8_t B;
                uint8_t C;
            };

            uint16_t BC;
        };

        union
        {
            struct
            {
                uint8_t D;
                uint8_t E;
            };

            uint16_t DE;
        };

        union
        {
            struct
            {
                uint8_t H;
                uint8_t L;
            };

            uint16_t HL;
        };

        uint16_t SP; /* same as our st ptr */
    } reg;

} CPU;

int boot_cpu(CPU *u, int debug_flag);
int load_rom(CPU *u, char *path, int flag);
int run_rom(CPU *u);

uint8_t m_read8(CPU *u);
uint16_t m_read16(CPU *u);
uint8_t m_peek8(CPU *u);
uint16_t m_peek16(CPU *u);
uint8_t m_get8(CPU *u, uint16_t n);
uint16_t m_get16(CPU *u, uint16_t n);
void m_set8(CPU *u, uint16_t n, uint8_t val);
void m_set16(CPU *u, uint16_t n, uint16_t val);

void s_push8(Stack *s, uint8_t n);
uint8_t s_pop8(Stack *s);
void s_push16(Stack *s, uint16_t n);
uint16_t s_pop16(Stack *s);
#endif
