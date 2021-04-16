#include <gameboy/cpu.h>
#include <gameboy/disassembler.h>
#include <gameboy/emulator.h>

#include <stdio.h>
#include <unistd.h>

void help_instruction()
{
    char* d_usage = "\t-d PATH: \tDisassemble ROM in PATH\n";
    char* e_usage = "\t-e PATH: \tEmulate ROM in PATH\n";
    char* help = "\t-h: \t\tHelp message\n";
    printf("Gameboy Emulator\nUsage:\n %s %s %s", d_usage, e_usage, help);
}

int main(int argc, char **argv)
{
    int dis_flag = 0;
    int emu_flag = 0;
    int c = 0;

    CPU u;
    boot_cpu(&u);

    while ((c = getopt(argc, argv, "d:e:")) != -1)
    {
        switch (c)
        {
        case 'd':
            dis_flag = 1;
            load_rom(&u, optarg);
            break;
        case 'e':
            emu_flag = 1;
            load_rom(&u, optarg);
            break;
        case 'h':
        default:
            help_instruction();
            return 1;
        }
    }

    for (int index = optind; index < argc; index++)
    {
        printf("Non-option argument: %s\n", argv[index]);
        help_instruction();
        return 1;
    }

    if (dis_flag)
    {
        disassemble_rom(&u);
    }
    else if (emu_flag)
    {
        emulate_rom(&u);
    }
    else
    {
        help_instruction();
    }

    return 0;
}
