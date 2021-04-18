#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>
#include <gameboy/emulator.h>

static uint8_t ordered_reg_value(CPU *u, uint8_t byte)
{
    switch (byte % 0x8)
    {
    case 0x0:
        return u->reg.B;
    case 0x1:
        return u->reg.C;
    case 0x2:
        return u->reg.D;
    case 0x3:
        return u->reg.E;
    case 0x4:
        return u->reg.H;
    case 0x5:
        return u->reg.L;
    case 0x6:
        return u->mem.content[u->reg.HL];
    case 0x7:
        return u->reg.A;
    default:
        exit(1);
    }
}

static void PREFIX_CB_CASE(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);
    switch (byte >> 4)
    {
    case 0x0: /* RLC */
        if (byte < 0x8)
        {
        }
        else /* RRC */
        {
        }
        break;
    case 0x1: /* RL */
        if (byte < 0x8)
        {
        }
        else /* RR */
        {
        }
        break;
    case 0x2: /* SLA */
        if (byte < 0x8)
        {
        }
        else /* SRA */
        {
        }
        break;
    case 0x3: /* SWAP */
        if (byte < 0x8)
        {
        }
        else /* SRL */
        {
        }
        break;
    case 0x4: /* BIT */
        if (byte < 0x8)
        {
        }
        else /* BIT */
        {
        }
        break;
    case 0x5: /* BIT */
        if (byte < 0x8)
        {
        }
        else /* BIT */
        {
        }
        break;
    case 0x6: /* BIT */
        if (byte < 0x8)
        {
        }
        else /* BIT */
        {
        }
        break;
    case 0x7: /* BIT */
        if (byte < 0x8)
        {
        }
        else /* BIT */
        {
        }
        break;
    case 0x8: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    case 0x9: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    case 0xA: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    case 0xB: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    case 0xC: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    case 0xD: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    case 0xE: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    case 0xF: /* RES */
        if (byte < 0x8)
        {
        }
        else /* RES */
        {
        }
        break;
    default:
        exit(1);
    }
}

static void LD_B_C(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        u->reg.B = value_of_letter;
    }
    else
    {
        u->reg.C = value_of_letter;
    }
}

static void LD_D_E(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        u->reg.D = value_of_letter;
    }
    else
    {
        u->reg.E = value_of_letter;
    }
}

static void LD_H_L(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        u->reg.H = value_of_letter;
    }
    else
    {
        u->reg.L = value_of_letter;
    }
}

static void LD_HL_A(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        m_set8(u, u->reg.HL, value_of_letter);
    }
    else
    {
        u->reg.A = value_of_letter;
    }
}

static void ADD_ADC_CASE(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* ADD */
    {
        uint16_t res = (uint16_t)(u->reg.A + value_of_letter);
        /* http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html */
        /* https://stackoverflow.com/questions/8868396/game-boy-what-constitutes-a-half-carry
         */
        uint16_t wrap = (uint16_t)((u->reg.A & 0xF) + (value_of_letter & 0xF));
        u->reg.A = (uint8_t)res;

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
    }
    else /* ADC */
    {
        uint16_t res =
            (uint16_t)(u->reg.A + value_of_letter + (u->reg.F & C_FLAG));
        uint16_t wrap = (uint16_t)(
            (u->reg.A & 0xF) + ((value_of_letter + (u->reg.F & C_FLAG)) & 0xF));
        u->reg.A = (uint8_t)res;

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
    }
}

static void SUB_SBC_CASE(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* SUB */
    {
        uint16_t res = (uint16_t)(u->reg.A - value_of_letter);
        uint16_t wrap = (uint16_t)((u->reg.A & 0xF) - (value_of_letter & 0xF));
        u->reg.A = (uint8_t)res;

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
    }
    else /* SBC */
    {
        uint16_t res =
            (uint16_t)(u->reg.A - (value_of_letter + (u->reg.F & C_FLAG)));
        uint16_t wrap = (uint16_t)(
            (u->reg.A & 0xF) - ((value_of_letter + (u->reg.F & C_FLAG)) & 0xF));
        u->reg.A = (uint8_t)res;

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
    }
}

static void AND_XOR_CASE(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* AND */
    {
        uint16_t res = (uint16_t)(u->reg.A & value_of_letter);
        u->reg.A = (uint8_t)res;

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        u->reg.F |= H_FLAG;
        u->reg.F &= ~C_FLAG;
    }
    else /* XOR */
    {
        uint16_t res = (uint16_t)(u->reg.A ^ value_of_letter);
        u->reg.A = (uint8_t)res;

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        u->reg.F &= ~H_FLAG;
        u->reg.F &= ~C_FLAG;
    }
}

static void OR_CP_CASE(CPU *u, uint8_t byte)
{
    uint8_t value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* OR */
    {
        uint16_t res = (uint16_t)(u->reg.A | value_of_letter);
        u->reg.A = (uint8_t)res;

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        u->reg.F &= ~H_FLAG;
        u->reg.F &= ~C_FLAG;
    }
    else /* CP */
    {
        uint16_t res = (uint16_t)(u->reg.A - value_of_letter);
        uint16_t wrap = (uint16_t)((u->reg.A & 0xF) - (value_of_letter & 0xF));

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
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
               "$%02x\t\t$%04x\t$%04x\t$%04x\t$%04x\t$%04x\t$%04x\n",
               u->mem.ptr, op, m_get8(u, u->mem.ptr),
               m_get8(u, u->mem.ptr + 1), u->reg.AF, u->reg.BC, u->reg.DE,
               u->reg.HL, u->st->ptr, u->reg.F);
    }

    switch (op) /* The order should be the s
                   same as in the GameBoy manual */
    {
        /* LD nn,n */
    case 0x06: /* LD B,d8 */
        u->reg.B = m_read8(u);
        break;
    case 0x0E: /* LD C,d8 */
        u->reg.C = m_read8(u);
        break;
    case 0x16: /* LD D,d8 */
        u->reg.D = m_read8(u);
        break;
    case 0x1E: /* LD E,d8 */
        u->reg.E = m_read8(u);
        break;
    case 0x26: /* LD H,d8 */
        u->reg.H = m_read8(u);
        break;
    case 0x2E: /* LD L,d8 */
        u->reg.L = m_read8(u);
        break;

        /* XXX */
    case 0x36: /* LD (HL),d8 */
        m_set8(u, u->reg.HL, m_read8(u));
        break;

        /* LD r1,r2 */
    CASE_LD_A:
        LD_HL_A(u, op & 0x0F);
        break;
    CASE_LD_B:
    CASE_LD_C:
        LD_B_C(u, op & 0x0F);
        break;
    CASE_LD_D:
    CASE_LD_E:
        LD_D_E(u, op & 0x0F);
        break;
    CASE_LD_H:
    CASE_LD_L:
        LD_H_L(u, op & 0x0F);
        break;
    CASE_LD_HL:
        LD_HL_A(u, op & 0x0F);
        break;

        /* LD A,n */
    case 0x0A: /* LD A, (BC) */
        u->reg.A = u->mem.content[u->reg.BC];
        break;
    case 0x1A: /* LD A, (DE) */
        u->reg.A = u->mem.content[u->reg.DE];
        break;
    case 0xFA: /* LD A,(a16) */
        u->reg.A = u->mem.content[m_read16(u)];
        break;
    case 0x3E: /* LD A,d8 */
        u->reg.A = m_read8(u);
        break;

        /* XXX */

        /* LD n,A */
    case 0x02: /* LD (BC),A */
        m_set8(u, u->reg.BC, u->reg.A);
        break;
    case 0x12: /* LD (DE),A */
        m_set8(u, u->reg.DE, u->reg.A);
        break;
    case 0xEA: /* LD (a16),A */
        m_set8(u, m_read16(u), u->reg.A);
        break;

        /* XXX */

        /* LD A,(C) */
    case 0xF2: /* LD A,(C) */
        u->reg.A = u->mem.content[0xFF00 + u->reg.C];
        break;

        /* LD (C),A */
    case 0xE2: /* LD (C), A */
        m_set8(u, 0xFF00 + u->reg.C, u->reg.A);
        break;

        /* LDD A,(HL) */
    case 0x3A: /* LD A,(HL-) */
        u->reg.A = u->mem.content[u->reg.HL--];
        break;

        /* LDD (HL),A */
    case 0x32: /* LD (HL-),A */
        m_set8(u, u->reg.HL--, u->reg.A);
        break;

        /* LDI A,(HL) */
    case 0x2A: /* LD A,(HL+) */
        u->reg.A = u->mem.content[u->reg.HL++];
        break;

        /* LDI (HL),A */
    case 0x22: /* LD (HL+),A */
        m_set8(u, u->reg.HL++, u->reg.A);
        break;

        /* LDH (n),A */
    case 0xE0: /* LDH (a8),A */ /* SIGN XXX */
        m_set8(u, 0xFF00 + m_read8(u), u->reg.A);
        break;

        /* LDH A,(n) */
    case 0xF0: /* LDH A,(a8) */ /* SIGN XXX */
        u->reg.A = u->mem.content[0xFF00 + m_read8(u)];
        break;

        /* LD n,nn */
    case 0x01: /* LD BC,d16 */
        u->reg.BC = m_read16(u);
        break;
    case 0x11: /* LD DE,d16 */
        u->reg.DE = m_read16(u);
        break;
    case 0x21: /* LD HL,d16 */
        u->reg.HL = m_read16(u);
        break;
    case 0x31: /* LD SP,d16 */
        u->reg.SP = m_read16(u);
        break;

        /* LD SP,HL */
    case 0xF9: /* LD SP,HL */
        u->reg.SP = u->reg.HL;
        break;

        /* LDHL SP,n */
    case 0xF8: /* LD HL,SP+r8 */
        u->reg.HL = u->reg.SP + m_read8(u);

        /* set_flags(u, Z, N, H, C); */
        u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        u->reg.F |= H_FLAG; /* XXX */
        u->reg.F |= C_FLAG; /* XXX */
        break;

        /* LD (nn),SP */
    case 0x08: /* LD (a16),SP */
        m_set8(u, m_read16(u), u->reg.SP);
        /* TODO(keyehzy): We need to roll our own */
        break;

        /* PUSH nn */
    case 0xF5: /* PUSH AF */
        s_push16(u->st, u->reg.AF);
        break;
    case 0xC5: /* PUSH BC */
        s_push16(u->st, u->reg.BC);
        break;
    case 0xD5: /* PUSH DE */
        s_push16(u->st, u->reg.DE);
        break;
    case 0xE5: /* PUSH HL */
        s_push16(u->st, u->reg.HL);
        break;

        /* POP nn */
    case 0xF1: /* POP AF */
        u->reg.AF = s_pop16(u->st);
        break;
    case 0xC1: /* POP BC */
        u->reg.BC = s_pop16(u->st);
        break;
    case 0xD1: /* POP DE */
        u->reg.DE = s_pop16(u->st);
        break;
    case 0xE1: /* POP HL */
        u->reg.HL = s_pop16(u->st);
        break;

        /* ADD A,n */
    CASE_ADD:
        ADD_ADC_CASE(u, op & 0x0F);
        break;
    case 0xC6:                  /* ADD,d8 */
        u->reg.A += m_read8(u); /* XXX flags */
        break;

        /* ADC A,n */
    CASE_ADC:
        ADD_ADC_CASE(u, op & 0x0F);
        break;
    case 0xCE: /* ADC A,d8 */
    {
        uint8_t next8 = m_read8(u);
        uint16_t res = (uint16_t)(u->reg.A + next8 + (u->reg.F & C_FLAG));
        uint16_t wrap = (uint16_t)((u->reg.A & 0xF) +
                                   ((next8 + (u->reg.F & C_FLAG)) & 0xF));
        u->reg.A = (uint8_t)res;

        if (u->reg.A == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
        break;
    }

    /* SUB n */
    CASE_SUB:
        SUB_SBC_CASE(u, op & 0x0F);
        break;
    case 0xD6:                  /* SUB A,d8 */
        u->reg.A -= m_read8(u); /* XXX flags */
        break;

        /* SBC */
    CASE_SBC:
        SUB_SBC_CASE(u, op & 0x0F);
        break;
    case 0xDE: /* SBC A,d8 */
    {
        uint8_t next8 = m_read8(u);
        uint16_t res = (uint16_t)(u->reg.A - (next8 + (u->reg.F & C_FLAG)));
        uint16_t wrap = (uint16_t)((u->reg.A & 0xF) -
                                   ((next8 + (u->reg.F & C_FLAG)) & 0xF));
        u->reg.A = (uint8_t)res;

        if (u->reg.A == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
        break;
    }

    /* AND n */
    CASE_AND:
        AND_XOR_CASE(u, op & 0x0F);
        break;
    case 0xE6:                            /* AND A,d8 */
        u->reg.A = u->reg.A & m_read8(u); /* XXX FLAGS */
        break;

        /* OR n */
    CASE_OR:
        OR_CP_CASE(u, op & 0x0F);
        break;
    case 0xF6:                            /* OR,d8 */
        u->reg.A = u->reg.A | m_read8(u); /* XXX FLAGS */
        break;

        /* XOR n */
    CASE_XOR:
        AND_XOR_CASE(u, op & 0x0F);
        break;
    case 0xEE: /* XOR A,d8 */
        u->reg.A ^= m_read8(u);

        /* set_flags(u, Z, N, H, C); */
        if (u->reg.A == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        u->reg.F |= H_FLAG;
        u->reg.F |= C_FLAG;
        break;

        /* CP n */
    CASE_CP:
        OR_CP_CASE(u, op & 0x0F);
        break;
    case 0xFE: /* CP d8 */
    {
        uint8_t next8 = m_read8(u);
        uint16_t res = (uint16_t)(u->reg.A - next8);
        uint16_t wrap = (uint16_t)((u->reg.A & 0xF) - (next8 & 0xF));

        if (res == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if (wrap > 0xF)
            u->reg.F |= H_FLAG;
        if (res > 0xFF)
            u->reg.F |= C_FLAG;
        break;
    }

    /* INC n */
    case 0x3C: /* INC A */
        u->reg.A++;

        if (u->reg.A == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->reg.A & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x04: /* INC B */
        u->reg.B++;

        if (u->reg.B == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->reg.B & 0xF) == 0)
            u->reg.F |= H_FLAG; /* XXX */
        break;
    case 0x0C: /* INC C */
        u->reg.C++;

        if (u->reg.C == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->reg.C & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x14: /* INC D */
        u->reg.D++;

        if (u->reg.D == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->reg.D & 0xF) == 0)
            u->reg.F |= H_FLAG; /* XXX */
        break;
    case 0x1C: /* INC E */
        u->reg.E++;

        if (u->reg.E == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->reg.E & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x24: /* INC H */
        u->reg.H++;

        if (u->reg.H == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->reg.H & 0xF) == 0)
            u->reg.F |= H_FLAG; /* XXX */
        break;
    case 0x2C: /* INC L */
        u->reg.L++;

        if (u->reg.L == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->reg.L & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x34: /* INC (HL) */
        u->mem.content[u->reg.HL]++;

        /* set_flags(u, Z, N, H, C); */
        if (u->mem.content[u->reg.HL] == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        if ((u->mem.content[u->reg.HL] & 0xF) == 0)
            u->reg.F |= H_FLAG; /* XXX */
        break;

        /* DEC n */
    case 0x3D: /* DEC A */
        u->reg.A--;

        if (u->reg.A == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->reg.A & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x05: /* DEC B */
        u->reg.B--;

        if (u->reg.B == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->reg.B & 0xF) == 0xF)
            u->reg.F |= H_FLAG; /* XXX */
        break;
    case 0x0D: /* DEC C */
        u->reg.C--;

        if (u->reg.C == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->reg.C & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x15: /* DEC D */
        u->reg.D = u->reg.D - 1;

        /* set_flags(u, Z, N, H, C); */
        if (u->reg.D == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->reg.D & 0xF) == 0xF)
            u->reg.F |= H_FLAG; /* XXX */
        break;
    case 0x1D: /* DEC E */
        u->reg.E--;

        if (u->reg.E == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->reg.E & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x25: /* DEC H */
        u->reg.H = u->reg.H - 1;

        /* set_flags(u, Z, N, H, C); */
        if (u->reg.H == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->reg.H & 0xF) == 0xF)
            u->reg.F |= H_FLAG; /* XXX */
        break;
    case 0x2D: /* DEC L */
        u->reg.L--;

        if (u->reg.L == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->reg.L & 0xF) == 0)
            u->reg.F |= H_FLAG;
        break;
    case 0x35: /* DEC (HL) */
        u->mem.content[u->reg.HL]--;

        /* set_flags(u, Z, N, H, C); */
        if (u->mem.content[u->reg.HL] == 0)
            u->reg.F |= Z_FLAG;
        u->reg.F |= N_FLAG;
        if ((u->mem.content[u->reg.HL] & 0xF) == 0xF)
            u->reg.F |= H_FLAG; /* XXX */
        break;

        /* ADD HL,n */
    case 0x09: /* ADD HL,BC */
    {
        uint32_t res = (uint32_t)(u->reg.HL + u->reg.BC);
        uint32_t wrap = (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.BC & 0xFFF));
        u->reg.HL = (uint16_t)res;

        u->reg.F &= ~N_FLAG;
        if (wrap > 0x0FF)
            u->reg.F |= H_FLAG;
        if (res > 0xFFFF)
            u->reg.F |= C_FLAG;
        break;
    }
    case 0x19: /* ADD HL,DE */
    {
        uint32_t res = (uint32_t)(u->reg.HL + u->reg.DE);
        uint32_t wrap = (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.DE & 0xFFF));
        u->reg.HL = (uint16_t)res;

        u->reg.F &= ~N_FLAG;
        if (wrap > 0x0FF)
            u->reg.F |= H_FLAG;
        if (res > 0xFFFF)
            u->reg.F |= C_FLAG;
        break;
    }
    case 0x29: /* ADD HL, HL */
    {
        uint32_t res = (uint32_t)(u->reg.HL + u->reg.HL);
        uint32_t wrap = (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.HL & 0xFFF));
        u->reg.HL = (uint16_t)res;

        u->reg.F &= ~N_FLAG;
        if (wrap > 0x0FF)
            u->reg.F |= H_FLAG;
        if (res > 0xFFFF)
            u->reg.F |= C_FLAG;
        break;
    }
    case 0x39: /* ADD HL,SP */
    {
        uint32_t res = (uint32_t)(u->reg.HL + u->reg.SP);
        uint32_t wrap = (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.SP & 0xFFF));
        u->reg.HL = (uint16_t)res;

        u->reg.F &= ~N_FLAG;
        if (wrap > 0x0FF)
            u->reg.F |= H_FLAG;
        if (res > 0xFFFF)
            u->reg.F |= C_FLAG;
        break;
    }

    /* ADD SP,n */
    case 0xE8: /* ADD SP,r8 */
        u->reg.SP += m_read8(u);

        /* set_flags(u, Z, N, H, C); */
        u->reg.F |= Z_FLAG;
        u->reg.F &= ~N_FLAG;
        u->reg.F |= H_FLAG; /* XXX */
        u->reg.F |= C_FLAG; /* XXX */
        break;

        /* INC nn */
    case 0x03: /* INC BC */
        u->reg.BC++;
        break;
    case 0x13: /* INC DE */
        u->reg.DE++;
        break;
    case 0x23: /* INC HL */
        u->reg.HL++;
        break;
    case 0x33: /* INC SP */
        u->reg.SP++;
        break;

        /* DEC nn */
    case 0x0B: /* DEC BC */
        u->reg.BC--;
        break;
    case 0x1B: /* DEC DE */
        u->reg.DE--;
        break;
    case 0x2B: /* DEC HL */
        u->reg.HL--;
        break;
    case 0x3B: /* DEC SP */
        u->reg.SP--;
        break;

        /* SWAP n */
        /* CB */

        /* DAA */
    case 0x27: /* DAA */
        break;

        /* CPL */
    case 0x2F: /* CPL */
        break; /* XXX FLAGS */

        /* CCF */
    case 0x3F:
        break;

        /* SCF */
    case 0x37: /* SCF */
        u->reg.F |= C_FLAG;
        break;

    case 0x0: /* NOP */
        break;

    case 0x76: /* HALT */
        break;

    case 0x10: /* STOP */
        break;

    case 0xF3: /* DI */
        break;

    case 0xFB: /* EI */
        break;

    case 0x07: /* RLCA */
        break;

    case 0x17: /* RLA (A) */
        /* see rotating section of
         * http://www.linux-kongress.org/2009/slides/compiler_survey_felix_von_leitner.pdf
         */
        u->reg.A = (u->reg.A << 1) | (u->reg.A >> 7);
        break;

    case 0x0F: /* RRCA */
        break;

    case 0x1F: /* RRA (A) */
        u->reg.A = (u->reg.A >> 1) | (u->reg.A << 7);
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
        PREFIX_CB_CASE(u, m_read8(u)); /* XXX */
        break;
    }

    /* JP nn */
    case 0xC3: /* JP a16 */
        u->mem.ptr = m_peek16(u);
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
        break;
    case 0xCA: /* JP Z,a16 */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = m_read16(u);
        }
        break;
    case 0xD2: /* JP NC,a16 */
        printf("%02x %02x %d\n", u->reg.F, C_FLAG, u->reg.F & C_FLAG);
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        break;
    case 0xDA: /* JP C,a16 */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = m_read16(u);
        }
        break;

        /* JP (HL) */
    case 0xE9: /* JP (HL) */
        u->mem.ptr = u->mem.content[u->reg.HL];
        break;

        /* JR n */
    case 0x18: /* JR r8 */ /* XXX signed? */
        u->mem.ptr += m_read8(u);
        break;

        /* JR cc,n */
    case 0x20: /* JR NZ (Z),d8 */
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr += m_read8(u);
        }
        else
        {
            m_read8(u);
        }
        break;
    case 0x28: /* JR Z,d8 */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr += m_read8(u);
        }
        else
        {
            m_read8(u);
        }
        break;
    case 0x30: /* JR NZ (C),a8 */
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr += m_read8(u);
        }
        else
        {
            m_read8(u);
        }
        break;

    case 0x38: /* JR C,d8 */
        if (u->reg.F & C_FLAG)
        {
            u->mem.ptr += m_read8(u);
        }
        else
        {
            m_read8(u);
        }
        break;

        /* CALL nn */
    case 0xCD: /* CALL a16 */
        s_push16(u->st, u->mem.ptr + 1);
        u->mem.ptr = m_peek16(u);
        break;

        /* CALL cc, nn */
    case 0xC4: /* CALL a16 */
        s_push16(u->st, u->mem.ptr + 1);
        u->mem.ptr = m_read16(u);
        break;
    case 0xCC: /* CALL Z,a16 */
        if (u->reg.F & Z_FLAG)
        {
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u);
        }
        break;
    case 0xD4: /* CALL NC,a16 */
        if (!(u->reg.F & C_FLAG))
        {
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_read16(u);
        }
        else
        {
            m_read16(u);
        }
        break;
    case 0xDC: /* CALL C,a16 */
        if (u->reg.F & C_FLAG)
        {
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u);
        }
        break;

        /* RST n */
    case 0xC7: /* RST $00 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x00;
        break;
    case 0xCF: /* RST $08 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x08;
        break;
    case 0xD7: /* RST $10 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x10;
        break;
    case 0xDF: /* RST $18 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x18;
        break;
    case 0xE7: /* RST $20 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x20;
        break;
    case 0xEF: /* RST $28 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x28;
        break;
    case 0xF7: /* RST $30 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x30;
        break;
    case 0xFF: /* RST $38 */
        s_push16(u->st, u->mem.ptr);
        u->mem.ptr = 0x0000 + 0x38;
        break;

        /* RET */
    case 0xC9: /* RET */
        u->mem.ptr = s_pop16(u->st);
        break;

        /* RET cc */
    case 0xC0: /* RET NZ */
        if (!(u->reg.F & Z_FLAG))
        {
            u->mem.ptr = s_pop16(u->st);
        }
        break;
    case 0xC8: /* RET Z */
        if (u->reg.F & Z_FLAG)
        {
            u->mem.ptr = s_pop16(u->st);
        }
        break;
    case 0xD0: /* RET NC */
        if (!(u->reg.F & C_FLAG))
        {
            u->mem.ptr = s_pop16(u->st);
        }
        break;
    case 0xD8: /* RET C */
        if (u->reg.F & C_FLAG)
        {
            u->mem.ptr = s_pop16(u->st);
        }
        break;

    case 0xD9: /* RETI */
        u->mem.ptr = s_pop16(u->st);
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
