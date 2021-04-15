#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>

char *letter_from_seq(uint8 byte)
{
    switch (byte % 0x8)
    {
    case 0x0:
        return "B";
        break;
    case 0x1:
        return "C";
        break;
    case 0x2:
        return "D";
        break;
    case 0x3:
        return "E";
        break;
    case 0x4:
        return "H";
        break;
    case 0x5:
        return "L";
        break;
    case 0x6:
        return "(HL)";
        break;
    case 0x7:
        return "A";
        break;
    default:
        exit(1);
    }
}

uint8 value_from_letter_seq(CPU *u, uint8 byte)
{
    switch (byte % 0x8)
    {
    case 0x0:
        return reg(u, 'B');
    case 0x1:
        return reg(u, 'C');
    case 0x2:
        return reg(u, 'D');
    case 0x3:
        return reg(u, 'E');
    case 0x4:
        return reg(u, 'H');
    case 0x5:
        return reg(u, 'L');
    case 0x6:
        return u->mem.content[u->reg.HL];
    case 0x7:
        return reg(u, 'A');
    default:
        exit(1);
    }
}

void LD_B_C(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tLD B, %s\n", letter);
        set_reg(u, 'B', value_of_letter);
    }
    else
    {
        printf("\t\tLD C, %s\n", letter);
        set_reg(u, 'C', value_of_letter);
    }
}

void LD_D_E(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tLD D, %s\n", letter);
        set_reg(u, 'D', value_of_letter);
    }
    else
    {
        printf("\t\tLD E, %s\n", letter);
        set_reg(u, 'E', value_of_letter);
    }
}

void LD_H_L(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tLD H, %s\n", letter);
        set_reg(u, 'H', value_of_letter);
    }
    else
    {
        printf("\t\tLD L, %s\n", letter);
        set_reg(u, 'L', value_of_letter);
    }
}

void LD_HL_A(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tLD (HL), %s\n", letter);
        /* u->mem.content[u->reg.HL] = value_of_letter; XXX */
    }
    else
    {
        printf("\t\tLD A, %s\n", letter);
        set_reg(u, 'A', value_of_letter);
    }
}

void ADD_ADC_CASE(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tADD A,%s\n", letter);
        set_reg(u, 'A', reg(u, 'A') + value_of_letter);
        /* set_flags(u, Z, N, H, C); */
    }
    else
    {
        printf("\t\tADC A,%s\n", letter);
        set_reg(u, 'A', reg(u, 'A') + value_of_letter + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
    }
}

void SUB_SBC_CASE(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tSUB A,%s\n", letter);
        set_reg(u, 'A', reg(u, 'A') - value_of_letter);
        /* set_flags(u, Z, N, H, C); */
    }
    else
    {
        printf("\t\tSBC A,%s\n", letter);
        set_reg(u, 'A', reg(u, 'A') - (value_of_letter + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
    }
}

void AND_XOR_CASE(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tAND A,%s\n", letter);
        set_reg(u, 'A', reg(u, 'A') & value_of_letter);
        /* set_flags(u, Z, N, H, C); */
    }
    else
    {
        printf("\t\tXOR A,%s\n", letter);
        set_reg(u, 'A', reg(u, 'A') ^ value_of_letter);
        /* set_flags(u, Z, N, H, C); */
    }
}

void OR_CP_CASE(CPU *u, uint8 byte)
{
    char *letter = letter_from_seq(byte);
    uint8 value_of_letter = value_from_letter_seq(u, byte);

    if (byte < 0x8)
    {
        printf("\t\tOR A,%s\n", letter);
        set_reg(u, 'A', reg(u, 'A') | value_of_letter);
        /* set_flags(u, Z, N, H, C); */
    }
    else
    {
        printf("\t\tCP A,%s\n", letter);
        /* no result */
        /* set_flags(u, Z, N, H, C); */
    }
}

int disassemble_rom(CPU *u)
{
    printf("ADDRESS\t\tOPCODE\t\tINSTRUCTION\n");

    u->mem.ptr = 0x000; /* entry point */

    while (1)
    {
        if (u->mem.ptr == 0x8000)
        {
            puts("END OF ROM");
            return 0;
        }

        if (u->mem.ptr == 0x104)
        {
            printf("\t~~~~SKIP COPYRIGHT~~~~\n");
            u->mem.ptr = 0x150;
            continue;
        }

        printf("$%04x\t\t$%02x", u->mem.ptr, m_peek8(u, u->mem.ptr));
        uint8 op = m_consume8(u);

        switch (op)
        {
        case 0x0: /* misc */
            puts("\t\tNOP");
            continue;
        case 0x10:
            puts("\t\tSTOP");
            continue;
        case 0x76:
            puts("\t\tHALT");
            continue;
        case 0xCB:
            puts("\t\tPREFIX CB");
            m_consume8(u); /* XXX */
            continue;
        case 0xF3:
            puts("\t\tDI");
            continue;
        case 0xFB:
            puts("\t\tEI");
            continue;

        case 0x20: /* JR r8 */
            printf(" $%02x\t\tJR NZ (Z),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            m_consume8(u); /* XXX */
            if (!get_flag(u, 'Z'))
            {
                /* u->mem.ptr += m_peek8(u, u->mem.ptr); XXX */
            }
            continue;
        case 0x30:
            printf(" $%02x\t\tJR NC (C),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            m_consume8(u); /* XXX */
            if (!get_flag(u, 'C'))
            {
                /* u->mem.ptr += m_peek8(u, u->mem.ptr); XXX */
            }
            continue;

        case 0x01: /* LD reg,d16 */
            printf(" $%04x\tLD BC,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            u->reg.BC = m_consume16(u);
            continue;
        case 0x11:
            printf(" $%04x\tLD DE,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            u->reg.DE = m_consume16(u);
            continue;
        case 0x21:
            printf(" $%04x\tLD HL,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            u->reg.HL = m_consume16(u);
            continue;
        case 0x31:
            printf(" $%04x\tLD SP,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            u->reg.SP = m_consume16(u);
            continue;

        case 0x02: /* LD (),A */
            printf("\t\tLD (BC),A\n");
            /* u->mem.content[u->reg.BC] = reg(u, 'A'); XXX */
            continue;
        case 0x12:
            printf("\t\tLD (DE),A\n");
            /* u->mem.content[u->reg.DE] = reg(u, 'A'); XXX */
            continue;
        case 0x22:
            printf("\t\tLD (HL+),A\n");
            /* u->mem.content[u->reg.HL++] = reg(u, 'A'); XXX */
            continue;

        case 0x32:
            printf("\t\tLD (SP-),A\n");
            /* u->mem.content[u->reg.SP--] = reg(u, 'A'); XXX */
            continue;

        case 0x03: /* INC 2 byte register */
            printf("\t\tINC BC\n");
            u->reg.BC++;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x13:
            printf("\t\tINC DE\n");
            u->reg.DE++;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x23:
            printf("\t\tINC HL\n");
            u->reg.HL++;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x33:
            printf("\t\tINC SP\n");
            u->reg.SP++;
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0x04:
        { /* INC 1 byte register */
            printf("\t\tINC B\n");
            set_reg(u, 'B', reg(u, 'B') + 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x14:
        {
            printf("\t\tINC D\n");
            set_reg(u, 'D', reg(u, 'D') + 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x24:
        {
            printf("\t\tINC H\n");
            set_reg(u, 'H', reg(u, 'H') + 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x34:
        {
            printf("\t\tINC (HL)\n");
            /* u->mem.content[u->reg.HL]++; XXX */
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x05:
        { /* DEC 1 byte register */
            printf("\t\tDEC B\n");
            set_reg(u, 'B', reg(u, 'B') - 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x15:
        {
            printf("\t\tDEC D\n");
            set_reg(u, 'D', reg(u, 'D') - 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x25:
        {
            printf("\t\tDEC H\n");
            set_reg(u, 'H', reg(u, 'H') - 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x35:
        {
            printf("\t\tDEC (HL)\n");
            /* u->mem.content[u->reg.HL]--; XXX */
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x06:
        { /* LD 1 byte register,d8 */
            printf(" $%02x\t\tLD B,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'B', m_consume8(u));
            continue;
        }
        case 0x16:
        {
            printf(" $%02x\t\tLD D,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'D', m_consume8(u));
            continue;
        }
        case 0x26:
        {
            printf(" $%02x\t\tLD H,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'H', m_consume8(u));
            continue;
        }
        case 0x36:
            printf(" $%02x\t\tLD (HL),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            /* u->mem.content[u->reg.HL] = m_consume8(u); XXX */
            continue;

        case 0x07: /* 8bit rotation/shift */
            puts("\t\tRLCA");
            continue;
        case 0x17:
        {
            /* see rotating section of
             * http://www.linux-kongress.org/2009/slides/compiler_survey_felix_von_leitner.pdf
             */
            printf("\t\tRLA (A)\n");
            set_reg(u, 'A', (reg(u, 'A') << 1) | (reg(u, 'A') >> 7));
            continue;
        }

        case 0x27: /* decimal adjust A */
            puts("\t\tDAA");
            continue;

        case 0x37: /* set carry flag */
            printf("\t\tSCF (FLAG C)\n");
            set_flag(u, 'C');
            continue;

        case 0x08: /* LD (a16),SP */
            printf(" $%04x\tLD ($%04x),SP\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u);                     /* XXX */
            /* u->reg.SP = u->mem.ptr++; XXX */ /* XXX SP */
            /* TODO(keyehzy): see if we use u->st->ptr too? */
            continue;

        case 0x18: /* JR r8 */
            printf(" $%02x\t\tJR $%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            m_consume8(u); /* XXX */
            /* u->mem.ptr += m_peek8(u, u->mem.ptr); XXX */
            continue;
        case 0x28:
            printf(" $%02x\t\tJR Z (Z),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            m_consume8(u); /* XXX */
            if (get_flag(u, 'Z'))
            {
                /* u->mem.ptr += m_peek8(u, u->mem.ptr); XXX */
            }
            continue;
        case 0x38:
            printf(" $%02x\t\tJR C (C),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            m_consume8(u); /* XXX */
            if (get_flag(u, 'C'))
            {
                /* u->mem.ptr += m_peek8(u, u->mem.ptr); XXX */
            }
            continue;

        case 0x09: /* add HL to 2 byte */
            printf("\t\tADD HL,BC\n");
            u->reg.HL += u->reg.BC;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x19:
            printf("\t\tADD HL,DE\n");
            u->reg.HL += u->reg.DE;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x29:
            printf("\t\tADD HL,HL\n");
            u->reg.HL += u->reg.HL;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x39:
            printf("\t\tADD HL,SP\n");
            u->reg.HL += u->reg.SP;
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0x0A:
        { /* load A to (2 byte) */
            printf("\t\tLD A, (BC)\n");
            set_reg(u, 'A', u->mem.content[u->reg.BC]);
            continue;
        }
        case 0x1A:
        {
            printf("\t\tLD A, (DE)\n");
            set_reg(u, 'A', u->mem.content[u->reg.DE]);
            continue;
        }
        case 0x2A:
            printf("\t\tLD A, (HL+)\n");
            set_reg(u, 'A', u->mem.content[u->reg.HL++]);
            continue;
        case 0x3A:
        {
            printf("\t\tLD A, (HL-)\n");
            set_reg(u, 'A', u->mem.content[u->reg.HL--]);
            continue;
        }

        case 0x0B: /* DEC 2 byte register */
            printf("\t\tDEC BC\n");
            u->reg.BC--;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x1B:
            printf("\t\tDEC DE\n");
            u->reg.DE--;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x2B:
            printf("\t\tDEC HL\n");
            u->reg.HL--;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x3B:
            printf("\t\tDEC SP\n");
            u->reg.SP--;
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0x0C:
        { /* INC 1 byte register */
            printf("\t\tINC C\n");
            set_reg(u, 'C', reg(u, 'C') + 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x1C:
        {
            printf("\t\tINC E\n");
            set_reg(u, 'E', reg(u, 'E') + 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x2C:
        {
            printf("\t\tINC L\n");
            set_reg(u, 'L', reg(u, 'L') + 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x3C:
        {
            printf("\t\tINC A\n");
            set_reg(u, 'A', reg(u, 'A') + 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x0D:
        { /* DEC 1 byte register */
            printf("\t\tDEC C\n");
            set_reg(u, 'C', reg(u, 'C') - 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x1D:
        {
            printf("\t\tDEC E\n");
            set_reg(u, 'E', reg(u, 'E') - 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x2D:
        {
            printf("\t\tDEC L\n");
            set_reg(u, 'L', reg(u, 'L') - 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x3D:
        {
            printf("\t\tDEC A\n");
            set_reg(u, 'A', reg(u, 'A') - 1);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x0E:
        { /* load 1 byte,d8 */
            printf(" $%02x\t\tLD C,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'C', m_consume8(u));
            continue;
        }
        case 0x1E:
        {
            printf(" $%02x\t\tLD E,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'E', m_consume8(u));
            continue;
        }
        case 0x2E:
        {
            printf(" $%02x\t\tLD L,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'L', m_consume8(u));
            continue;
        }
        case 0x3E:
        {
            printf(" $%02x\t\tLD A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', m_consume8(u));
            continue;
        }

        case 0x0F: /* 8bit rotation/shift */
            puts("\t\tRRCA");
            continue;
        case 0x1F:
        {
            printf("\t\tRRA (A)\n");
            set_reg(u, 'A', (reg(u, 'A') >> 1) | (reg(u, 'A') << 7));
            continue;
        }

        case 0x2F: /* complement */
            puts("\t\tCPL");
            continue;

        case 0x3F: /* complement carry flag */
            puts("\t\tSCF");
            continue;
        }

        switch (op >> 4) /* ROWS 4-7 (HALT excluded) */
        {
        case 0x4: /* LD instruction */
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
        case 0x8: /* ADD instruction */
            ADD_ADC_CASE(u, op & 0x0F);
            continue;
        case 0x9: /* SUB instruction */
            SUB_SBC_CASE(u, op & 0x0F);
            continue;
        case 0xA: /* AND instruction */
            AND_XOR_CASE(u, op & 0x0F);
            continue;
        case 0xB: /* OR instruction */
            OR_CP_CASE(u, op & 0x0F);
            continue;
        }

        switch (op)
        {
        case 0xC0: /* return */
            puts("\t\tRET NZ");
            continue;
        case 0xD0:
            puts("\t\tRET NC");
            continue;

        case 0xE0: /* put memory */
            printf(" $%02x\t\tLDH ($%02x),A\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            m_consume8(u); /* XXX */
            /* u->mem.content[0xFF00 + m_consume8(u)] = reg(u, 'A'); XXX */
            continue;
        case 0xF0:
        {
            printf(" $%02x\t\tLDH A,($%02x)\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', u->mem.content[0xFF00 + m_consume8(u)]);
            continue;
        }

        case 0xC1: /* register POP */
            puts("\t\tPOP BC");
            /* u->reg.BC = s_pop16(u->st); XXX */
            continue;
        case 0xD1:
            puts("\t\tPOP DE");
            /* u->reg.DE = s_pop16(u->st); XXX */
            continue;
        case 0xE1:
            puts("\t\tPOP HL");
            /* u->reg.HL = s_pop16(u->st); XXX */
            continue;
        case 0xF1:
            puts("\t\tPOP AF");
            /* u->reg.AF = s_pop16(u->st); XXX */
            continue;

        case 0xC2: /* jp a16 */
            printf(" $%04x\tJP NZ,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            continue;
        case 0xD2:
            printf(" $%04x\tJP NC,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            continue;

        case 0xE2: /* load address to register */
            printf("\t\tLD (C),A\n");
            /* u->mem.content[0xFF00 + reg(u, 'C')] = reg(u, 'A'); XXX */
            continue;

        case 0xF2:
        {
            printf("\t\tLD A,(C)\n");
            set_reg(u, 'A', reg(u, 'A') + u->mem.content[0xFF00 + reg(u, 'C')]);
            continue;
        }

        case 0xC3: /* JP a16 */
            printf(" $%04x\tJP $%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            /* u->mem.ptr = m_peek16(u, u->mem.ptr); */
            continue;

        case 0xC4: /* CALL a16 */
            printf(" $%04x\tCALL NZ,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            continue;
        case 0xD4:
            printf(" $%04x\tCALL NC,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            continue;

        case 0xC5: /* register PUSH */
            puts("\t\tPUSH BC");
            /* s_push16(u->st, u->reg.BC); XXX */
            continue;
        case 0xD5:
            puts("\t\tPUSH DE");
            /* s_push16(u->st, u->reg.DE); XXX */
            continue;
        case 0xE5:
            puts("\t\tPUSH HL");
            /* s_push16(u->st, u->reg.HL); XXX */
            continue;
        case 0xF5:
            puts("\t\tPUSH AF");
            /* s_push16(u->st, u->reg.AF); XXX */
            continue;

        case 0xC6:
        { /* d8 arithmetic */
            printf(" $%02x\t\tADD A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') + m_consume8(u));
            continue;
        }
        case 0xD6:
        {
            printf(" $%02x\t\tSUB A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') - m_consume8(u));
            continue;
        }
        case 0xE6:
        {
            printf(" $%02x\t\tAND A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') & m_consume8(u));
            continue;
        }
        case 0xF6:
        {
            printf(" $%02x\t\tOR A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') | m_consume8(u));
            continue;
        }

        case 0xC7: /* RST (restarts) */
            puts("\t\tRST $00");
            /* s_push16(u->st, u->mem.ptr); XXX */
            /* u->mem.ptr = 0x0000 + 0x00; XXX */
            continue;
        case 0xD7:
            puts("\t\tRST $10");
            /* s_push16(u->st, u->mem.ptr); XXX */
            /* u->mem.ptr = 0x0000 + 0x10; XXX */
            continue;
        case 0xE7:
            puts("\t\tRST $20");
            /* s_push16(u->st, u->mem.ptr); XXX */
            /* u->mem.ptr = 0x0000 + 0x20; XXX */
            continue;
        case 0xF7:
            puts("\t\tRST $30");
            /* s_push16(u->st, u->mem.ptr); XXX */
            /* u->mem.ptr = 0x0000 + 0x30; XXX */
            continue;

        case 0xC8: /* return flag */
            puts("\t\tRET Z");
            continue;
        case 0xD8:
            puts("\t\tRET C");
            continue;

        case 0xE8:
            /* add SP, r8 */
            printf(" $%02x\tADD SP,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            u->reg.SP += m_consume8(u);
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0xF8: /* load HL,SP+r8 */
            printf(" $%02x\t\tLD HL,SP+$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            m_consume8(u); /* XXX */
            continue;

        case 0xC9: /* return */
            puts("\t\tRET");
            /* u->mem.ptr = s_pop16(u->st); XXX */
            continue;
        case 0xD9:
            puts("\t\tRETI");
            /* u->mem.ptr = s_pop16(u->st); XXX */
            /* enable interrupts? */
            continue;

        case 0xE9: /* jump address */
            puts("\t\tJP (HL)");
            /* u->mem.ptr = u->mem.content[u->reg.HL]; */
            continue;

        case 0xF9: /* load 2 byte */
            puts("\t\tLD SP,HL");
            continue;

        case 0xCA: /* jump flag,a16 */
            puts("\t\tZ,a16");
            continue;
        case 0xDA:
            puts("\t\tC,a16");
            continue;

        case 0xEA: /* load a16 to register*/
            puts("\t\tLD (a16),A");
            /* u->mem.content[m_consume16(u)] = reg(u, 'A'); XXX */
            continue;
        case 0xFA:
        {
            puts("\t\tLD A,(a16)");
            set_reg(u, 'A', u->mem.content[m_consume16(u)]);
            continue;
        }

        case 0xCC: /* call a16 */
            printf(" $%04x\tCALL Z,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            if (get_flag(u, 'Z'))
            {
                /* s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_peek16(u, u->mem.ptr); XXX */
            }
            continue;
        case 0xDC:
            printf(" $%04x\tCALL C,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            if (get_flag(u, 'C'))
            {
                /* s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_peek16(u, u->mem.ptr); XXX */
            }
            continue;
        case 0xCD:
            printf(" $%04x\tCALL $%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            m_consume16(u); /* XXX */
            /* s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u, u->mem.ptr); XXX */
            continue;

        case 0xCE:
        { /* extra arithmetic d8 */
            printf(" $%02x\t\tADC A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') + (m_consume8(u) + get_flag(u, 'C')));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xDE:
        {
            printf(" $%02x\t\tSBC A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') - (m_consume8(u) + get_flag(u, 'C')));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xEE:
        {
            printf(" $%02x\t\tXOR A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') ^ m_consume8(u));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xFE:
        {
            printf(" $%02x\t\tCP $%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') - m_consume8(u));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0xCF: /* RST (restarts) */
            puts("\t\tRST $08");
            /* s_push16(u->st, u->mem.ptr); XXX */
            /* u->mem.ptr = 0x0000 + 0x08; XXX */
            continue;
        case 0xDF:
            puts("\t\tRST $18");
            /* s_push16(u->st, u->mem.ptr); */
            /* u->mem.ptr = 0x0000 + 0x18; XXX */
            continue;
        case 0xEF:
            puts("\t\tRST $28");
            /* s_push16(u->st, u->mem.ptr); XXX */
            /* u->mem.ptr = 0x0000 + 0x28; XXX */
            continue;
        case 0xFF:
            puts("\t\tRST $38");
            /* s_push16(u->st, u->mem.ptr); XXX */
            /* u->mem.ptr = 0x0000 + 0x38; XXX */
            continue;
        }

        printf("\t\tdunno $%02x\n", op);
    }
    return 1;
}
