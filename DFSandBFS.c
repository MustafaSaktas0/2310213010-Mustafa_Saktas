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
int queue_push(queue *q, int value);
int queue_pop(queue *q, int *outValue);

int graph_has_edge(graph *g, int from, int to);

void menu();

//////////////////////////////////////////////////////////////////

int main()
{
    int nodeCount;
    printf("Enter node count: ");
    if (scanf("%d", &nodeCount) != 1 || nodeCount <= 0)
    {
        printf("Invalid node count!\n");
        return 0;
    }

    graph g = create_graph(nodeCount);

    while (1)
    {
        menu();

        int choice;
        printf("Select an option: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            break;
        }

        switch (choice)
        {
            case 1:
            {
                int from, to;
                printf("Enter from node: ");
                if (scanf("%d", &from) != 1) { printf("Invalid input!\n"); break; }
                printf("Enter to node: ");
                if (scanf("%d", &to) != 1) { printf("Invalid input!\n"); break; }

                graph_add_edge_undirected(&g, from, to);
                break;
            }
            case 2:
            {
                int startNode;
                printf("Enter start node for BFS: ");
                if (scanf("%d", &startNode) != 1) { printf("Invalid input!\n"); break; }
                bfs_traversal(&g, startNode);
                break;
            }
            case 3:
            {
                int startNode;
                printf("Enter start node for DFS: ");
                if (scanf("%d", &startNode) != 1) { printf("Invalid input!\n"); break; }
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

    free_graph(&g);
    return 0;
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
    if (g == NULL || g->adj == NULL)
        return;

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

int graph_has_edge(graph *g, int from, int to)
{
    edge *iter = g->adj[from];
    while (iter != NULL)
    {
        if (iter->to == to)
            return 1;
        iter = iter->next;
    }
    return 0;
}

void graph_add_edge_undirected(graph *g, int from, int to)
{
    if (from < 0 || from >= g->nodeCount || to < 0 || to >= g->nodeCount)
    {
        printf("Invalid node index!\n");
        return;
    }

    // İstersen self-loop istemiyorsan aç:
    // if (from == to) { printf("Self-loop is not allowed!\n"); return; }

    // duplicate edge engelleme (isteğe bağlı ama temiz)
    if (graph_has_edge(g, from, to))
    {
        printf("Edge already exists!\n");
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

    printf("Edge added successfully.\n");
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

// success => 1, fail => 0
int queue_push(queue *q, int value)
{
    if (q->back >= q->capacity)
        return 0;

    q->arr[q->back] = value;
    q->back++;
    return 1;
}

// success => 1, fail => 0
int queue_pop(queue *q, int *outValue)
{
    if (queue_is_empty(q))
        return 0;

    *outValue = q->arr[q->front];
    q->front++;
    return 1;
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
    if (!queue_push(&q, startNode))
    {
        printf("Queue overflow!\n");
        free_queue(&q);
        free(visitedArr);
        return;
    }

    printf("\nBFS: ");
    while (!queue_is_empty(&q))
    {
        int currentNode;
        queue_pop(&q, &currentNode);
        printf("%d ", currentNode);

        edge *iter = g->adj[currentNode];
        while (iter != NULL)
        {
            if (visitedArr[iter->to] == 0)
            {
                visitedArr[iter->to] = 1;

                if (!queue_push(&q, iter->to))
                {
                    printf("\nQueue overflow!\n");
                    free_queue(&q);
                    free(visitedArr);
                    return;
                }
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
