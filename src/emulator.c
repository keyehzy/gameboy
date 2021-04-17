#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>

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

int emulate_rom(CPU *u)
{
    if (u->info.cartridge_type !=
        0) /* TODO(keyenzy): Implement multiple ROM Banks */
    {
        puts("Multiple ROM banks not implemented yet.");
        exit(1);
    }

    printf("ADDRESS\tOPCODE\tBYTES\t\tAF\tBC\tDE\tHL\tSP\tPC\tZNHC\n");

    printf("ADDRESS\tOPCODE\tBYTES\t\tFLAGS(ZNHC)\n");

    while (1)
    {
        if (u->mem.ptr == 0x8000)
        {
            puts("END OF ROM");
            return 0;
        }

        printf("$%04x\t$%02x\t$%02x "
               "$%02x\t\t$%04x\t$%04x\t$%04x\t$%04x\t$%04x\t$%04x\t$%02x\n",
               u->mem.ptr, m_peek8(u), m_get8(u, u->mem.ptr + 1),
               m_get8(u, u->mem.ptr + 2), u->reg.AF, u->reg.BC, u->reg.DE,
               u->reg.HL, u->reg.SP, u->reg.PC, u->reg.F);

        uint8_t op = m_read8(u);

        switch (op)
        {
        case 0x0: /* NOP */
            continue;
        case 0x10: /* STOP */
            continue;
        case 0x76: /* HALT */
            continue;
        case 0xCB:                         /* PREFIX CB */
            PREFIX_CB_CASE(u, m_read8(u)); /* XXX */
            continue;
        case 0xF3: /* DI */
            continue;
        case 0xFB: /* EI */
            continue;

        case 0x20: /* JR NZ (Z),d8 */
            if (!(u->reg.F & Z_FLAG))
            {
                u->mem.ptr += m_read8(u);
            }
            else
            {
                m_read8(u);
            }
            continue;
        case 0x30: /* JR NZ (C),a8 */
            if (!(u->reg.F & C_FLAG))
            {
                u->mem.ptr += m_read8(u);
            }
            else
            {
                m_read8(u);
            }
            continue;

        case 0x01: /* LD BC,d16 */
            u->reg.BC = m_read16(u);
            continue;
        case 0x11: /* LD DE,d16 */
            u->reg.DE = m_read16(u);
            continue;
        case 0x21: /* LD HL,d16 */
            u->reg.HL = m_read16(u);
            continue;
        case 0x31: /* LD SP,d16 */
            u->reg.SP = m_read16(u);
            continue;

        case 0x02: /* LD (BC),A */
            m_set8(u, u->reg.BC, u->reg.A);
            continue;
        case 0x12: /* LD (DE),A */
            m_set8(u, u->reg.DE, u->reg.A);
            continue;
        case 0x22: /* LD (HL+),A */
            m_set8(u, u->reg.HL++, u->reg.A);
            continue;
        case 0x32: /* LD (HL-),A */
            m_set8(u, u->reg.HL--, u->reg.A);
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

            if (u->reg.B == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->reg.B & 0xF) == 0)
                u->reg.F |= H_FLAG; /* XXX */
            continue;
        case 0x14: /* INC D */
            u->reg.D++;

            if (u->reg.D == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->reg.D & 0xF) == 0)
                u->reg.F |= H_FLAG; /* XXX */
            continue;
        case 0x24: /* INC H */
            u->reg.H++;

            if (u->reg.H == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->reg.H & 0xF) == 0)
                u->reg.F |= H_FLAG; /* XXX */
            continue;
        case 0x34: /* INC (HL) */
            u->mem.content[u->reg.HL]++;

            /* set_flags(u, Z, N, H, C); */
            if (u->mem.content[u->reg.HL] == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->mem.content[u->reg.HL] & 0xF) == 0)
                u->reg.F |= H_FLAG; /* XXX */
            continue;

        case 0x05: /* DEC B */
            u->reg.B--;

            if (u->reg.B == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->reg.B & 0xF) == 0xF)
                u->reg.F |= H_FLAG; /* XXX */
            continue;
        case 0x15: /* DEC D */
            u->reg.D = u->reg.D - 1;

            /* set_flags(u, Z, N, H, C); */
            if (u->reg.D == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->reg.D & 0xF) == 0xF)
                u->reg.F |= H_FLAG; /* XXX */
            continue;
        case 0x25: /* DEC H */
            u->reg.H = u->reg.H - 1;

            /* set_flags(u, Z, N, H, C); */
            if (u->reg.H == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->reg.H & 0xF) == 0xF)
                u->reg.F |= H_FLAG; /* XXX */
            continue;
        case 0x35: /* DEC (HL) */
            u->mem.content[u->reg.HL]--;

            /* set_flags(u, Z, N, H, C); */
            if (u->mem.content[u->reg.HL] == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->mem.content[u->reg.HL] & 0xF) == 0xF)
                u->reg.F |= H_FLAG; /* XXX */
            continue;

        case 0x06: /* LD B,d8 */
            u->reg.B = m_read8(u);
            continue;
        case 0x16: /* LD D,d8 */
            u->reg.D = m_read8(u);
            continue;
        case 0x26: /* LD H,d8 */
            u->reg.H = m_read8(u);
            continue;
        case 0x36: /* LD (HL),d8 */
            m_set8(u, u->reg.HL, m_read8(u));
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
            u->reg.F |= C_FLAG;
            continue;

        case 0x08: /* LD (a16),SP */
            m_set8(u, m_read16(u), u->reg.SP);
            /* TODO(keyehzy): We need to roll our own */
            continue;

        case 0x18: /* JR r8 */ /* XXX signed? */
            u->mem.ptr += m_read8(u);
            continue;
        case 0x28: /* JR Z,d8 */
            if (u->reg.F & Z_FLAG)
            {
                u->mem.ptr += m_read8(u);
            }
            else
            {
                m_read8(u);
            }
            continue;
        case 0x38: /* JR C,d8 */
            if (u->reg.F & C_FLAG)
            {
                u->mem.ptr += m_read8(u);
            }
            else
            {
                m_read8(u);
            }
            continue;

        case 0x09: /* ADD HL,BC */
        {
            uint32_t res = (uint32_t)(u->reg.HL + u->reg.BC);
            uint32_t wrap =
                (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.BC & 0xFFF));
            u->reg.HL = (uint16_t)res;

            u->reg.F &= ~N_FLAG;
            if (wrap > 0x0FF)
                u->reg.F |= H_FLAG;
            if (res > 0xFFFF)
                u->reg.F |= C_FLAG;
            continue;
        }
        case 0x19: /* ADD HL,DE */
        {
            uint32_t res = (uint32_t)(u->reg.HL + u->reg.DE);
            uint32_t wrap =
                (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.DE & 0xFFF));
            u->reg.HL = (uint16_t)res;

            u->reg.F &= ~N_FLAG;
            if (wrap > 0x0FF)
                u->reg.F |= H_FLAG;
            if (res > 0xFFFF)
                u->reg.F |= C_FLAG;
            continue;
        }
        case 0x29: /* ADD HL, HL */
        {
            uint32_t res = (uint32_t)(u->reg.HL + u->reg.HL);
            uint32_t wrap =
                (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.HL & 0xFFF));
            u->reg.HL = (uint16_t)res;

            u->reg.F &= ~N_FLAG;
            if (wrap > 0x0FF)
                u->reg.F |= H_FLAG;
            if (res > 0xFFFF)
                u->reg.F |= C_FLAG;
            continue;
        }
        case 0x39: /* ADD HL,SP */
        {
            uint32_t res = (uint32_t)(u->reg.HL + u->reg.SP);
            uint32_t wrap =
                (uint32_t)((u->reg.HL & 0xFFF) + (u->reg.SP & 0xFFF));
            u->reg.HL = (uint16_t)res;

            u->reg.F &= ~N_FLAG;
            if (wrap > 0x0FF)
                u->reg.F |= H_FLAG;
            if (res > 0xFFFF)
                u->reg.F |= C_FLAG;
            continue;
        }

        case 0x0A: /* LD A, (BC) */
            u->reg.A = u->mem.content[u->reg.BC];
            continue;
        case 0x1A: /* LD A, (DE) */
            u->reg.A = u->mem.content[u->reg.DE];
            continue;
        case 0x2A: /* LD A,(HL+) */
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

            if (u->reg.C == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->reg.C & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;
        case 0x1C: /* INC E */
            u->reg.E++;

            if (u->reg.E == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->reg.E & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;
        case 0x2C: /* INC L */
            u->reg.L++;

            if (u->reg.L == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->reg.L & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;
        case 0x3C: /* INC A */
            u->reg.A++;

            if (u->reg.A == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            if ((u->reg.A & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;

        case 0x0D: /* DEC C */
            u->reg.C--;

            if (u->reg.C == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->reg.C & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;
        case 0x1D: /* DEC E */
            u->reg.E--;

            if (u->reg.E == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->reg.E & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;
        case 0x2D: /* DEC L */
            u->reg.L--;

            if (u->reg.L == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->reg.L & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;
        case 0x3D: /* DEC A */
            u->reg.A--;

            if (u->reg.A == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F |= N_FLAG;
            if ((u->reg.A & 0xF) == 0)
                u->reg.F |= H_FLAG;
            continue;

        case 0x0E: /* LD C,d8 */
            u->reg.C = m_read8(u);
            continue;
        case 0x1E: /* LD E,d8 */
            u->reg.E = m_read8(u);
            continue;
        case 0x2E: /* LD L,d8 */
            u->reg.L = m_read8(u);
            continue;
        case 0x3E: /* LD A,d8 */
            u->reg.A = m_read8(u);
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
            if (!(u->reg.F & Z_FLAG))
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;
        case 0xD0: /* RET NC */
            if (!(u->reg.F & C_FLAG))
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;

        case 0xE0: /* LDH (a8),A */ /* SIGN XXX */
            m_set8(u, 0xFF00 + m_read8(u), u->reg.A);
            continue;
        case 0xF0: /* LDH A,(a8) */ /* SIGN XXX */
            u->reg.A = u->mem.content[0xFF00 + m_read8(u)];
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
            if (!(u->reg.F & Z_FLAG))
            {
                u->mem.ptr = m_read16(u);
            }
            else
            {
                m_read16(u);
            }
            continue;
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
            continue;

        case 0xE2: /* LD (C), A */
            m_set8(u, 0xFF00 + u->reg.C, u->reg.A);
            continue;

        case 0xF2: /* LD A,(C) */
            u->reg.A = u->mem.content[0xFF00 + u->reg.C];
            continue;

        case 0xC3: /* JP a16 */
            u->mem.ptr = m_peek16(u);
            continue;

        case 0xC4: /* CALL a16 */
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_read16(u);
            continue;
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
            u->reg.A += m_read8(u);
            continue;
        case 0xD6: /* SUB A,d8 */
            u->reg.A -= m_read8(u);
            continue;
        case 0xE6: /* AND A,d8 */
            u->reg.A = u->reg.A & m_read8(u);
            continue;
        case 0xF6: /* OR,d8 */
            u->reg.A = u->reg.A | m_read8(u);
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
            if (u->reg.F & Z_FLAG)
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;
        case 0xD8: /* RET C */
            if (u->reg.F & C_FLAG)
            {
                u->mem.ptr = s_pop16(u->st);
            }
            continue;

        case 0xE8: /* ADD SP,r8 */
            u->reg.SP += m_read8(u);

            /* set_flags(u, Z, N, H, C); */
            u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            u->reg.F |= H_FLAG; /* XXX */
            u->reg.F |= C_FLAG; /* XXX */
            continue;

        case 0xF8: /* LD HL,SP+r8 */
            u->reg.HL = u->reg.SP + m_read8(u);

            /* set_flags(u, Z, N, H, C); */
            u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            u->reg.F |= H_FLAG; /* XXX */
            u->reg.F |= C_FLAG; /* XXX */
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
            if (u->reg.F & Z_FLAG)
            {
                u->mem.ptr = m_read16(u);
            }
            continue;
        case 0xDA: /* JP C,a16 */
            if (u->reg.F & Z_FLAG)
            {
                u->mem.ptr = m_read16(u);
            }
            continue;

        case 0xEA: /* LD (a16),A */
            m_set8(u, m_read16(u), u->reg.A);
            continue;
        case 0xFA: /* LD A,(a16) */
            u->reg.A = u->mem.content[m_read16(u)];
            continue;

        case 0xCC: /* CALL Z,a16 */
            if (u->reg.F & Z_FLAG)
            {
                s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_peek16(u);
            }
            continue;
        case 0xDC: /* CALL C,a16 */
            if (u->reg.F & C_FLAG)
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
            continue;
        }
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
            continue;
        }
        case 0xEE: /* XOR A,d8 */
            u->reg.A ^= m_read8(u);

            /* set_flags(u, Z, N, H, C); */
            if (u->reg.A == 0)
                u->reg.F |= Z_FLAG;
            u->reg.F &= ~N_FLAG;
            u->reg.F |= H_FLAG;
            u->reg.F |= C_FLAG;
            continue;
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
            continue;
        }

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
    return 0;
}
