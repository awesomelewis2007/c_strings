/* 
 * C Strings
 * The strings command written in C
 * By: Lewis Evans
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "colour.h"

void print_help(){
    printf("Usage: strings [options] [file]\n");
    printf("Options:\n");
    printf("  -ln, --line-numbers\t\tShow line numbers\n");
    printf("  -h, --help\t\t\tShow this help message\n");
}

int main(int argc, char *argv[]) {
    bool show_line_numbers = false;
    
    if (argc == 1) {
        printf("Usage: strings [options] [file]\n");
        return 1;
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    if (argc > 2) {
        if (strcmp(argv[2], "-ln") == 0 || strcmp(argv[2], "--line-numbers") == 0) {
            show_line_numbers = true;
        }
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int line_number = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        for (int i = 0; i < read; i++) {
            int printable_chars = 0;
            int start_index = i;
            while (isprint(line[i])) {
                printable_chars++;
                i++;
            }

            if (printable_chars > 2) {
                if (show_line_numbers) {

                    printf("%s%d%s | %s", ANSI_COLOR_CYAN, line_number, ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
                }
                for (int j = start_index; j < start_index + printable_chars; j++) {
                    printf("%c", line[j]);
                }
                printf("\n");
            }
        }
    }

}