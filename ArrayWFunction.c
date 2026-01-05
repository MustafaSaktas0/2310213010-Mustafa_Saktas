#include <stdio.h>
#include <stdlib.h>

void arrInsertSelectedIndex(int **arr, int *size, int index);
void arrDeleteSelectedIndex(int **arr, int *size, int index);
void arrPrintSelectedIndex(int *arr, int size, int index);
void arrPrintAllIndex(int *arr, int size);
void arrChangeValueSelectedIndex(int **arr, int *size, int index);

void menu()
{
    printf("\n============================================\n");
    printf("=================== MENU ===================\n");
    printf("1. Insert element at selected index\n");
    printf("2. Delete element at selected index\n");
    printf("3. Print element at selected index\n");
    printf("4. Change element value at selected index\n");
    printf("5. Print all elements\n");
    printf("0. Exit\n");
    printf("============================================\n\n");
}

/////////////////////////////////////////////////////////////////////////

int main()
{
    int size;

    printf("Enter the initial array size: ");
    scanf("%d", &size);

    int *arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory not allocated!\n");
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        printf("Enter the array's %d. index: ", i);
        scanf("%d", &arr[i]);
    }

    while (1)
    {
        menu();
        int choice, index;

        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                printf("Enter the index to insert: ");
                scanf("%d", &index);
                arrInsertSelectedIndex(&arr, &size, index);
                break;
            }
            case 2:
            {
                printf("Enter the index to delete: ");
                scanf("%d", &index);
                arrDeleteSelectedIndex(&arr, &size, index);
                break;
            }
            case 3:
            {
                printf("Enter the index to print: ");
                scanf("%d", &index);
                arrPrintSelectedIndex(arr, size, index);
                break;
            }
            case 4:
            {
                printf("Enter the index number to change the value: ");
                scanf("%d", &index);
                arrChangeValueSelectedIndex(&arr, &size, index);
                break;
            }
            case 5:
            {
                arrPrintAllIndex(arr, size);
                break;
            }
            case 0:
            {
                free(arr);
                printf("Exiting program.\n");
                return 0;
            }
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

/////////////////////////////////////////////////////////////////////////

void arrInsertSelectedIndex(int **arr, int *size, int index)
{
    if (index < 0 || index > *size)
    {
        printf("\nInvalid index!\n");
        return;
    }

    int value;
    printf("Enter the value to insert: ");
    scanf("%d", &value);

    int *temp = (int*)realloc(*arr, (*size + 1) * sizeof(int));
    if (temp == NULL)
    {
        printf("\nMemory reallocation failed!\n");
        exit(1);
    }
    *arr = temp;

    for (int i = *size; i > index; i--)
    {
        (*arr)[i] = (*arr)[i - 1];
    }

    (*arr)[index] = value;
    (*size)++;

    printf("\nElement inserted successfully.\n");
}

void arrDeleteSelectedIndex(int **arr, int *size, int index)
{
    if (index < 0 || index >= *size)
    {
        printf("\nInvalid index!\n");
        return;
    }

    for (int i = index; i < *size - 1; i++)
    {
        (*arr)[i] = (*arr)[i + 1];
    }

    (*size)--;

    if (*size == 0)
    {
        free(*arr);
        *arr = NULL;
        printf("\nElement deleted successfully.\n");
        return;
    }

    int *temp = (int*)realloc(*arr, (*size) * sizeof(int));
    if (temp == NULL)
    {
        printf("\nMemory reallocation failed!\n");
        exit(1);
    }
    *arr = temp;

    printf("\nElement deleted successfully.\n");
}

void arrPrintSelectedIndex(int *arr, int size, int index)
{
    if (index < 0 || index >= size)
    {
        printf("\nInvalid index!\n");
        return;
    }

    printf("\nSelected index = %d , value = %d\n", index, arr[index]);
}

void arrChangeValueSelectedIndex(int **arr, int *size, int index)
{
    if (index < 0 || index >= *size)
    {
        printf("\nInvalid index!\n");
        return;
    }

    int newValue;
    printf("Enter the new value: ");
    scanf("%d", &newValue);

    (*arr)[index] = newValue;
    printf("\nElement value changed successfully.\n");
}

void arrPrintAllIndex(int *arr, int size)
{
    printf("\n==========================\n");
    printf("Array Elements:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d. index value = %d\n", i, arr[i]);
    }
    printf("==========================\n");
}
