#include <gameboy/cpu.h>
#include <gameboy/debugger.h>
#include <gameboy/disassembler.h>
#include <gameboy/emulator.h>
#include <gameboy/screen.h>

#include <getopt.h>
#include <stdio.h>

void help_instruction()
{
    char *d_usage = "-d or --disassemble PATH: \tDisassemble ROM in PATH\n";
    char *e_usage = "-e or --emulate PATH: \t\tEmulate ROM in PATH\n";
    char *debug = "-D or --debug PATH: \t\tDebugger\n";
    char *info = "--info: \t\t\tDump ROM information\n";
    char *help = "-h: \t\t\t\tHelp message\n";
    printf("Gameboy Emulator\nUsage:\n %s %s %s %s %s", d_usage, e_usage, debug,
           info, help);
}

static int info_flag;

int main(int argc, char **argv)
{
    int c;
    CPU u;

    while (1)
    {
        static struct option long_options[] = {
            {"info", no_argument, &info_flag, 1},
            {"debug", required_argument, 0, 'D'},
            {"emulate", required_argument, 0, 'e'},
            {"disassemble", required_argument, 0, 'd'},
            {"screen", no_argument, 0, 'S'},
            {0, 0, 0, 0}};

        int option_index = 0;

        c = getopt_long(argc, argv, "d:e:D:Sh", long_options, &option_index);

        if (c == -1)
        {
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
            boot_cpu(&u);
            load_rom(&u, optarg, info_flag);
            disassemble_rom(&u);
            break;
        case 'e':
            boot_cpu(&u);
            load_rom(&u, optarg, info_flag);
            emulate_rom(&u);
            break;
        case 'D':
            boot_cpu(&u);
            load_rom(&u, optarg, info_flag);
            debugger(&u);
            break;
        case 'S':
            init_screen();
            update_screen();
            break;

        case '?':
        default:
            help_instruction();
            return 1;
        }
    }
    return 0;
}
