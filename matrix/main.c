#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct sparseMatrix {
    element data[MAX_TERMS];
    int rows;
    int cols;
    int terms;
} SparseMatrix;

SparseMatrix* matrix_transpose(SparseMatrix* a)
{
    SparseMatrix* b = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if (b == NULL) {
        fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다.\n");
        exit(1);
    }
    int bindex = 0;

    b->rows = a->cols;
    b->cols = a->rows;
    b->terms = a->terms;

    for (int c = 0; c < a->cols; c++) {
        for (int i = 0; i < a->terms; i++) {
            if (a->data[i].col == c) {
                b->data[bindex].row = a->data[i].col;
                b->data[bindex].col = a->data[i].row;
                b->data[bindex].value = a->data[i].value;
                bindex++;
            }
        }
    }
    return b;
}

void matrix_print(SparseMatrix* a)
{
    printf("The transposed matrix is:\n");
    for (int i = 0; i < a->terms; i++) {
        printf("%d, %d, %d \n", a->data[i].row, a->data[i].col, a->data[i].value);
    }
}

int main(void)
{
    int row, col, terms;
    printf("Enter the number of rows, columns, and non-zero terms: ");
    scanf_s("%d %d %d", &row, &col, &terms);

    SparseMatrix m = { .terms = terms, .rows = row, .cols = col };
    printf("Enter row, column, and value pairs in order: \n");
    for (int i = 0; i < terms; i++) {
        scanf_s("%d %d %d", &m.data[i].row, &m.data[i].col, &m.data[i].value);
    }

    SparseMatrix* result = matrix_transpose(&m);
    matrix_print(result);
    free(result);
    system("pause");
    return 0;
}
