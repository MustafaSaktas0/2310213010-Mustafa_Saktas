#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////
typedef struct {
    int *arr;
    int front;
    int back;
    int capacity;
} queue;
//////////////////////////////////////////////////////////////////

queue create_queue(int capacity);
void free_queue(queue *q);
int queue_is_empty(queue *q);
void queue_push(queue *q, int value);
int queue_pop(queue *q);

int** create_adjacency_matrix(int nodeCount);
void fill_adjacency_matrix(int **graph, int nodeCount);
void print_adjacency_matrix(int **graph, int nodeCount);
void free_adjacency_matrix(int **graph, int nodeCount);

int find_clusters_bfs(int **graph, int nodeCount, int *clusterIdArr);
void print_clusters(int nodeCount, int *clusterIdArr, int clusterCount);

void menu();

//////////////////////////////////////////////////////////////////

int main()
{
    int nodeCount;
    printf("Enter node count: ");
    scanf("%d", &nodeCount);

    if (nodeCount <= 0)
    {
        printf("Invalid node count!\n");
        return 0;
    }

    int **graph = create_adjacency_matrix(nodeCount);
    fill_adjacency_matrix(graph, nodeCount);

    int *clusterIdArr = (int*)malloc(nodeCount * sizeof(int));
    if (clusterIdArr == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                print_adjacency_matrix(graph, nodeCount);
                break;

            case 2:
            {
                int clusterCount = find_clusters_bfs(graph, nodeCount, clusterIdArr);
                print_clusters(nodeCount, clusterIdArr, clusterCount);
                break;
            }

            case 0:
                free(clusterIdArr);
                free_adjacency_matrix(graph, nodeCount);
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
    printf("\n==================== CLUSTER MENU ====================\n");
    printf("1- Print Adjacency Matrix\n");
    printf("2- Find Clusters (Connected Components)\n");
    printf("0- Exit\n");
    printf("======================================================\n");
}

queue create_queue(int capacity)
{
    queue q;
    q.arr = (int*)malloc(capacity * sizeof(int));
    if (q.arr == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }
    q.front = 0;
    q.back = 0;
    q.capacity = capacity;
    return q;
}

void free_queue(queue *q)
{
    free(q->arr);
    q->arr = NULL;
    q->front = 0;
    q->back = 0;
    q->capacity = 0;
}

int queue_is_empty(queue *q)
{
    return q->front == q->back;
}

void queue_push(queue *q, int value)
{
    if (q->back >= q->capacity)
    {
        printf("Queue overflow!\n");
        return;
    }

    q->arr[q->back] = value;
    q->back++;
}

int queue_pop(queue *q)
{
    if (queue_is_empty(q))
    {
        printf("Queue underflow!\n");
        return -1;
    }

    int value = q->arr[q->front];
    q->front++;
    return value;
}

int** create_adjacency_matrix(int nodeCount)
{
    int **graph = (int**)malloc(nodeCount * sizeof(int*));
    if (graph == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    for (int i = 0; i < nodeCount; i++)
    {
        graph[i] = (int*)malloc(nodeCount * sizeof(int));
        if (graph[i] == NULL)
        {
            printf("Memory not allocated!\n");
            exit(1);
        }
    }

    return graph;
}

void fill_adjacency_matrix(int **graph, int nodeCount)
{
    printf("\nEnter adjacency matrix (0/1):\n");
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j++)
        {
            printf("graph[%d][%d]: ", i, j);
            scanf("%d", &graph[i][j]);
        }
    }
}

void print_adjacency_matrix(int **graph, int nodeCount)
{
    printf("\n--- Adjacency Matrix ---\n");
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void free_adjacency_matrix(int **graph, int nodeCount)
{
    for (int i = 0; i < nodeCount; i++)
        free(graph[i]);

    free(graph);
}

int find_clusters_bfs(int **graph, int nodeCount, int *clusterIdArr)
{
    for (int i = 0; i < nodeCount; i++)
        clusterIdArr[i] = -1;

    int clusterCount = 0;
    queue q = create_queue(nodeCount);

    for (int startNode = 0; startNode < nodeCount; startNode++)
    {
        if (clusterIdArr[startNode] != -1)
            continue;

        clusterIdArr[startNode] = clusterCount;
        queue_push(&q, startNode);

        while (!queue_is_empty(&q))
        {
            int currentNode = queue_pop(&q);

            // Underflow koruması: teoride olmaz, ama güvenli dursun
            if (currentNode == -1)
                break;

            for (int neighbor = 0; neighbor < nodeCount; neighbor++)
            {
                if (graph[currentNode][neighbor] == 1 && clusterIdArr[neighbor] == -1)
                {
                    clusterIdArr[neighbor] = clusterCount;
                    queue_push(&q, neighbor);
                }
            }
        }

        // reset queue pointers for next BFS
        q.front = 0;
        q.back = 0;

        clusterCount++;
    }

    free_queue(&q);
    return clusterCount;
}

void print_clusters(int nodeCount, int *clusterIdArr, int clusterCount)
{
    printf("\nCluster count = %d\n", clusterCount);

    for (int c = 0; c < clusterCount; c++)
    {
        printf("\nCluster %d: ", c);
        for (int i = 0; i < nodeCount; i++)
        {
            if (clusterIdArr[i] == c)
                printf("%d ", i);
        }
        printf("\n");
    }
}
