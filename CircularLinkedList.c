#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////
typedef struct Node {
    int data;
    struct Node *next;
} node;
//////////////////////////////////////////////////////////////////

node* create_circular_node(int data);

void add_node_head_of_circular_linkedlist(node **root, int data);
void add_node_end_of_circular_linkedlist(node **root, int data);
void add_node_after_selected_value_circular(node **root, int afterValue, int data);

void delete_node_head_of_circular_linkedlist(node **root);
void delete_node_end_of_circular_linkedlist(node **root);
void delete_node_selected_value_circular(node **root, int value);

void write_circular_linkedlist(node *root);

void menu()
{
    printf("\n============= CIRCULAR LINKED LIST MENU =============\n");
    printf("1- Add Node at the End\n");
    printf("2- Add Node at the Head\n");
    printf("3- Add Node After Selected Value\n");
    printf("4- Delete Node at the End\n");
    printf("5- Delete Node at the Head\n");
    printf("6- Delete Node with Selected Value\n");
    printf("7- Write Circular Linked List\n");
    printf("0- Exit\n");
    printf("=====================================================\n");
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
                add_node_end_of_circular_linkedlist(&root, data);
                break;
            }
            case 2:
            {
                int data;
                printf("Enter data: ");
                scanf("%d", &data);
                add_node_head_of_circular_linkedlist(&root, data);
                break;
            }
            case 3:
            {
                int afterValue, data;
                printf("Enter after which value: ");
                scanf("%d", &afterValue);
                printf("Enter new data: ");
                scanf("%d", &data);
                add_node_after_selected_value_circular(&root, afterValue, data);
                break;
            }
            case 4:
                delete_node_end_of_circular_linkedlist(&root);
                break;
            case 5:
                delete_node_head_of_circular_linkedlist(&root);
                break;
            case 6:
            {
                int value;
                printf("Enter value to delete: ");
                scanf("%d", &value);
                delete_node_selected_value_circular(&root, value);
                break;
            }
            case 7:
                write_circular_linkedlist(root);
                break;
            default:
                printf("Invalid option!\n");
        }
    }

    // free all nodes
    while (root != NULL)
        delete_node_head_of_circular_linkedlist(&root);

    return 0;
}

//////////////////////////////////////////////////////////////////

node* create_circular_node(int data)
{
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = new_node; // circular
    return new_node;
}

void add_node_head_of_circular_linkedlist(node **root, int data)
{
    if (*root == NULL)
    {
        *root = create_circular_node(data);
        return;
    }

    // insert after root and swap data (simple head insert technique)
    node *new_node = create_circular_node(data);
    new_node->next = (*root)->next;
    (*root)->next = new_node;

    int temp = (*root)->data;
    (*root)->data = new_node->data;
    new_node->data = temp;
}

void add_node_end_of_circular_linkedlist(node **root, int data)
{
    if (*root == NULL)
    {
        *root = create_circular_node(data);
        return;
    }

    node *new_node = create_circular_node(data);

    node *iter = *root;
    while (iter->next != *root)
        iter = iter->next;

    iter->next = new_node;
    new_node->next = *root;
}

void add_node_after_selected_value_circular(node **root, int afterValue, int data)
{
    if (*root == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    node *iter = *root;
    do {
        if (iter->data == afterValue)
        {
            node *new_node = create_circular_node(data);
            new_node->next = iter->next;
            iter->next = new_node;
            return;
        }
        iter = iter->next;
    } while (iter != *root);

    printf("Value not found!\n");
}

void delete_node_head_of_circular_linkedlist(node **root)
{
    if (*root == NULL)
    {
        printf("Nothing to delete!\n");
        return;
    }

    // single node
    if ((*root)->next == *root)
    {
        free(*root);
        *root = NULL;
        return;
    }

    // copy next node into root, delete next node
    node *temp = (*root)->next;
    (*root)->data = temp->data;
    (*root)->next = temp->next;
    free(temp);
}

void delete_node_end_of_circular_linkedlist(node **root)
{
    if (*root == NULL)
    {
        printf("Nothing to delete!\n");
        return;
    }

    // single node
    if ((*root)->next == *root)
    {
        free(*root);
        *root = NULL;
        return;
    }

    node *iter = *root;
    node *prev = NULL;

    while (iter->next != *root)
    {
        prev = iter;
        iter = iter->next;
    }

    // iter is last node
    prev->next = *root;
    free(iter);
}

void delete_node_selected_value_circular(node **root, int value)
{
    if (*root == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    // if value is at root -> use head delete trick
    if ((*root)->data == value)
    {
        delete_node_head_of_circular_linkedlist(root);
        printf("Node deleted successfully.\n");
        return;
    }

    node *iter = *root;
    while (iter->next != *root && iter->next->data != value)
        iter = iter->next;

    if (iter->next == *root)
    {
        printf("Value not found!\n");
        return;
    }

    node *temp = iter->next;
    iter->next = temp->next;
    free(temp);

    printf("Node deleted successfully.\n");
}

void write_circular_linkedlist(node *root)
{
    if (root == NULL)
    {
        printf("\n(empty)\n");
        return;
    }

    node *iter = root;

    printf("\n-------- CIRCULAR LIST --------\n");
    do {
        printf("%d\n", iter->data);
        iter = iter->next;
    } while (iter != root);
    printf("--------------------------------\n");
}
