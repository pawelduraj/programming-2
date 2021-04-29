#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#define SIZE 4

struct matrix {
    double matrix[SIZE][SIZE];
};

// Prints the matrix given by first argument. Second argument is the number of characters reserved
// for a single element. Third argument is the number of decimal digits to be printed.
void print(const struct matrix *m, int characters, int precision) {
    for (int i = 0; i < SIZE; i++) {
        printf("|");
        for (int j = 0; j < SIZE; j++)
            printf("% *.*f ", characters, precision, m->matrix[i][j]);
        printf("|\n");
    }
}

// Fill the matrix with random values from range [0, 9].
void random(struct matrix *m) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            m->matrix[i][j] = rand() % 10;
}

// Fills the matrix with zeros.
void reset(struct matrix *m) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            m->matrix[i][j] = 0;
}

// Returns copy of the given matrix.
struct matrix copy(const struct matrix *m) {
    struct matrix result;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result.matrix[i][j] = m->matrix[i][j];
    return result;
}

// Fills the matrix with the given values.
void fill(struct matrix *m, ...) {
    va_list list;
    int size = SIZE * SIZE;
    va_start(list, size);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            m->matrix[i][j] = va_arg(list, int);
    va_end(list);
}

// Returns sum of two matrices.
struct matrix add(const struct matrix *m1, const struct matrix *m2) {
    struct matrix result;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result.matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];
    return result;
}

// Returns difference of two matrices.
struct matrix subtract(const struct matrix *m1, const struct matrix *m2) {
    struct matrix result;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result.matrix[i][j] = m1->matrix[i][j] - m2->matrix[i][j];
    return result;
}

// Returns product of matrix and number.
struct matrix multByNumber(const struct matrix *m1, double number) {
    struct matrix result;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result.matrix[i][j] = m1->matrix[i][j] * number;
    return result;
}

// Returns product of two matrices.
struct matrix mult(const struct matrix *m1, const struct matrix *m2) {
    struct matrix result;
    reset(&result);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                result.matrix[i][j] += m1->matrix[i][k] * m2->matrix[k][j];
    return result;
}

// Checks if matrices are equal.
bool equals(const struct matrix *m1, const struct matrix *m2) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (m1->matrix[i][j] != m2->matrix[i][j]) return false;
    return true;
}

// Returns the transposed matrix.
struct matrix transpose(const struct matrix *m) {
    struct matrix result;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result.matrix[i][j] = m->matrix[j][i];
    return result;
}

// Returns trace of the matrix.
double trace(const struct matrix *m) {
    double result = 0;
    for (int i = 0; i < SIZE; i++)
        result += m->matrix[i][i];
    return result;
}

// Checks if the matrix is a lower triangular matrix.
bool isLowerTriangular(const struct matrix *m) {
    for (int i = 0; i < SIZE; i++)
        for (int j = i + 1; j < SIZE; j++)
            if (m->matrix[i][j] != 0) return false;
    return true;
}

// Checks if the matrix is an upper triangular matrix.
bool isUpperTriangular(const struct matrix *m) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < i; j++)
            if (m->matrix[i][j] != 0) return false;
    return true;
}

// Checks if the matrix is an identity matrix.
bool isIdentity(const struct matrix *m) {
    if (!isLowerTriangular(m)) return 0;
    if (!isUpperTriangular(m)) return 0;
    for (int i = 0; i < SIZE; i++)
        if (m->matrix[i][i] != 1) return false;
    return true;
}

// Checks if the matrix is a sparse matrix.
bool isSparse(const struct matrix *m) {
    int zeros = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (m->matrix[i][j] == 0) zeros++;
    if (zeros > (SIZE * SIZE) / 2) return true;
    return false;
}

// Checks if the matrix is a symmetric matrix.
bool isSymmetric(const struct matrix *m) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < i; j++)
            if (m->matrix[i][j] != m->matrix[j][i]) return false;
    return true;
}

// Returns determinant of the matrix.
double det(const struct matrix *matrix, int MAX) {
    struct matrix m = copy(matrix);
    int swaps = 0;

    // for each element on the main diagonal
    for (int i = 0; i < MAX; i++) {

        // if the element on the main diagonal is 0
        if (m.matrix[i][i] == 0) {

            // for each row with index greater than i
            for (int k = i + 1; k < MAX; k++) {

                // if row with index k doesn't have zero in column with index i
                if (m.matrix[k][i] != 0) {

                    // swap rows i, k
                    for (int l = i; l < MAX; l++) {
                        double d = m.matrix[i][l];
                        m.matrix[i][l] = m.matrix[k][l];
                        m.matrix[k][l] = d;
                    }
                    swaps++;
                    break;
                }
            }
        }

        // if element on the main diagonal equals 0 then determinant is 0
        if (m.matrix[i][i] == 0) return 0;

        // for each row with index greater than i
        for (int j = i + 1; j < MAX; j++) {

            // add/subtract from each row below the index i row on the index i multiplied
            // by some value in order to get zeros in column i in rows with index greater than i
            double d = m.matrix[j][i] / m.matrix[i][i];
            for (int k = i; k < MAX; k++)
                m.matrix[j][k] -= (d * m.matrix[i][k]);
        }
    }

    // calculate and return the product of elements on the main diagonal
    double result = m.matrix[0][0];
    for (int i = 1; i < MAX; i++)
        result *= m.matrix[i][i];
    return (swaps % 2 == 0) ? result : -1 * result;
}

// Returns determinant of the matrix.
double determinant(const struct matrix *matrix) {
    return det(matrix, SIZE);
}

// Returns algebraic complement of the element with given indexes in the given matrix.
double algebraicComplement(const struct matrix *matrix, int row, int column) {
    struct matrix m = copy(matrix);
    for (int i = row + 1; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            m.matrix[i - 1][j] = m.matrix[i][j];
    for (int j = column + 1; j < SIZE; j++)
        for (int i = 0; i < SIZE; i++)
            m.matrix[i][j - 1] = m.matrix[i][j];
    if ((row + column) % 2 == 0) return det(&m, SIZE - 1);
    return -1 * det(&m, SIZE - 1);
}

// Corrects zeros in the matrix to eliminate negative zeros.
void correctZeros(struct matrix *m) {
    for (int i = 0; i <SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (m->matrix[i][j] == 0)
                m->matrix[i][j] = 0;
}

// Returns inverse of the matrix. Inversion is calculated using the following formula:
// A = 1/d * B
// d - determinant of given matrix
// B - transposed matrix of algebraic complement of the given matrix
struct matrix inverse(const struct matrix *m) {
    struct matrix result;
    double det = determinant(m);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result.matrix[j][i] = algebraicComplement(m, i, j) / det;
    correctZeros(&result);
    return result;
}

int main() {

    struct matrix a;
    struct matrix b;
    struct matrix c;


    // TEST 1
    printf("\nTEST 1\n");
    random(&a);
    random(&b);
    printf("A:\n");
    print(&a, 3, 0);
    printf("B:\n");
    print(&b, 3, 0);
    printf("A + B:\n");
    c = add(&a, &b);
    print(&c, 3, 0);
    printf("A - B:\n");
    c = subtract(&a, &b);
    print(&c, 3, 0);
    printf("A * B:\n");
    c = mult(&a, &b);
    print(&c, 4, 0);
    printf("A * 3:\n");
    c = multByNumber(&a, 3);
    print(&c, 3, 0);
    printf("A^T:\n");
    c = transpose(&a);
    print(&c, 3, 0);
    printf("A == B: %d\n", equals(&a, &b));


    // TEST 2
    printf("\nTEST 2\n");
    fill(&a, 1, 2, 3, 4, 0, 2, 3, 4, 0, 0, 3, 4, 0, 0, 0, 4);
    print(&a, 2, 0);
    printf("trace:               %.0f\n", trace(&a));
    printf("determinant:         %.0f\n", determinant(&a));
    printf("is lower triangular: %d\n", isLowerTriangular(&a));
    printf("is upper triangular: %d\n", isUpperTriangular(&a));
    printf("is identity:         %d\n", isIdentity(&a));
    printf("is sparse:           %d\n", isSparse(&a));
    printf("is symmetric:        %d\n", isSymmetric(&a));
    printf("inverse:\n");
    c = inverse(&a);
    print(&c, 5, 2);


    // TEST 3
    printf("\nTEST 3\n");
    fill(&a, 1, 0, 0, 0, 2, 1, 0, 0, 3, 2, 1, 0, 4, 3, 2, 1);
    print(&a, 2, 0);
    printf("trace:               %.0f\n", trace(&a));
    printf("determinant:         %.0f\n", determinant(&a));
    printf("is lower triangular: %d\n", isLowerTriangular(&a));
    printf("is upper triangular: %d\n", isUpperTriangular(&a));
    printf("is identity:         %d\n", isIdentity(&a));
    printf("is sparse:           %d\n", isSparse(&a));
    printf("is symmetric:        %d\n", isSymmetric(&a));
    printf("inverse:\n");
    c = inverse(&a);
    print(&c, 3, 0);


    // TEST 4
    printf("\nTEST 4\n");
    fill(&a, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    print(&a, 2, 0);
    printf("trace:               %.0f\n", trace(&a));
    printf("determinant:         %.0f\n", determinant(&a));
    printf("is lower triangular: %d\n", isLowerTriangular(&a));
    printf("is upper triangular: %d\n", isUpperTriangular(&a));
    printf("is identity:         %d\n", isIdentity(&a));
    printf("is sparse:           %d\n", isSparse(&a));
    printf("is symmetric:        %d\n", isSymmetric(&a));
    printf("inverse:\n");
    c = inverse(&a);
    print(&c, 2, 0);


    // TEST 5
    printf("\nTEST 5\n");
    fill(&a, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0);
    print(&a, 2, 0);
    printf("trace:               %.0f\n", trace(&a));
    printf("determinant:         %.0f\n", determinant(&a));
    printf("is lower triangular: %d\n", isLowerTriangular(&a));
    printf("is upper triangular: %d\n", isUpperTriangular(&a));
    printf("is identity:         %d\n", isIdentity(&a));
    printf("is sparse:           %d\n", isSparse(&a));
    printf("is symmetric:        %d\n", isSymmetric(&a));


    // TEST 6
    printf("\nTEST 6\n");
    fill(&a, 4, 0, 0, 2, 0, 4, 2, 0, 0, 2, 4, 0, 2, 0, 0, 4);
    print(&a, 2, 0);
    printf("trace:               %.0f\n", trace(&a));
    printf("determinant:         %.0f\n", determinant(&a));
    printf("is lower triangular: %d\n", isLowerTriangular(&a));
    printf("is upper triangular: %d\n", isUpperTriangular(&a));
    printf("is identity:         %d\n", isIdentity(&a));
    printf("is sparse:           %d\n", isSparse(&a));
    printf("is symmetric:        %d\n", isSymmetric(&a));
    printf("inverse:\n");
    c = inverse(&a);
    print(&c, 6, 2);


    // TEST 7
    printf("\nTEST 7\n");
    fill(&a, 5, 6, 2, 5, 0, -5, -1, 3, 0, -2, 8, -7, 2, 9, -7, 2);
    print(&a, 2, 0);
    printf("trace:               %.0f\n", trace(&a));
    printf("determinant:         %.0f\n", determinant(&a));
    printf("is lower triangular: %d\n", isLowerTriangular(&a));
    printf("is upper triangular: %d\n", isUpperTriangular(&a));
    printf("is identity:         %d\n", isIdentity(&a));
    printf("is sparse:           %d\n", isSparse(&a));
    printf("is symmetric:        %d\n", isSymmetric(&a));
    printf("inverse:\n");
    c = inverse(&a);
    print(&c, 10, 7);


    return 0;
}
