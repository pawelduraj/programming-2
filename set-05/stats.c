#include <stdio.h>
#include <stdlib.h>

// The program calculates some statistics for words in the given file. If the filename is not specified,
// statistics are calculated for the default file: input.txt
int main(int argc, char *argv[]) {

    if (argc > 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return 0;
    }

    FILE *file;
    if (argc == 2) {
        file = fopen(argv[1], "r");
        if (!file) {
            printf("cannot open file: %s\n", argv[1]);
            return 0;
        }
    } else {
        file = fopen("input.txt", "r");
        if (!file) {
            printf("cannot open file: input.txt\n");
            return 0;
        }
    }

    int minimum = INT_MAX, maximum = 0, sum = 0, counter = 0;
    int isReadingWord = 0, wordLength = 0;
    char character = (char) fgetc(file);

    while (character != EOF) {

        if (character == ' ' || (character >= '\t' && character <= '\r')) {
            if (isReadingWord) {
                counter++;
                sum += wordLength;
                if (wordLength > maximum) maximum = wordLength;
                if (wordLength < minimum) minimum = wordLength;
                isReadingWord = 0;
            }
        } else if (isReadingWord) {
            wordLength++;
        } else {
            isReadingWord = -1;
            wordLength = 1;
        }

        character = (char) fgetc(file);
    }

    if (isReadingWord) {
        sum += wordLength;
        counter++;
        if (wordLength > maximum) maximum = wordLength;
        if (wordLength < minimum) minimum = wordLength;
    }

    fclose(file);

    file = fopen("statistics.dat", "w");
    if (!file) {
        printf("cannot save statistics to statistics.dat\n");
        return 0;
    }

    fprintf(file, "word count:          %d\n", counter);
    fprintf(file, "minimum word length: %d\n", minimum);
    fprintf(file, "maximum word length: %d\n", maximum);
    fprintf(file, "average word length: %.2f\n", sum / (double) counter);
    fclose(file);
    printf("statistics saved to statistics.dat\n");

    return 0;
}
