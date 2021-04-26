#include <stdio.h>
#include <stdlib.h>

// The program calculates sum of product prices in the given file. If the filename is not specified,
// sum is calculated for the default file: settlement.txt
// The program can be used in 2 modes:
// 1 - products are separated from the price by space:
//     product_name 1.23
// 2 - products are separated from the price by colon:
//     product name: 1.23
// Sum of product prices is saved to bills.txt
int main(int argc, char *argv[]) {

    if (argc < 2 || argc > 3) {
        printf("usage: %s <mode> <filename>\n", argv[0]);
        return 0;
    }

    char mode = argv[1][0];
    if (mode != '1' && mode != '2') {
        printf("invalid mode\n1: product_name 1.23\n2: product name: 1.23\n");
        return 0;
    }

    FILE *file;
    if (argc == 3) {
        file = fopen(argv[2], "r");
        if (!file) {
            printf("cannot open file: %s\n", argv[2]);
            return 0;
        }
    } else {
        file = fopen("settlement.txt", "r");
        if (!file) {
            printf("cannot open file: settlement.txt\n");
            return 0;
        }
    }

    double sum = 0;
    char price[1024];
    int p = 0, readingNumber = 0;
    char character = (char) getc(file);
    char separator = mode == '1' ? ' ' : ':';

    while (character != EOF) {
        if (readingNumber) {
            if (character == '\n') {
                price[p] = '\0';
                sum += strtod(price, NULL);
                p = 0;
                readingNumber = 0;
            } else price[p++] = character;
        } else if (character == separator)
            readingNumber = -1;
        character = (char) getc(file);
    }
    if (readingNumber) {
        price[p] = '\0';
        sum += strtod(price, NULL);
    }

    fclose(file);

    file = fopen("bills.txt", "a");
    if (!file) {
        printf("cannot save bill to bills.txt\n");
        return 0;
    }

    fprintf(file, "%.2f\n", sum);
    fclose(file);

    return 0;
}
