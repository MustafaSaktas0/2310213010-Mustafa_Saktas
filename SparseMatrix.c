#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////
// Triplet representation: (row, col, value)
typedef struct {
    int row;
    int col;
    int value;
} triplet;

typedef struct {
    int rowCount;
    int colCount;
    int nonZeroCount;
    triplet *data;
} sparseMatrix;
//////////////////////////////////////////////////////////////////

int* create_dense_matrix(int rowCount, int colCount);
void fill_dense_matrix(int *matrix, int rowCount, int colCount);
void print_dense_matrix(int *matrix, int rowCount, int colCount);

sparseMatrix convert_dense_to_sparse(int *matrix, int rowCount, int colCount);
int* convert_sparse_to_dense(sparseMatrix *s);

void print_sparse_matrix(sparseMatrix *s);
void free_sparse_matrix(sparseMatrix *s);

void menu();

//////////////////////////////////////////////////////////////////

int main()
{
    int rowCount, colCount;

    printf("Enter row count: ");
    scanf("%d", &rowCount);
    printf("Enter column count: ");
    scanf("%d", &colCount);

    int *denseMatrix = create_dense_matrix(rowCount, colCount);
    fill_dense_matrix(denseMatrix, rowCount, colCount);

    sparseMatrix sparse = {0,0,0,NULL};

    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\n--- DENSE MATRIX ---\n");
                print_dense_matrix(denseMatrix, rowCount, colCount);
                break;

            case 2:
                if (sparse.data != NULL)
                    free_sparse_matrix(&sparse);

                sparse = convert_dense_to_sparse(denseMatrix, rowCount, colCount);
                printf("\nConverted dense -> sparse successfully.\n");
                break;

            case 3:
                if (sparse.data == NULL)
                {
                    printf("\nSparse matrix is not created yet. First convert (choice 2).\n");
                }
                else
                {
                    printf("\n--- SPARSE (TRIPLET) ---\n");
                    print_sparse_matrix(&sparse);
                }
                break;

            case 4:
            {
                if (sparse.data == NULL)
                {
                    printf("\nSparse matrix is not created yet. First convert (choice 2).\n");
                    break;
                }

                int *denseFromSparse = convert_sparse_to_dense(&sparse);
                printf("\n--- DENSE FROM SPARSE ---\n");
                print_dense_matrix(denseFromSparse, sparse.rowCount, sparse.colCount);
                free(denseFromSparse);
                break;
            }

            case 0:
                if (sparse.data != NULL)
                    free_sparse_matrix(&sparse);

                free(denseMatrix);
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid option!\n");
        }
    }
}

//////////////////////////////////////////////////////////////////

void menu()
{
    printf("\n==================== SPARSE MATRIX MENU ====================\n");
    printf("1- Print Dense Matrix\n");
    printf("2- Convert Dense -> Sparse (Triplet)\n");
    printf("3- Print Sparse Matrix (Triplet)\n");
    printf("4- Convert Sparse -> Dense and Print\n");
    printf("0- Exit\n");
    printf("============================================================\n");
}

int* create_dense_matrix(int rowCount, int colCount)
{
    int *matrix = (int*)malloc(rowCount * colCount * sizeof(int));
    if (matrix == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }
    return matrix;
}

void fill_dense_matrix(int *matrix, int rowCount, int colCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            printf("Enter value at [%d][%d]: ", i, j);
            scanf("%d", &matrix[i * colCount + j]);
        }
    }
}

void print_dense_matrix(int *matrix, int rowCount, int colCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            printf("%d ", matrix[i * colCount + j]);
        }
        printf("\n");
    }
}

sparseMatrix convert_dense_to_sparse(int *matrix, int rowCount, int colCount)
{
    sparseMatrix s;
    s.rowCount = rowCount;
    s.colCount = colCount;
    s.nonZeroCount = 0;
    s.data = NULL;

    // count non-zero
    for (int i = 0; i < rowCount * colCount; i++)
    {
        if (matrix[i] != 0)
            s.nonZeroCount++;
    }

    s.data = (triplet*)malloc(s.nonZeroCount * sizeof(triplet));
    if (s.data == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    int k = 0;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            int value = matrix[i * colCount + j];
            if (value != 0)
            {
                s.data[k].row = i;
                s.data[k].col = j;
                s.data[k].value = value;
                k++;
            }
        }
    }

    return s;
}

int* convert_sparse_to_dense(sparseMatrix *s)
{
    int *dense = (int*)calloc(s->rowCount * s->colCount, sizeof(int));
    if (dense == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    for (int i = 0; i < s->nonZeroCount; i++)
    {
        int r = s->data[i].row;
        int c = s->data[i].col;
        dense[r * s->colCount + c] = s->data[i].value;
    }

    return dense;
}

void print_sparse_matrix(sparseMatrix *s)
{
    printf("rowCount=%d colCount=%d nonZeroCount=%d\n", s->rowCount, s->colCount, s->nonZeroCount);
    printf("row col value\n");

    for (int i = 0; i < s->nonZeroCount; i++)
    {
        printf("%d   %d   %d\n", s->data[i].row, s->data[i].col, s->data[i].value);
    }
}

void free_sparse_matrix(sparseMatrix *s)
{
    free(s->data);
    s->data = NULL;
    s->nonZeroCount = 0;
}