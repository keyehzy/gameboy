#include <gameboy/cpu.h>
#include <gameboy/disassembler.h>
#include <gameboy/emulator.h>

#include <getopt.h>
#include <stdio.h>

void help_instruction()
{
    char *d_usage = "\t-d PATH: \tDisassemble ROM in PATH\n";
    char *e_usage = "\t-e PATH: \tEmulate ROM in PATH\n";
    char *help = "\t-h: \t\tHelp message\n";
    printf("Gameboy Emulator\nUsage:\n %s %s %s", d_usage, e_usage, help);
}

static int info_flag;

int main(int argc, char **argv)
{
    int c;

    CPU u;
    boot_cpu(&u);

    while (1)
    {
        static struct option long_options[] = {
            {"info", no_argument, &info_flag, 1},
            {"help", no_argument, 0, 'h'},
            {"emulate", required_argument, 0, 'e'},
            {"disassemble", required_argument, 0, 'd'},
            {0, 0, 0, 0}};

        int option_index = 0;

        c = getopt_long(argc, argv, "d:e:h", long_options, &option_index);

        if (c == -1)
        {
            help_instruction();
            break;
        }

        switch (c)
        {
        case 0:
            if (long_options[option_index].flag != 0)
                break;
            help_instruction();
            break;
        case 'd':
            load_rom(&u, optarg, info_flag);
            disassemble_rom(&u);
            break;
        case 'e':
            load_rom(&u, optarg, info_flag);
            emulate_rom(&u);
            break;
        case 'h':
        default:
            help_instruction();
            return 1;
        }
    }
    return 0;
}
