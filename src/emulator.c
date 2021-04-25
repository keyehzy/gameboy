#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>
#include <gameboy/emulator.h>

#define cast_signed8(x) (int)((int8_t)(x))
#define cycles(x) u->cycles += (x)

static void ADD_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst + src);
    /* http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html */
    /* https://stackoverflow.com/questions/8868396/game-boy-what-constitutes-a-half-carry
     */
    uint16_t wrap = (uint16_t)((*dst & 0xF) + (src & 0xF));
    *dst = (uint8_t)res;
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 0;
    u->reg.FH = wrap > 0xF;
    u->reg.FC = res > 0xFF;
}

static void ADD_16(CPU *u, uint16_t *dst, uint16_t src)
{
    uint32_t res = (uint32_t)(*dst + src);
    uint32_t wrap = (uint32_t)((*dst & 0xFFF) + (src & 0xFFF));
    *dst = (uint16_t)res;
    cycles(8);

    u->reg.FN = 0;
    u->reg.FH = wrap > 0x0FF;
    u->reg.FC = res > 0xFFFF;
}

static void ADC_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst + src + (u->reg.F & C_FLAG));
    uint16_t wrap =
        (uint16_t)((*dst & 0xF) + ((src + (u->reg.F & C_FLAG)) & 0xF));
    *dst = (uint8_t)res;
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 0;
    u->reg.FH = wrap > 0xF;
    u->reg.FC = res > 0xFF;
}

static void SUB_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst - src);
    uint16_t wrap = (uint16_t)((*dst & 0xF) - (src & 0xF));
    *dst = (uint8_t)res;
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 1;
    u->reg.FH = wrap > 0xF;
    u->reg.FC = res > 0xFF;
}

static void SBC_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst - (src + (u->reg.F & C_FLAG)));
    uint16_t wrap =
        (uint16_t)((*dst & 0xF) - ((src + (u->reg.F & C_FLAG)) & 0xF));
    *dst = (uint8_t)res;
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 0;
    u->reg.FH = wrap > 0xF;
    u->reg.FC = res > 0xFF;
}

static void AND_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst & src);
    *dst = (uint8_t)res;
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 0;
    u->reg.FH = 1;
    u->reg.FC = 0;
}

static void XOR_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst ^ src);
    *dst = (uint8_t)res;
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = 0;
}

static void OR_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst | src);
    *dst = (uint8_t)res;
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = 0;
}

static void CP_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)((*dst) - src);
    uint16_t wrap = (uint16_t)(((*dst) & 0xF) - (src & 0xF));
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 1;
    u->reg.FH = wrap > 0xF;
    u->reg.FC = res > 0xFF;
}

static void INC_8(CPU *u, uint8_t *dst)
{
    uint8_t res = ++(*dst);
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 0;
    u->reg.FH = (res & 0xF) == 0;
}

static void DEC_8(CPU *u, uint8_t *dst)
{
    uint8_t res = --(*dst);
    cycles(4);

    u->reg.FZ = res == 0;
    u->reg.FN = 1;
    u->reg.FH = (res & 0xF) == 0xF;
}

static void SWAP_8(uint8_t *dst)
{
    uint8_t lower = (*dst) & 0x1;
    uint8_t upper = (*dst) & 0x10;

    *dst = upper + (lower << 4);
}

static void RLC(CPU *u, uint8_t *dst)
{
    uint8_t carry = (*dst) & 0x80;
    (*dst) = ((*dst) << 1) | ((*dst) >> 7);

    u->reg.FZ = (*dst) == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = carry;
}

static void RL(CPU *u, uint8_t *dst)
{
    uint8_t carry = (*dst) & 0x80;
    (*dst) = ((*dst) << 1) | ((*dst) >> 7);
    (*dst) |= carry;

    u->reg.FZ = (*dst) == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = carry;
}

static void RRC(CPU *u, uint8_t *dst)
{
    uint8_t carry = (*dst) & 0x1;
    (*dst) = ((*dst) >> 1) | ((*dst) << 7);

    u->reg.FZ = (*dst) == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = carry;
}

static void RR(CPU *u, uint8_t *dst)
{
    uint8_t carry = (*dst) & 0x1;
    (*dst) = ((*dst) >> 1) | ((*dst) << 7);
    (*dst) |= carry;

    u->reg.FZ = (*dst) == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = carry; /* XXX */
    cycles(4);
}

static void SLA(CPU *u, uint8_t *dst)
{
    uint8_t carry = (*dst) & 0x80;
    (*dst) <<= 1;
    /* XXX SB of n set to 0 */
    u->reg.FZ = (*dst) == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = carry;
}

static void SRA(CPU *u, uint8_t *dst)
{
    uint8_t carry = (*dst) & 0x1;
    (*dst) >>= 1;
    /* XXX MSB doesn't change */
    u->reg.FZ = (*dst) == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = carry;
}

static void SRL(CPU *u, uint8_t *dst)
{
    uint8_t carry = (*dst) & 0x1;
    (*dst) >>= 1;
    /* XXX MSB set to 0 */
    u->reg.FZ = (*dst) == 0;
    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = carry;
}

static void BIT(CPU *u, uint8_t dst, uint8_t bit)
{
    u->reg.FZ = ((dst & bit) == 0);
    u->reg.FN = 0;
    u->reg.FH = 1;
}

int execute_opcode(CPU *u, uint8_t op)
{
    if (u->mem.ptr >= 0x8000)
    {
        fprintf(stderr, "End of ROM.\n");
        return 1;
    }

    switch (op) /* The order should be the
                   same as in the GameBoy manual */
    {
        /* LD nn,n */
    case 0x06: /* LD B,d8 */
        u->reg.B = m_read8(u);
        cycles(8);
        break;
    case 0x0E: /* LD C,d8 */
        u->reg.C = m_read8(u);
        cycles(8);
        break;
    case 0x16: /* LD D,d8 */
        u->reg.D = m_read8(u);
        cycles(8);
        break;
    case 0x1E: /* LD E,d8 */
        u->reg.E = m_read8(u);
        cycles(8);
        break;
    case 0x26: /* LD H,d8 */
        u->reg.H = m_read8(u);
        cycles(8);
        break;
    case 0x2E: /* LD L,d8 */
        u->reg.L = m_read8(u);
        cycles(8);
        break;

        /* LD r1,r2 */
    case 0x7F:
        u->reg.A = u->reg.A;
        cycles(4);
        break;
    case 0x78:
        u->reg.A = u->reg.B;
        cycles(4);
        break;
    case 0x79:
        u->reg.A = u->reg.C;
        cycles(4);
        break;
    case 0x7A:
        u->reg.A = u->reg.D;
        cycles(4);
        break;
    case 0x7B:
        u->reg.A = u->reg.E;
        cycles(4);
        break;
    case 0x7C:
        u->reg.A = u->reg.H;
        cycles(4);
        break;
    case 0x7D:
        u->reg.A = u->reg.L;
        cycles(4);
        break;
    case 0x7E:
        u->reg.A = m_get8(u, u->reg.HL);
        cycles(8);
        break;

    case 0x47:
        u->reg.B = u->reg.A;
        cycles(4);
        break;
    case 0x40:
        u->reg.B = u->reg.B;
        cycles(4);
        break;
    case 0x41:
        u->reg.B = u->reg.C;
        cycles(4);
        break;
    case 0x42:
        u->reg.B = u->reg.D;
        cycles(4);
        break;
    case 0x43:
        u->reg.B = u->reg.E;
        cycles(4);
        break;
    case 0x44:
        u->reg.B = u->reg.H;
        cycles(4);
        break;
    case 0x45:
        u->reg.B = u->reg.L;
        cycles(4);
        break;
    case 0x46:
        u->reg.B = m_get8(u, u->reg.HL);
        cycles(8);
        break;

    case 0x4F:
        u->reg.C = u->reg.A;
        cycles(4);
        break;
    case 0x48:
        u->reg.C = u->reg.B;
        cycles(4);
        break;
    case 0x49:
        u->reg.C = u->reg.C;
        cycles(4);
        break;
    case 0x4A:
        u->reg.C = u->reg.D;
        cycles(4);
        break;
    case 0x4B:
        u->reg.C = u->reg.E;
        cycles(4);
        break;
    case 0x4C:
        u->reg.C = u->reg.H;
        cycles(4);
        break;
    case 0x4D:
        u->reg.C = u->reg.L;
        cycles(4);
        break;
    case 0x4E:
        u->reg.C = m_get8(u, u->reg.HL);
        cycles(8);
        break;

    case 0x57:
        u->reg.D = u->reg.A;
        cycles(4);
        break;
    case 0x50:
        u->reg.D = u->reg.B;
        cycles(4);
        break;
    case 0x51:
        u->reg.D = u->reg.C;
        cycles(4);
        break;
    case 0x52:
        u->reg.D = u->reg.D;
        cycles(4);
        break;
    case 0x53:
        u->reg.D = u->reg.E;
        cycles(4);
        break;
    case 0x54:
        u->reg.D = u->reg.H;
        cycles(4);
        break;
    case 0x55:
        u->reg.D = u->reg.L;
        cycles(4);
        break;
    case 0x56:
        u->reg.D = m_get8(u, u->reg.HL);
        cycles(8);
        break;

    case 0x5F:
        u->reg.E = u->reg.A;
        cycles(4);
        break;
    case 0x58:
        u->reg.E = u->reg.B;
        cycles(4);
        break;
    case 0x59:
        u->reg.E = u->reg.C;
        cycles(4);
        break;
    case 0x5A:
        u->reg.E = u->reg.D;
        cycles(4);
        break;
    case 0x5B:
        u->reg.E = u->reg.E;
        cycles(4);
        break;
    case 0x5C:
        u->reg.E = u->reg.H;
        cycles(4);
        break;
    case 0x5D:
        u->reg.E = u->reg.L;
        cycles(4);
        break;
    case 0x5E:
        u->reg.E = m_get8(u, u->reg.HL);
        cycles(8);
        break;

    case 0x67:
        u->reg.H = u->reg.A;
        cycles(4);
        break;
    case 0x60:
        u->reg.H = u->reg.B;
        cycles(4);
        break;
    case 0x61:
        u->reg.H = u->reg.C;
        cycles(4);
        break;
    case 0x62:
        u->reg.H = u->reg.D;
        cycles(4);
        break;
    case 0x63:
        u->reg.H = u->reg.E;
        cycles(4);
        break;
    case 0x64:
        u->reg.H = u->reg.H;
        cycles(4);
        break;
    case 0x65:
        u->reg.H = u->reg.L;
        cycles(4);
        break;
    case 0x66:
        u->reg.H = m_get8(u, u->reg.HL);
        cycles(8);
        break;

    case 0x6F:
        u->reg.L = u->reg.A;
        cycles(4);
        break;
    case 0x68:
        u->reg.L = u->reg.B;
        cycles(4);
        break;
    case 0x69:
        u->reg.L = u->reg.C;
        cycles(4);
        break;
    case 0x6A:
        u->reg.L = u->reg.D;
        cycles(4);
        break;
    case 0x6B:
        u->reg.L = u->reg.E;
        cycles(4);
        break;
    case 0x6C:
        u->reg.L = u->reg.H;
        cycles(4);
        break;
    case 0x6D:
        u->reg.L = u->reg.L;
        cycles(4);
        break;
    case 0x6E:
        u->reg.L = m_get8(u, u->reg.HL);
        cycles(8);
        break;

    case 0x77:
        m_set8(u, u->reg.HL, u->reg.A);
        cycles(8);
        break;
    case 0x70:
        m_set8(u, u->reg.HL, u->reg.B);
        cycles(8);
        break;
    case 0x71:
        m_set8(u, u->reg.HL, u->reg.C);
        cycles(8);
        break;
    case 0x72:
        m_set8(u, u->reg.HL, u->reg.D);
        cycles(8);
        break;
    case 0x73:
        m_set8(u, u->reg.HL, u->reg.E);
        cycles(8);
        break;
    case 0x74:
        m_set8(u, u->reg.HL, u->reg.H);
        cycles(8);
        break;
    case 0x75:
        m_set8(u, u->reg.HL, u->reg.L);
        cycles(8);
        break;

    case 0x36: /* LD (HL),d8 */
        m_set8(u, u->reg.HL, m_read8(u));
        cycles(12);
        break;

        /* LD A,n */
    case 0x0A: /* LD A, (BC) */
        u->reg.A = m_get8(u, u->reg.BC);
        cycles(8);
        break;
    case 0x1A: /* LD A, (DE) */
        u->reg.A = m_get8(u, u->reg.DE);
        cycles(8);
        break;
    case 0xFA: /* LD A,(a16) */
        u->reg.A = m_get8(u, m_read16(u));
        cycles(16);
        break;
    case 0x3E: /* LD A,d8 */
        u->reg.A = m_read8(u);
        cycles(8);
        break;

        /* LD n,A */
    case 0x02: /* LD (BC),A */
        m_set8(u, u->reg.BC, u->reg.A);
        cycles(8);
        break;
    case 0x12: /* LD (DE),A */
        m_set8(u, u->reg.DE, u->reg.A);
        cycles(8);
        break;
    case 0xEA: /* LD (a16),A */
        m_set8(u, m_read16(u), u->reg.A);
        cycles(16);
        break;

        /* LD A,(C) */
    case 0xF2: /* LD A,(C) */
        u->reg.A = m_get8(u, 0xFF00 + u->reg.C);
        cycles(8);
        break;

        /* LD (C),A */
    case 0xE2: /* LD (C), A */
        m_set8(u, 0xFF00 + u->reg.C, u->reg.A);
        cycles(8);
        break;

    case 0x3A: /* LD A,(HL-) */
        u->reg.A = m_get8(u, u->reg.HL--);
        cycles(8);
        break;

    case 0x32: /* LD (HL-),A */
        m_set8(u, u->reg.HL--, u->reg.A);
        cycles(8);
        break;

    case 0x2A: /* LD A,(HL+) */
        u->reg.A = m_get8(u, u->reg.HL++);
        cycles(8);
        break;

    case 0x22: /* LD (HL+),A */
        m_set8(u, u->reg.HL++, u->reg.A);
        cycles(8);
        break;

    case 0xE0: /* LDH (a8),A */ /* SIGN XXX */
        m_set8(u, 0xFF00 + m_read8(u), u->reg.A);
        cycles(12);
        break;

        /* LDH A,(n) */
    case 0xF0: /* LDH A,(a8) */ /* SIGN XXX */
        u->reg.A = m_get8(u, 0xFF00 + m_read8(u));
        cycles(12);
        break;

        /* LD n,nn */
    case 0x01: /* LD BC,d16 */
        u->reg.BC = m_read16(u);
        cycles(12);
        break;
    case 0x11: /* LD DE,d16 */
        u->reg.DE = m_read16(u);
        cycles(12);
        break;
    case 0x21: /* LD HL,d16 */
        u->reg.HL = m_read16(u);
        cycles(12);
        break;
    case 0x31: /* LD SP,d16 */
        u->reg.SP = m_read16(u);
        cycles(12);
        break;

        /* LD SP,HL */
    case 0xF9: /* LD SP,HL */
        u->reg.SP = u->reg.HL;
        cycles(8);
        break;

        /* LDHL SP,n */
    case 0xF8: /* LD HL,SP+r8 */
        u->reg.HL = u->reg.SP + cast_signed8(m_read8(u));
        cycles(12);

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = 1;
        u->reg.FN = 0;
        u->reg.FH = 1; /* XXX */
        u->reg.FC = 1; /* XXX */
        break;

        /* LD (nn),SP */
    case 0x08: /* LD (a16),SP */
        m_set8(u, m_read16(u), u->reg.SP);
        cycles(20);
        break;

    case 0xF5: /* PUSH nn */
        s_push16(u, u->reg.AF);
        cycles(16);
        break;
    case 0xC5:
        s_push16(u, u->reg.BC);
        cycles(16);
        break;
    case 0xD5:
        s_push16(u, u->reg.DE);
        cycles(16);
        break;
    case 0xE5:
        s_push16(u, u->reg.HL);
        cycles(16);
        break;

    case 0xF1: /* POP nn */
        u->reg.AF = s_pop16(u);
        cycles(12);
        break;
    case 0xC1:
        u->reg.BC = s_pop16(u);
        cycles(12);
        break;
    case 0xD1:
        u->reg.DE = s_pop16(u);
        cycles(12);
        break;
    case 0xE1:
        u->reg.HL = s_pop16(u);
        cycles(12);
        break;

    case 0x87: /* ADD A,n */
        ADD_8(u, &u->reg.A, u->reg.A);
        break;
    case 0x80:
        ADD_8(u, &u->reg.A, u->reg.B);
        break;
    case 0x81:
        ADD_8(u, &u->reg.A, u->reg.C);
        break;
    case 0x82:
        ADD_8(u, &u->reg.A, u->reg.D);
        break;
    case 0x83:
        ADD_8(u, &u->reg.A, u->reg.E);
        break;
    case 0x84:
        ADD_8(u, &u->reg.A, u->reg.H);
        break;
    case 0x85:
        ADD_8(u, &u->reg.A, u->reg.L);
        break;
    case 0x86:
        ADD_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xC6:
        ADD_8(u, &u->reg.A, m_read8(u));
        cycles(4);
        break;

    case 0x8F: /* ADC A,n */
        ADC_8(u, &u->reg.A, u->reg.A);
        break;
    case 0x88:
        ADC_8(u, &u->reg.A, u->reg.B);
        break;
    case 0x89:
        ADC_8(u, &u->reg.A, u->reg.C);
        break;
    case 0x8A:
        ADC_8(u, &u->reg.A, u->reg.D);
        break;
    case 0x8B:
        ADC_8(u, &u->reg.A, u->reg.E);
        break;
    case 0x8C:
        ADC_8(u, &u->reg.A, u->reg.H);
        break;
    case 0x8D:
        ADC_8(u, &u->reg.A, u->reg.L);
        break;
    case 0x8E:
        ADC_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xCE:
        ADC_8(u, &u->reg.A, m_read8(u));
        cycles(4);
        break;

    case 0x97: /* SUB n */
        SUB_8(u, &u->reg.A, u->reg.A);
        break;
    case 0x90:
        SUB_8(u, &u->reg.A, u->reg.B);
        break;
    case 0x91:
        SUB_8(u, &u->reg.A, u->reg.C);
        break;
    case 0x92:
        SUB_8(u, &u->reg.A, u->reg.D);
        break;
    case 0x93:
        SUB_8(u, &u->reg.A, u->reg.E);
        break;
    case 0x94:
        SUB_8(u, &u->reg.A, u->reg.H);
        break;
    case 0x95:
        SUB_8(u, &u->reg.A, u->reg.L);
        break;
    case 0x96:
        SUB_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xD6:
        SUB_8(u, &u->reg.A, m_read8(u));
        cycles(4);
        break;

    case 0x9F: /* SBC */
        SBC_8(u, &u->reg.A, u->reg.A);
        break;
    case 0x98:
        SBC_8(u, &u->reg.A, u->reg.B);
        break;
    case 0x99:
        SBC_8(u, &u->reg.A, u->reg.C);
        break;
    case 0x9A:
        SBC_8(u, &u->reg.A, u->reg.D);
        break;
    case 0x9B:
        SBC_8(u, &u->reg.A, u->reg.E);
        break;
    case 0x9C:
        SBC_8(u, &u->reg.A, u->reg.H);
        break;
    case 0x9D:
        SBC_8(u, &u->reg.A, u->reg.L);
        break;
    case 0x9E:
        SBC_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xDE:
        SBC_8(u, &u->reg.A, m_read8(u));
        cycles(4);
        break;

    case 0xA7: /* AND n */
        AND_8(u, &u->reg.A, u->reg.A);
        break;
    case 0xA0:
        AND_8(u, &u->reg.A, u->reg.B);
        break;
    case 0xA1:
        AND_8(u, &u->reg.A, u->reg.C);
        break;
    case 0xA2:
        AND_8(u, &u->reg.A, u->reg.D);
        break;
    case 0xA3:
        AND_8(u, &u->reg.A, u->reg.E);
        break;
    case 0xA4:
        AND_8(u, &u->reg.A, u->reg.H);
        break;
    case 0xA5:
        AND_8(u, &u->reg.A, u->reg.L);
        break;
    case 0xA6:
        AND_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xE6:
        AND_8(u, &u->reg.A, m_read8(u));
        cycles(4);
        break;

    case 0xB7: /* OR n */
        OR_8(u, &u->reg.A, u->reg.A);
        break;
    case 0xB0:
        OR_8(u, &u->reg.A, u->reg.B);
        break;
    case 0xB1:
        OR_8(u, &u->reg.A, u->reg.C);
        break;
    case 0xB2:
        OR_8(u, &u->reg.A, u->reg.D);
        break;
    case 0xB3:
        OR_8(u, &u->reg.A, u->reg.E);
        break;
    case 0xB4:
        OR_8(u, &u->reg.A, u->reg.H);
        break;
    case 0xB5:
        OR_8(u, &u->reg.A, u->reg.L);
        break;
    case 0xB6:
        OR_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xF6:
        OR_8(u, &u->reg.A, m_read8(u));
        cycles(4);
        break;

    case 0xAF: /* XOR n */
        XOR_8(u, &u->reg.A, u->reg.A);
        break;
    case 0xA8:
        XOR_8(u, &u->reg.A, u->reg.B);
        break;
    case 0xA9:
        XOR_8(u, &u->reg.A, u->reg.C);
        break;
    case 0xAA:
        XOR_8(u, &u->reg.A, u->reg.D);
        break;
    case 0xAB:
        XOR_8(u, &u->reg.A, u->reg.E);
        break;
    case 0xAC:
        XOR_8(u, &u->reg.A, u->reg.H);
        break;
    case 0xAD:
        XOR_8(u, &u->reg.A, u->reg.L);
        break;
    case 0xAE:
        XOR_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xEE:
        XOR_8(u, &u->reg.A, m_read8(u));
        cycles(4);
        break;

    case 0xBF: /* CP n */
        CP_8(u, &u->reg.A, u->reg.A);
        break;
    case 0xB8:
        CP_8(u, &u->reg.A, u->reg.B);
        break;
    case 0xB9:
        CP_8(u, &u->reg.A, u->reg.C);
        break;
    case 0xBA:
        CP_8(u, &u->reg.A, u->reg.D);
        break;
    case 0xBB:
        CP_8(u, &u->reg.A, u->reg.E);
        break;
    case 0xBC:
        CP_8(u, &u->reg.A, u->reg.H);
        break;
    case 0xBD:
        CP_8(u, &u->reg.A, u->reg.L);
        break;
    case 0xBE:
        CP_8(u, &u->reg.A, m_get8(u, u->reg.HL));
        cycles(4);
        break;
    case 0xFE:
        CP_8(u, &u->reg.A, m_read8(u));
        cycles(4); /* FIX CYCLES */
        break;

    case 0x3C: /* INC n */
        INC_8(u, &u->reg.A);
        break;
    case 0x04:
        INC_8(u, &u->reg.B);
        break;
    case 0x0C:
        INC_8(u, &u->reg.C);
        break;
    case 0x14:
        INC_8(u, &u->reg.D);
        break;
    case 0x1C:
        INC_8(u, &u->reg.E);
        break;
    case 0x24:
        INC_8(u, &u->reg.H);
        break;
    case 0x2C:
        INC_8(u, &u->reg.L);
        break;
    case 0x34:
        INC_8(u, m_ptr8(u, u->reg.HL));
        cycles(12);
        break;

    case 0x3D: /* DEC n */
        DEC_8(u, &u->reg.A);
        break;
    case 0x05:
        DEC_8(u, &u->reg.B);
        break;
    case 0x0D:
        DEC_8(u, &u->reg.C);
        break;
    case 0x15:
        DEC_8(u, &u->reg.F);
        break;
    case 0x1D:
        DEC_8(u, &u->reg.E);
        break;
    case 0x25:
        DEC_8(u, &u->reg.H);
        break;
    case 0x2D:
        DEC_8(u, &u->reg.L);
        break;
    case 0x35:
        DEC_8(u, m_ptr8(u, u->reg.HL));
        cycles(12);
        break;

    case 0x09: /* ADD HL,n */
        ADD_16(u, &u->reg.HL, u->reg.BC);
        break;
    case 0x19:
        ADD_16(u, &u->reg.HL, u->reg.DE);
        break;
    case 0x29:
        ADD_16(u, &u->reg.HL, u->reg.HL);
        break;
    case 0x39:
        ADD_16(u, &u->reg.HL, u->reg.SP);
        break;

    case 0xE8: /* ADD SP,n */
        u->reg.SP += cast_signed8(m_read8(u));
        cycles(16);

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = 1;
        u->reg.FN = 0;
        u->reg.FH = 1; /* XXX */
        u->reg.FC = 1; /* XXX */
        break;

    case 0x03: /* INC nn */
        u->reg.BC++;
        cycles(8);
        break;
    case 0x13:
        u->reg.DE++;
        cycles(8);
        break;
    case 0x23:
        u->reg.HL++;
        cycles(8);
        break;
    case 0x33:
        u->reg.SP++;
        cycles(8);
        break;

    case 0x0B: /* DEC nn */
        u->reg.BC--;
        cycles(8);
        break;
    case 0x1B:
        u->reg.DE--;
        cycles(8);
        break;
    case 0x2B:
        u->reg.HL--;
        cycles(8);
        break;
    case 0x3B:
        u->reg.SP--;
        cycles(8);
        break;

    case 0x27: /* DAA XXX */
        cycles(4);
        break;

    case 0x2F: /* CPL */
        u->reg.A = ~(u->reg.A);
        cycles(4);

        u->reg.FN = 1;
        u->reg.FH = 1;
        break;

    case 0x3F: /* CCF */
        u->reg.F ^= C_FLAG;
        cycles(4);

        u->reg.FN = 0;
        u->reg.FH = 0;
        break;

    case 0x37: /* SCF */
        u->reg.FC = 1;
        cycles(4);
        break;

    case 0x0: /* NOP */
        cycles(4);
        break;

    case 0x76: /* HALT */
        /* Power down CPU */
        cycles(4);
        break;

    case 0x10: /* STOP */
        /* Halt CPU & LCD */
        cycles(4);
        break;

    case 0xF3: /* DI */
        u->interrupts = 0;
        cycles(4);
        break;

    case 0xFB: /* EI */
        u->interrupts = 1;
        cycles(4);
        break;

    case 0x07: /* RLCA */ /* see https://stackoverflow.com/a/2761205 */
        RLC(u, &u->reg.A);
        cycles(4);
        break;

    case 0x17: /* RLA */
        RL(u, &u->reg.A);
        cycles(4);
        break;

    case 0x0F: /* RRCA */
        RRC(u, &u->reg.A);
        cycles(4);
        break;

    case 0x1F: /* RRA */
        RR(u, &u->reg.A);
        cycles(4);
        break;

    case 0xCB: /* PREFIX CB */
    {
        uint8_t next = m_read8(u);
        switch (next)
        {
        case 0x07: /* RLC */
            RLC(u, &u->reg.A);
            cycles(8);
            break;
        case 0x00:
            RLC(u, &u->reg.B);
            cycles(8);
            break;
        case 0x01:
            RLC(u, &u->reg.C);
            cycles(8);
            break;
        case 0x02:
            RLC(u, &u->reg.D);
            cycles(8);
            break;
        case 0x03:
            RLC(u, &u->reg.E);
            cycles(8);
            break;
        case 0x04:
            RLC(u, &u->reg.H);
            cycles(8);
            break;
        case 0x05:
            RLC(u, &u->reg.L);
            cycles(8);
            break;
        case 0x06:
            RLC(u, m_ptr8(u, u->reg.HL));
            cycles(16);
            break;

        case 0x0F: /* RRC */
            RRC(u, &u->reg.A);
            cycles(8);
            break;
        case 0x08:
            RRC(u, &u->reg.B);
            cycles(8);
            break;
        case 0x09:
            RRC(u, &u->reg.C);
            cycles(8);
            break;
        case 0x0A:
            RRC(u, &u->reg.D);
            cycles(8);
            break;
        case 0x0B:
            RRC(u, &u->reg.E);
            cycles(8);
            break;
        case 0x0C:
            RRC(u, &u->reg.H);
            cycles(8);
            break;
        case 0x0D:
            RRC(u, &u->reg.L);
            cycles(8);
            break;
        case 0x0E:
            RRC(u, m_ptr8(u, u->reg.A));
            cycles(16);
            break;

        case 0x17: /* RL */
            RL(u, &u->reg.A);
            cycles(8);
            break;
        case 0x10:
            RL(u, &u->reg.B);
            cycles(8);
            break;
        case 0x11:
            RL(u, &u->reg.C);
            cycles(8);
            break;
        case 0x12:
            RL(u, &u->reg.D);
            cycles(8);
            break;
        case 0x13:
            RL(u, &u->reg.E);
            cycles(8);
            break;
        case 0x14:
            RL(u, &u->reg.H);
            cycles(8);
            break;
        case 0x15:
            RL(u, &u->reg.L);
            cycles(8);
            break;
        case 0x16:
            RL(u, m_ptr8(u, u->reg.A));
            cycles(16);
            break;

        case 0x1F: /* RR */
            RR(u, &u->reg.A);
            cycles(8);
            break;
        case 0x18:
            RR(u, &u->reg.B);
            cycles(8);
            break;
        case 0x19:
            RR(u, &u->reg.C);
            cycles(8);
            break;
        case 0x1A:
            RR(u, &u->reg.D);
            cycles(8);
            break;
        case 0x1B:
            RR(u, &u->reg.E);
            cycles(8);
            break;
        case 0x1C:
            RR(u, &u->reg.H);
            cycles(8);
            break;
        case 0x1D:
            RR(u, &u->reg.L);
            cycles(8);
            break;
        case 0x1E:
            RR(u, m_ptr8(u, u->reg.A));
            cycles(16);
            break;

        case 0x27: /* SLA */
            SLA(u, &u->reg.A);
            cycles(8);
            break;
        case 0x20:
            SLA(u, &u->reg.B);
            cycles(8);
            break;
        case 0x21:
            SLA(u, &u->reg.C);
            cycles(8);
            break;
        case 0x22:
            SLA(u, &u->reg.D);
            cycles(8);
            break;
        case 0x23:
            SLA(u, &u->reg.E);
            cycles(8);
            break;
        case 0x24:
            SLA(u, &u->reg.H);
            cycles(8);
            break;
        case 0x25:
            SLA(u, &u->reg.L);
            cycles(8);
            break;
        case 0x26:
            SLA(u, m_ptr8(u, u->reg.HL));
            cycles(16);
            break;

        case 0x2F: /* SRA */
            SRA(u, &u->reg.A);
            cycles(8);
            break;
        case 0x28:
            SRA(u, &u->reg.B);
            cycles(8);
            break;
        case 0x29:
            SRA(u, &u->reg.C);
            cycles(8);
            break;
        case 0x2A:
            SRA(u, &u->reg.D);
            cycles(8);
            break;
        case 0x2B:
            SRA(u, &u->reg.E);
            cycles(8);
            break;
        case 0x2C:
            SRA(u, &u->reg.H);
            cycles(8);
            break;
        case 0x2D:
            SRA(u, &u->reg.L);
            cycles(8);
            break;
        case 0x2E:
            SRA(u, m_ptr8(u, u->reg.HL));
            cycles(16);
            break;

        case 0x37: /* SWAP */
            SWAP_8(&u->reg.A);
            cycles(8);
            break;
        case 0x30:
            SWAP_8(&u->reg.B);
            cycles(8);
            break;
        case 0x31:
            SWAP_8(&u->reg.C);
            cycles(8);
            break;
        case 0x32:
            SWAP_8(&u->reg.D);
            cycles(8);
            break;
        case 0x33:
            SWAP_8(&u->reg.E);
            cycles(8);
            break;
        case 0x34:
            SWAP_8(&u->reg.H);
            cycles(8);
            break;
        case 0x35:
            SWAP_8(&u->reg.L);
            cycles(8);
            break;
        case 0x36:
            SWAP_8(m_ptr8(u, u->reg.HL));
            cycles(16);
            break;

        case 0x3F: /* SRL */
            SRL(u, &u->reg.A);
            cycles(8);
            break;
        case 0x38:
            SRL(u, &u->reg.B);
            cycles(8);
            break;
        case 0x39:
            SRL(u, &u->reg.C);
            cycles(8);
            break;
        case 0x3A:
            SRL(u, &u->reg.D);
            cycles(8);
            break;
        case 0x3B:
            SRL(u, &u->reg.E);
            cycles(8);
            break;
        case 0x3C:
            SRL(u, &u->reg.H);
            cycles(8);
            break;
        case 0x3D:
            SRL(u, &u->reg.L);
            cycles(8);
            break;
        case 0x3E:
            SRL(u, m_ptr8(u, u->reg.HL));
            cycles(16);
            break;

        case 0x47: /* BIT */
            BIT(u, u->reg.A, 0x1);
            cycles(8);
            break;
        case 0x40:
            BIT(u, u->reg.B, 0x1);
            cycles(8);
            break;
        case 0x41:
            BIT(u, u->reg.C, 0x1);
            cycles(8);
            break;
        case 0x42:
            BIT(u, u->reg.D, 0x1);
            cycles(8);
            break;
        case 0x43:
            BIT(u, u->reg.E, 0x1);
            cycles(8);
            break;
        case 0x44:
            BIT(u, u->reg.H, 0x1);
            cycles(8);
            break;
        case 0x45:
            BIT(u, u->reg.L, 0x1);
            cycles(8);
            break;
        case 0x46:
            BIT(u, m_get8(u, u->reg.HL), 0x1);
            cycles(16);
            break;

        case 0x4F:
            BIT(u, u->reg.A, 0x2);
            cycles(8);
            break;
        case 0x48:
            BIT(u, u->reg.B, 0x2);
            cycles(8);
            break;
        case 0x49:
            BIT(u, u->reg.C, 0x2);
            cycles(8);
            break;
        case 0x4A:
            BIT(u, u->reg.D, 0x2);
            cycles(8);
            break;
        case 0x4B:
            BIT(u, u->reg.E, 0x2);
            cycles(8);
            break;
        case 0x4C:
            BIT(u, u->reg.H, 0x2);
            cycles(8);
            break;
        case 0x4D:
            BIT(u, u->reg.L, 0x2);
            cycles(8);
            break;
        case 0x4E:
            BIT(u, m_get8(u, u->reg.HL), 0x2);
            cycles(8);
            break;

        case 0x57:
            BIT(u, u->reg.A, 0x4);
            cycles(8);
            break;
        case 0x50:
            BIT(u, u->reg.B, 0x4);
            cycles(8);
            break;
        case 0x51:
            BIT(u, u->reg.C, 0x4);
            cycles(8);
            break;
        case 0x52:
            BIT(u, u->reg.D, 0x4);
            cycles(8);
            break;
        case 0x53:
            BIT(u, u->reg.E, 0x4);
            cycles(8);
            break;
        case 0x54:
            BIT(u, u->reg.H, 0x4);
            cycles(8);
            break;
        case 0x55:
            BIT(u, u->reg.L, 0x4);
            cycles(8);
            break;
        case 0x56:
            BIT(u, m_get8(u, u->reg.HL), 0x4);
            cycles(8);
            break;

        case 0x5F:
            BIT(u, u->reg.A, 0x8);
            cycles(8);
            break;
        case 0x58:
            BIT(u, u->reg.B, 0x8);
            cycles(8);
            break;
        case 0x59:
            BIT(u, u->reg.C, 0x8);
            cycles(8);
            break;
        case 0x5A:
            BIT(u, u->reg.D, 0x8);
            cycles(8);
            break;
        case 0x5B:
            BIT(u, u->reg.E, 0x8);
            cycles(8);
            break;
        case 0x5C:
            BIT(u, u->reg.H, 0x8);
            cycles(8);
            break;
        case 0x5D:
            BIT(u, u->reg.L, 0x8);
            cycles(8);
            break;
        case 0x5E:
            BIT(u, m_get8(u, u->reg.HL), 0x8);
            cycles(8);
            break;

        case 0x67:
            BIT(u, u->reg.A, 0x10);
            cycles(8);
            break;
        case 0x60:
            BIT(u, u->reg.B, 0x10);
            cycles(8);
            break;
        case 0x61:
            BIT(u, u->reg.C, 0x10);
            cycles(8);
            break;
        case 0x62:
            BIT(u, u->reg.D, 0x10);
            cycles(8);
            break;
        case 0x63:
            BIT(u, u->reg.E, 0x10);
            cycles(8);
            break;
        case 0x64:
            BIT(u, u->reg.H, 0x10);
            cycles(8);
            break;
        case 0x65:
            BIT(u, u->reg.L, 0x10);
            cycles(8);
            break;
        case 0x66:
            BIT(u, m_get8(u, u->reg.HL), 0x10);
            cycles(8);
            break;

        case 0x6F:
            BIT(u, u->reg.A, 0x20);
            cycles(8);
            break;
        case 0x68:
            BIT(u, u->reg.B, 0x20);
            cycles(8);
            break;
        case 0x69:
            BIT(u, u->reg.C, 0x20);
            cycles(8);
            break;
        case 0x6A:
            BIT(u, u->reg.D, 0x20);
            cycles(8);
            break;
        case 0x6B:
            BIT(u, u->reg.E, 0x20);
            cycles(8);
            break;
        case 0x6C:
            BIT(u, u->reg.H, 0x20);
            cycles(8);
            break;
        case 0x6D:
            BIT(u, u->reg.L, 0x20);
            cycles(8);
            break;
        case 0x6E:
            BIT(u, m_get8(u, u->reg.HL), 0x20);
            cycles(8);
            break;

        case 0x77:
            BIT(u, u->reg.A, 0x40);
            cycles(8);
            break;
        case 0x70:
            BIT(u, u->reg.B, 0x40);
            cycles(8);
            break;
        case 0x71:
            BIT(u, u->reg.C, 0x40);
            cycles(8);
            break;
        case 0x72:
            BIT(u, u->reg.D, 0x40);
            cycles(8);
            break;
        case 0x73:
            BIT(u, u->reg.D, 0x40);
            cycles(8);
            break;
        case 0x74:
            BIT(u, u->reg.H, 0x40);
            cycles(8);
            break;
        case 0x75:
            BIT(u, u->reg.L, 0x40);
            cycles(8);
            break;
        case 0x76:
            BIT(u, m_get8(u, u->reg.HL), 0x40);
            cycles(8);
            break;

        case 0x7F:
            BIT(u, u->reg.A, 0x80);
            cycles(8);
            break;
        case 0x78:
            BIT(u, u->reg.B, 0x80);
            cycles(8);
            break;
        case 0x79:
            BIT(u, u->reg.C, 0x80);
            cycles(8);
            break;
        case 0x7A:
            BIT(u, u->reg.D, 0x80);
            cycles(8);
            break;
        case 0x7B:
            BIT(u, u->reg.E, 0x80);
            cycles(8);
            break;
        case 0x7C:
            BIT(u, u->reg.H, 0x80);
            cycles(8);
            break;
        case 0x7D:
            BIT(u, u->reg.L, 0x80);
            cycles(8);
            break;
        case 0x7E:
            BIT(u, m_get8(u, u->reg.HL), 0x80);
            cycles(8);
            break;

        case 0x87: /* RES */
            u->reg.A &= ~0x1;
            cycles(8);
            break;
        case 0x80:
            u->reg.B &= ~0x1;
            cycles(8);
            break;
        case 0x81:
            u->reg.C &= ~0x1;
            cycles(8);
            break;
        case 0x82:
            u->reg.D &= ~0x1;
            cycles(8);
            break;
        case 0x83:
            u->reg.E &= ~0x1;
            cycles(8);
            break;
        case 0x84:
            u->reg.H &= ~0x1;
            cycles(8);
            break;
        case 0x85:
            u->reg.L &= ~0x1;
            cycles(8);
            break;
        case 0x86:
            u->mem.content[u->reg.HL] &= ~0x1;
            cycles(16);
            break;

        case 0x8F:
            u->reg.A &= ~0x2;
            cycles(8);
            break;
        case 0x88:
            u->reg.B &= ~0x2;
            cycles(8);
            break;
        case 0x89:
            u->reg.C &= ~0x2;
            cycles(8);
            break;
        case 0x8A:
            u->reg.D &= ~0x2;
            cycles(8);
            break;
        case 0x8B:
            u->reg.E &= ~0x2;
            cycles(8);
            break;
        case 0x8C:
            u->reg.H &= ~0x2;
            cycles(8);
            break;
        case 0x8D:
            u->reg.L &= ~0x2;
            cycles(8);
            break;
        case 0x8E:
            u->mem.content[u->reg.HL] &= ~0x2;
            cycles(16);
            break;

        case 0x97:
            u->reg.A &= ~0x4;
            cycles(8);
            break;
        case 0x90:
            u->reg.B &= ~0x4;
            cycles(8);
            break;
        case 0x91:
            u->reg.C &= ~0x4;
            cycles(8);
            break;
        case 0x92:
            u->reg.D &= ~0x4;
            cycles(8);
            break;
        case 0x93:
            u->reg.E &= ~0x4;
            cycles(8);
            break;
        case 0x94:
            u->reg.H &= ~0x4;
            cycles(8);
            break;
        case 0x95:
            u->reg.L &= ~0x4;
            cycles(8);
            break;
        case 0x96:
            u->mem.content[u->reg.HL] &= ~0x4;
            cycles(16);
            break;

        case 0x9F:
            u->reg.A &= ~0x8;
            cycles(8);
            break;
        case 0x98:
            u->reg.B &= ~0x8;
            cycles(8);
            break;
        case 0x99:
            u->reg.C &= ~0x8;
            cycles(8);
            break;
        case 0x9A:
            u->reg.D &= ~0x8;
            cycles(8);
            break;
        case 0x9B:
            u->reg.E &= ~0x8;
            cycles(8);
            break;
        case 0x9C:
            u->reg.H &= ~0x8;
            cycles(8);
            break;
        case 0x9D:
            u->reg.L &= ~0x8;
            cycles(8);
            break;
        case 0x9E:
            u->mem.content[u->reg.HL] &= ~0x8;
            cycles(16);
            break;

        case 0xA7:
            u->reg.A &= ~0x10;
            cycles(8);
            break;
        case 0xA0:
            u->reg.B &= ~0x10;
            cycles(8);
            break;
        case 0xA1:
            u->reg.C &= ~0x10;
            cycles(8);
            break;
        case 0xA2:
            u->reg.D &= ~0x10;
            cycles(8);
            break;
        case 0xA3:
            u->reg.E &= ~0x10;
            cycles(8);
            break;
        case 0xA4:
            u->reg.H &= ~0x10;
            cycles(8);
            break;
        case 0xA5:
            u->reg.L &= ~0x10;
            cycles(8);
            break;
        case 0xA6:
            u->mem.content[u->reg.HL] &= ~0x10;
            cycles(16);
            break;

        case 0xAF:
            u->reg.A &= ~0x20;
            cycles(8);
            break;
        case 0xA8:
            u->reg.B &= ~0x20;
            cycles(8);
            break;
        case 0xA9:
            u->reg.C &= ~0x20;
            cycles(8);
            break;
        case 0xAA:
            u->reg.D &= ~0x20;
            cycles(8);
            break;
        case 0xAB:
            u->reg.E &= ~0x20;
            cycles(8);
            break;
        case 0xAC:
            u->reg.H &= ~0x20;
            cycles(8);
            break;
        case 0xAD:
            u->reg.L &= ~0x20;
            cycles(8);
            break;
        case 0xAE:
            u->mem.content[u->reg.HL] &= ~0x20;
            cycles(16);
            break;

        case 0xB7:
            u->reg.A &= ~0x40;
            cycles(8);
            break;
        case 0xB0:
            u->reg.B &= ~0x40;
            cycles(8);
            break;
        case 0xB1:
            u->reg.C &= ~0x40;
            cycles(8);
            break;
        case 0xB2:
            u->reg.D &= ~0x40;
            cycles(8);
            break;
        case 0xB3:
            u->reg.E &= ~0x40;
            cycles(8);
            break;
        case 0xB4:
            u->reg.H &= ~0x40;
            cycles(8);
            break;
        case 0xB5:
            u->reg.L &= ~0x40;
            cycles(8);
            break;
        case 0xB6:
            u->mem.content[u->reg.HL] &= ~0x40;
            cycles(16);
            break;

        case 0xBF:
            u->reg.A &= ~0x80;
            cycles(8);
            break;
        case 0xB8:
            u->reg.B &= ~0x80;
            cycles(8);
            break;
        case 0xB9:
            u->reg.C &= ~0x80;
            cycles(8);
            break;
        case 0xBA:
            u->reg.D &= ~0x80;
            cycles(8);
            break;
        case 0xBB:
            u->reg.E &= ~0x80;
            cycles(8);
            break;
        case 0xBC:
            u->reg.H &= ~0x80;
            cycles(8);
            break;
        case 0xBD:
            u->reg.L &= ~0x80;
            cycles(8);
            break;
        case 0xBE:
            u->mem.content[u->reg.HL] &= ~0x80;
            cycles(16);
            break;

        case 0xC7: /* SET */
            u->reg.A |= 0x1;
            cycles(8);
            break;
        case 0xC0:
            u->reg.B |= 0x1;
            cycles(8);
            break;
        case 0xC1:
            u->reg.C |= 0x1;
            cycles(8);
            break;
        case 0xC2:
            u->reg.D |= 0x1;
            cycles(8);
            break;
        case 0xC3:
            u->reg.E |= 0x1;
            cycles(8);
            break;
        case 0xC4:
            u->reg.H |= 0x1;
            cycles(8);
            break;
        case 0xC5:
            u->reg.L |= 0x1;
            cycles(8);
            break;
        case 0xC6:
            u->mem.content[u->reg.HL] |= 0x1;
            cycles(16);
            break;

        case 0xCF:
            u->reg.A |= 0x2;
            cycles(8);
            break;
        case 0xC8:
            u->reg.B |= 0x2;
            cycles(8);
            break;
        case 0xC9:
            u->reg.C |= 0x2;
            cycles(8);
            break;
        case 0xCA:
            u->reg.D |= 0x2;
            cycles(8);
            break;
        case 0xCB:
            u->reg.E |= 0x2;
            cycles(8);
            break;
        case 0xCC:
            u->reg.H |= 0x2;
            cycles(8);
            break;
        case 0xCD:
            u->reg.L |= 0x2;
            cycles(8);
            break;
        case 0xCE:
            u->mem.content[u->reg.HL] |= 0x2;
            cycles(16);
            break;

        case 0xD7:
            u->reg.A |= 0x4;
            cycles(8);
            break;
        case 0xD0:
            u->reg.B |= 0x4;
            cycles(8);
            break;
        case 0xD1:
            u->reg.C |= 0x4;
            cycles(8);
            break;
        case 0xD2:
            u->reg.D |= 0x4;
            cycles(8);
            break;
        case 0xD3:
            u->reg.E |= 0x4;
            cycles(8);
            break;
        case 0xD4:
            u->reg.H |= 0x4;
            cycles(8);
            break;
        case 0xD5:
            u->reg.L |= 0x4;
            cycles(8);
            break;
        case 0xD6:
            u->mem.content[u->reg.HL] |= 0x4;
            cycles(16);
            break;

        case 0xDF:
            u->reg.A |= 0x8;
            cycles(8);
            break;
        case 0xD8:
            u->reg.B |= 0x8;
            cycles(8);
            break;
        case 0xD9:
            u->reg.C |= 0x8;
            cycles(8);
            break;
        case 0xDA:
            u->reg.D |= 0x8;
            cycles(8);
            break;
        case 0xDB:
            u->reg.E |= 0x8;
            cycles(8);
            break;
        case 0xDC:
            u->reg.H |= 0x8;
            cycles(8);
            break;
        case 0xDD:
            u->reg.L |= 0x8;
            cycles(8);
            break;
        case 0xDE:
            u->mem.content[u->reg.HL] |= 0x8;
            cycles(16);
            break;

        case 0xE7:
            u->reg.A |= 0x10;
            cycles(8);
            break;
        case 0xE0:
            u->reg.B |= 0x10;
            cycles(8);
            break;
        case 0xE1:
            u->reg.C |= 0x10;
            cycles(8);
            break;
        case 0xE2:
            u->reg.D |= 0x10;
            cycles(8);
            break;
        case 0xE3:
            u->reg.E |= 0x10;
            cycles(8);
            break;
        case 0xE4:
            u->reg.H |= 0x10;
            cycles(8);
            break;
        case 0xE5:
            u->reg.L |= 0x10;
            cycles(8);
            break;
        case 0xE6:
            u->mem.content[u->reg.HL] |= 0x10;
            cycles(16);
            break;

        case 0xEF:
            u->reg.A |= 0x20;
            cycles(8);
            break;
        case 0xE8:
            u->reg.B |= 0x20;
            cycles(8);
            break;
        case 0xE9:
            u->reg.C |= 0x20;
            cycles(8);
            break;
        case 0xEA:
            u->reg.D |= 0x20;
            cycles(8);
            break;
        case 0xEB:
            u->reg.E |= 0x20;
            cycles(8);
            break;
        case 0xEC:
            u->reg.H |= 0x20;
            cycles(8);
            break;
        case 0xED:
            u->reg.L |= 0x20;
            cycles(8);
            break;
        case 0xEE:
            u->mem.content[u->reg.HL] |= 0x20;
            cycles(16);
            break;

        case 0xF7:
            u->reg.A |= 0x40;
            cycles(8);
            break;
        case 0xF0:
            u->reg.B |= 0x40;
            cycles(8);
            break;
        case 0xF1:
            u->reg.C |= 0x40;
            cycles(8);
            break;
        case 0xF2:
            u->reg.D |= 0x40;
            cycles(8);
            break;
        case 0xF3:
            u->reg.E |= 0x40;
            cycles(8);
            break;
        case 0xF4:
            u->reg.H |= 0x40;
            cycles(8);
            break;
        case 0xF5:
            u->reg.L |= 0x40;
            cycles(8);
            break;
        case 0xF6:
            u->mem.content[u->reg.HL] |= 0x40;
            cycles(16);
            break;

        case 0xFF:
            u->reg.A |= 0x80;
            cycles(8);
            break;
        case 0xF8:
            u->reg.B |= 0x80;
            cycles(8);
            break;
        case 0xF9:
            u->reg.C |= 0x80;
            cycles(8);
            break;
        case 0xFA:
            u->reg.D |= 0x80;
            cycles(8);
            break;
        case 0xFB:
            u->reg.E |= 0x80;
            cycles(8);
            break;
        case 0xFC:
            u->reg.H |= 0x80;
            cycles(8);
            break;
        case 0xFD:
            u->reg.L |= 0x80;
            cycles(8);
            break;
        case 0xFE:
            u->mem.content[u->reg.HL] |= 0x80;
            cycles(16);
            break;
        }
        break;
    }

    case 0xC3: /* JP nn */
        u->mem.ptr = m_peek16(u);
        cycles(12);
        break;

    case 0xC2: /* JP cc,nn */
    {
        uint16_t next16 = m_read16(u);
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }
    case 0xCA:
    {
        uint16_t next16 = m_read16(u);
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }
    case 0xD2:
    {
        uint16_t next16 = m_read16(u);
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }
    case 0xDA:
    {
        uint16_t next16 = m_read16(u);
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }

    case 0xE9: /* JP (HL) */
        u->mem.ptr = m_get8(u, u->reg.HL);
        cycles(4);
        break;

    case 0x18: /* JR n */
        u->mem.ptr += cast_signed8(m_read8(u));
        cycles(8);
        break;

    case 0x20: /* JR cc,n */
    {
        uint16_t next8 = cast_signed8(m_read8(u));
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr += next8;
        }
        cycles(8);
        break;
    }
    case 0x28: /* JR Z,d8 */
    {
        uint16_t next8 = cast_signed8(m_read8(u));
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr += next8;
        }
        cycles(8);
        break;
    }
    case 0x30: /* JR NZ (C),a8 */
    {
        uint16_t next8 = cast_signed8(m_read8(u));
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr += next8;
        }
        cycles(8);
        break;
    }

    case 0x38: /* JR C,d8 */
    {
        uint16_t next8 = cast_signed8(m_read8(u));
        if (u->reg.F & C_FLAG)
        {
            u->mem.ptr += next8;
        }
        cycles(8);
        break;
    }

    case 0xCD: /* CALL nn */
        s_push16(u, u->mem.ptr + 1);
        u->mem.ptr = m_peek16(u);
        cycles(12);
        break;

    case 0xC4: /* CALL nn, nn */
    {
        uint16_t next16 = m_read16(u);
        if (!(u->reg.F & Z_FLAG))
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }
    case 0xCC: /* CALL Z,a16 */
    {
        uint16_t next16 = m_read16(u);
        if (u->reg.F & Z_FLAG)
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }
    case 0xD4: /* CALL NC,a16 */
    {
        uint16_t next16 = m_read16(u);
        if (!(u->reg.F & C_FLAG))
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }
    case 0xDC: /* CALL C,a16 */
    {
        uint16_t next16 = m_read16(u);
        if (u->reg.F & C_FLAG)
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = next16;
        }
        cycles(12);
        break;
    }

    case 0xC7: /* RST n */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x00;
        cycles(32);
        break;
    case 0xCF:
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x08;
        cycles(32);
        break;
    case 0xD7:
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x10;
        cycles(32);
        break;
    case 0xDF:
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x18;
        cycles(32);
        break;
    case 0xE7:
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x20;
        cycles(32);
        break;
    case 0xEF:
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x28;
        cycles(32);
        break;
    case 0xF7:
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x30;
        cycles(32);
        break;
    case 0xFF:
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x38;
        cycles(32);
        break;

    case 0xC9: /* RET */
        u->mem.ptr = s_pop16(u);
        cycles(8);
        break;

    case 0xC0: /* RET cc */
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr = s_pop16(u);
        }
        cycles(8);
        break;
    case 0xC8:
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = s_pop16(u);
        }
        cycles(8);
        break;
    case 0xD0:
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr = s_pop16(u);
        }
        cycles(8);
        break;
    case 0xD8:
        if (u->reg.F & C_FLAG)
        {
            u->mem.ptr = s_pop16(u);
        }
        cycles(8);
        break;

    case 0xD9: /* RETI */
        u->mem.ptr = s_pop16(u);
        u->interrupts = 1;
        cycles(8);
        break;

    default:
        fprintf(stderr, "Found unknown instrucition $%02x\n", op);
        exit(1);
    }

    return 0;
}
/********************************************************************/
/* $FF0F IF Interrupt Flag                                          */
/*                                                                  */
/*         Bit 4: Transition from High to Low of Pin number P10-P13 */
/*         Bit 3: Serial I/O transfer complete                      */
/*         Bit 2: Timer Overflow                                    */
/*         Bit 1: LCDC (see STAT)                                   */
/*         Bit 0: V-Blank                                           */
/*                                                                  */
/* Interrupt        Priority     Start Address                      */
/* V-Blank             1         $0040                              */
/* LCDC Status         2         $0048                              */
/* Timer Overflow      3         $0050                              */
/* Serial Transfer     4         $0058                              */
/* Hi-Lo of P10-P13    5         $0060                              */
/********************************************************************/
#define IF 0xFF0F
/*********************************************************************/
/* $FFFF IE - Interrupt Enable                                       */
/*                                                                   */
/*         Bit 4: Transition from High to Low of Pin number P10-P13. */
/*         Bit 3: Serial I/O transfer complete                       */
/*         Bit 2: Timer Overflow                                     */
/*         Bit 1: LCDC (see STAT)                                    */
/*         Bit 0: V-Blank 0: disable 1: enable                       */
/*********************************************************************/
#define IE 0xFFFF

static void request_interupt(CPU *u, int kind)
{
    uint8_t set_interrupt = m_get8(u, IF) | (1 << kind);
    m_set8(u, IF, set_interrupt);
}

static void handle_interupt(CPU *u, int kind)
{
    u->interrupts = 0;
    uint8_t reset_interrupt = m_get8(u, IF) & ~(1 << kind);
    m_set8(u, IF, reset_interrupt);

    s_push16(u, u->mem.ptr);

    switch (kind)
    {
    case 0:
        u->mem.ptr = 0x40;
        break;
        u->mem.ptr = 0x48;
        break;
        u->mem.ptr = 0x50;
        break;
        u->mem.ptr = 0x60;
        break;
    }
}

void execute_interupts(CPU *u)
{
    if (u->interrupts)
    {
        uint8_t interrupt_flag = m_get8(u, IF);
        uint8_t interrupt_enabled = m_get8(u, IE);

        if (interrupt_flag)
        {
            for (uint8_t i = 0; i < 5; i++)
            {
                if ((interrupt_flag & interrupt_enabled) & (1 << i))
                {
                    handle_interupt(u, i);
                }
            }
        }
    }
}
/*********************************************************/
/* $FF40  LCDC  (value $91 at reset) - LCD Control (R/W) */
/*                                                       */
/*         Bit 7 - LCD Control Operation                 */
/*             0: Stop completely (no picture on screen) */
/*             1: operation                              */
/*         Bit 6 - Window Tile Map Display Select        */
/*             0: $9800-$9BFF                            */
/*             1: $9C00-$9FFF                            */
/*         Bit 5 - Window Display                        */
/*             0: off                                    */
/*             1: on                                     */
/*         Bit 4 - BG & Window Tile Data Select          */
/*             0: $8800-$97FF                            */
/*             1: $8000-$8FFF <- Same area as OBJ        */
/*         Bit 3 - BG Tile Map Display Select            */
/*             0: $9800-$9BFF                            */
/*             1: $9C00-$9FFF                            */
/*         Bit 2 - OBJ (Sprite) Size                     */
/*             0: 8*8                                    */
/*             1: 8*16 (width*height)                    */
/*         Bit 1 - OBJ (Sprite) Display                  */
/*             0: off                                    */
/*             1: on                                     */
/*         Bit 0 - BG & Window Display                   */
/*             0: off                                    */
/*             1: on                                     */
/*********************************************************/
#define LCDC 0xFF40

static uint8_t check_lcd(CPU *u)
{
    return m_get8(u, LCDC) & 0x80;
}

/**************************************************************************/
/* $FF41  STAT - LCDC Status                                              */
/*         Bits 6-3 - Interrupt Selection                                 */
/*             Bit 6 - LYC=LY Coincidence (Selectable)                    */
/*             Bit 5 - Mode 10                                            */
/*             Bit 4 - Mode 01                                            */
/*             Bit 3 - Mode 00                                            */
/*                 0: Non Selection                                       */
/*                 1: Selection                                           */
/*         Bit 2 - Coincidence Flag                                       */
/*             0: LYC not equal to LCDC LY                                */
/*             1: LYC = LCDC LY                                           */
/*         Bit 1-0 - Mode Flag                                            */
/*             00: During H-Blank                                         */
/*             01: During V-Blank                                         */
/*             10: During Searching OAM-RAM                               */
/*             11: During Transfering Data to LCD Driver                  */
/*                                                                        */
/*         It takes a total of 456 CPU cycles to write one scanline       */
/*         from which:                                                    */
/*                 80 CPU cycles during `Searching OAM-RAM`               */
/*                 172 CPU cycles during `Transfering Data to LCD Driver` */
/*                 204 CPU cycles during `H-Blank`                        */
/**************************************************************************/
#define STAT 0xFF41

/**********************************************************************************/
/* $FF44 LY - LCDC Y-Coordinate */
/*                                                                                */
/* The LY indicates the vertical line to which the present data is transferred
 * to */
/* the LCD Driver. The LY can take on any value between 0 through 153. The
 * values */
/* between 144 and 153 indicate the V-Blank period. Writing will reset the */
/* counter. It takes 456 CPU clock cycles to draw on scanline and move to the */
/* next. */
/**********************************************************************************/
#define LY 0xFF44
int scanline_counter = 456;

/*******************************************************************/
/* $FF45 (LYC) LYC - LY Compare                                    */
/*                                                                 */
/* The LYC compares itself with the LY. If the values are the same */
/* it causes the STAT to set the coincident flag.                  */
/*******************************************************************/
#define LYC 0xFF45

static void set_lcd_status(CPU *u)
{
    uint8_t *status = m_ptr8(u, STAT);
    if (check_lcd(u) == 0)
    {
        scanline_counter = 456; /* Reset scanline */
        u->mem.content[LY] = 0;
        *status =
            ((*status) & 0xfc) | 0x1; /* set bits 0-1 to 01, i.e V-Blank */
        return;
    }

    uint8_t line = m_get8(u, LY);
    uint8_t mode = m_get8(u, STAT) & 0x3;

    uint8_t new_mode = 0;
    uint8_t check_new_mode = 0;

    if (line >= 144 && line <= 153) /* V-blank, see pg. 55 item 36 */
    {
        new_mode = 0x01;
        *status = ((*status) & 0xfc) | 0x1; /* set bit 0-1 to 01 */
        check_new_mode = (*status) & 0x10;  /* check bit 4 */
    }
    else
    {
        /* Here we need to check where in cycle we are: */
        /* LY = 456-375 --- Mode 2 - `Searching OAM-RAM` */
        /*      374-202 --- Mode 3 - `Transfering Data to LCD Driver` */
        /*      201-0   --- Mode 1 -  `H-Blank` */

        if (scanline_counter >= 375 && scanline_counter <= 456)
        {
            new_mode = 0x10;
            *status = ((*status) & 0xfc) | 0x2; /* set bit 0-1 to 10 */
            check_new_mode = (*status) & 0x20;  /* check bit 5 */
        }

        if (scanline_counter >= 202 && scanline_counter <= 374)
        {
            new_mode = 0x11;
            *status |= 0x3; /* set bit 0-1 to 11 */
        }

        if (scanline_counter >= 0 && scanline_counter <= 201)
        {
            new_mode = 0x00;
            *status &= ~0x3;                  /* set bit 0-1 to 00 */
            check_new_mode = (*status) & 0x8; /* check bit 3 */
        }
    }

    if (check_new_mode && (new_mode != mode))
    {
        request_interupt(u, 1);
    }

    if (line == m_get8(u, LYC)) /* see pg 55 item 36 */
    {
        *status |= 0x4; /* set bit 2 */
        if (*status & 0x40)
        {
            request_interupt(u, 2);
        }
    }
    else
    {
        *status &= ~0x4; /* reset bit 2 */
    }
}

void update_graphics(CPU *u, int cycles)
{
    set_lcd_status(u);

    if (check_lcd(u))
    {
        scanline_counter -= cycles;
    }
    else
    {
        return;
    }

    if (scanline_counter <= 0)
    {
        u->mem.content[LY]++;
        uint8_t line = m_get8(u, LY);

        scanline_counter = 456;

        if (line == 144)
        {
            request_interupt(u, 0);
        }
        else if (line > 153)
        {
            u->mem.content[LY] = 0;
        }
        else if (line < 144)
        {
            /* draw_line(); */ /* XXX SDL */
        }
    }
}

/***************************************************************/
/* $FF04 Name - DIV                                            */
/*                                                             */
/* This register is incremented 16384(~16779 on SGB)times a    */
/* second. Writing any value sets it to $00.  Here we are also */
/* maintaining a counter `div_counter` for this task. At each  */
/* iteration we increase this counter by the number of cycles  */
/* ran. When this counter overflows we increment the div       */
/* register. This way, we have approximately 60 fps.           */
/***************************************************************/
#define DIV 0xFF04
int div_counter = 0;

static void update_div_register(CPU *u, int cycles)
{
    div_counter += cycles;
    if (div_counter >= 0xff /*CLOCK_SPEED/16382*/) /* overflows */
    {
        div_counter = 0;
        u->mem.content[DIV]++;
    }
}

/*********************************************************************/
/* $FF07 - TAC                                                       */
/*                                                                   */
/* This register specifies at what frequency the CPU is running and  */
/* also if the timer is enabled or not. This information is enconded */
/* in a three bit register. Where                                    */
/*                                                                   */
/* bit 0+1:                                                          */
/*         00: 4096 Hz                                               */
/*         01: 262144 hz                                             */
/*         10: 65536 Hz                                              */
/*         11: 16384 Hz                                              */
/* bit 2:                                                            */
/*         0: Stop Timer                                             */
/*         1: Start Timer                                            */
/*********************************************************************/
#define TAC 0xFF07
static uint8_t check_frequency(CPU *u)
{
    return m_get8(u, TAC) & 0x3;
}

static uint16_t get_freq(CPU *u)
{
    uint8_t byte = check_frequency(u);
    switch (byte)
    {
    case 0x00: /* (CLOCK_SPEED / FREQ) */
        return 0x400;
    case 0x01:
        return 0x10;
    case 0x10:
        return 0x40;
    case 0x11:
        return 0x100;
    default:
        fprintf(stderr, "Unknown frequency, aborting.\n");
        exit(1);
    }
}

static uint8_t check_timer(CPU *u)
{
    return m_get8(u, TAC) & 0x4;
}

/*******************************************************************/
/* $FF05 TIMA - Timer counter                                      */
/*                                                                 */
/* This timer is incremented by a clock frequency specified by the */
/* TAC register ($FF07). The timer generates an interrupt when it  */
/* overflows.                                                      */
/*******************************************************************/
#define TIMA 0xFF05

/******************************************************/
/* $FF06 TMA - Timer Modulo                           */
/*                                                    */
/* When the TIMA overflows, this data will be loaded. */
/******************************************************/
#define TMA 0xFF06
int timer_counter = (int)(CLOCK_SPEED / DEFAULT_FREQ);

static void update_timer_counter(CPU *u, int cycles)
{
    timer_counter -= cycles;

    if (timer_counter <= 0)
    {
        timer_counter = get_freq(u);

        if (m_get8(u, TIMA) == 0xff) /* overflows */
        {
            m_set8(u, TIMA, m_get8(u, TMA));
            request_interupt(u, 2);
        }
        else
        {
            m_set8(u, TIMA, m_get8(u, TIMA) + 1);
        }
    }
}

void update_timers(CPU *u, int cycles)
{
    update_div_register(u, cycles);
    if (check_timer(u))
    {
        update_timer_counter(u, cycles);
    }
}

static void update(CPU *u)
{
    const int initial_cycles = u->cycles;
    int delta_cycles = 0;

    while (delta_cycles < MAX_CYCLES_PER_SECOND)
    {
        execute_opcode(u, m_read8(u));
        delta_cycles = u->cycles - initial_cycles;

        update_timers(u, delta_cycles);
        update_graphics(u, delta_cycles);
        execute_interupts(u);
    }
}

int emulate_rom(CPU *u)
{
    if (u->info.cartridge_type !=
        0) /* TODO(keyenzy): Implement multiple ROM Banks */
    {
        puts("Multiple ROM banks not implemented yet.");
        exit(1);
    }

    while (1)
    {
        update(u);
    }

    return 0;
}
