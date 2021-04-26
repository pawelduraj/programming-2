#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Returns a string containing input from stdin.
char *read() {
    int max = 16, size = 0;
    char *string = calloc(max, sizeof(char));
    char character;
    scanf("%c", &character);
    while (character != '\n') {
        if (size + 1 == max) {
            char *newString = calloc(max * 2, sizeof(char));
            for (int i = 0; i < max; i++) newString[i] = string[i];
            free(string);
            string = newString;
            max *= 2;
        }
        string[size++] = character;
        scanf("%c", &character);
    }
    string[size] = '\0';
    return string;
}

// Returns index of the given character in the given string.
// If the character is not in the string then function returns -1.
int getIndex(char c, const char *string) {
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] == c) return i;
    return -1;
}

// Prints the given character as word if the character is digit.
void printDigit(char c) {
    if (c == '0') printf(" zero");
    else if (c == '1') printf(" one");
    else if (c == '2') printf(" two");
    else if (c == '3') printf(" three");
    else if (c == '4') printf(" four");
    else if (c == '5') printf(" five");
    else if (c == '6') printf(" six");
    else if (c == '7') printf(" seven");
    else if (c == '8') printf(" eight");
    else if (c == '9') printf(" nine");
}

// Returns number of zeros in the binary representation of the given number.
int countZeros(long number) {
    if (!number) return 1;
    int skip = -1, counter = 0;
    for (int i = sizeof(long) * 8 - 1; i >= 0; i--) {
        if ((number & (((long) 0b1) << i)) != (long) 0)
            skip = 0;
        else if (skip == 0)
            counter++;
    }
    return counter;
}

// Checks if there is a digit in the given string.
int hasDigit(const char *string) {
    for (int i = 0; string[i] != '\0'; i++)
        if (string[i] <= '9' && string[i] >= '0') return -1;
    return 0;
}

// Prints a Roman number which is equal to the result of operation: number * position
void printRomanNumber(int number, int position) {
    char a, b, c;
    if (position == 1) { a = 'I', b = 'V', c = 'X'; }
    else if (position == 10) { a = 'X', b = 'L', c = 'C'; }
    else if (position == 100) { a = 'C', b = 'D', c = 'M'; }
    else { a = 'M', b = ' ', c = ' '; }

    if (number == 1) printf("%c", a);
    else if (number == 2) printf("%c%c", a, a);
    else if (number == 3) printf("%c%c%c", a, a, a);
    else if (number == 4) printf("%c%c", a, b);
    else if (number == 5) printf("%c", b);
    else if (number == 6) printf("%c%c", b, a);
    else if (number == 7) printf("%c%c%c", b, a, a);
    else if (number == 8) printf("%c%c%c%c", b, a, a, a);
    else if (number == 9) printf("%c%c", a, c);
}

// Prints help.
void printHelp() {
    printf("0 - reverse text and replace lowercase letters with uppercase letters      [TASK 0]\n");
    printf("1 - replace characters in text                                             [TASK 1]\n");
    printf("2 - print number as words                                                  [TASK 2]\n");
    printf("3 - print number of zeros in the binary representation of the given number [TASK 3]\n");
    printf("4 - convert number from decimal to Roman or from Roman to decimal          [TASK 4]\n");
    printf("5 - print help\n");
    printf("6 - exit\n");
}

int main() {

    char *text, *command;

    printHelp();

    while (1) {

        printf(">>>");
        command = read();

        if (command[0] == '0' && command[1] == '\0') {

            // TASK 0
            // Functions used: read
            printf("Input:");
            text = read();
            printf("Output:");
            for (int i = (int) strlen(text) - 1; i >= 0; i--)
                putchar(toupper(text[i]));
            printf("\n");
            free(text);

        } else if (command[0] == '1' && command[1] == '\0') {

            // TASK 1
            // Functions used: read
            char s1[] = "abcdefghijklmnopqrstuvwxyz";
            char s2[] = "zyxwvutsrqponmlkjihgfedcba";
            printf("Input:");
            text = read();
            printf("Output:");
            for (int i = 0; text[i] != '\0'; i++) {
                int index = getIndex(text[i], s1);
                if (index != -1 && index < strlen(s2))
                    putchar(s2[index]);
                else putchar(text[i]);
            }
            printf("\n");
            free(text);

        } else if (command[0] == '2' && command[1] == '\0') {

            // TASK 2
            // Functions used: read, printDigit
            printf("Input:");
            text = read();
            printf("Output:");
            for (int i = 0; text[i] != '\0'; i++)
                printDigit(text[i]);
            printf("\n");
            free(text);

        } else if (command[0] == '3' && command[1] == '\0') {

            // TASK 3
            // Functions used: read, countZeros
            printf("Input:");
            text = read();
            long number = strtol(text, NULL, 10);
            printf("Output: %d\n", countZeros(number));
            free(text);

        } else if (command[0] == '4' && command[1] == '\0') {

            // TASK 4
            // Functions used: read, hasDigit, printRomanNumber
            printf("Input:");
            text = read();
            if (hasDigit(text)) {
                int number = strtol(text, NULL, 10);
                if (number > 0 && number < 4000) {
                    printf("Output: ");
                    for (int i = 1000; i > 0; i /= 10)
                        printRomanNumber((number / i) % 10, i);
                    printf("\n");
                } else printf("Output: error\n");
            } else {
                int valid = -1, decimal = 0;
                for (int i = 0; text[i] != '\0'; i++) {
                    if (text[i] == 'M') {
                        decimal += 1000;
                    } else if (text[i] == 'C' && text[i + 1] == 'M') {
                        decimal += 900;
                        i++;
                    } else if (text[i] == 'D') {
                        decimal += 500;
                    } else if (text[i] == 'C' && text[i + 1] == 'D') {
                        decimal += 400;
                        i++;
                    } else if (text[i] == 'C') {
                        decimal += 100;
                    } else if (text[i] == 'X' && text[i + 1] == 'C') {
                        decimal += 90;
                        i++;
                    } else if (text[i] == 'L') {
                        decimal += 50;
                    } else if (text[i] == 'X' && text[i + 1] == 'L') {
                        decimal += 40;
                        i++;
                    } else if (text[i] == 'X') {
                        decimal += 10;
                    } else if (text[i] == 'I' && text[i + 1] == 'X') {
                        decimal += 9;
                        i++;
                    } else if (text[i] == 'V') {
                        decimal += 5;
                    } else if (text[i] == 'I' && text[i + 1] == 'V') {
                        decimal += 4;
                        i++;
                    } else if (text[i] == 'I') {
                        decimal += 1;
                    } else {
                        valid = 0;
                        break;
                    }
                }
                if (valid) printf("Output: %d\n", decimal);
                else printf("Output: error\n");
            }
            free(text);

        } else if (command[0] == '5' && command[1] == '\0') {

            printHelp();

        } else if (command[0] == '6' && command[1] == '\0') {

            free(command);
            break;

        }

        free(command);
    }

    return 0;
}
