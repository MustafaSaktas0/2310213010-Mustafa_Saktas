#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////
typedef struct Edge {
    int to;
    struct Edge *next;
} edge;

typedef struct {
    int nodeCount;
    edge **adj;
} graph;

typedef struct {
    int *arr;
    int front;
    int back;
    int capacity;
} queue;
//////////////////////////////////////////////////////////////////

graph create_graph(int nodeCount);
void free_graph(graph *g);

void graph_add_edge_undirected(graph *g, int from, int to);
void graph_print(graph *g);

void bfs_traversal(graph *g, int startNode);
void dfs_traversal(graph *g, int startNode);
void dfs_traversal_recursive(graph *g, int currentNode, int *visitedArr);

queue create_queue(int capacity);
void free_queue(queue *q);
int queue_is_empty(queue *q);
void queue_push(queue *q, int value);
int queue_pop(queue *q);

void menu();

//////////////////////////////////////////////////////////////////

int main()
{
    int nodeCount;
    printf("Enter node count: ");
    scanf("%d", &nodeCount);

    graph g = create_graph(nodeCount);

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
                int from, to;
                printf("Enter from node: ");
                scanf("%d", &from);
                printf("Enter to node: ");
                scanf("%d", &to);

                graph_add_edge_undirected(&g, from, to);
                printf("Edge added successfully.\n");
                break;
            }
            case 2:
            {
                int startNode;
                printf("Enter start node for BFS: ");
                scanf("%d", &startNode);
                bfs_traversal(&g, startNode);
                break;
            }
            case 3:
            {
                int startNode;
                printf("Enter start node for DFS: ");
                scanf("%d", &startNode);
                dfs_traversal(&g, startNode);
                break;
            }
            case 4:
                graph_print(&g);
                break;

            case 0:
                free_graph(&g);
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
    printf("\n==================== DFS / BFS MENU ====================\n");
    printf("1- Add Undirected Edge\n");
    printf("2- BFS Traversal\n");
    printf("3- DFS Traversal\n");
    printf("4- Print Graph (Adjacency List)\n");
    printf("0- Exit\n");
    printf("=========================================================\n");
}

graph create_graph(int nodeCount)
{
    graph g;
    g.nodeCount = nodeCount;

    g.adj = (edge**)calloc(nodeCount, sizeof(edge*));
    if (g.adj == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    return g;
}

void free_graph(graph *g)
{
    for (int i = 0; i < g->nodeCount; i++)
    {
        edge *iter = g->adj[i];
        while (iter != NULL)
        {
            edge *temp = iter;
            iter = iter->next;
            free(temp);
        }
    }

    free(g->adj);
    g->adj = NULL;
    g->nodeCount = 0;
}

void graph_add_edge_undirected(graph *g, int from, int to)
{
    if (from < 0 || from >= g->nodeCount || to < 0 || to >= g->nodeCount)
    {
        printf("Invalid node index!\n");
        return;
    }

    edge *new_edge_1 = (edge*)malloc(sizeof(edge));
    if (new_edge_1 == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }
    new_edge_1->to = to;
    new_edge_1->next = g->adj[from];
    g->adj[from] = new_edge_1;

    edge *new_edge_2 = (edge*)malloc(sizeof(edge));
    if (new_edge_2 == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }
    new_edge_2->to = from;
    new_edge_2->next = g->adj[to];
    g->adj[to] = new_edge_2;
}

void graph_print(graph *g)
{
    printf("\n--- Graph (Adjacency List) ---\n");
    for (int i = 0; i < g->nodeCount; i++)
    {
        printf("%d: ", i);
        edge *iter = g->adj[i];
        while (iter != NULL)
        {
            printf("%d ", iter->to);
            iter = iter->next;
        }
        printf("\n");
    }
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
    q->arr[q->back] = value;
    q->back++;
}

int queue_pop(queue *q)
{
    int value = q->arr[q->front];
    q->front++;
    return value;
}

void bfs_traversal(graph *g, int startNode)
{
    if (startNode < 0 || startNode >= g->nodeCount)
    {
        printf("Invalid start node!\n");
        return;
    }

    int *visitedArr = (int*)calloc(g->nodeCount, sizeof(int));
    if (visitedArr == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    queue q = create_queue(g->nodeCount);

    visitedArr[startNode] = 1;
    queue_push(&q, startNode);

    printf("\nBFS: ");
    while (!queue_is_empty(&q))
    {
        int currentNode = queue_pop(&q);
        printf("%d ", currentNode);

        edge *iter = g->adj[currentNode];
        while (iter != NULL)
        {
            if (visitedArr[iter->to] == 0)
            {
                visitedArr[iter->to] = 1;
                queue_push(&q, iter->to);
            }
            iter = iter->next;
        }
    }
    printf("\n");

    free_queue(&q);
    free(visitedArr);
}

void dfs_traversal(graph *g, int startNode)
{
    if (startNode < 0 || startNode >= g->nodeCount)
    {
        printf("Invalid start node!\n");
        return;
    }

    int *visitedArr = (int*)calloc(g->nodeCount, sizeof(int));
    if (visitedArr == NULL)
    {
        printf("Memory not allocated!\n");
        exit(1);
    }

    printf("\nDFS: ");
    dfs_traversal_recursive(g, startNode, visitedArr);
    printf("\n");

    free(visitedArr);
}

void dfs_traversal_recursive(graph *g, int currentNode, int *visitedArr)
{
    visitedArr[currentNode] = 1;
    printf("%d ", currentNode);

    edge *iter = g->adj[currentNode];
    while (iter != NULL)
    {
        if (visitedArr[iter->to] == 0)
            dfs_traversal_recursive(g, iter->to, visitedArr);

        iter = iter->next;
    }
}
