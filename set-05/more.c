#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// The program prints N lines from a file with the given name. After printing out N lines the program waits for pressing
// any key. If user clicks 'q' or 'ESC' the program exits, otherwise it prints next N lines.
int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("usage: %s <filename> <number_of_lines>\n", argv[0]);
        return 0;
    }

    int limit = strtol(argv[2], NULL, 10);
    if (limit <= 0) {
        printf("number of lines must be greater than 0\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("cannot open file: %s\n", argv[1]);
        return 0;
    }

    char character = (char) fgetc(file);
    int input, counter = 0;

    while (character != EOF) {
        putchar(character);
        if (character == '\n') {
            if (++counter == limit) {
                counter = 0;
                input = getch();
                if (input == 113 || input == 27) break;
            }
        }
        character = (char) fgetc(file);
    }

    fclose(file);
    return 0;
}
