#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>

void LD_B_C(CPU *u, uint8 byte)
{
    switch (byte)
    {
    case 0x0:
    {
        printf("LD B = 0x%x, B = 0x%x\n", reg(u, 'B'), reg(u, 'B'));
        uint8 B = reg(u, 'B');
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }
    case 0x1:
    {
        printf("LD B = 0x%x, C = 0x%x\n", reg(u, 'B'), reg(u, 'C'));
        uint8 B = reg(u, 'C');
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }
    case 0x2:
    {
        printf("LD B = 0x%x, D = 0x%x\n", reg(u, 'B'), reg(u, 'D'));
        uint8 B = reg(u, 'D');
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }
    case 0x3:
    {
        printf("LD B = 0x%x, E = 0x%x\n", reg(u, 'B'), reg(u, 'E'));
        uint8 B = reg(u, 'E');
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }
    case 0x4:
    {
        printf("LD B = 0x%x, H = 0x%x\n", reg(u, 'B'), reg(u, 'H'));
        uint8 B = reg(u, 'H');
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }
    case 0x5:
    {
        printf("LD B = 0x%x, L = 0x%x\n", reg(u, 'B'), reg(u, 'L'));
        uint8 B = reg(u, 'L');
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }
    case 0x6:
    {
        printf("LD B = 0x%x, (HL) = 0x%x\n", reg(u, 'B'), u->mem.content[u->reg.HL]);
        uint8 B = u->mem.content[u->reg.HL];
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }
    case 0x7:
    {
        printf("LD B = 0x%x, A = 0x%x\n", reg(u, 'B'), reg(u, 'A'));
        uint8 B = reg(u, 'A');
        u->reg.BC = reg_combine(B, reg(u, 'C'));
        break;
    }

    case 0x8:
    {
        printf("LD C = 0x%x, B = 0x%x\n", reg(u, 'C'), reg(u, 'B'));
        uint8 C = reg(u, 'B');
        u->reg.BC = reg_combine(reg(u, 'B'), C);
        break;
    }
    case 0x9:
    {
        printf("LD C = 0x%x, C = 0x%x\n", reg(u, 'C'), reg(u, 'C'));
        uint8 C = reg(u, 'C');
        u->reg.BC = reg_combine(reg(u, 'B'), C);
        break;
    }
    case 0xA:
    {
        printf("LD C = 0x%x, D = 0x%x\n", reg(u, 'C'), reg(u, 'D'));
        uint8 C = reg(u, 'D');
        u->reg.BC = reg_combine(reg(u, 'B'), C);
        break;
    }
    case 0xB:
    {
        printf("LD C = 0x%x, E = 0x%x\n", reg(u, 'C'), reg(u, 'E'));
        uint8 C = reg(u, 'E');
        u->reg.BC = reg_combine(reg(u, 'B'), C);
        break;
    }
    case 0xC:
    {
        printf("LD C = 0x%x, H = 0x%x\n", reg(u, 'C'), reg(u, 'H'));
        uint8 C = reg(u, 'H');
        u->reg.BC = reg_combine(reg(u, 'B'), C);
        break;
    }
    case 0xD:
    {
        printf("LD C = 0x%x, L = 0x%x\n", reg(u, 'C'), reg(u, 'L'));
        uint8 C = reg(u, 'L');
        u->reg.BC = reg_combine(reg(u, 'B'), C);
        break;
    }
    case 0xE:
    {
        printf("LD C = 0x%x, (HL) = 0x%x\n", reg(u, 'C'), u->mem.content[u->reg.HL]);
        uint8 C = u->mem.content[u->reg.HL];
        u->reg.BC = reg_combine(reg(u, 'B'), C);
        break;
    }
    case 0xF:
    {
        printf("LD C = 0x%x, L = 0x%x\n", reg(u, 'C'), reg(u, 'A'));
        uint8 C = reg(u, 'A');
        u->reg.BC = reg_combine(reg(u, 'B'), C);
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
        printf("LD D = 0x%x, B = 0x%x\n", reg(u, 'D'), reg(u, 'B'));
        uint8 D = reg(u, 'B');
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }
    case 0x1:
    {
        printf("LD D = 0x%x, C = 0x%x\n", reg(u, 'D'), reg(u, 'C'));
        uint8 D = reg(u, 'C');
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }
    case 0x2:
    {
        printf("LD D = 0x%x, D = 0x%x\n", reg(u, 'D'), reg(u, 'D'));
        uint8 D = reg(u, 'D');
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }
    case 0x3:
    {
        printf("LD D = 0x%x, E = 0x%x\n", reg(u, 'D'), reg(u, 'E'));
        uint8 D = reg(u, 'E');
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }
    case 0x4:
    {
        printf("LD D = 0x%x, H = 0x%x\n", reg(u, 'D'), reg(u, 'H'));
        uint8 D = reg(u, 'H');
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }
    case 0x5:
    {
        printf("LD D = 0x%x, L = 0x%x\n", reg(u, 'D'), reg(u, 'L'));
        uint8 D = reg(u, 'L');
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }
    case 0x6:
    {
        printf("LD D = 0x%x, (HL) = 0x%x\n", reg(u, 'D'), u->mem.content[u->reg.HL]);
        uint8 D = u->mem.content[u->reg.HL];
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }
    case 0x7:
    {
        printf("LD D = 0x%x, A = 0x%x\n", reg(u, 'D'), reg(u, 'A'));
        uint8 D = reg(u, 'A');
        u->reg.DE = reg_combine(D, reg(u, 'E'));
        break;
    }

    case 0x8:
    {
        printf("LD E = 0x%x, B = 0x%x\n", reg(u, 'E'), reg(u, 'B'));
        uint8 E = reg(u, 'B');
        u->reg.DE = reg_combine(reg(u, 'D'), E);
        break;
    }
    case 0x9:
    {
        printf("LD E = 0x%x, C = 0x%x\n", reg(u, 'E'), reg(u, 'C'));
        uint8 E = reg(u, 'C');
        u->reg.DE = reg_combine(reg(u, 'D'), E);
        break;
    }
    case 0xA:
    {
        printf("LD E = 0x%x, D = 0x%x\n", reg(u, 'E'), reg(u, 'D'));
        uint8 E = reg(u, 'D');
        u->reg.DE = reg_combine(reg(u, 'D'), E);
        break;
    }
    case 0xB:
    {
        printf("LD E = 0x%x, E = 0x%x\n", reg(u, 'E'), reg(u, 'E'));
        uint8 E = reg(u, 'E');
        u->reg.DE = reg_combine(reg(u, 'D'), E);
        break;
    }
    case 0xC:
    {
        printf("LD E = 0x%x, H = 0x%x\n", reg(u, 'E'), reg(u, 'H'));
        uint8 E = reg(u, 'H');
        u->reg.DE = reg_combine(reg(u, 'D'), E);
        break;
    }
    case 0xD:
    {
        printf("LD E = 0x%x, L = 0x%x\n", reg(u, 'E'), reg(u, 'L'));
        uint8 E = reg(u, 'L');
        u->reg.DE = reg_combine(reg(u, 'D'), E);
        break;
    }
    case 0xE:
    {
        printf("LD E = 0x%x, (HL) = 0x%x\n", reg(u, 'E'), u->mem.content[u->reg.HL]);
        uint8 E = u->mem.content[u->reg.HL];
        u->reg.DE = reg_combine(reg(u, 'D'), E);
        break;
    }
    case 0xF:
    {
        printf("LD E = 0x%x, A = 0x%x\n", reg(u, 'E'), reg(u, 'A'));
        uint8 E = reg(u, 'A');
        u->reg.DE = reg_combine(reg(u, 'D'), E);
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
        printf("LD H = 0x%x, B = 0x%x\n", reg(u, 'H'), reg(u, 'B'));
        uint8 H = reg(u, 'B');
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }
    case 0x1:
    {
        printf("LD H = 0x%x, C = 0x%x\n", reg(u, 'H'), reg(u, 'C'));
        uint8 H = reg(u, 'C');
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }
    case 0x2:
    {
        printf("LD H = 0x%x, D = 0x%x\n", reg(u, 'H'), reg(u, 'D'));
        uint8 H = reg(u, 'D');
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }
    case 0x3:
    {
        printf("LD H = 0x%x, E = 0x%x\n", reg(u, 'H'), reg(u, 'E'));
        uint8 H = reg(u, 'E');
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }
    case 0x4:
    {
        printf("LD H = 0x%x, H = 0x%x\n", reg(u, 'H'), reg(u, 'H'));
        uint8 H = reg(u, 'H');
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }
    case 0x5:
    {
        printf("LD H = 0x%x, L = 0x%x\n", reg(u, 'H'), reg(u, 'L'));
        uint8 H = reg(u, 'L');
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }
    case 0x6:
    {
        printf("LD H = 0x%x, (HL) = 0x%x\n", reg(u, 'H'), u->mem.content[u->reg.HL]);
        uint8 H = u->mem.content[u->reg.HL];
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }
    case 0x7:
    {
        printf("LD H = 0x%x, A = 0x%x\n", reg(u, 'H'), reg(u, 'A'));
        uint8 H = reg(u, 'A');
        u->reg.HL = reg_combine(H, reg(u, 'L'));
        break;
    }

    case 0x8:
    {
        printf("LD L = 0x%x, B = 0x%x\n", reg(u, 'L'), reg(u, 'B'));
        uint8 L = reg(u, 'B');
        u->reg.HL = reg_combine(reg(u, 'H'), L);
        break;
    }
    case 0x9:
    {
        printf("LD L = 0x%x, C = 0x%x\n", reg(u, 'L'), reg(u, 'C'));
        uint8 L = reg(u, 'C');
        u->reg.HL = reg_combine(reg(u, 'H'), L);
        break;
    }
    case 0xA:
    {
        printf("LD L = 0x%x, D = 0x%x\n", reg(u, 'L'), reg(u, 'D'));
        uint8 L = reg(u, 'D');
        u->reg.HL = reg_combine(reg(u, 'H'), L);
        break;
    }
    case 0xB:
    {
        printf("LD L = 0x%x, E = 0x%x\n", reg(u, 'L'), reg(u, 'E'));
        uint8 L = reg(u, 'E');
        u->reg.HL = reg_combine(reg(u, 'H'), L);
        break;
    }
    case 0xC:
    {
        printf("LD L = 0x%x, H = 0x%x\n", reg(u, 'L'), reg(u, 'H'));
        uint8 L = reg(u, 'H');
        u->reg.HL = reg_combine(reg(u, 'H'), L);
        break;
    }
    case 0xD:
    {
        printf("LD L = 0x%x, L = 0x%x\n", reg(u, 'L'), reg(u, 'L'));
        uint8 L = reg(u, 'L');
        u->reg.HL = reg_combine(reg(u, 'H'), L);
        break;
    }
    case 0xE:
    {
        printf("LD L = 0x%x, (HL) = 0x%x\n", reg(u, 'L'), u->mem.content[u->reg.HL]);
        uint8 L = u->mem.content[u->reg.HL];
        u->reg.HL = reg_combine(reg(u, 'H'), L);
        break;
    }
    case 0xF:
    {
        printf("LD L = 0x%x, A = 0x%x\n", reg(u, 'L'), reg(u, 'A'));
        uint8 L = reg(u, 'A');
        u->reg.HL = reg_combine(reg(u, 'H'), L);
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
        printf("LD (HL) = 0x%x, B = 0x%x\n", u->mem.content[u->reg.HL], reg(u, 'B'));
        u->mem.content[u->reg.HL] = reg(u, 'B');
        break;
    }
    case 0x1:
    {
        printf("LD (HL) = 0x%x, C = 0x%x\n", u->mem.content[u->reg.HL], reg(u, 'C'));
        u->mem.content[u->reg.HL] = reg(u, 'C');
        break;
    }
    case 0x2:
    {
        printf("LD (HL) = 0x%x, D = 0x%x\n", u->mem.content[u->reg.HL], reg(u, 'D'));
        u->mem.content[u->reg.HL] = reg(u, 'D');
        break;
    }
    case 0x3:
    {
        printf("LD (HL) = 0x%x, E = 0x%x\n", u->mem.content[u->reg.HL], reg(u, 'E'));
        u->mem.content[u->reg.HL] = reg(u, 'E');
        break;
    }
    case 0x4:
    {
        printf("LD (HL) = 0x%x, H = 0x%x\n", u->mem.content[u->reg.HL], reg(u, 'H'));
        u->mem.content[u->reg.HL] = reg(u, 'H');
        break;
    }
    case 0x5:
    {
        printf("LD (HL) = 0x%x, L = 0x%x\n", u->mem.content[u->reg.HL], reg(u, 'L'));
        u->mem.content[u->reg.HL] = reg(u, 'L');
        break;
    }
    case 0x6:
    {
        puts("HALT should've been handled elsewhere.");
        exit(1);
    }
    case 0x7:
    {
        printf("LD (HL) = 0x%x, A = 0x%x\n", u->mem.content[u->reg.HL], reg(u, 'A'));
        u->mem.content[u->reg.HL] = reg(u, 'A');
        break;
    }

    case 0x8:
    {
        printf("LD A = 0x%x, B = 0x%x\n", reg(u, 'A'), reg(u, 'B'));
        uint8 A = reg(u, 'B');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        break;
    }
    case 0x9:
    {
        printf("LD A = 0x%x, C = 0x%x\n", reg(u, 'A'), reg(u, 'C'));
        uint8 A = reg(u, 'C');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        break;
    }
    case 0xA:
    {
        printf("LD A = 0x%x, D = 0x%x\n", reg(u, 'A'), reg(u, 'D'));
        uint8 A = reg(u, 'D');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        break;
    }
    case 0xB:
    {
        printf("LD A = 0x%x, E = 0x%x\n", reg(u, 'A'), reg(u, 'E'));
        uint8 A = reg(u, 'E');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        break;
    }
    case 0xC:
    {
        printf("LD A = 0x%x, H = 0x%x\n", reg(u, 'A'), reg(u, 'H'));
        uint8 A = reg(u, 'H');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        break;
    }
    case 0xD:
    {
        printf("LD A = 0x%x, L = 0x%x\n", reg(u, 'A'), reg(u, 'L'));
        uint8 A = reg(u, 'L');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        break;
    }
    case 0xE:
    {
        printf("LD A = 0x%x, (HL) = 0x%x\n", reg(u, 'A'), u->mem.content[u->reg.HL]);
        uint8 A = u->mem.content[u->reg.HL];
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        break;
    }
    case 0xF:
    {
        printf("LD A = 0x%x, A = 0x%x\n", reg(u, 'A'), reg(u, 'A'));
        uint8 A = reg(u, 'A');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
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
        printf("ADD A = 0x%x, B = 0x%x\n", reg(u, 'A'), reg(u, 'B'));
        uint8 A = reg(u, 'A') + reg(u, 'B');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* add C to A */
        printf("ADD A = 0x%x, C = 0x%x\n", reg(u, 'A'), reg(u, 'C'));
        uint8 A = reg(u, 'A') + reg(u, 'C');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* add D to A */
        printf("ADD A = 0x%x, D = 0x%x\n", reg(u, 'A'), reg(u, 'D'));
        uint8 A = reg(u, 'A') + reg(u, 'D');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* add E to A */
        printf("ADD A = 0x%x, E = 0x%x\n", reg(u, 'A'), reg(u, 'E'));
        uint8 A = reg(u, 'A') + reg(u, 'E');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* add H to A */
        printf("ADD A = 0x%x, H = 0x%x\n", reg(u, 'A'), reg(u, 'H'));
        uint8 A = reg(u, 'A') + reg(u, 'H');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* add L to A */
        printf("ADD A = 0x%x, L = 0x%x\n", reg(u, 'A'), reg(u, 'L'));
        uint8 A = reg(u, 'A') + reg(u, 'L');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* add (HL) to A */
        printf("ADD A = 0x%x, (HL) = 0x%x\n", reg(u, 'A'), u->mem.content[u->reg.HL]);
        uint8 A = reg(u, 'A') + u->mem.content[u->reg.HL];
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* add A to A */
        printf("ADD A = 0x%x, A = 0x%x\n", reg(u, 'A'), reg(u, 'A'));
        uint8 A = reg(u, 'A') + reg(u, 'A');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* adc B to A */
        printf("ADC A = 0x%x, B = 0x%x\n", reg(u, 'A'), reg(u, 'B'));
        uint8 A = reg(u, 'A') + reg(u, 'B') + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* adc C to A */
        printf("ADC A = 0x%x, C = 0x%x\n", reg(u, 'A'), reg(u, 'C'));
        uint8 A = reg(u, 'A') + reg(u, 'C') + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* adc D to A */
        printf("ADC A = 0x%x, D = 0x%x\n", reg(u, 'A'), reg(u, 'D'));
        uint8 A = reg(u, 'A') + reg(u, 'D') + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* adc E to A */
        printf("ADC A = 0x%x, E = 0x%x\n", reg(u, 'A'), reg(u, 'E'));
        uint8 A = reg(u, 'A') + reg(u, 'E') + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* adc H to A */
        printf("ADC A = 0x%x, H = 0x%x\n", reg(u, 'A'), reg(u, 'H'));
        uint8 A = reg(u, 'A') + reg(u, 'H') + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* adc L to A */
        printf("ADC A = 0x%x, L = 0x%x\n", reg(u, 'A'), reg(u, 'L'));
        uint8 A = reg(u, 'A') + reg(u, 'L') + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* adc (HL) to A */
        printf("ADC A = 0x%x, (HL) = 0x%x\n", reg(u, 'A'), u->mem.content[u->reg.HL]);
        uint8 A = reg(u, 'A') + u->mem.content[u->reg.HL] + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* adc A to A */
        printf("ADC A = 0x%x, A = 0x%x\n", reg(u, 'A'), reg(u, 'A'));
        uint8 A = reg(u, 'A') + reg(u, 'A') + u->status_flag.C;
        u->reg.AF = reg_combine(A, reg(u, 'F'));
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
        printf("SUB A = 0x%x, B = 0x%x\n", reg(u, 'A'), reg(u, 'B'));
        uint8 A = reg(u, 'A') - reg(u, 'B');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* sub C to A */
        printf("SUB A = 0x%x, C = 0x%x\n", reg(u, 'A'), reg(u, 'C'));
        uint8 A = reg(u, 'A') - reg(u, 'C');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* sub D to A */
        printf("SUB A = 0x%x, D = 0x%x\n", reg(u, 'A'), reg(u, 'D'));
        uint8 A = reg(u, 'A') - reg(u, 'D');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* sub E to A */
        printf("SUB A = 0x%x, E = 0x%x\n", reg(u, 'A'), reg(u, 'E'));
        uint8 A = reg(u, 'A') - reg(u, 'E');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* sub H to A */
        printf("SUB A = 0x%x, H = 0x%x\n", reg(u, 'A'), reg(u, 'H'));
        uint8 A = reg(u, 'A') - reg(u, 'H');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* sub L to A */
        printf("SUB A = 0x%x, L = 0x%x\n", reg(u, 'A'), reg(u, 'L'));
        uint8 A = reg(u, 'A') - reg(u, 'L');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* sub (HL) to A */
        printf("SUB A = 0x%x, (HL) = 0x%x\n", reg(u, 'A'), u->mem.content[u->reg.HL]);
        uint8 A = reg(u, 'A') - u->mem.content[u->reg.HL];
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* sub A to A */
        printf("SUB A = 0x%x, A = 0x%x\n", reg(u, 'A'), reg(u, 'A'));
        uint8 A = reg(u, 'A') - reg(u, 'A');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* sbc B to A */
        printf("SBC A = 0x%x, B = 0x%x\n", reg(u, 'A'), reg(u, 'B'));
        uint8 A = reg(u, 'A') - (reg(u, 'B') + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* sbc C to A */
        printf("SBC A = 0x%x, C = 0x%x\n", reg(u, 'A'), reg(u, 'C'));
        uint8 A = reg(u, 'A') - (reg(u, 'C') + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* sbc D to A */
        printf("SBC A = 0x%x, D = 0x%x\n", reg(u, 'A'), reg(u, 'D'));
        uint8 A = reg(u, 'A') - (reg(u, 'D') + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* sbc E to A */
        printf("SBC A = 0x%x, E = 0x%x\n", reg(u, 'A'), reg(u, 'E'));
        uint8 A = reg(u, 'A') - (reg(u, 'E') + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* sbc H to A */
        printf("SBC A = 0x%x, H = 0x%x\n", reg(u, 'A'), reg(u, 'H'));
        uint8 A = reg(u, 'A') - (reg(u, 'H') + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* sbc L to A */
        printf("SBC A = 0x%x, L = 0x%x\n", reg(u, 'A'), reg(u, 'L'));
        uint8 A = reg(u, 'A') - (reg(u, 'L') + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* sbc (HL) to A */
        printf("SBC A = 0x%x, (HL) = 0x%x\n", reg(u, 'A'), u->mem.content[u->reg.HL]);
        uint8 A = reg(u, 'A') - (u->mem.content[u->reg.HL] + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* sbc A to A */
        printf("SBC A = 0x%x, A = 0x%x\n", reg(u, 'A'), reg(u, 'A'));
        uint8 A = reg(u, 'A') - (reg(u, 'B') + u->status_flag.C);
        u->reg.AF = reg_combine(A, reg(u, 'F'));
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
        printf("AND A = 0x%x, B = 0x%x\n", reg(u, 'A'), reg(u, 'B'));
        uint8 A = reg(u, 'A') & reg(u, 'B');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* and C to A */
        printf("AND A = 0x%x, C = 0x%x\n", reg(u, 'A'), reg(u, 'C'));
        uint8 A = reg(u, 'A') & reg(u, 'C');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* and D to A */
        printf("AND A = 0x%x, D = 0x%x\n", reg(u, 'A'), reg(u, 'D'));
        uint8 A = reg(u, 'A') & reg(u, 'D');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* and E to A */
        printf("AND A = 0x%x, E = 0x%x\n", reg(u, 'A'), reg(u, 'E'));
        uint8 A = reg(u, 'A') & reg(u, 'E');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* and H to A */
        printf("AND A = 0x%x, H = 0x%x\n", reg(u, 'A'), reg(u, 'H'));
        uint8 A = reg(u, 'A') & reg(u, 'H');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* and L to A */
        printf("AND A = 0x%x, L = 0x%x\n", reg(u, 'A'), reg(u, 'L'));
        uint8 A = reg(u, 'A') & reg(u, 'L');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* and (HL) to A */
        printf("AND A = 0x%x, (HL) = 0x%x\n", reg(u, 'A'), u->mem.content[u->reg.HL]);
        uint8 A = reg(u, 'A') & u->mem.content[u->reg.HL];
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* and A to A */
        printf("AND A = 0x%x, A = 0x%x\n", reg(u, 'A'), reg(u, 'A'));
        uint8 A = reg(u, 'A') & reg(u, 'A');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* XOR B to A */
        printf("XOR A = 0x%x, B = 0x%x\n", reg(u, 'A'), reg(u, 'B'));
        uint8 A = reg(u, 'A') ^ reg(u, 'B');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* XOR C to A */
        printf("XOR A = 0x%x, C = 0x%x\n", reg(u, 'A'), reg(u, 'C'));
        uint8 A = reg(u, 'A') ^ reg(u, 'C');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* XOR D to A */
        printf("XOR A = 0x%x, D = 0x%x\n", reg(u, 'A'), reg(u, 'D'));
        uint8 A = reg(u, 'A') ^ reg(u, 'D');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* XOR E to A */
        printf("XOR A = 0x%x, E = 0x%x\n", reg(u, 'A'), reg(u, 'E'));
        uint8 A = reg(u, 'A') ^ reg(u, 'E');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* XOR H to A */
        printf("XOR A = 0x%x, H = 0x%x\n", reg(u, 'A'), reg(u, 'H'));
        uint8 A = reg(u, 'A') ^ reg(u, 'H');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* XOR L to A */
        printf("XOR A = 0x%x, L = 0x%x\n", reg(u, 'A'), reg(u, 'L'));
        uint8 A = reg(u, 'A') ^ reg(u, 'L');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* XOR (HL) to A */
        printf("XOR A = 0x%x, (HL) = 0x%x\n", reg(u, 'A'), u->mem.content[u->reg.HL]);
        uint8 A = reg(u, 'A') ^ u->mem.content[u->reg.HL];
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* XOR A to A */
        printf("XOR A = 0x%x, A = 0x%x\n", reg(u, 'A'), reg(u, 'A'));
        uint8 A = reg(u, 'A') ^ reg(u, 'B');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
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
        printf("OR A, B");
        uint8 A = reg(u, 'A') | reg(u, 'B');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x1:
    { /* OR C to A */
        puts("OR A, C");
        uint8 A = reg(u, 'A') | reg(u, 'C');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x2:
    { /* OR D to A */
        puts("OR A, D");
        uint8 A = reg(u, 'A') | reg(u, 'D');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x3:
    { /* OR E to A */
        puts("OR A, E");
        uint8 A = reg(u, 'A') | reg(u, 'E');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x4:
    { /* OR H to A */
        puts("OR A, H");
        uint8 A = reg(u, 'A') | reg(u, 'H');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x5:
    { /* OR L to A */
        puts("OR A, L");
        uint8 A = reg(u, 'A') | reg(u, 'L');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x6:
    { /* OR (HL) to A */
        puts("OR A, (HL)");
        uint8 A = reg(u, 'A') | u->mem.content[u->reg.HL];
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x7:
    { /* OR A to A */
        puts("OR A, A");
        uint8 A = reg(u, 'A') | reg(u, 'A');
        u->reg.AF = reg_combine(A, reg(u, 'F'));
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x8:
    { /* CP B to A */
        printf("CP A, B");
        uint8 A = reg(u, 'A') - reg(u, 'B');
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0x9:
    { /* CP C to A */
        puts("CP A, C");
        uint8 A = reg(u, 'A') - reg(u, 'C');
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xA:
    { /* CP D to A */
        puts("CP A, D");
        uint8 A = reg(u, 'A') - reg(u, 'D');
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xB:
    { /* CP E to A */
        puts("CP A, E");
        uint8 A = reg(u, 'A') - reg(u, 'E');
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xC:
    { /* CP H to A */
        puts("CP A, H");
        uint8 A = reg(u, 'A') - reg(u, 'H');
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xD:
    { /* CP L to A */
        puts("CP A, L");
        uint8 A = reg(u, 'A') - reg(u, 'L');
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xE:
    { /* CP (HL) to A */
        puts("CP A, (HL)");
        uint8 A = reg(u, 'A') - u->mem.content[u->reg.HL];
        /* set_flags(u, Z, N, H, C); */
        break;
    }

    case 0xF:
    { /* CP A to A */
        puts("CP A, A");
        uint8 A = reg(u, 'A') - reg(u, 'B');
        /* set_flags(u, Z, N, H, C); */
        break;
    }
    }
}

int disassemble_rom(CPU *u)
{
    u->mem.ptr = 0x100; /* entry point */

    while (1)
    {
        uint8 op = m_consume8(u);

        printf("0x%x ", u->mem.ptr - 1);

        switch (op)
        {
        case 0x0: /* misc */
            puts("NOP");
            continue;
        case 0x10:
            puts("STOP");
            continue;
        case 0x77:
            puts("HALT");
            continue;
        case 0xCB:
            puts("PREFIX CB");
            continue;
        case 0xF3:
            puts("DI");
            continue;
        case 0xFB:
            puts("EI");
            continue;

        case 0x20: /* JR r8 */
            puts("JR NZ,r8");
            continue;
        case 0x30:
            puts("JR NC,r8");
            continue;

        case 0x01: /* LD reg,d16 */
            puts("LD BC,d16");
            u->reg.BC = m_consume16(u);
            continue;
        case 0x11:
            puts("LD DE,d16");
            u->reg.DE = m_consume16(u);
            continue;
        case 0x21:
            puts("LD HL,d16");
            u->reg.HL = m_consume16(u);
            continue;
        case 0x31:
            puts("LD SP,d16");
            u->reg.SP = m_consume16(u);
            continue;

        case 0x02: /* LD (),A */
            puts("LD (B)C,A");
            continue;
        case 0x12:
            puts("LD (D)E,A");
            continue;
        case 0x22:
            puts("LD (HL+),A");
            continue;
        case 0x32:
            puts("LD (SP-),A");
            continue;

        case 0x03: /* INC 2 byte register */
            puts("INC BC");
            u->reg.BC++;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x13:
            puts("INC DE");
            u->reg.DE++;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x23:
            puts("INC HL");
            u->reg.HL++;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x33:
            puts("INC SP");
            u->reg.SP++;
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0x04:
        { /* INC 1 byte register */
            puts("INC B");
            uint8 B = reg(u, 'B') + 1;
            u->reg.BC = reg_combine(B, reg(u, 'C'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x14:
        {
            puts("INC D");
            uint8 D = reg(u, 'D') + 1;
            u->reg.DE = reg_combine(D, reg(u, 'E'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x24:
        {
            puts("INC H");
            uint8 H = reg(u, 'H') + 1;
            u->reg.HL = reg_combine(H, reg(u, 'L'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x34:
        {
            puts("INC (HL)");
            u->mem.content[u->reg.HL]++;
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x05:
        { /* DEC 1 byte register */
            puts("DEC B");
            uint8 B = reg(u, 'B') - 1;
            u->reg.BC = reg_combine(B, reg(u, 'C'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x15:
        {
            puts("DEC D");
            uint8 D = reg(u, 'D') - 1;
            u->reg.DE = reg_combine(D, reg(u, 'E'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x25:
        {
            puts("DEC H");
            uint8 H = reg(u, 'H') - 1;
            u->reg.HL = reg_combine(H, reg(u, 'L'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x35:
        {
            puts("DEC (HL)");
            u->mem.content[u->reg.HL]--;
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x06:
        { /* LD 1 byte register,d8 */
            printf("LD B = 0x%x, 0x%x\n", reg(u, 'B'), m_peek8(u, u->mem.ptr));
            uint8 B = m_consume8(u);
            u->reg.BC = reg_combine(B, reg(u, 'C'));
            continue;
        }
        case 0x16:
        {
            printf("LD D = 0x%x, 0x%x\n", reg(u, 'D'), m_peek8(u, u->mem.ptr));
            uint8 D = m_consume8(u);
            u->reg.DE = reg_combine(D, reg(u, 'E'));
            continue;
        }
        case 0x26:
        {
            printf("LD H = 0x%x, 0x%x\n", reg(u, 'H'), m_peek8(u, u->mem.ptr));
            uint8 H = m_consume8(u);
            u->reg.HL = reg_combine(H, reg(u, 'L'));
            continue;
        }
        case 0x36:
            printf("LD (HL) = 0x%x, 0x%x\n", u->mem.content[u->reg.HL], m_peek8(u, u->mem.ptr));
            u->mem.content[u->reg.HL] = m_consume8(u);
            continue;

        case 0x07: /* 8bit rotation/shift */
            puts("RLCA");
            continue;
        case 0x17:
            puts("RLA");
            continue;

        case 0x27: /* decimal adjust A */
            puts("DAA");
            continue;

        case 0x37: /* set carry flag */
            puts("SCF");
            continue;

        case 0x08: /* LD (16),SP */
            puts("LD (a16),SP");
            continue;

        case 0x18: /* JR r8 */
            puts("JR r8");
            u->mem.ptr += m_peek8(u, u->mem.ptr);
            continue;
        case 0x28:
            puts("JR Z,r8");
            continue;
        case 0x38:
            puts("JR C,r8");
            continue;

        case 0x09: /* add HL to 2 byte */
            puts("ADD HL,BC");
            u->reg.HL += u->reg.BC;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x19:
            puts("ADD HL,DE");
            u->reg.HL += u->reg.DE;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x29:
            puts("ADD HL,HL");
            u->reg.HL += u->reg.HL;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x39:
            puts("ADD HL,SP");
            u->reg.HL += u->reg.SP;
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0x0A: /* load A to (2 byte) */
            puts("LD A,(BC)");
            continue;
        case 0x1A:
            puts("LD A,(DE)");
            continue;
        case 0x2A:
            puts("LD A,(HL+)");
            continue;
        case 0x3A:
            puts("LD A,(HL-)");
            continue;

        case 0x0B: /* DEC 2 byte register */
            puts("DEC BC");
            u->reg.BC--;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x1B:
            puts("DEC DE");
            u->reg.DE--;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x2B:
            puts("DEC HL");
            u->reg.HL--;
            /* set_flags(u, Z, N, H, C); */
            continue;
        case 0x3B:
            puts("DEC SP");
            u->reg.SP--;
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0x0C:
        { /* INC 1 byte register */
            puts("INC C");
            uint8 C = reg(u, 'C') + 1;
            u->reg.BC = reg_combine(reg(u, 'B'), C);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x1C:
        {
            puts("INC E");
            uint8 E = reg(u, 'E') + 1;
            u->reg.DE = reg_combine(reg(u, 'D'), E);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x2C:
        {
            puts("INC L");
            uint8 L = reg(u, 'L') + 1;
            u->reg.HL = reg_combine(reg(u, 'H'), L);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x3C:
        {
            puts("INC A");
            uint8 A = reg(u, 'A') + 1;
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x0D:
        { /* DEC 1 byte register */
            puts("INC C");
            uint8 C = reg(u, 'C') - 1;
            u->reg.BC = reg_combine(reg(u, 'B'), C);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x1D:
        {
            puts("INC E");
            uint8 E = reg(u, 'E') - 1;
            u->reg.DE = reg_combine(reg(u, 'D'), E);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x2D:
        {
            puts("INC L");
            uint8 L = reg(u, 'L') - 1;
            u->reg.HL = reg_combine(reg(u, 'H'), L);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0x3D:
        {
            puts("INC A");
            uint8 A = reg(u, 'A') - 1;
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0x0E: /* load 1 byte,d8 */
            puts("LD C,d8");
            continue;
        case 0x1E:
            puts("LD E,d8");
            continue;
        case 0x2E:
            puts("LD L,d8");
            continue;
        case 0x3E:
            puts("LD A,d8");
            continue;

        case 0x0F: /* 8bit rotation/shift */
            puts("RRCA");
            continue;
        case 0x1F:
            puts("RRA");
            continue;

        case 0x2F: /* complement */
            puts("CPL");
            continue;

        case 0x3F: /* complement carry flag */
            puts("SCF");
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
            puts("RET NZ");
            continue;
        case 0xD0:
            puts("RET NC");
            continue;

        case 0xE0: /* put memory */
            puts("LDH (a8), A");
            continue;
        case 0xF0:
            puts("LDH A,(a8)");
            continue;

        case 0xC1: /* register POP */
            puts("POP BC");
            u->reg.BC = s_pop16(u->st);
            continue;
        case 0xD1:
            puts("POP DE");
            u->reg.DE = s_pop16(u->st);
            continue;
        case 0xE1:
            puts("POP HL");
            u->reg.HL = s_pop16(u->st);
            continue;
        case 0xF1:
            puts("POP AF");
            u->reg.AF = s_pop16(u->st);
            continue;

        case 0xC2: /* jp a16 */
            puts("JP NZ,a16");
            continue;
        case 0xD2:
            puts("JP NC,a16");
            continue;

        case 0xE2: /* load addres to register */
            puts("LD (C), A");
            continue;
        case 0xF2:
            puts("LD A,(C)");
            continue;

        case 0xC3: /* JP a16 */
            printf("JP 0x%x\n", m_peek16(u, u->mem.ptr));
            u->mem.ptr = m_peek16(u, u->mem.ptr);
            continue;

        case 0xC4: /* CALL a16 */
            puts("CALL NZ,a16");
            continue;
        case 0xD4:
            puts("CALL NC,a16");
            continue;

        case 0xC5: /* register PUSH */
            puts("PUSH BC");
            s_push16(u->st, u->reg.BC);
            continue;
        case 0xD5:
            puts("PUSH DE");
            s_push16(u->st, u->reg.DE);
            continue;
        case 0xE5:
            puts("PUSH HL");
            s_push16(u->st, u->reg.HL);
            continue;
        case 0xF5:
            puts("PUSH AF");
            s_push16(u->st, u->reg.AF);
            continue;

        case 0xC6:
        { /* d8 arithmetic */
            puts("ADD A,d8");
            uint8 A = reg(u, 'A') + m_consume8(u);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            continue;
        }
        case 0xD6:
        {
            puts("SUB A,d8");
            uint8 A = reg(u, 'A') - m_consume8(u);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            continue;
        }
        case 0xE6:
        {
            puts("AND A,d8");
            uint8 A = reg(u, 'A') & m_consume8(u);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            continue;
        }
        case 0xF6:
        {
            puts("OR A,d8");
            uint8 A = reg(u, 'A') | m_consume8(u);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            continue;
        }

        case 0xC7: /* RST (restarts) */
            puts("RST 00H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x00;
            continue;
        case 0xD7:
            puts("RST 10H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x10;
            continue;
        case 0xE7:
            puts("RST 20H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x20;
            continue;
        case 0xF7:
            puts("RST 30H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x30;
            continue;

        case 0xC8: /* return flag */
            puts("RET Z");
            continue;
        case 0xD8:
            puts("RET C");
            continue;

        case 0xE8:
            /* add SP, r8 */
            puts("ADD SP,r8");
            u->reg.SP += m_consume8(u);
            /* set_flags(u, Z, N, H, C); */
            continue;

        case 0xF8: /* load HL,SP+r8 */
            puts("LD HL,SP+r8");
            continue;

        case 0xC9: /* return */
            puts("RET");
            u->mem.ptr = s_pop16(u->st);
            continue;
        case 0xD9:
            puts("RETI");
            u->mem.ptr = s_pop16(u->st);
            /* enable interrupts? */
            continue;

        case 0xE9: /* jump address */
            puts("JP (HL)");
            u->mem.ptr = u->mem.content[u->reg.HL];
            continue;

        case 0xF9: /* load 2 byte */
            puts("LD SP,HL");
            continue;

        case 0xCA: /* jump flag,a16 */
            puts("Z,a16");
            continue;
        case 0xDA:
            puts("C,a16");
            continue;

        case 0xEA: /* load a16 to register*/
            puts("LD (a16),A");
            u->mem.content[u->mem.ptr] = reg(u, 'A');
            continue;
        case 0xFA:
        {
            puts("LD A,(a16)");
            uint8 A = m_consume16(u);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            continue;
        }

        case 0xCC: /* call a16 */
            puts("CALL Z,a16");
            continue;
        case 0xDC:
            puts("CALL C,a16");
            continue;
        case 0xCD:
            puts("CALL a16");
            s_push16(u->st, u->mem.ptr + 1);
            u->mem.ptr = m_peek16(u, u->mem.ptr);
            continue;

        case 0xCE:
        { /* extra arithmetic d8 */
            puts("ADC A,d8");
            uint8 A = reg(u, 'A') + (m_consume8(u) + u->status_flag.C);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xDE:
        {
            puts("SBC A,d8");
            uint8 A = reg(u, 'A') - (m_consume8(u) + u->status_flag.C);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xEE:
        {
            puts("XOR d8");
            uint8 A = reg(u, 'A') ^ m_consume8(u);
            u->reg.AF = reg_combine(A, reg(u, 'F'));
            /* set_flags(u, Z, N, H, C); */
            continue;
        }
        case 0xFE:
        {
            puts("CP d8");
            uint8 A = reg(u, 'A') - m_consume8(u);
            /* set_flags(u, Z, N, H, C); */
            continue;
        }

        case 0xCF: /* RST (restarts) */
            puts("RST 08H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x08;
            continue;
        case 0xDF:
            puts("RST 18H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x18;
            continue;
        case 0xEF:
            puts("RST 28H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x28;
            continue;
        case 0xFF:
            puts("RST 38H");
            s_push16(u->st, u->mem.ptr);
            u->mem.ptr = 0x0000 + 0x38;
            continue;
        }

        printf("dunno 0x%x\n", op);
    }
    return 1;
}
