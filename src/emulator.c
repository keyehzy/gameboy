#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>

static uint8 ordered_reg_value(CPU *u, uint8 byte)
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

static void PREFIX_CB_CASE(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);
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

static void LD_B_C(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        u->reg.B = value_of_letter;
    }
    else
    {
        u->reg.C = value_of_letter;
    }
}

static void LD_D_E(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        u->reg.D = value_of_letter;
    }
    else
    {
        u->reg.E = value_of_letter;
    }
}

static void LD_H_L(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        u->reg.H = value_of_letter;
    }
    else
    {
        u->reg.L = value_of_letter;
    }
}

static void LD_HL_A(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8)
    {
        u->mem.content[u->reg.HL] = value_of_letter;
    }
    else
    {
        u->reg.A = value_of_letter;
    }
}

static void ADD_ADC_CASE(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* ADD */
    {
        uint8 res = u->reg.A + value_of_letter;
        u->reg.A = res;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 0;
        u->reg.FH = 0; /* XXX */
        u->reg.FC = 0; /* XXX */
    }
    else /* ADC */
    {
        uint8 res = u->reg.A + value_of_letter + u->reg.FC;
        u->reg.A = res;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 0;
        u->reg.FH = 0; /* XXX */
        u->reg.FC = 0; /* XXX */
    }
}

static void SUB_SBC_CASE(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* SUB */
    {
        uint8 res = u->reg.A - value_of_letter;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 1;
        u->reg.FH = 0; /* XXX */
        u->reg.FC = 0; /* XXX */
    }
    else /* SBC */
    {
        uint8 res = u->reg.A - (value_of_letter + u->reg.FC);
        u->reg.A = res;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 1;
        u->reg.FH = 0; /* XXX */
        u->reg.FC = 0; /* XXX */
    }
}

static void AND_XOR_CASE(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* AND */
    {
        uint8 res = u->reg.A & value_of_letter;
        u->reg.A = res;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 0;
        u->reg.FH = 1;
        u->reg.FC = 0;
    }
    else /* XOR */
    {
        uint8 res = u->reg.A ^ value_of_letter;
        u->reg.A = res;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 0;
        u->reg.FH = 0;
        u->reg.FC = 0;
    }
}

static void OR_CP_CASE(CPU *u, uint8 byte)
{
    uint8 value_of_letter = ordered_reg_value(u, byte);

    if (byte < 0x8) /* OR */
    {
        uint8 res = u->reg.A | value_of_letter;
        u->reg.A = res;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 0;
        u->reg.FH = 0;
        u->reg.FC = 0;
    }
    else /* CP */
    {
        uint8 res = u->reg.A - value_of_letter;

        /* set_flags(u, Z, N, H, C); */
        u->reg.FZ = res == 0;
        u->reg.FN = 1;
        u->reg.FH = 0; /* XXX */
        u->reg.FC = 0; /* XXX */
    }
}

int emulate_rom(CPU *u)
{
    u->mem.ptr = 0x100; /* entry point */

    printf("ADDRESS\tOPCODE\tBYTES\t\tAF\tBC\tDE\tHL\tSP\tPC\tZNHC\n");

    while (1)
    {
        if (u->mem.ptr == 0x8000)
        {
            puts("END OF ROM");
            return 0;
        }

        printf("$%04x\t$%02x\t$%02x $%02x\t\t%04x\t%04x\t%04x\t%04x\t%04x\t%04x\t%d%d%d%d\n",
                u->mem.ptr,
               m_peek8(u), m_get8(u, u->mem.ptr + 1), m_get8(u, u->mem.ptr + 2),
               u->reg.AF, u->reg.BC, u->reg.DE, u->reg.HL, u->reg.SP, u->reg.PC,
               u->reg.FZ, u->reg.FN, u->reg.FH, u->reg.FC
               );

        uint8 op = m_consume8(u);

        switch (op)
        {
        case 0x0: /* NOP */
            continue;
        case 0x10: /* STOP */
            continue;
        case 0x76: /* HALT */
            continue;
        case 0xCB:                            /* PREFIX CB */
            PREFIX_CB_CASE(u, m_consume8(u)); /* XXX */
            continue;
        case 0xF3: /* DI */
            continue;
        case 0xFB: /* EI */
            continue;

        case 0x20: /* JR NZ (Z),d8 */
            if (!u->reg.FZ)
            {
                u->mem.ptr += m_peek8(u);
            }
            continue;
        case 0x30: /* JR NZ (C),a8 */
            if (!u->reg.FC)
            {
                u->mem.ptr += m_peek8(u);
            }
            continue;

        case 0x01: /* LD BC,d16 */
            u->reg.BC = m_consume16(u);
            continue;
        case 0x11: /* LD DE,d16 */
            u->reg.DE = m_consume16(u);
            continue;
        case 0x21: /* LD HL,d16 */
            u->reg.HL = m_consume16(u);
            continue;
        case 0x31: /* LD SP,d16 */
            u->reg.SP = m_consume16(u);
            continue;

        case 0x02: /* LD (BC),A */
            u->mem.content[u->reg.BC] = u->reg.A;
            continue;
        case 0x12: /* LD (DE),A */
            u->mem.content[u->reg.DE] = u->reg.A;
            continue;
        case 0x22: /* LD (HL+),A */
            u->mem.content[u->reg.HL++] = u->reg.A;
            continue;
        case 0x32: /* LD (HL-),A */
            u->mem.content[u->reg.HL--] = u->reg.A;
            continue;

        case 0x03: /* INC BC */
            u->reg.BC++;
            continue;
        case 0x13: /* INC DE */
            u->reg.DE++;
            continue;
        case 0x23: /* INC HL */
            u->reg.HL++;
            continue;
        case 0x33: /* INC SP */
            u->reg.SP++;
            continue;

        case 0x04: /* INC B */
            u->reg.B++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.B == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x14: /* INC D */
            u->reg.D++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.D == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x24: /* INC H */
            u->reg.H++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.H == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x34: /* INC (HL) */
            u->mem.content[u->reg.HL]++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->mem.content[u->reg.HL] == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;

        case 0x05: /* DEC B */
            u->reg.B--;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.B == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x15: /* DEC D */
            u->reg.D = u->reg.D - 1;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.D == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x25: /* DEC H */
            u->reg.H = u->reg.H - 1;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.H == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x35: /* DEC (HL) */
            u->mem.content[u->reg.HL]--;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->mem.content[u->reg.HL] == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;

        case 0x06: /* LD B,d8 */
            u->reg.B = m_consume8(u);
            continue;
        case 0x16: /* LD D,d8 */
            u->reg.D = m_consume8(u);
            continue;
        case 0x26: /* LD H,d8 */
            u->reg.H = m_consume8(u);
            continue;
        case 0x36: /* LD (HL),d8 */
            u->mem.content[u->reg.HL] = m_consume8(u);
            continue;

        case 0x07: /* RLCA */
            continue;
        case 0x17: /* RLA (A) */
            /* see rotating section of
             * http://www.linux-kongress.org/2009/slides/compiler_survey_felix_von_leitner.pdf
             */
            u->reg.A = (u->reg.A << 1) | (u->reg.A >> 7);
            continue;

        case 0x27: /* DAA */
            continue;

        case 0x37: /* SCF (FLAG C) */
            u->reg.FC = 1;
            continue;

        case 0x08: /* LD (a16),SP */
            u->mem.content[m_consume16(u)] = u->reg.SP;
            /* TODO(keyehzy): We need to roll our own */
            continue;

        case 0x18: /* JR r8 */ /* XXX signed? */
            u->mem.ptr += m_peek8(u);
            continue;
        case 0x28: /* JR Z,d8 */
            if (u->reg.FZ)
            {
                u->mem.ptr += m_peek8(u);
            }
            continue;
        case 0x38: /* JR C,d8 */
            if (u->reg.FC)
            {
                u->mem.ptr += m_peek8(u);
            }
            continue;

        case 0x09: /* ADD HL,BC */
            u->reg.HL += u->reg.BC;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;
        case 0x19: /* ADD HL,DE */
            u->reg.HL += u->reg.DE;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;
        case 0x29: /* ADD HL, HL */
            u->reg.HL += u->reg.HL;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;
        case 0x39: /* ADD HL,SP */
            u->reg.HL += u->reg.SP;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;

        case 0x0A: /* LD A, (BC) */
            u->reg.A = u->mem.content[u->reg.BC];
            continue;
        case 0x1A: /* LD A, (DE) */
            u->reg.A = u->mem.content[u->reg.DE];
            continue;
        case 0x2A: /* LD A,(HL+) */
            printf("\t\tLD A, (HL+)\n");
            u->reg.A = u->mem.content[u->reg.HL++];
            continue;
        case 0x3A: /* LD A,(HL-) */
            u->reg.A = u->mem.content[u->reg.HL--];
            continue;

        case 0x0B: /* DEC BC */
            u->reg.BC--;
            continue;
        case 0x1B: /* DEC DE */
            u->reg.DE--;
            continue;
        case 0x2B: /* DEC HL */
            u->reg.HL--;
            continue;
        case 0x3B: /* DEC SP */
            u->reg.SP--;
            continue;

        case 0x0C: /* INC C */
            u->reg.C++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.C == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x1C: /* INC E */
            u->reg.E++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.E == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x2C: /* INC L */
            u->reg.L++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.L == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x3C: /* INC A */
            u->reg.A++;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.L == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            continue;

        case 0x0D: /* DEC C */
            u->reg.C--;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.L == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x1D: /* DEC E */
            u->reg.E--;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.L == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x2D: /* DEC L */
            u->reg.L--;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.L == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;
        case 0x3D: /* DEC A */
            u->reg.A--;

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.L == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            continue;

        case 0x0E: /* LD C,d8 */
            u->reg.C = m_consume8(u);
            continue;
        case 0x1E: /* LD E,d8 */
            u->reg.E = m_consume8(u);
            continue;
        case 0x2E: /* LD L,d8 */
            u->reg.L = m_consume8(u);
            continue;
        case 0x3E: /* LD A,d8 */
            u->reg.A = m_consume8(u);
            continue;

        case 0x0F: /* RRCA */
            continue;
        case 0x1F: /* RRA (A) */
            u->reg.A = (u->reg.A >> 1) | (u->reg.A << 7);
            continue;

        case 0x2F: /* CPL */
            continue;

        case 0x3F: /* SCF */
            continue;
        }

        switch (op >> 4) /* ROWS 4-7 */
        {
        case 0x4:
            LD_B_C(u, op & 0x0F);
            continue;
        case 0x5:
            LD_D_E(u, op & 0x0F);
            continue;
        case 0x6:
            LD_H_L(u, op & 0x0F);
            continue;
        case 0x7:
            LD_HL_A(u, op & 0x0F);
            continue;
        }

        switch (op >> 4) /* ROWS 8-B */
        {
        case 0x8:
            ADD_ADC_CASE(u, op & 0x0F);
            continue;
        case 0x9:
            SUB_SBC_CASE(u, op & 0x0F);
            continue;
        case 0xA:
            AND_XOR_CASE(u, op & 0x0F);
            continue;
        case 0xB:
            OR_CP_CASE(u, op & 0x0F);
            continue;
        }

        switch (op)
        {
        case 0xC0: /* RET NZ */
            if (!u->reg.FZ)
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;
        case 0xD0: /* RET NC */
            if (!u->reg.FC)
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;

        case 0xE0: /* LDH (a8),A */ /* CHECK XXX */
            u->mem.content[0xFF00 + m_consume8(u)] = u->reg.A;
            continue;
        case 0xF0: /* LDH A,(a8) */
            u->reg.A = u->mem.content[0xFF00 + m_consume8(u)];
            continue;

        case 0xC1: /* POP BC */
            u->reg.BC = s_pop16(u->st);
            continue;
        case 0xD1: /* POP DE */
            u->reg.DE = s_pop16(u->st);
            continue;
        case 0xE1: /* POP HL */
            u->reg.HL = s_pop16(u->st);
            continue;
        case 0xF1: /* POP AF */
            u->reg.AF = s_pop16(u->st);
            continue;

        case 0xC2: /* JP NZ,a16 */
            if (!u->reg.FZ)
            {
                u->mem.ptr = m_consume16(u);
            }
            continue;
        case 0xD2: /* JP NC,a16 */
            if (!u->reg.FC)
            {
                u->mem.ptr = m_consume16(u);
            }
            continue;

        case 0xE2: /* LD (C), A */
            u->mem.content[0xFF00 + u->reg.C] = u->reg.A;
            continue;

        case 0xF2: /* LD A,(C) */
            u->reg.A = u->mem.content[0xFF00 + u->reg.C];
            continue;

        case 0xC3: /* JP a16 */
            u->mem.ptr = m_peek16(u);
            continue;

        case 0xC4: /* CALL a16 */
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_consume16(u);
            continue;
        case 0xD4: /* CALL NC,a16 */
            if (!u->reg.FC)
            {
                s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_consume16(u);
            }
            continue;

        case 0xC5: /* PUSH BC */
            s_push16(u->st, u->reg.BC);
            continue;
        case 0xD5: /* PUSH DE */
            s_push16(u->st, u->reg.DE);
            continue;
        case 0xE5: /* PUSH HL */
            s_push16(u->st, u->reg.HL);
            continue;
        case 0xF5: /* PUSH AF */
            s_push16(u->st, u->reg.AF);
            continue;

        case 0xC6: /* ADD,d8 */
            u->reg.A += m_consume8(u);
            continue;
        case 0xD6: /* SUB A,d8 */
            u->reg.A -= m_consume8(u);
            continue;
        case 0xE6: /* AND A,d8 */
            u->reg.A = u->reg.A & m_consume8(u);
            continue;
        case 0xF6: /* OR,d8 */
            u->reg.A = u->reg.A | m_consume8(u);
            continue;

        case 0xC7: /* RST $00 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x00;
            continue;
        case 0xD7: /* RST $10 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x10;
            continue;
        case 0xE7: /* RST $20 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x20;
            continue;
        case 0xF7: /* RST $30 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x30;
            continue;

        case 0xC8: /* RET Z */
            if (u->reg.FZ)
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;
        case 0xD8: /* RET C */
            if (u->reg.FC)
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;

        case 0xE8: /* ADD SP,r8 */
            u->reg.SP += m_consume8(u);

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;

        case 0xF8: /* LD HL,SP+r8 */
            u->reg.HL = u->reg.SP + m_consume8(u);

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;

        case 0xC9: /* RET */
            u->mem.ptr = s_pop16(u->st);
            continue;
        case 0xD9: /* RETI */
            u->mem.ptr = s_pop16(u->st);
            /* XXX enable interrupts? */
            continue;

        case 0xE9: /* JP (HL) */
            u->mem.ptr = u->mem.content[u->reg.HL];
            continue;

        case 0xF9: /* LD SP,HL */
            u->reg.SP = u->reg.HL;
            continue;

        case 0xCA: /* JP Z,a16 */
            if (u->reg.FZ)
            {
                u->mem.ptr = m_consume16(u);
            }
            continue;
        case 0xDA: /* JP C,a16 */
            if (u->reg.FZ)
            {
                u->mem.ptr = m_consume16(u);
            }
            continue;

        case 0xEA: /* LD (a16),A */
            u->mem.content[m_consume16(u)] = u->reg.A;
            continue;
        case 0xFA: /* LD A,(a16) */
            u->reg.A = u->mem.content[m_consume16(u)];
            continue;

        case 0xCC: /* CALL Z,a16 */
            if (u->reg.FZ)
            {
                s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_peek16(u);
            }
            continue;
        case 0xDC: /* CALL C,a16 */
            if (u->reg.FC)
            {
                s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_peek16(u);
            }
            continue;
        case 0xCD: /* CALL a16 */
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u);
            continue;

        case 0xCE: /* ADC A,d8 */
            u->reg.A += (m_consume8(u) + u->reg.FC);

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.A == 0;
            u->reg.FN = 0;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;
        case 0xDE: /* SBC A,d8 */
            u->reg.A -= (m_consume8(u) + u->reg.FC);

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.A == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;
        case 0xEE: /* XOR A,d8 */
            u->reg.A ^= m_consume8(u);

            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.A == 0;
            u->reg.FN = 0;
            u->reg.FH = 0;
            u->reg.FC = 0;
            continue;
        case 0xFE: /* CP d8 */
            /* set_flags(u, Z, N, H, C); */
            u->reg.FZ = u->reg.A - m_consume8(u) == 0;
            u->reg.FN = 1;
            u->reg.FH = 0; /* XXX */
            u->reg.FC = 0; /* XXX */
            continue;

        case 0xCF: /* RST $08 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x08;
            continue;
        case 0xDF: /* RST $18 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x18;
            continue;
        case 0xEF: /* RST $28 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x28;
            continue;
        case 0xFF: /* RST $38 */
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x38;
            continue;
        }

        printf("\t\tdunno $%02x\n", op);
    }
    return 1;
}
