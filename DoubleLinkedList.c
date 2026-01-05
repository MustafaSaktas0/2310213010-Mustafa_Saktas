#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} node;
//////////////////////////////////////////////////////////////////

node* create_doubly_linkedlist_node(int data);

void add_node_head_of_doubly_linkedlist(node **root, int data);
void add_node_end_of_doubly_linkedlist(node **root, int data);
void add_node_after_selected_value(node **root, int afterValue, int data);

void delete_node_head_of_doubly_linkedlist(node **root);
void delete_node_end_of_doubly_linkedlist(node **root);
void delete_node_selected_value(node **root, int value);

void write_doubly_linkedlist_forward(node *root);
void write_doubly_linkedlist_backward(node *root);

void menu()
{
    printf("\n================ DOUBLY LINKED LIST MENU ================\n");
    printf("1- Add Node at the End\n");
    printf("2- Add Node at the Head\n");
    printf("3- Add Node After Selected Value\n");
    printf("4- Delete Node at the End\n");
    printf("5- Delete Node at the Head\n");
    printf("6- Delete Node with Selected Value\n");
    printf("7- Write Forward\n");
    printf("8- Write Backward\n");
    printf("0- Exit\n");
    printf("=========================================================\n");
}

//////////////////////////////////////////////////////////////////

int main()
{
    node *root = NULL;

    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("Exiting program.\n");
            break;
        }

        switch (choice)
        {
            case 1:
            {
                int data;
                printf("Enter data: ");
                scanf("%d", &data);
                add_node_end_of_doubly_linkedlist(&root, data);
                break;
            }
            case 2:
            {
                int data;
                printf("Enter data: ");
                scanf("%d", &data);
                add_node_head_of_doubly_linkedlist(&root, data);
                break;
            }
            case 3:
            {
                int afterValue, data;
                printf("Enter after which value: ");
                scanf("%d", &afterValue);
                printf("Enter new data: ");
                scanf("%d", &data);
                add_node_after_selected_value(&root, afterValue, data);
                break;
            }
            case 4:
                delete_node_end_of_doubly_linkedlist(&root);
                break;
            case 5:
                delete_node_head_of_doubly_linkedlist(&root);
                break;
            case 6:
            {
                int value;
                printf("Enter value to delete: ");
                scanf("%d", &value);
                delete_node_selected_value(&root, value);
                break;
            }
            case 7:
                write_doubly_linkedlist_forward(root);
                break;
            case 8:
                write_doubly_linkedlist_backward(root);
                break;
            default:
                printf("Invalid option!\n");
        }
    }

    // free all nodes
    while (root != NULL)
        delete_node_head_of_doubly_linkedlist(&root);

    return 0;
}

//////////////////////////////////////////////////////////////////

node* create_doubly_linkedlist_node(int data)
{
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void add_node_head_of_doubly_linkedlist(node **root, int data)
{
    node *new_node = create_doubly_linkedlist_node(data);

    if (*root == NULL)
    {
        *root = new_node;
        return;
    }

    new_node->next = *root;
    (*root)->prev = new_node;
    *root = new_node;
}

void add_node_end_of_doubly_linkedlist(node **root, int data)
{
    node *new_node = create_doubly_linkedlist_node(data);

    if (*root == NULL)
    {
        *root = new_node;
        return;
    }

    node *iter = *root;
    while (iter->next != NULL)
        iter = iter->next;

    iter->next = new_node;
    new_node->prev = iter;
}

void add_node_after_selected_value(node **root, int afterValue, int data)
{
    if (*root == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    node *iter = *root;
    while (iter != NULL && iter->data != afterValue)
        iter = iter->next;

    if (iter == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    node *new_node = create_doubly_linkedlist_node(data);

    new_node->next = iter->next;
    new_node->prev = iter;

    if (iter->next != NULL)
        iter->next->prev = new_node;

    iter->next = new_node;
}

void delete_node_head_of_doubly_linkedlist(node **root)
{
    if (*root == NULL)
    {
        printf("Nothing to delete!\n");
        return;
    }

    node *temp = *root;
    *root = (*root)->next;

    if (*root != NULL)
        (*root)->prev = NULL;

    free(temp);
}

void delete_node_end_of_doubly_linkedlist(node **root)
{
    if (*root == NULL)
    {
        printf("Nothing to delete!\n");
        return;
    }

    node *iter = *root;

    while (iter->next != NULL)
        iter = iter->next;

    // iter is last node
    if (iter->prev != NULL)
        iter->prev->next = NULL;
    else
        *root = NULL; // only one node existed

    free(iter);
}

void delete_node_selected_value(node **root, int value)
{
    if (*root == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    node *iter = *root;
    while (iter != NULL && iter->data != value)
        iter = iter->next;

    if (iter == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    if (iter->prev != NULL)
        iter->prev->next = iter->next;
    else
        *root = iter->next; // deleting head

    if (iter->next != NULL)
        iter->next->prev = iter->prev;

    free(iter);
    printf("Node deleted successfully.\n");
}

void write_doubly_linkedlist_forward(node *root)
{
    node *iter = root;
    printf("\n-------- FORWARD --------\n");
    while (iter != NULL)
    {
        printf("%d\n", iter->data);
        iter = iter->next;
    }
    printf("-------------------------\n");
}

void write_doubly_linkedlist_backward(node *root)
{
    if (root == NULL)
    {
        printf("\n(empty)\n");
        return;
    }

    node *iter = root;
    while (iter->next != NULL)
        iter = iter->next; // go tail

    printf("\n-------- BACKWARD -------\n");
    while (iter != NULL)
    {
        printf("%d\n", iter->data);
        iter = iter->prev;
    }
    printf("-------------------------\n");
}
