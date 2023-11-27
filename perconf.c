#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define C_RESET   "\x1b[0m"

void read_number(const char * file_name, double * out) {
    FILE * file_pointer;
    if ((file_pointer = fopen(file_name, "r"))) {
        fscanf(file_pointer, "%lf", out);
        fclose(file_pointer);
    } else {
        printf("Error: cannot open '%s'\n", file_name);
        exit(1);
    }
}

void print_help(void) {
    printf(
        C_BLUE "Usage:" C_RESET " perconf [flags]\n"
        C_GREEN "Flags:\n" C_RESET
        "    --help        - display help\n"
        "    -m <number>   - minimum (including)\n"
        "    -M <number>   - maximum (including)\n"
        "    -c <number>   - current value\n"
        "    -i <number>   - number to add (in %%). Can be positive or negative\n"
        "    -s <number>   - number to set (in %%)\n\n"
        C_GREEN "        FILE CONFIG\n" C_RESET
        "    -FM <file>    - file to read maximum from\n"
        "    -Fm <file>    - file to read minimum from\n"
        "    -Fc <file>    - file to read actual value from\n"
        "    -Fi <file>    - file to read increase from (in %%). Can be positive or negative\n"
        "    -Fs <file>    - file to set number from (in %%)\n"
        "    -Fo <file>    - file to write output to. If not specified - use stdout\n\n"
        C_GREEN "        OUTPUT FORMAT\n" C_RESET
        "    -f <template> - printf template. Requires one number type (default: \"%%.lf\")\n\n"
        "If there is no -[F]<i | s>, then the percentage will be printed out or written "
        "to -Fo.\n\n"
    );
}

int main(int argc, const char * argv[]) {
    FILE * file;
    double max = 0, min = 0, cur = 0, increase = 0, exact_number = 0, max_offset = 0;

    bool out_to_file = false;
    bool set_number = false;
    const char * out_file_name;
    const char * out_format = "%.lf";
    bool modify = false;

    const char * cur_arg;
    if (argc < 2) {
        print_help();
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        cur_arg = argv[i];

        if (cur_arg[0] == '-') switch (cur_arg[1])
            {
                // --x
                case '-':
                    if (strcmp(cur_arg + 2, "help") == 0) {
                        print_help();
                        return 0;
                    }
                    break;
                // -Fx
                case 'F':
                    switch (cur_arg[2]) {
                        case 'M':
                            cur_arg = argv[++i];
                            read_number(cur_arg, &max);
                            break;
                        case 'm':
                            cur_arg = argv[++i];
                            read_number(cur_arg, &min);
                            break;
                        case 'c':
                            cur_arg = argv[++i];
                            read_number(cur_arg, &cur);
                            break;
                        case 'i':
                            cur_arg = argv[++i];
                            read_number(cur_arg, &increase);
                            modify = true;
                            break;
                        case 's':
                            cur_arg = argv[++i];
                            read_number(cur_arg, &exact_number);
                            modify = set_number = true;
                            break;
                        case 'o':
                            out_to_file = true;
                            out_file_name = argv[++i];
                            break;
                    }
                    break;
                // -x
                case 'M':
                    max = atof(argv[++i]);
                    break;
                case 'm':
                    min = atof(argv[++i]);
                    break;
                case 'c':
                    cur = atof(argv[++i]);
                    break;
                case 'i':
                    increase = atof(argv[++i]);
                    modify = true;
                    break;
                case 's':
                    exact_number = atof(argv[++i]);
                    modify = set_number = true;
                    break;
                case 'f':
                    out_format = argv[++i];
                    break;
            }
    }

    max_offset = max - min;
    if (modify) {
        if (set_number)
            cur = min + max_offset / 100. * exact_number;
        else
            cur += max_offset / 100. * increase;

        cur = cur > max ? max : cur < min ? min : cur;
    } else {
        cur = (cur - min) / max_offset * 100.;
    }

    if (out_to_file) {
        if ((file = fopen(out_file_name, "w"))) {
            fprintf(file, out_format, cur);
            fclose(file);
        } else {
            printf("Error: cannot open file %s\n", out_file_name);
            return 1;
        }
    } else {
        printf(out_format, cur);
    }

    return 0;
}
