#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>

void LD_B_C(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    {
        printf("\t\tLD B,B\n");
        set_reg(u, 'B', reg(u, 'B'));
        break;
    }
    case 0x1:
    {
        printf("\t\tLD B,C\n");
        set_reg(u, 'B', reg(u, 'C'));
        break;
    }
    case 0x2:
    {
        printf("\t\tLD B,D\n");
        set_reg(u, 'B', reg(u, 'D'));
        break;
    }
    case 0x3:
    {
        printf("\t\tLD B,E\n");
        set_reg(u, 'B', reg(u, 'E'));
        break;
    }
    case 0x4:
    {
        printf("\t\tLD B,H\n");
        set_reg(u, 'B', reg(u, 'H'));
        break;
    }
    case 0x5:
    {
        printf("\t\tLD B,L\n");
        set_reg(u, 'B', reg(u, 'L'));
        break;
    }
    case 0x6:
    {
        printf("\t\tLD B, (HL)\n");
        set_reg(u, 'B', u->mem.content[u->reg.HL]);
        break;
    }
    case 0x7:
    {
        printf("\t\tLD B,A\n");
        set_reg(u, 'B', reg(u, 'A'));
        break;
    }

    case 0x8:
    {
        printf("\t\tLD C,B\n");
        set_reg(u, 'C', reg(u, 'B'));
        break;
    }
    case 0x9:
    {
        printf("\t\tLD C,C\n");
        set_reg(u, 'C', reg(u, 'C'));
        break;
    }
    case 0xA:
    {
        printf("\t\tLD C,D\n");
        set_reg(u, 'C', reg(u, 'D'));
        break;
    }
    case 0xB:
    {
        printf("\t\tLD C,E\n");
        set_reg(u, 'C', reg(u, 'E'));
        break;
    }
    case 0xC:
    {
        printf("\t\tLD C,H\n");
        set_reg(u, 'C', reg(u, 'H'));
        break;
    }
    case 0xD:
    {
        printf("\t\tLD C,L\n");
        set_reg(u, 'C', reg(u, 'L'));
        break;
    }
    case 0xE:
    {
        printf("\t\tLD C, (HL)\n");
        set_reg(u, 'C', u->mem.content[u->reg.HL]);
        break;
    }
    case 0xF:
    {
        printf("\t\tLD C,L\n");
        set_reg(u, 'C', reg(u, 'A'));
        break;
    }
    }
}

void LD_D_E(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    {
        printf("\t\tLD D,B\n");
        set_reg(u, 'D', reg(u, 'B'));
        break;
    }
    case 0x1:
    {
        printf("\t\tLD D,C\n");
        set_reg(u, 'D', reg(u, 'C'));
        break;
    }
    case 0x2:
    {
        printf("\t\tLD D,D\n");
        set_reg(u, 'D', reg(u, 'D'));
        break;
    }
    case 0x3:
    {
        printf("\t\tLD D,E\n");
        set_reg(u, 'D', reg(u, 'E'));
        break;
    }
    case 0x4:
    {
        printf("\t\tLD D,H\n");
        set_reg(u, 'D', reg(u, 'H'));
        break;
    }
    case 0x5:
    {
        printf("\t\tLD D,L\n");
        set_reg(u, 'D', reg(u, 'L'));
        break;
    }
    case 0x6:
    {
        printf("\t\tLD D, (HL)\n");
        set_reg(u, 'D', u->mem.content[u->reg.HL]);
        break;
    }
    case 0x7:
    {
        printf("\t\tLD D,A\n");
        set_reg(u, 'D', reg(u, 'A'));
        break;
    }

    case 0x8:
    {
        printf("\t\tLD E,B\n");
        set_reg(u, 'E', reg(u, 'B'));
        break;
    }
    case 0x9:
    {
        printf("\t\tLD E,C\n");
        set_reg(u, 'E', reg(u, 'C'));
        break;
    }
    case 0xA:
    {
        printf("\t\tLD E,D\n");
        set_reg(u, 'E', reg(u, 'D'));
        break;
    }
    case 0xB:
    {
        printf("\t\tLD E,E\n");
        set_reg(u, 'E', reg(u, 'E'));
        break;
    }
    case 0xC:
    {
        printf("\t\tLD E,H\n");
        set_reg(u, 'E', reg(u, 'H'));
        break;
    }
    case 0xD:
    {
        printf("\t\tLD E,L\n");
        set_reg(u, 'E', reg(u, 'L'));
        break;
    }
    case 0xE:
    {
        printf("\t\tLD E, (HL)\n");
        set_reg(u, 'E', u->mem.content[u->reg.HL]);
        break;
    }
    case 0xF:
    {
        printf("\t\tLD E,A\n");
        set_reg(u, 'E', reg(u, 'A'));
        break;
    }
    }
}

void LD_H_L(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    {
        printf("\t\tLD H,B\n");
        set_reg(u, 'H', reg(u, 'B'));
        break;
    }
    case 0x1:
    {
        printf("\t\tLD H,C\n");
        set_reg(u, 'H', reg(u, 'C'));
        break;
    }
    case 0x2:
    {
        printf("\t\tLD H,D\n");
        set_reg(u, 'H', reg(u, 'D'));
        break;
    }
    case 0x3:
    {
        printf("\t\tLD H,E\n");
        set_reg(u, 'H', reg(u, 'E'));
        break;
    }
    case 0x4:
    {
        printf("\t\tLD H,H\n");
        set_reg(u, 'H', reg(u, 'H'));
        break;
    }
    case 0x5:
    {
        printf("\t\tLD H,L\n");
        set_reg(u, 'H', reg(u, 'L'));
        break;
    }
    case 0x6:
    {
        printf("\t\tLD H, (HL)\n");
        set_reg(u, 'H', u->mem.content[u->reg.HL]);
        break;
    }
    case 0x7:
    {
        printf("\t\tLD H,A\n");
        set_reg(u, 'H', reg(u, 'A'));
        break;
    }

    case 0x8:
    {
        printf("\t\tLD L,B\n");
        set_reg(u, 'L', reg(u, 'B'));
        break;
    }
    case 0x9:
    {
        printf("\t\tLD L,C\n");
        set_reg(u, 'L', reg(u, 'C'));
        break;
    }
    case 0xA:
    {
        printf("\t\tLD L,D\n");
        set_reg(u, 'L', reg(u, 'D'));
        break;
    }
    case 0xB:
    {
        printf("\t\tLD L,E\n");
        set_reg(u, 'L', reg(u, 'E'));
        break;
    }
    case 0xC:
    {
        printf("\t\tLD L,H\n");
        set_reg(u, 'L', reg(u, 'H'));
        break;
    }
    case 0xD:
    {
        printf("\t\tLD L,L\n");
        set_reg(u, 'L', reg(u, 'L'));
        break;
    }
    case 0xE:
    {
        printf("\t\tLD L, (HL)\n");
        set_reg(u, 'L', u->mem.content[u->reg.HL]);
        break;
    }
    case 0xF:
    {
        printf("\t\tLD L,A\n");
        set_reg(u, 'L', reg(u, 'A'));
        break;
    }
    }
}

void LD_HL_A(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    {
        printf("\t\tLD (HL),B\n");
        u->mem.content[u->reg.HL] = reg(u, 'B');
        break;
    }
    case 0x1:
    {
        printf("\t\tLD (HL),C\n");
        u->mem.content[u->reg.HL] = reg(u, 'C');
        break;
    }
    case 0x2:
    {
        printf("\t\tLD (HL),D\n");
        u->mem.content[u->reg.HL] = reg(u, 'D');
        break;
    }
    case 0x3:
    {
        printf("\t\tLD (HL),E\n");
        u->mem.content[u->reg.HL] = reg(u, 'E');
        break;
    }
    case 0x4:
    {
        printf("\t\tLD (HL),H\n");
        u->mem.content[u->reg.HL] = reg(u, 'H');
        break;
    }
    case 0x5:
    {
        printf("\t\tLD (HL),L\n");
        u->mem.content[u->reg.HL] = reg(u, 'L');
        break;
    }
    case 0x6:
    {
        puts("\t\tHALT should've been handled elsewhere.");
        exit(1);
    }
    case 0x7:
    {
        printf("\t\tLD (HL),A\n");
        u->mem.content[u->reg.HL] = reg(u, 'A');
        break;
    }

    case 0x8:
    {
        printf("\t\tLD A,B\n");
        set_reg(u, 'A', reg(u, 'B'));
        break;
    }
    case 0x9:
    {
        printf("\t\tLD A,C\n");
        set_reg(u, 'A', reg(u, 'C'));
        break;
    }
    case 0xA:
    {
        printf("\t\tLD A,D\n");
        set_reg(u, 'A', reg(u, 'D'));
        break;
    }
    case 0xB:
    {
        printf("\t\tLD A,E\n");
        set_reg(u, 'A', reg(u, 'E'));
        break;
    }
    case 0xC:
    {
        printf("\t\tLD A,H\n");
        set_reg(u, 'A', reg(u, 'H'));
        break;
    }
    case 0xD:
    {
        printf("\t\tLD A,L\n");
        set_reg(u, 'A', reg(u, 'L'));
        break;
    }
    case 0xE:
    {
        printf("\t\tLD A, (HL)\n");
        set_reg(u, 'A', u->mem.content[u->reg.HL]);
        break;
    }
    case 0xF:
    {
        printf("\t\tLD A,A\n");
        set_reg(u, 'A', reg(u, 'A'));
        break;
    }
    }
}

void ADD_ADC_CASE(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    { /* add B to A */
        printf("\t\tADD A,B\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* add C to A */
        printf("\t\tADD A,C\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* add D to A */
        printf("\t\tADD A,D\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'D'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* add E to A */
        printf("\t\tADD A,E\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'E'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* add H to A */
        printf("\t\tADD A,H\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'H'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* add L to A */
        printf("\t\tADD A,L\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'L'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* add (HL) to A */
        printf("\t\tADD A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') + u->mem.content[u->reg.HL]);
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* add A to A */
        printf("\t\tADD A,A\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'A'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* adc B to A */
        printf("\t\tADC A,B\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'B') + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* adc C to A */
        printf("\t\tADC A,C\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'C') + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* adc D to A */
        printf("\t\tADC A,D\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'D') + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* adc E to A */
        printf("\t\tADC A,E\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'E') + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* adc H to A */
        printf("\t\tADC A,H\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'H') + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* adc L to A */
        printf("\t\tADC A,L\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'L') + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* adc (HL) to A */
        printf("\t\tADC A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') + u->mem.content[u->reg.HL] + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* adc A to A */
        printf("\t\tADC A,A\n");
        set_reg(u, 'A', reg(u, 'A') + reg(u, 'A') + get_flag(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }
    }
}

void SUB_SBC_CASE(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    { /* sub B to A */
        printf("\t\tSUB A,B\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* sub C to A */
        printf("\t\tSUB A,C\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* sub D to A */
        printf("\t\tSUB A,D\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'D'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* sub E to A */
        printf("\t\tSUB A,E\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'E'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* sub H to A */
        printf("\t\tSUB A,H\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'H'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* sub L to A */
        printf("\t\tSUB A,L\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'L'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* sub (HL) to A */
        printf("\t\tSUB A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') - u->mem.content[u->reg.HL]);
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* sub A to A */
        printf("\t\tSUB A,A\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'A'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* sbc B to A */
        printf("\t\tSBC A,B\n");
        set_reg(u, 'A', reg(u, 'A') - (reg(u, 'B') + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* sbc C to A */
        printf("\t\tSBC A,C\n");
        set_reg(u, 'A', reg(u, 'A') - (reg(u, 'C') + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* sbc D to A */
        printf("\t\tSBC A,D\n");
        set_reg(u, 'A', reg(u, 'A') - (reg(u, 'D') + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* sbc E to A */
        printf("\t\tSBC A,E\n");
        set_reg(u, 'A', reg(u, 'A') - (reg(u, 'E') + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* sbc H to A */
        printf("\t\tSBC A,H\n");
        set_reg(u, 'A', reg(u, 'A') - (reg(u, 'H') + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* sbc L to A */
        printf("\t\tSBC A,L\n");
        set_reg(u, 'A', reg(u, 'A') - (reg(u, 'L') + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* sbc (HL) to A */
        printf("\t\tSBC A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') - (u->mem.content[u->reg.HL] + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* sbc A to A */
        printf("\t\tSBC A,A\n");
        set_reg(u, 'A', reg(u, 'A') - (reg(u, 'B') + get_flag(u, 'C')));
        /* set_flags(u, Z, N, H, C); */
        break;
    }
    }
}

void AND_XOR_CASE(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    { /* and B to A */
        printf("\t\tAND A,B\n");
        set_reg(u, 'A', reg(u, 'A') & reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* and C to A */
        printf("\t\tAND A,C\n");
        set_reg(u, 'A', reg(u, 'A') & reg(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* and D to A */
        printf("\t\tAND A,D\n");
        set_reg(u, 'A', reg(u, 'A') & reg(u, 'D'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* and E to A */
        printf("\t\tAND A,E\n");
        set_reg(u, 'A', reg(u, 'A') & reg(u, 'E'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* and H to A */
        printf("\t\tAND A,H\n");
        set_reg(u, 'A', reg(u, 'A') & reg(u, 'H'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* and L to A */
        printf("\t\tAND A,L\n");
        set_reg(u, 'A', reg(u, 'A') & reg(u, 'L'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* and (HL) to A */
        printf("\t\tAND A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') & u->mem.content[u->reg.HL]);
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* and A to A */
        printf("\t\tAND A,A\n");
        set_reg(u, 'A', reg(u, 'A') & reg(u, 'A'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* XOR B to A */
        printf("\t\tXOR A,B\n");
        set_reg(u, 'A', reg(u, 'A') ^ reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* XOR C to A */
        printf("\t\tXOR A,C\n");
        set_reg(u, 'A', reg(u, 'A') ^ reg(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* XOR D to A */
        printf("\t\tXOR A,D\n");
        set_reg(u, 'A', reg(u, 'A') ^ reg(u, 'D'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* XOR E to A */
        printf("\t\tXOR A,E\n");
        set_reg(u, 'A', reg(u, 'A') ^ reg(u, 'E'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* XOR H to A */
        printf("\t\tXOR A,H\n");
        set_reg(u, 'A', reg(u, 'A') ^ reg(u, 'H'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* XOR L to A */
        printf("\t\tXOR A,L\n");
        set_reg(u, 'A', reg(u, 'A') ^ reg(u, 'L'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* XOR (HL) to A */
        printf("\t\tXOR A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') ^ u->mem.content[u->reg.HL]);
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* XOR A to A */
        printf("\t\tXOR A,A\n");
        set_reg(u, 'A', reg(u, 'A') ^ reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }
    }
}

void OR_CP_CASE(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    { /* OR B to A */
        printf("\t\tOR A,B\n");
        set_reg(u, 'A', reg(u, 'A') | reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* OR C to A */
        printf("\t\tOR A,C\n");
        set_reg(u, 'A', reg(u, 'A') | reg(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* OR D to A */
        printf("\t\tOR A,D\n");
        set_reg(u, 'A', reg(u, 'A') | reg(u, 'D'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* OR E to A */
        printf("\t\tOR A,E\n");
        set_reg(u, 'A', reg(u, 'A') | reg(u, 'E'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* OR H to A */
        printf("\t\tOR A,H\n");
        set_reg(u, 'A', reg(u, 'A') | reg(u, 'H'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* OR L to A */
        printf("\t\tOR A,L\n");
        set_reg(u, 'A', reg(u, 'A') | reg(u, 'L'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* OR (HL) to A */
        printf("\t\tOR A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') | u->mem.content[u->reg.HL]);
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* OR A to A */
        printf("\t\tOR A,A\n");
        set_reg(u, 'A', reg(u, 'A') | reg(u, 'A'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* CP B to A */
        printf("\t\tCP A,B\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* CP C to A */
        printf("\t\tCP A,C\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'C'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* CP D to A */
        printf("\t\tCP A,D\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'D'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* CP E to A */
        printf("\t\tCP A,E\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'E'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* CP H to A */
        printf("\t\tCP A,H\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'H'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* CP L to A */
        printf("\t\tCP A,L\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'L'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* CP (HL) to A */
        printf("\t\tCP A, (HL)\n");
        set_reg(u, 'A', reg(u, 'A') - u->mem.content[u->reg.HL]);
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* CP A to A */
        printf("\t\tCP A,A\n");
        set_reg(u, 'A', reg(u, 'A') - reg(u, 'B'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }
    }
}

int disassemble_rom(CPU *u)
{
    printf("ADDRESS\t\tOPCODE\t\tINSTRUCTION\n");

    u->mem.ptr = 0x100; /* entry point */

    while (1)
    {
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
        case 0x77:
            puts("\t\tHALT");
            continue;
        case 0xCB:
            puts("\t\tPREFIX CB");
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
            if (!get_flag(u, 'Z'))
                u->mem.ptr += m_peek8(u, u->mem.ptr);
            continue;
        case 0x30:
            printf(" $%02x\tJR NC (C),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            if (!get_flag(u, 'C'))
                u->mem.ptr += m_peek8(u, u->mem.ptr);
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
            u->mem.content[u->reg.BC] = reg(u, 'A');
            continue;
        case 0x12:
            printf("\t\tLD (DE),A\n");
            u->mem.content[u->reg.DE] = reg(u, 'A');
            continue;
        case 0x22:
            printf("\t\tLD (HL+),A\n");
            u->mem.content[u->reg.HL++] = reg(u, 'A');
            continue;

        case 0x32:
            printf("\t\tLD (SP-),A\n");
            u->mem.content[u->reg.SP--] = reg(u, 'A');
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
            u->mem.content[u->reg.HL]++;
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
            u->mem.content[u->reg.HL]--;
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
            u->mem.content[u->reg.HL] = m_consume8(u);
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
            u->reg.SP = u->mem.ptr++; /* XXX SP */
            /* TODO(keyehzy): see if we use u->st->ptr too? */
            continue;

        case 0x18: /* JR r8 */
            printf(" $%02x\tJR $%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            u->mem.ptr += m_peek8(u, u->mem.ptr);
            continue;
        case 0x28:
            printf(" $%02x\tJR Z (Z),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            if (get_flag(u, 'Z'))
                u->mem.ptr += m_peek8(u, u->mem.ptr);
            continue;
        case 0x38:
            printf(" $%02x\tJR C (C),$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            if (get_flag(u, 'C'))
                u->mem.ptr += m_peek8(u, u->mem.ptr);
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
            printf(" $%02x\tLDH (\t$%02x),A\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            u->mem.content[0xFF00 + m_consume8(u)] = reg(u, 'A');
            continue;
        case 0xF0:
        {
            printf(" $%02x\tLDH A,($%02x)\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', u->mem.content[0xFF00 + m_consume8(u)]);
            continue;
        }

        case 0xC1: /* register POP */
            puts("\t\tPOP BC");
            u->reg.BC = s_pop16(u->st);
            continue;
        case 0xD1:
            puts("\t\tPOP DE");
            u->reg.DE = s_pop16(u->st);
            continue;
        case 0xE1:
            puts("\t\tPOP HL");
            u->reg.HL = s_pop16(u->st);
            continue;
        case 0xF1:
            puts("\t\tPOP AF");
            u->reg.AF = s_pop16(u->st);
            continue;

        case 0xC2: /* jp a16 */
            printf(" $%04x\tJP NZ,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            continue;
        case 0xD2:
            printf(" $%04x\tJP NC,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            continue;

        case 0xE2: /* load address to register */
            printf("\t\tLD (C),A\n");
            u->mem.content[0xFF00 + reg(u, 'C')] = reg(u, 'A');
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
            u->mem.ptr = m_peek16(u, u->mem.ptr);
            continue;

        case 0xC4: /* CALL a16 */
            printf(" $%04x\tCALL NZ,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            continue;
        case 0xD4:
            printf(" $%04x\tCALL NC,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            continue;

        case 0xC5: /* register PUSH */
            puts("\t\tPUSH BC");
            s_push16(u->st, u->reg.BC);
            continue;
        case 0xD5:
            puts("\t\tPUSH DE");
            s_push16(u->st, u->reg.DE);
            continue;
        case 0xE5:
            puts("\t\tPUSH HL");
            s_push16(u->st, u->reg.HL);
            continue;
        case 0xF5:
            puts("\t\tPUSH AF");
            s_push16(u->st, u->reg.AF);
            continue;

        case 0xC6:
        { /* d8 arithmetic */
            printf(" $%02x\tADD A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') + m_consume8(u));
            continue;
        }
        case 0xD6:
        {
            printf(" $%02x\tSUB A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') - m_consume8(u));
            continue;
        }
        case 0xE6:
        {
            printf(" $%02x\tAND A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') & m_consume8(u));
            continue;
        }
        case 0xF6:
        {
            printf(" $%02x\tOR A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') | m_consume8(u));
            continue;
        }

        case 0xC7: /* RST (restarts) */
            puts("\t\tRST $00");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x00;
            continue;
        case 0xD7:
            puts("\t\tRST $10");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x10;
            continue;
        case 0xE7:
            puts("\t\tRST $20");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x20;
            continue;
        case 0xF7:
            puts("\t\tRST $30");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x30;
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
            printf(" $%02x\tLD HL,SP+$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            continue;

        case 0xC9: /* return */
            puts("\t\tRET");
            u->mem.ptr = s_pop16(u->st);
            continue;
        case 0xD9:
            puts("\t\tRETI");
            u->mem.ptr = s_pop16(u->st);
            /* enable interrupts? */
            continue;

        case 0xE9: /* jump address */
            puts("\t\tJP (HL)");
            u->mem.ptr = u->mem.content[u->reg.HL];
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
            u->mem.content[m_consume16(u)] = reg(u, 'A');
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
            if (get_flag(u, 'Z'))
            {
                s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_peek16(u, u->mem.ptr);
            }
            continue;
        case 0xDC:
            printf(" $%04x\tCALL C,$%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            if (get_flag(u, 'C'))
            {
                s_push16(u->st, u->mem.ptr + 1);
                u->mem.ptr = m_peek16(u, u->mem.ptr);
            }
            continue;
        case 0xCD:
            printf(" $%04x\tCALL $%04x\n", m_peek16(u, u->mem.ptr),
                   m_peek16(u, u->mem.ptr));
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u, u->mem.ptr);
            continue;

        case 0xCE:
        { /* extra arithmetic d8 */
            printf(" $%02x\tADC A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') + (m_consume8(u) + get_flag(u, 'C')));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xDE:
        {
            printf(" $%02x\tSBC A,$%02x\n", m_peek8(u, u->mem.ptr),
                   m_peek8(u, u->mem.ptr));
            set_reg(u, 'A', reg(u, 'A') - (m_consume8(u) + get_flag(u, 'C')));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xEE:
        {
            printf(" $%02x\tXOR A,$%02x\n", m_peek8(u, u->mem.ptr),
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
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x08;
            continue;
        case 0xDF:
            puts("\t\tRST $18");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x18;
            continue;
        case 0xEF:
            puts("\t\tRST $28");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x28;
            continue;
        case 0xFF:
            puts("\t\tRST $38");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x38;
            continue;
        }

        printf("\t\tdunno $%02x\n", op);
    }
    return 1;
}
