#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} node;
//////////////////////////////////////////////////////////////////

node* create_tree_node(int data);

node* create_tree_from_array(int *arr, int size, int index, int sentinelValue);

void write_tree_preorder(node *root);
void write_tree_inorder(node *root);
void write_tree_postorder(node *root);

void free_tree(node *root);

void menu();
void menu_traversal();

//////////////////////////////////////////////////////////////////

int main()
{
    int size;
    printf("Enter array size: ");
    scanf("%d", &size);

    int *arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    printf("\nEnter array values (use -1 for NULL node):\n");
    for (int i = 0; i < size; i++)
    {
        printf("arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    int sentinelValue = -1;
    node *root = NULL;

    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (root != NULL)
                {
                    free_tree(root);
                    root = NULL;
                }
                root = create_tree_from_array(arr, size, 0, sentinelValue);
                printf("Tree created successfully.\n");
                break;

            case 2:
            {
                if (root == NULL)
                {
                    printf("Tree is not created yet. First create (choice 1).\n");
                    break;
                }

                menu_traversal();
                int tChoice;
                printf("Select traversal type: ");
                scanf("%d", &tChoice);

                if (tChoice == 1)
                {
                    printf("\nPreorder: ");
                    write_tree_preorder(root);
                    printf("\n");
                }
                else if (tChoice == 2)
                {
                    printf("\nInorder: ");
                    write_tree_inorder(root);
                    printf("\n");
                }
                else if (tChoice == 3)
                {
                    printf("\nPostorder: ");
                    write_tree_postorder(root);
                    printf("\n");
                }
                else
                {
                    printf("Invalid traversal type!\n");
                }

                break;
            }

            case 0:
                if (root != NULL)
                    free_tree(root);
                free(arr);
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
    printf("\n==================== TREE MENU ====================\n");
    printf("1- Create Tree from Array\n");
    printf("2- Traverse Tree\n");
    printf("0- Exit\n");
    printf("===================================================\n");
}

void menu_traversal()
{
    printf("\n============== TRAVERSAL MENU ==============\n");
    printf("1- Preorder\n");
    printf("2- Inorder\n");
    printf("3- Postorder\n");
    printf("===========================================\n");
}

node* create_tree_node(int data)
{
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node* create_tree_from_array(int *arr, int size, int index, int sentinelValue)
{
    if (index >= size)
        return NULL;

    if (arr[index] == sentinelValue)
        return NULL;

    node *root = create_tree_node(arr[index]);

    root->left = create_tree_from_array(arr, size, 2 * index + 1, sentinelValue);
    root->right = create_tree_from_array(arr, size, 2 * index + 2, sentinelValue);

    return root;
}

void write_tree_preorder(node *root)
{
    if (root == NULL) return;
    printf("%d ", root->data);
    write_tree_preorder(root->left);
    write_tree_preorder(root->right);
}

void write_tree_inorder(node *root)
{
    if (root == NULL) return;
    write_tree_inorder(root->left);
    printf("%d ", root->data);
    write_tree_inorder(root->right);
}

void write_tree_postorder(node *root)
{
    if (root == NULL) return;
    write_tree_postorder(root->left);
    write_tree_postorder(root->right);
    printf("%d ", root->data);
}

void free_tree(node *root)
{
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
