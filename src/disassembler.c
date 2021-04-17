#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>

static char *letter_from_seq(uint8 byte)
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

static void PREFIX_CB_CASE(uint8 byte)
{
    char *letter = letter_from_seq(byte);
    switch (byte >> 4)
    {
    case 0x0:
        if (byte < 0x8)
        {
            printf("\t\tRLC %s", letter);
        }
        else
        {
            printf("\t\tRRC %s", letter);
        }
        break;
    case 0x1:
        if (byte < 0x8)
        {
            printf("\t\tRL %s", letter);
        }
        else
        {
            printf("\t\tRR %s", letter);
        }
        break;
    case 0x2:
        if (byte < 0x8)
        {
            printf("\t\tSLA %s", letter);
        }
        else
        {
            printf("\t\tSRA %s", letter);
        }
        break;
    case 0x3:
        if (byte < 0x8)
        {
            printf("\t\tSWAP %s", letter);
        }
        else
        {
            printf("\t\tSRL %s", letter);
        }
        break;
    case 0x4:
        if (byte < 0x8)
        {
            printf("\t\tBIT 0,%s", letter);
        }
        else
        {
            printf("\t\tBIT 1,%s", letter);
        }
        break;
    case 0x5:
        if (byte < 0x8)
        {
            printf("\t\tBIT 2,%s", letter);
        }
        else
        {
            printf("\t\tBIT 3,%s", letter);
        }
        break;
    case 0x6:
        if (byte < 0x8)
        {
            printf("\t\tBIT 4,%s", letter);
        }
        else
        {
            printf("\t\tBIT 5,%s", letter);
        }
        break;
    case 0x7:
        if (byte < 0x8)
        {
            printf("\t\tBIT 6,%s", letter);
        }
        else
        {
            printf("\t\tBIT 7,%s", letter);
        }
        break;
    case 0x8:
        if (byte < 0x8)
        {
            printf("\t\tRES 0,%s", letter);
        }
        else
        {
            printf("\t\tRES 1,%s", letter);
        }
        break;
    case 0x9:
        if (byte < 0x8)
        {
            printf("\t\tRES 2,%s", letter);
        }
        else
        {
            printf("\t\tRES 3,%s", letter);
        }
        break;
    case 0xA:
        if (byte < 0x8)
        {
            printf("\t\tRES 4,%s", letter);
        }
        else
        {
            printf("\t\tRES 5,%s", letter);
        }
        break;
    case 0xB:
        if (byte < 0x8)
        {
            printf("\t\tRES 6,%s", letter);
        }
        else
        {
            printf("\t\tRES 7,%s", letter);
        }
        break;
    case 0xC:
        if (byte < 0x8)
        {
            printf("\t\tSET 0,%s", letter);
        }
        else
        {
            printf("\t\tSET 1,%s", letter);
        }
        break;
    case 0xD:
        if (byte < 0x8)
        {
            printf("\t\tSET 2,%s", letter);
        }
        else
        {
            printf("\t\tSET 3,%s", letter);
        }
        break;
    case 0xE:
        if (byte < 0x8)
        {
            printf("\t\tSET 4,%s", letter);
        }
        else
        {
            printf("\t\tSET 5,%s", letter);
        }
        break;
    case 0xF:
        if (byte < 0x8)
        {
            printf("\t\tSET 6,%s", letter);
        }
        else
        {
            printf("\t\tSET 7,%s", letter);
        }
        break;
    default:
        exit(1);
    }
}

static void LD_B_C(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tLD B, %s\n", letter);
    }
    else
    {
        printf("\t\tLD C, %s\n", letter);
    }
}

static void LD_D_E(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tLD D, %s\n", letter);
    }
    else
    {
        printf("\t\tLD E, %s\n", letter);
    }
}

static void LD_H_L(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tLD H, %s\n", letter);
    }
    else
    {
        printf("\t\tLD L, %s\n", letter);
    }
}

static void LD_HL_A(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tLD (HL), %s\n", letter);
    }
    else
    {
        printf("\t\tLD A, %s\n", letter);
    }
}

static void ADD_ADC_CASE(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tADD A,%s\n", letter);
    }
    else
    {
        printf("\t\tADC A,%s\n", letter);
    }
}

static void SUB_SBC_CASE(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tSUB A,%s\n", letter);
    }
    else
    {
        printf("\t\tSBC A,%s\n", letter);
    }
}

static void AND_XOR_CASE(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tAND A,%s\n", letter);
    }
    else
    {
        printf("\t\tXOR A,%s\n", letter);
    }
}

static void OR_CP_CASE(uint8 byte)
{
    char *letter = letter_from_seq(byte);

    if (byte < 0x8)
    {
        printf("\t\tOR A,%s\n", letter);
    }
    else
    {
        printf("\t\tCP A,%s\n", letter);
        /* no result */
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

        printf("$%04x\t\t$%02x", u->mem.ptr, m_peek8(u));
        uint8 op = m_read8(u);

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
            printf(" $%02x", m_peek8(u));
            PREFIX_CB_CASE(m_read8(u));
            printf("\n");
            continue;
        case 0xF3:
            puts("\t\tDI");
            continue;
        case 0xFB:
            puts("\t\tEI");
            continue;

        case 0x20: /* JR r8 */
            printf(" $%02x\t\tJR NZ (Z),$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        case 0x30:
            printf(" $%02x\t\tJR NC (C),$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;

        case 0x01: /* LD reg,d16 */
            printf(" $%04x\tLD BC,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;
        case 0x11:
            printf(" $%04x\tLD DE,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;
        case 0x21:
            printf(" $%04x\tLD HL,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;
        case 0x31:
            printf(" $%04x\tLD SP,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;

        case 0x02: /* LD (),A */
            printf("\t\tLD (BC),A\n");
            continue;
        case 0x12:
            printf("\t\tLD (DE),A\n");
            continue;
        case 0x22:
            printf("\t\tLD (HL+),A\n");
            continue;

        case 0x32:
            printf("\t\tLD (HL-),A\n");
            continue;

        case 0x03: /* INC 2 byte register */
            printf("\t\tINC BC\n");
            continue;
        case 0x13:
            printf("\t\tINC DE\n");
            continue;
        case 0x23:
            printf("\t\tINC HL\n");
            continue;
        case 0x33:
            printf("\t\tINC SP\n");
            continue;

        case 0x04:
        { /* INC 1 byte register */
            printf("\t\tINC B\n");
            continue;
        }
        case 0x14:
        {
            printf("\t\tINC D\n");
            continue;
        }
        case 0x24:
        {
            printf("\t\tINC H\n");
            continue;
        }
        case 0x34:
        {
            printf("\t\tINC (HL)\n");
            continue;
        }

        case 0x05:
        { /* DEC 1 byte register */
            printf("\t\tDEC B\n");
            continue;
        }
        case 0x15:
        {
            printf("\t\tDEC D\n");
            continue;
        }
        case 0x25:
        {
            printf("\t\tDEC H\n");
            continue;
        }
        case 0x35:
        {
            printf("\t\tDEC (HL)\n");
            continue;
        }

        case 0x06:
        { /* LD 1 byte register,d8 */
            printf(" $%02x\t\tLD B,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0x16:
        {
            printf(" $%02x\t\tLD D,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0x26:
        {
            printf(" $%02x\t\tLD H,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0x36:
            printf(" $%02x\t\tLD (HL),$%02x\n", m_peek8(u), m_peek8(u));
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
            continue;
        }

        case 0x27: /* decimal adjust A */
            puts("\t\tDAA");
            continue;

        case 0x37: /* set carry flag */
            printf("\t\tSCF (FLAG C)\n");
            continue;

        case 0x08: /* LD (a16),SP */
            printf(" $%04x\tLD ($%04x),SP\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;

        case 0x18: /* JR r8 */
            printf(" $%02x\t\tJR $%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        case 0x28:
            printf(" $%02x\t\tJR Z (Z),$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        case 0x38:
            printf(" $%02x\t\tJR C (C),$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;

        case 0x09: /* add HL to 2 byte */
            printf("\t\tADD HL,BC\n");
            continue;
        case 0x19:
            printf("\t\tADD HL,DE\n");
            continue;
        case 0x29:
            printf("\t\tADD HL,HL\n");
            continue;
        case 0x39:
            printf("\t\tADD HL,SP\n");
            continue;

        case 0x0A:
        { /* load A to (2 byte) */
            printf("\t\tLD A, (BC)\n");
            continue;
        }
        case 0x1A:
        {
            printf("\t\tLD A, (DE)\n");
            continue;
        }
        case 0x2A:
            printf("\t\tLD A, (HL+)\n");
            continue;
        case 0x3A:
        {
            printf("\t\tLD A, (HL-)\n");
            continue;
        }

        case 0x0B: /* DEC 2 byte register */
            printf("\t\tDEC BC\n");
            continue;
        case 0x1B:
            printf("\t\tDEC DE\n");
            continue;
        case 0x2B:
            printf("\t\tDEC HL\n");
            continue;
        case 0x3B:
            printf("\t\tDEC SP\n");
            continue;

        case 0x0C:
        { /* INC 1 byte register */
            printf("\t\tINC C\n");
            continue;
        }
        case 0x1C:
        {
            printf("\t\tINC E\n");
            continue;
        }
        case 0x2C:
        {
            printf("\t\tINC L\n");
            continue;
        }
        case 0x3C:
        {
            printf("\t\tINC A\n");
            continue;
        }

        case 0x0D:
        { /* DEC 1 byte register */
            printf("\t\tDEC C\n");
            continue;
        }
        case 0x1D:
        {
            printf("\t\tDEC E\n");
            continue;
        }
        case 0x2D:
        {
            printf("\t\tDEC L\n");
            continue;
        }
        case 0x3D:
        {
            printf("\t\tDEC A\n");
            continue;
        }

        case 0x0E:
        { /* load 1 byte,d8 */
            printf(" $%02x\t\tLD C,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0x1E:
        {
            printf(" $%02x\t\tLD E,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0x2E:
        {
            printf(" $%02x\t\tLD L,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0x3E:
        {
            printf(" $%02x\t\tLD A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }

        case 0x0F: /* 8bit rotation/shift */
            puts("\t\tRRCA");
            continue;
        case 0x1F:
        {
            printf("\t\tRRA (A)\n");
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
            LD_B_C(op & 0x0F);
            continue;
        case 0x5:
            LD_D_E(op & 0x0F);
            continue;
        case 0x6:
            LD_H_L(op & 0x0F);
            continue;
        case 0x7:
            LD_HL_A(op & 0x0F);
            continue;
        }

        switch (op >> 4) /* ROWS 8-B */
        {
        case 0x8: /* ADD instruction */
            ADD_ADC_CASE(op & 0x0F);
            continue;
        case 0x9: /* SUB instruction */
            SUB_SBC_CASE(op & 0x0F);
            continue;
        case 0xA: /* AND instruction */
            AND_XOR_CASE(op & 0x0F);
            continue;
        case 0xB: /* OR instruction */
            OR_CP_CASE(op & 0x0F);
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
            printf(" $%02x\t\tLDH ($%02x),A\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        case 0xF0:
        {
            printf(" $%02x\t\tLDH A,($%02x)\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }

        case 0xC1: /* register POP */
            puts("\t\tPOP BC");
            continue;
        case 0xD1:
            puts("\t\tPOP DE");
            continue;
        case 0xE1:
            puts("\t\tPOP HL");
            continue;
        case 0xF1:
            puts("\t\tPOP AF");
            continue;

        case 0xC2: /* jp a16 */
            printf(" $%04x\tJP NZ,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;
        case 0xD2:
            printf(" $%04x\tJP NC,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;

        case 0xE2: /* load address to register */
            printf("\t\tLD (C),A\n");
            continue;

        case 0xF2:
        {
            printf("\t\tLD A,(C)\n");
            continue;
        }

        case 0xC3: /* JP a16 */
            printf(" $%04x\tJP $%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;

        case 0xC4: /* CALL a16 */
            printf(" $%04x\tCALL NZ,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;
        case 0xD4:
            printf(" $%04x\tCALL NC,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;

        case 0xC5: /* register PUSH */
            puts("\t\tPUSH BC");
            continue;
        case 0xD5:
            puts("\t\tPUSH DE");
            continue;
        case 0xE5:
            puts("\t\tPUSH HL");
            continue;
        case 0xF5:
            puts("\t\tPUSH AF");
            continue;

        case 0xC6:
        { /* d8 arithmetic */
            printf(" $%02x\t\tADD A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0xD6:
        {
            printf(" $%02x\t\tSUB A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0xE6:
        {
            printf(" $%02x\t\tAND A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0xF6:
        {
            printf(" $%02x\t\tOR A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }

        case 0xC7: /* RST (restarts) */
            puts("\t\tRST $00");
            continue;
        case 0xD7:
            puts("\t\tRST $10");
            continue;
        case 0xE7:
            puts("\t\tRST $20");
            continue;
        case 0xF7:
            puts("\t\tRST $30");
            continue;

        case 0xC8: /* return flag */
            puts("\t\tRET Z");
            continue;
        case 0xD8:
            puts("\t\tRET C");
            continue;

        case 0xE8:
            /* add SP, r8 */
            printf(" $%02x\tADD SP,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;

        case 0xF8: /* load HL,SP+r8 */
            printf(" $%02x\t\tLD HL,SP+$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;

        case 0xC9: /* return */
            puts("\t\tRET");
            continue;
        case 0xD9:
            puts("\t\tRETI");
            /* enable interrupts? */
            continue;

        case 0xE9: /* jump address */
            puts("\t\tJP (HL)");
            continue;

        case 0xF9: /* load 2 byte */
            puts("\t\tLD SP,HL");
            continue;

        case 0xCA: /* jump flag,a16 */
            puts("\t\tJP Z,a16");
            continue;
        case 0xDA:
            puts("\t\tJP C,a16");
            continue;

        case 0xEA: /* load a16 to register*/
            puts("\t\tLD (a16),A");
            continue;
        case 0xFA:
        {
            puts("\t\tLD A,(a16)");
            m_read16(u);
            continue;
        }

        case 0xCC: /* call a16 */
            printf(" $%04x\tCALL Z,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;
        case 0xDC:
            printf(" $%04x\tCALL C,$%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;
        case 0xCD:
            printf(" $%04x\tCALL $%04x\n", m_peek16(u), m_peek16(u));
            m_read16(u);
            continue;

        case 0xCE:
        { /* extra arithmetic d8 */
            printf(" $%02x\t\tADC A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0xDE:
        {
            printf(" $%02x\t\tSBC A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0xEE:
        {
            printf(" $%02x\t\tXOR A,$%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }
        case 0xFE:
        {
            printf(" $%02x\t\tCP $%02x\n", m_peek8(u), m_peek8(u));
            m_read8(u);
            continue;
        }

        case 0xCF: /* RST (restarts) */
            puts("\t\tRST $08");
            continue;
        case 0xDF:
            puts("\t\tRST $18");
            continue;
        case 0xEF:
            puts("\t\tRST $28");
            continue;
        case 0xFF:
            puts("\t\tRST $38");
            continue;
        }

        printf("\t\tdunno $%02x\n", op);
    }
    return 1;
}
