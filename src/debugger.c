#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gameboy/cpu.h>
#include <gameboy/debugger.h>
#include <gameboy/emulator.h>

#include <readline/chardefs.h>
#include <readline/history.h>
#include <readline/readline.h>

Debugger Dbg = {.breakpoint = 0xFFFF};

static int step_func(CPU *u, char *);
static int continue_func(CPU *u, char *);
static int breakpoint_func(CPU *u, char *addr);
static int print_func(CPU *u, char *addr);
static int help_func(CPU *u, char *);

CMD commands[] = {{"s", step_func, "Step to next instruction.\n"},
                  {"c", continue_func, "Continue until next breakpoint.\n"},
                  {"b", breakpoint_func, "Mark address with breakpoint.\n"},
                  {"p", print_func, "Return value in memory of address.\n"},
                  {"help", help_func, "This text.\n"},
                  {"?", help_func, "Same as `help`.\n"}};

static int print_status(CPU *u, uint8_t op)
{
    printf("ADDRESS\tOPCODE\tBYTES\tAF\tBC\tDE\tHL\tSP\tZNHC\tCYCLE\n");
    printf("$%04x\t$%02x\t$%04x "
           "\t$%04x\t$%04x\t$%04x\t$%04x\t$%04x\t%d%d%d%d\t%d\n",
           u->mem.ptr, op, m_get16(u, u->mem.ptr + 1), u->reg.AF, u->reg.BC,
           u->reg.DE, u->reg.HL, u->reg.SP, u->reg.FZ, u->reg.FN, u->reg.FH,
           u->reg.FC, u->cycles);

    return 0;
}

static int step_func(CPU *u, char *addr)
{
    uint8_t next_opcode = m_read8(u);

    const int initial_cycles = u->cycles;
    execute_opcode(u, next_opcode);
    update_timers(u, u->cycles - initial_cycles);
    update_graphics(u, u->cycles - initial_cycles);
    execute_interupts(u);

    print_status(u, m_peek8(u));
    return 0;
}

static int continue_func(CPU *u, char *addr)
{
    uint8_t next_opcode;
    do
    {
        next_opcode = m_read8(u);

        const int initial_cycles = u->cycles;
        execute_opcode(u, next_opcode);
        update_timers(u, u->cycles - initial_cycles);
        update_graphics(u, u->cycles - initial_cycles);
        execute_interupts(u);

    } while (u->mem.ptr != Dbg.breakpoint);
    print_status(u, m_peek8(u));
    return 0;
}

static int breakpoint_func(CPU *u, char *addr)
{
    uint16_t hex_addr = (uint16_t)strtol(addr, NULL, 16);
    Dbg.breakpoint = hex_addr;
    printf("Address $%04x marked with a breakpoint.\n", hex_addr);
    return 0;
}

static int print_func(CPU *u, char *addr)
{
    uint16_t hex_addr = (uint16_t)strtol(addr, NULL, 16);
    printf("$%04x: $%02x\n", hex_addr, m_get8(u, hex_addr));
    return 0;
}

static int help_func(CPU *u, char *addr)
{
    for (int i = 0; commands[i].name; i++)
    {
        printf("%s: %s", commands[i].name, commands[i].doc);
    }
    return 0;
}

static CMD *find_command(char *name)
{
    for (int i = 0; commands[i].name; i++)
    {
        if (strcmp(name, commands[i].name) == 0)
            return (&commands[i]);
    }

    return ((CMD *)NULL);
}

static int execute_line(CPU *u, char *buf)
{
    CMD *command;
    char *word;

    int i;

    for (i = 0; buf[i] && whitespace(buf[i]); i++)
    {
    }
    word = buf + i;

    for (; buf[i] && !whitespace(buf[i]); i++)
    {
    }

    if (buf[i])
        buf[i++] = '\0';

    command = find_command(word);

    if (!command)
    {
        fprintf(stderr, "%s: No such command.\n", word);
        return 1;
    }

    for (; whitespace(buf[i]); i++)
    {
    }

    word = buf + i;

    return (*(command->func))(u, word);
}

int debugger(CPU *u)
{
    char *buf;
    while ((buf = readline(">> ")) != NULL)
    {
        if (strlen(buf) > 0)
        {
            add_history(buf);
            execute_line(u, buf);
        }
    }
    free(buf);
    return 0;
}
