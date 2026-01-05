#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////
typedef struct {
    int *arr;        // 1-indexed
    int size;
    int capacity;
    int isMinHeap;   // 1 => MinHeap, 0 => MaxHeap
} heap;
//////////////////////////////////////////////////////////////////

heap create_heap(int capacity, int isMinHeap);
void free_heap(heap *h);

void heap_insert(heap *h, int value);
int heap_delete_root(heap *h);
int heap_get_root(heap *h);

void heap_print(heap *h);

void menu();
void menu_select_heap();

int heap_compare(heap *h, int childValue, int parentValue);
void heap_swap(int *a, int *b);

//////////////////////////////////////////////////////////////////

int main()
{
    int heapTypeChoice;
    menu_select_heap();
    printf("Select heap type: ");
    scanf("%d", &heapTypeChoice);

    int isMinHeap = 1;
    if (heapTypeChoice == 1) isMinHeap = 1;
    else if (heapTypeChoice == 2) isMinHeap = 0;
    else
    {
        printf("Invalid heap type!\n");
        return 0;
    }

    heap h = create_heap(10, isMinHeap);

    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                int value;
                printf("Enter value to insert: ");
                scanf("%d", &value);
                heap_insert(&h, value);
                printf("Inserted successfully.\n");
                break;
            }
            case 2:
            {
                if (h.size == 0)
                {
                    printf("Heap is empty!\n");
                    break;
                }
                int deletedValue = heap_delete_root(&h);
                printf("Deleted root = %d\n", deletedValue);
                break;
            }
            case 3:
            {
                if (h.size == 0)
                {
                    printf("Heap is empty!\n");
                    break;
                }
                printf("Root = %d\n", heap_get_root(&h));
                break;
            }
            case 4:
                heap_print(&h);
                break;

            case 0:
                free_heap(&h);
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid option!\n");
        }
    }
}

//////////////////////////////////////////////////////////////////

void menu_select_heap()
{
    printf("\n==================== HEAP TYPE MENU ====================\n");
    printf("1- Min Heap\n");
    printf("2- Max Heap\n");
    printf("========================================================\n");
}

void menu()
{
    printf("\n==================== HEAP MENU ====================\n");
    printf("1- Insert\n");
    printf("2- Delete Root (Pop)\n");
    printf("3- Get Root (Peek)\n");
    printf("4- Print Heap Array\n");
    printf("0- Exit\n");
    printf("====================================================\n");
}

heap create_heap(int capacity, int isMinHeap)
{
    heap h;
    h.arr = (int*)malloc((capacity + 1) * sizeof(int));
    if (h.arr == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    h.size = 0;
    h.capacity = capacity;
    h.isMinHeap = isMinHeap;
    return h;
}

void free_heap(heap *h)
{
    free(h->arr);
    h->arr = NULL;
    h->size = 0;
    h->capacity = 0;
}

void heap_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// if child should go above parent => 1
int heap_compare(heap *h, int childValue, int parentValue)
{
    if (h->isMinHeap == 1)
        return childValue < parentValue;
    else
        return childValue > parentValue;
}

void heap_insert(heap *h, int value)
{
    if (h->size == h->capacity)
    {
        h->capacity = h->capacity * 2;
        int *temp = (int*)realloc(h->arr, (h->capacity + 1) * sizeof(int));
        if (temp == NULL)
        {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
        h->arr = temp;
    }

    h->size++;
    h->arr[h->size] = value;

    int index = h->size;
    while (index > 1)
    {
        int parentIndex = index / 2;

        if (heap_compare(h, h->arr[index], h->arr[parentIndex]))
        {
            heap_swap(&h->arr[index], &h->arr[parentIndex]);
            index = parentIndex;
        }
        else
        {
            break;
        }
    }
}

int heap_get_root(heap *h)
{
    return h->arr[1];
}

int heap_delete_root(heap *h)
{
    int rootValue = h->arr[1];

    h->arr[1] = h->arr[h->size];
    h->size--;

    int index = 1;
    while (1)
    {
        int leftIndex = index * 2;
        int rightIndex = index * 2 + 1;
        int bestIndex = index;

        if (leftIndex <= h->size && heap_compare(h, h->arr[leftIndex], h->arr[bestIndex]))
            bestIndex = leftIndex;

        if (rightIndex <= h->size && heap_compare(h, h->arr[rightIndex], h->arr[bestIndex]))
            bestIndex = rightIndex;

        if (bestIndex != index)
        {
            heap_swap(&h->arr[index], &h->arr[bestIndex]);
            index = bestIndex;
        }
        else
        {
            break;
        }
    }

    return rootValue;
}

void heap_print(heap *h)
{
    printf("\n-------- HEAP ARRAY --------\n");
    if (h->size == 0)
    {
        printf("(empty)\n");
        printf("----------------------------\n");
        return;
    }

    for (int i = 1; i <= h->size; i++)
    {
        printf("%d. index = %d\n", i, h->arr[i]);
    }
    printf("----------------------------\n");
}
