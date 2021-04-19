#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>
#include <gameboy/emulator.h>

#define cast_signed8(x) (int)((int8_t)(x))
#define cycle(x) u->cycle += (x)

static void ADD_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst + src);
    /* http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html */
    /* https://stackoverflow.com/questions/8868396/game-boy-what-constitutes-a-half-carry
     */
    uint16_t wrap = (uint16_t)((*dst & 0xF) + (src & 0xF));
    *dst = (uint8_t)res;
    cycle(4);

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
    cycle(8);

    u->reg.FN = 0;
    if (wrap > 0x0FF)
        u->reg.F |= H_FLAG;
    if (res > 0xFFFF)
        u->reg.F |= C_FLAG;
}

static void ADC_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst + src + (u->reg.F & C_FLAG));
    uint16_t wrap =
        (uint16_t)((*dst & 0xF) + ((src + (u->reg.F & C_FLAG)) & 0xF));
    *dst = (uint8_t)res;
    cycle(4);

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
    cycle(4);

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
    cycle(4);

    u->reg.FZ = res == 0;

    u->reg.FN = 0;
    u->reg.FH = wrap > 0xF;
    u->reg.FC = res > 0xFF;
}

static void AND_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst & src);
    *dst = (uint8_t)res;
    cycle(4);

    u->reg.FZ = res == 0;

    u->reg.FN = 0;
    u->reg.FH = 1;
    u->reg.FC = 0;
}

static void XOR_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst ^ src);
    *dst = (uint8_t)res;
    cycle(4);

    u->reg.FZ = res == 0;

    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = 0;
}

static void OR_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst | src);
    *dst = (uint8_t)res;
    cycle(4);

    u->reg.FZ = res == 0;

    u->reg.FN = 0;
    u->reg.FH = 0;
    u->reg.FC = 0;
}

static void CP_8(CPU *u, uint8_t *dst, uint8_t src)
{
    uint16_t res = (uint16_t)(*dst - src);
    uint16_t wrap = (uint16_t)((*dst & 0xF) - (src & 0xF));
    cycle(4);

    u->reg.FZ = res == 0;

    u->reg.FN = 1;
    u->reg.FH = wrap > 0xF;
    u->reg.FC = res > 0xFF;
}

static void INC_8(CPU *u, uint8_t *dst)
{
    uint8_t res = ++(*dst);
    cycle(4);

    u->reg.FZ = res == 0;

    u->reg.FN = 0;

    if ((res & 0xF) == 0)
    {
        u->reg.F |= H_FLAG;
    }
    else
    {
        u->reg.F &= ~H_FLAG;
    }
}

static void DEC_8(CPU *u, uint8_t *dst)
{
    uint8_t res = --(*dst);
    cycle(4);

    u->reg.FZ = res == 0;

    u->reg.FN = 1;

    if ((res & 0xF) == 0)
    {
        u->reg.F |= H_FLAG;
    }
    else
    {
        u->reg.F &= ~H_FLAG;
    }
}

int execute_opcode(CPU *u, uint8_t op)
{
    if (u->mem.ptr >= 0x8000)
    {
        if (u->debug)
        {
            puts("END OF ROM");
        }
        return 1;
    }

    if (u->debug)
    {
        printf("$%04x\t$%02x\t$%02x "
               "$%02x\t\t$%04x\t$%04x\t$%04x\t$%04x\t$%04x\t%d%d%d%d\n",
               u->mem.ptr - 1, op, m_get8(u, u->mem.ptr),
               m_get8(u, u->mem.ptr + 1), u->reg.AF, u->reg.BC, u->reg.DE,
               u->reg.HL, u->st->ptr, u->reg.FZ, u->reg.FN, u->reg.FH,
               u->reg.FC);
    }

    switch (op) /* The order should be the
                   same as in the GameBoy manual */
    {
        /* LD nn,n */
    case 0x06: /* LD B,d8 */
        u->reg.B = m_read8(u);
        cycle(8);
        break;
    case 0x0E: /* LD C,d8 */
        u->reg.C = m_read8(u);
        cycle(8);
        break;
    case 0x16: /* LD D,d8 */
        u->reg.D = m_read8(u);
        cycle(8);
        break;
    case 0x1E: /* LD E,d8 */
        u->reg.E = m_read8(u);
        cycle(8);
        break;
    case 0x26: /* LD H,d8 */
        u->reg.H = m_read8(u);
        cycle(8);
        break;
    case 0x2E: /* LD L,d8 */
        u->reg.L = m_read8(u);
        cycle(8);
        break;

        /* LD r1,r2 */
    case 0x7F:
        u->reg.A = u->reg.A;
        cycle(4);
        break;
    case 0x78:
        u->reg.A = u->reg.B;
        cycle(4);
        break;
    case 0x79:
        u->reg.A = u->reg.C;
        cycle(4);
        break;
    case 0x7A:
        u->reg.A = u->reg.D;
        cycle(4);
        break;
    case 0x7B:
        u->reg.A = u->reg.E;
        cycle(4);
        break;
    case 0x7C:
        u->reg.A = u->reg.H;
        cycle(4);
        break;
    case 0x7D:
        u->reg.A = u->reg.L;
        cycle(4);
        break;
    case 0x7E:
        u->reg.A = m_get8(u, u->reg.HL);
        cycle(8);
        break;

    case 0x47:
        u->reg.B = u->reg.A;
        cycle(4);
        break;
    case 0x40:
        u->reg.B = u->reg.B;
        cycle(4);
        break;
    case 0x41:
        u->reg.B = u->reg.C;
        cycle(4);
        break;
    case 0x42:
        u->reg.B = u->reg.D;
        cycle(4);
        break;
    case 0x43:
        u->reg.B = u->reg.E;
        cycle(4);
        break;
    case 0x44:
        u->reg.B = u->reg.H;
        cycle(4);
        break;
    case 0x45:
        u->reg.B = u->reg.L;
        cycle(4);
        break;
    case 0x46:
        u->reg.B = m_get8(u, u->reg.HL);
        cycle(8);
        break;

    case 0x4F:
        u->reg.C = u->reg.A;
        cycle(4);
        break;
    case 0x48:
        u->reg.C = u->reg.B;
        cycle(4);
        break;
    case 0x49:
        u->reg.C = u->reg.C;
        cycle(4);
        break;
    case 0x4A:
        u->reg.C = u->reg.D;
        cycle(4);
        break;
    case 0x4B:
        u->reg.C = u->reg.E;
        cycle(4);
        break;
    case 0x4C:
        u->reg.C = u->reg.H;
        cycle(4);
        break;
    case 0x4D:
        u->reg.C = u->reg.L;
        cycle(4);
        break;
    case 0x4E:
        u->reg.C = m_get8(u, u->reg.HL);
        cycle(8);
        break;

    case 0x57:
        u->reg.D = u->reg.A;
        cycle(4);
        break;
    case 0x50:
        u->reg.D = u->reg.B;
        cycle(4);
        break;
    case 0x51:
        u->reg.D = u->reg.C;
        cycle(4);
        break;
    case 0x52:
        u->reg.D = u->reg.D;
        cycle(4);
        break;
    case 0x53:
        u->reg.D = u->reg.E;
        cycle(4);
        break;
    case 0x54:
        u->reg.D = u->reg.H;
        cycle(4);
        break;
    case 0x55:
        u->reg.D = u->reg.L;
        cycle(4);
        break;
    case 0x56:
        u->reg.D = m_get8(u, u->reg.HL);
        cycle(8);
        break;

    case 0x5F:
        u->reg.E = u->reg.A;
        cycle(4);
        break;
    case 0x58:
        u->reg.E = u->reg.B;
        cycle(4);
        break;
    case 0x59:
        u->reg.E = u->reg.C;
        cycle(4);
        break;
    case 0x5A:
        u->reg.E = u->reg.D;
        cycle(4);
        break;
    case 0x5B:
        u->reg.E = u->reg.E;
        cycle(4);
        break;
    case 0x5C:
        u->reg.E = u->reg.H;
        cycle(4);
        break;
    case 0x5D:
        u->reg.E = u->reg.L;
        cycle(4);
        break;
    case 0x5E:
        u->reg.E = m_get8(u, u->reg.HL);
        cycle(8);
        break;

    case 0x67:
        u->reg.H = u->reg.A;
        cycle(4);
        break;
    case 0x60:
        u->reg.H = u->reg.B;
        cycle(4);
        break;
    case 0x61:
        u->reg.H = u->reg.C;
        cycle(4);
        break;
    case 0x62:
        u->reg.H = u->reg.D;
        cycle(4);
        break;
    case 0x63:
        u->reg.H = u->reg.E;
        cycle(4);
        break;
    case 0x64:
        u->reg.H = u->reg.H;
        cycle(4);
        break;
    case 0x65:
        u->reg.H = u->reg.L;
        cycle(4);
        break;
    case 0x66:
        u->reg.H = m_get8(u, u->reg.HL);
        cycle(8);
        break;

    case 0x6F:
        u->reg.L = u->reg.A;
        cycle(4);
        break;
    case 0x68:
        u->reg.L = u->reg.B;
        cycle(4);
        break;
    case 0x69:
        u->reg.L = u->reg.C;
        cycle(4);
        break;
    case 0x6A:
        u->reg.L = u->reg.D;
        cycle(4);
        break;
    case 0x6B:
        u->reg.L = u->reg.E;
        cycle(4);
        break;
    case 0x6C:
        u->reg.L = u->reg.H;
        cycle(4);
        break;
    case 0x6D:
        u->reg.L = u->reg.L;
        cycle(4);
        break;
    case 0x6E:
        u->reg.L = m_get8(u, u->reg.HL);
        cycle(8);
        break;

    case 0x77:
        m_set8(u, u->reg.HL, u->reg.A);
        cycle(8);
        break;
    case 0x70:
        m_set8(u, u->reg.HL, u->reg.B);
        cycle(8);
        break;
    case 0x71:
        m_set8(u, u->reg.HL, u->reg.C);
        cycle(8);
        break;
    case 0x72:
        m_set8(u, u->reg.HL, u->reg.D);
        cycle(8);
        break;
    case 0x73:
        m_set8(u, u->reg.HL, u->reg.E);
        cycle(8);
        break;
    case 0x74:
        m_set8(u, u->reg.HL, u->reg.H);
        cycle(8);
        break;
    case 0x75:
        m_set8(u, u->reg.HL, u->reg.L);
        cycle(8);
        break;

    case 0x36: /* LD (HL),d8 */
        m_set8(u, u->reg.HL, m_read8(u));
        cycle(12);
        break;

        /* LD A,n */
    case 0x0A: /* LD A, (BC) */
        u->reg.A = m_get8(u, u->reg.BC);
        cycle(8);
        break;
    case 0x1A: /* LD A, (DE) */
        u->reg.A = m_get8(u, u->reg.DE);
        cycle(8);
        break;
    case 0xFA: /* LD A,(a16) */
        u->reg.A = m_get8(u, m_read16(u));
        cycle(16);
        break;
    case 0x3E: /* LD A,d8 */
        u->reg.A = m_read8(u);
        cycle(8);
        break;

        /* LD n,A */
    case 0x02: /* LD (BC),A */
        m_set8(u, u->reg.BC, u->reg.A);
        cycle(8);
        break;
    case 0x12: /* LD (DE),A */
        m_set8(u, u->reg.DE, u->reg.A);
        cycle(8);
        break;
    case 0xEA: /* LD (a16),A */
        m_set8(u, m_read16(u), u->reg.A);
        cycle(16);
        break;

        /* LD A,(C) */
    case 0xF2: /* LD A,(C) */
        u->reg.A = m_get8(u, 0xFF00 + u->reg.C);
        cycle(8);
        break;

        /* LD (C),A */
    case 0xE2: /* LD (C), A */
        m_set8(u, 0xFF00 + u->reg.C, u->reg.A);
        cycle(8);
        break;

        /* LDD A,(HL) */
    case 0x3A: /* LD A,(HL-) */
        u->reg.A = m_get8(u, u->reg.HL--);
        cycle(8);
        break;

        /* LDD (HL),A */
    case 0x32: /* LD (HL-),A */
        m_set8(u, u->reg.HL--, u->reg.A);
        cycle(8);
        break;

        /* LDI A,(HL) */
    case 0x2A: /* LD A,(HL+) */
        u->reg.A = m_get8(u, u->reg.HL++);
        cycle(8);
        break;

        /* LDI (HL),A */
    case 0x22: /* LD (HL+),A */
        m_set8(u, u->reg.HL++, u->reg.A);
        cycle(8);
        break;

        /* LDH (n),A */
    case 0xE0: /* LDH (a8),A */ /* SIGN XXX */
        m_set8(u, 0xFF00 + m_read8(u), u->reg.A);
        cycle(12);
        break;

        /* LDH A,(n) */
    case 0xF0: /* LDH A,(a8) */ /* SIGN XXX */
        u->reg.A = m_get8(u, 0xFF00 + m_read8(u));
        cycle(12);
        break;

        /* LD n,nn */
    case 0x01: /* LD BC,d16 */
        u->reg.BC = m_read16(u);
        cycle(12);
        break;
    case 0x11: /* LD DE,d16 */
        u->reg.DE = m_read16(u);
        cycle(12);
        break;
    case 0x21: /* LD HL,d16 */
        u->reg.HL = m_read16(u);
        cycle(12);
        break;
    case 0x31: /* LD SP,d16 */
        u->reg.SP = m_read16(u);
        cycle(12);
        break;

        /* LD SP,HL */
    case 0xF9: /* LD SP,HL */
        u->reg.SP = u->reg.HL;
        cycle(8);
        break;

        /* LDHL SP,n */
    case 0xF8: /* LD HL,SP+r8 */
        u->reg.HL = u->reg.SP + cast_signed8(m_read8(u));
        cycle(12);

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = 1;
        u->reg.FN = 0;
        u->reg.FH = 1; /* XXX */
        u->reg.FC = 1; /* XXX */
        break;

        /* LD (nn),SP */
    case 0x08: /* LD (a16),SP */
        m_set8(u, m_read16(u), u->reg.SP);
        cycle(20);
        /* TODO(keyehzy): We need to roll our own */
        break;

        /* PUSH nn */
    case 0xF5: /* PUSH AF */
        s_push16(u, u->reg.AF);
        cycle(16);
        break;
    case 0xC5: /* PUSH BC */
        s_push16(u, u->reg.BC);
        cycle(16);
        break;
    case 0xD5: /* PUSH DE */
        s_push16(u, u->reg.DE);
        cycle(16);
        break;
    case 0xE5: /* PUSH HL */
        s_push16(u, u->reg.HL);
        cycle(16);
        break;

        /* POP nn */
    case 0xF1: /* POP AF */
        u->reg.AF = s_pop16(u);
        cycle(12);
        break;
    case 0xC1: /* POP BC */
        u->reg.BC = s_pop16(u);
        cycle(12);
        break;
    case 0xD1: /* POP DE */
        u->reg.DE = s_pop16(u);
        cycle(12);
        break;
    case 0xE1: /* POP HL */
        u->reg.HL = s_pop16(u);
        cycle(12);
        break;

        /* ADD A,n */
    case 0x87:
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
        cycle(4);
        break;
    case 0xC6:
        ADD_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

        /* ADC A,n */
    case 0x8F:
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
        cycle(4);
        break;
    case 0xCE: /* ADC A,d8 */
        ADC_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

    /* SUB n */
    case 0x97:
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
        cycle(4);
        break;
    case 0xD6:
        SUB_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

        /* SBC */
    case 0x9F:
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
        cycle(4);
        break;
    case 0xDE:
        SBC_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

    /* AND n */
    case 0xA7:
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
        cycle(4);
        break;
    case 0xE6: /* AND A,d8 */
        AND_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

        /* OR n */
    case 0xB7:
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
        cycle(4);
        break;
    case 0xF6: /* OR,d8 */
        OR_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

        /* XOR n */
    case 0xAF:
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
        cycle(4);
        break;
    case 0xEE:
        XOR_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

        /* CP n */
    case 0xBF:
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
        cycle(4);
        break;
    case 0xFE: /* CP d8 */
        CP_8(u, &u->reg.A, m_read8(u));
        cycle(4);
        break;

    /* INC n */
    case 0x3C: /* INC A */
        INC_8(u, &u->reg.A);
        break;
    case 0x04: /* INC B */
        INC_8(u, &u->reg.B);
        break;
    case 0x0C: /* INC C */
        INC_8(u, &u->reg.C);
        break;
    case 0x14: /* INC D */
        INC_8(u, &u->reg.D);
        break;
    case 0x1C: /* INC E */
        INC_8(u, &u->reg.E);
        break;
    case 0x24: /* INC H */
        INC_8(u, &u->reg.H);
        break;
    case 0x2C: /* INC L */
        INC_8(u, &u->reg.L);
        break;
    case 0x34: /* INC (HL) */
        INC_8(u, &u->mem.content[u->reg.HL]);
        cycle(8); /* XXX */
        break;

        /* DEC n */
    case 0x3D: /* DEC A */
        DEC_8(u, &u->reg.A);
        break;
    case 0x05: /* DEC B */
        DEC_8(u, &u->reg.B);
        break;
    case 0x0D: /* DEC C */
        DEC_8(u, &u->reg.C);
        break;
    case 0x15: /* DEC D */
        DEC_8(u, &u->reg.F);
        break;
    case 0x1D: /* DEC E */
        DEC_8(u, &u->reg.E);
        break;
    case 0x25: /* DEC H */
        DEC_8(u, &u->reg.H);
        break;
    case 0x2D: /* DEC L */
        DEC_8(u, &u->reg.L);
        break;
    case 0x35: /* DEC (HL) */
        DEC_8(u, &u->mem.content[u->reg.HL]);
        cycle(8); /* XXX */
        break;

        /* ADD HL,n */
    case 0x09: /* ADD HL,BC */
        ADD_16(u, &u->reg.HL, u->reg.BC);
        break;
    case 0x19: /* ADD HL,DE */
        ADD_16(u, &u->reg.HL, u->reg.DE);
        break;
    case 0x29: /* ADD HL, HL */
        ADD_16(u, &u->reg.HL, u->reg.HL);
        break;
    case 0x39: /* ADD HL,SP */
        ADD_16(u, &u->reg.HL, u->reg.SP);
        break;

    /* ADD SP,n */
    case 0xE8: /* ADD SP,r8 */
        u->reg.SP += cast_signed8(m_read8(u));
        cycle(16); /* XXX */

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = 1;
        u->reg.FN = 0;
        u->reg.FH = 1; /* XXX */
        u->reg.FC = 1; /* XXX */
        break;

        /* INC nn */
    case 0x03: /* INC BC */
        u->reg.BC++;
        cycle(8);
        break;
    case 0x13: /* INC DE */
        u->reg.DE++;
        cycle(8);
        break;
    case 0x23: /* INC HL */
        u->reg.HL++;
        cycle(8);
        break;
    case 0x33: /* INC SP */
        u->reg.SP++;
        cycle(8);
        break;

        /* DEC nn */
    case 0x0B: /* DEC BC */
        u->reg.BC--;
        cycle(8);
        break;
    case 0x1B: /* DEC DE */
        u->reg.DE--;
        cycle(8);
        break;
    case 0x2B: /* DEC HL */
        u->reg.HL--;
        cycle(8);
        break;
    case 0x3B: /* DEC SP */
        u->reg.SP--;
        cycle(8);
        break;

        /* SWAP n */
        /* CB */

        /* DAA */
    case 0x27:    /* DAA */
        cycle(4); /* XXX */
        break;

        /* CPL */
    case 0x2F: /* CPL */
        u->reg.A = ~u->reg.A;
        cycle(4);

        u->reg.FH = 1;
        u->reg.FC = 1;
        break;

        /* CCF */
    case 0x3F:
        u->reg.F ^= C_FLAG;
        cycle(4);

        u->reg.FH = 0;
        u->reg.FC = 0;
        break;

        /* SCF */
    case 0x37: /* SCF */
        u->reg.FC = 1;
        cycle(4);
        break;

    case 0x0: /* NOP */
        cycle(4);
        break;

    case 0x76: /* HALT */
        cycle(4);
        break;

    case 0x10: /* STOP */
        cycle(4);
        break;

    case 0xF3: /* DI */
        cycle(4);
        break;

    case 0xFB: /* EI */

        cycle(4);
        break;

    case 0x07: /* RLCA */
        cycle(4);
        break;

    case 0x17: /* RLA (A) */
        /* see rotating section of
         * http://www.linux-kongress.org/2009/slides/compiler_survey_felix_von_leitner.pdf
         */
        u->reg.A = (u->reg.A << 1) | (u->reg.A >> 7);
        cycle(4);
        break;

    case 0x0F: /* RRCA */
        cycle(4);
        break;

    case 0x1F: /* RRA */
        u->reg.A = (u->reg.A >> 1) | (u->reg.A << 7);
        cycle(4);
        break;

    case 0xCB: /* PREFIX CB */
    {
        uint8_t next = m_read8(u);
        switch (next)
        {
        CASE_CB_RLC:
            break;
        CASE_CB_RRC:
            break;
        CASE_CB_RL:
            break;
        CASE_CB_RR:
            break;
        CASE_CB_SLA:
            break;
        CASE_CB_SRA:
            break;
        CASE_CB_SWAP:
            break;
        CASE_CB_SRL:
            break;
        CASE_CB_BIT:
            break;
        CASE_CB_SET:
            break;
        CASE_CB_RES:
            break;
        }
        break;
    }

    /* JP nn */
    case 0xC3: /* JP a16 */
        u->mem.ptr = m_peek16(u);
        cycle(12);
        break;

        /* JP cc,nn */
    case 0xC2: /* JP NZ,a16 */
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;
    case 0xCA: /* JP Z,a16 */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;
    case 0xD2: /* JP NC,a16 */
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;
    case 0xDA: /* JP C,a16 */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;

        /* JP (HL) */
    case 0xE9: /* JP (HL) */
        u->mem.ptr = m_get8(u, u->reg.HL);
        cycle(4);
        break;

        /* JR n */
    case 0x18: /* JR r8 */
        u->mem.ptr += cast_signed8(m_read8(u));
        cycle(8);
        break;

        /* JR cc,n */
    case 0x20: /* JR NZ (Z),d8 */
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr += cast_signed8(m_read8(u));
        }
        else
        {
            m_read8(u);
        }
        cycle(8);
        break;
    case 0x28: /* JR Z,d8 */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr += cast_signed8(m_read8(u));
        }
        else
        {
            m_read8(u);
        }
        cycle(8);
        break;
    case 0x30: /* JR NZ (C),a8 */
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr += cast_signed8(m_read8(u));
        }
        else
        {
            m_read8(u);
        }
        cycle(8);
        break;

    case 0x38: /* JR C,d8 */
        if (u->reg.F & C_FLAG)
        {
            u->mem.ptr += cast_signed8(m_read8(u));
        }
        else
        {
            m_read8(u);
        }
        cycle(8);
        break;

        /* CALL nn */
    case 0xCD: /* CALL a16 */
        s_push16(u, u->mem.ptr + 1);
        u->mem.ptr = m_peek16(u);
        cycle(12);
        break;

        /* CALL cc, nn */
    case 0xC4: /* CALL NZ,a16 */
        if (!(u->reg.F & Z_FLAG))
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;
    case 0xCC: /* CALL Z,a16 */
        if (u->reg.F & Z_FLAG)
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;
    case 0xD4: /* CALL NC,a16 */
        if (!(u->reg.F & C_FLAG))
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;
    case 0xDC: /* CALL C,a16 */
        if (u->reg.F & C_FLAG)
        {
            s_push16(u, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u);
        }
        else
        {
            m_read16(u);
        }
        cycle(12);
        break;

        /* RST n */
    case 0xC7: /* RST $00 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x00;
        cycle(32);
        break;
    case 0xCF: /* RST $08 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x08;
        cycle(32);
        break;
    case 0xD7: /* RST $10 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x10;
        cycle(32);
        break;
    case 0xDF: /* RST $18 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x18;
        cycle(32);
        break;
    case 0xE7: /* RST $20 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x20;
        cycle(32);
        break;
    case 0xEF: /* RST $28 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x28;
        cycle(32);
        break;
    case 0xF7: /* RST $30 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x30;
        cycle(32);
        break;
    case 0xFF: /* RST $38 */
        s_push16(u, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x38;
        cycle(32);
        break;

        /* RET */
    case 0xC9: /* RET */
        u->mem.ptr = s_pop16(u);
        cycle(8);
        break;

        /* RET cc */
    case 0xC0: /* RET NZ */
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr = s_pop16(u);
        }
        cycle(8);
        break;
    case 0xC8: /* RET Z */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = s_pop16(u);
        }
        cycle(8);
        break;
    case 0xD0: /* RET NC */
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr = s_pop16(u);
        }
        cycle(8);
        break;
    case 0xD8: /* RET C */
        if (u->reg.F & C_FLAG)
        {
            u->mem.ptr = s_pop16(u);
        }
        cycle(8);
        break;

    case 0xD9: /* RETI */
        u->mem.ptr = s_pop16(u);
        cycle(8);
        /* XXX enable interrupts? */
        break;

    default:
        if (u->debug)
        {
            printf("\t\tdunno $%02x\n", op);
        }
        exit(1);
    }

    return 0;
}

int emulate_rom(CPU *u)
{
    if (u->info.cartridge_type !=
        0) /* TODO(keyenzy): Implement multiple ROM Banks */
    {
        puts("Multiple ROM banks not implemented yet.");
        exit(1);
    }

    if (u->debug)
    {
        printf("ADDRESS\tOPCODE\tBYTES\t\tAF\tBC\tDE\tHL\tSP\tZNHC\n");
    }

    uint8_t next_opcode = m_read8(u);

    while (execute_opcode(u, next_opcode) == 0)
    {
        next_opcode = m_read8(u);
        /* Do stuff */
    }

    return 0;
}
