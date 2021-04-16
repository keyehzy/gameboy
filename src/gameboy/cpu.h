#ifndef CPU_H
#define CPU_H

typedef unsigned char uint8;
typedef unsigned short uint16;

typedef struct
{
    uint8 ptr;
    uint8 content[256];
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
    uint16 ptr;
    uint8 content[0x10000]; /* 64kB */
} Memory;

typedef struct
{
    Memory mem;
    Stack *st;
    struct
    {
        union
        {
            struct
            {
                uint8 A;

                union
                {
                    struct
                    {
                       unsigned _B0 : 1;
                       unsigned _B1 : 1;
                       unsigned _B2 : 1;
                       unsigned _B3 : 1;
                       unsigned FC : 1;
                       unsigned FH : 1;
                       unsigned FN : 1;
                       unsigned FZ : 1;
                    };

                    uint8 F;
                };
            };

            uint16 AF;
        };

        union
        {
            struct
            {
                uint8 B;
                uint8 C;
            };

            uint16 BC;
        };

        union
        {
            struct
            {
                uint8 D;
                uint8 E;
            };

            uint16 DE;
        };

        union
        {
            struct
            {
                uint8 H;
                uint8 L;
            };

            uint16 HL;
        };

        uint16 SP; /* XXX we need to use our own stack pointer */
        uint16 PC;
    } reg;

} CPU;

int boot_cpu(CPU *u);
int load_rom(CPU *u, char *path);
int run_rom(CPU *u);

uint8 m_consume8(CPU *u);
uint16 m_consume16(CPU *u);
uint8 m_peek8(CPU *u, uint16 n);

uint16 m_peek16(CPU *u, uint16 n);
void s_push16(Stack *s, uint16 n);
uint16 s_pop16(Stack *s);

uint8 reg(CPU *u, char REG);
uint16 combine_reg(uint8 high, uint8 low);
void set_reg(CPU *u, char REG, uint8 VAL);

uint8 get_flag(CPU *u, char FLAG);
void set_flag(CPU *u, char FLAG);
void reset_flag(CPU *u, char FLAG);
#endif
