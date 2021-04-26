#include <stdio.h>
#include <stdlib.h>

// The program prints last N lines from a file with the given name.
// NOTE: File must use LF line endings.
int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("usage: %s <filename> <number_of_lines>\n", argv[0]);
        return 0;
    }

    int tail = strtol(argv[2], NULL, 10);
    if (tail <= 0) {
        printf("number of lines must be greater than 0\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("cannot open file: %s\n", argv[1]);
        return 0;
    }

    int counter = 0;
    char character;
    long offset = 0;

    while (fseek(file, offset--, SEEK_END) == 0) {
        character = (char) fgetc(file);
        if (character == '\n')
            if (++counter == tail)
                break;
    }

    character = (char) fgetc(file);
    while (character != EOF) {
        putchar(character);
        character = (char) fgetc(file);
    }

    fclose(file);
    return 0;
}
