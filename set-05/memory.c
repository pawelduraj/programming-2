#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Returns random number from range [0, 9].
int random() {
    return rand() % 10;
}

int main() {

    int x, y, z;


    // TASK 1
    x = 15;

    // create 1d array and fill it with random numbers
    int *array = malloc(x * sizeof(int));
    for (int i = 0; i < x; i++)
        array[i] = random();

    // print 1d array
    printf("TASK 1\nx = %d\nA =", x);
    for (int i = 0; i < x; i++)
        printf(" %d", array[i]);

    // print 1d array without duplicates
    printf("\nB =");
    for (int i = 0; i < x; i++) {
        int found = 0;
        for (int j = 0; j < i; j++) {
            if (array[i] == array[j]) {
                found = -1;
                break;
            }
        }
        if (!found) printf(" %d", array[i]);
    }
    printf("\n\n");

    // release memory
    free(array);


    // TASK 2
    x = 5, y = 7;

    // create 2d array and fill it with random numbers
    int **array2d = (int **) malloc(x * sizeof(int *));
    for (int i = 0; i < x; i++) {
        array2d[i] = (int *) malloc(y * sizeof(int));
        for (int j = 0; j < y; j++)
            array2d[i][j] = random();
    }

    // print 2d array
    printf("TASK 2\nx = %d\ny = %d\nA =", x, y);
    for (int i = 0; i < x; i++) {
        if (i != 0) printf("   ");
        for (int j = 0; j < y; j++)
            printf(" %d", array2d[i][j]);
        printf("\n");
    }

    // sort numbers in each row
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            int min = j;
            for (int k = j + 1; k < y; k++)
                if (array2d[i][k] < array2d[i][min])
                    min = k;
            int temp = array2d[i][min];
            array2d[i][min] = array2d[i][j];
            array2d[i][j] = temp;
        }
    }

    // calculate standard deviation for each row
    double *deviations = (double *) malloc(x * sizeof(double));
    for (int i = 0; i < x; i++) {
        int intSum = 0;
        for (int j = 0; j < y; j++)
            intSum += array2d[i][j];
        double avg = intSum / (double) y;
        double doubleSum = 0;
        for (int j = 0; j < y; j++)
            doubleSum += (array2d[i][j] - avg) * (array2d[i][j] - avg);
        deviations[i] = sqrt(doubleSum / y);
    }

    // sort rows in 2d array
    for (int i = 0; i < x; i++) {
        int min = i;
        for (int j = i + 1; j < x; j++)
            if (deviations[j] < deviations[i])
                min = j;
        double tempDouble = deviations[i];
        deviations[i] = deviations[min];
        deviations[min] = tempDouble;
        int *tempArray = array2d[i];
        array2d[i] = array2d[min];
        array2d[min] = tempArray;
    }

    // print 2d array
    printf("B =");
    for (int i = 0; i < x; i++) {
        if (i != 0) printf("   ");
        for (int j = 0; j < y; j++)
            printf(" %d", array2d[i][j]);
        printf("\n");
    }
    printf("\n");

    // release memory
    free(deviations);
    for (int i = 0; i < x; i++)
        free(array2d[i]);
    free(array2d);


    // TASK 3
    x = 2, y = 3, z = 4;

    // create 3d array and fill it with random numbers
    int ***array3d = (int ***) malloc(x * sizeof(int **));
    for (int i = 0; i < x; i++) {
        array3d[i] = (int **) malloc(y * sizeof(int *));
        for (int j = 0; j < y; j++) {
            array3d[i][j] = (int *) malloc(z * sizeof(int));
            for (int k = 0; k < z; k++)
                array3d[i][j][k] = random();
        }
    }

    // print 3d array
    printf("TASK 3\nx = %d\ny = %d\nz = %d\nARRAY:\n", x, y, z);
    for (int i = 0; i < x; i++) {
        printf("x = %d, y = [1, %d], z = [1, %d]\n", i + 1, y, z);
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++)
                printf("%d ", array3d[i][j][k]);
            printf("\n");
        }
    }

    // release memory
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            free(array3d[i][j]);
    for (int i = 0; i < x; i++)
        free(array3d[i]);
    free(array3d);


    return 0;
}
