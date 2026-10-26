
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX] = {0};
int vertices = 0;

/* Create a vertex */
void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }

    vertices++;
    printf("Vertex %d added successfully.\n", vertices);
}

/* Create an edge */
void createEdge()
{
    int u, v;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter two vertex numbers (1 to %d): ", vertices);
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices || v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    if (graph[u - 1][v - 1] == 1)
    {
        printf("Edge already exists!\n");
        return;
    }

    graph[u - 1][v - 1] = 1;
    graph[v - 1][u - 1] = 1;

    printf("Edge added successfully.\n");
}

/* Read and display the graph */
void readGraph()
{
    int i, j;
    int isolatedVertex = 0;

    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }

    for (i = 0; i < vertices; i++)
    {
        int connected = 0;

        for (j = 0; j < vertices; j++)
        {
            if (graph[i][j] == 1)
            {
                connected = 1;
                break;
            }
        }

        if (connected == 0)
        {
            isolatedVertex = 1;
            break;
        }
    }

    if (isolatedVertex == 1)
    {
        printf("No graph exists. All vertices are not connected.\n");
        return;
    }

    printf("\nGraph Representation (Adjacency List):\n\n");

    for (i = 0; i < vertices; i++)
    {
        printf("%d -> ", i + 1);

        int found = 0;

        for (j = 0; j < vertices; j++)
        {
            if (graph[i][j] == 1)
            {
                printf("%d ", j + 1);
                found = 1;
            }
        }

        if (found == 0)
            printf("No connections");

        printf("\n");
    }
}

/* Update an edge */
void updateEdge()
{
    int u, v, choice;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices || v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    if (graph[u - 1][v - 1] == 1)
    {
        printf("Edge already exists between %d and %d.\n", u, v);
        printf("1. Remove Edge\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            graph[u - 1][v - 1] = 0;
            graph[v - 1][u - 1] = 0;
            printf("Edge removed successfully.\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
    else
    {
        printf("No edge exists between %d and %d.\n", u, v);
        printf("1. Add Edge\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            graph[u - 1][v - 1] = 1;
            graph[v - 1][u - 1] = 1;
            printf("Edge added successfully.\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

/* Delete an edge */
void deleteEdge()
{
    int u, v;

    if (vertices < 2)
    {
        printf("At least two vertices are required.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (u < 1 || u > vertices || v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    if (graph[u - 1][v - 1] == 0)
    {
        printf("No edge exists between %d and %d.\n", u, v);
        return;
    }

    graph[u - 1][v - 1] = 0;
    graph[v - 1][u - 1] = 0;

    printf("Edge deleted successfully.\n");
}

/* Delete a vertex */
void deleteVertex()
{
    int v, i, j;

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter vertex number to delete (1 to %d): ", vertices);
    scanf("%d", &v);

    if (v < 1 || v > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    v--;

    /* Shift rows upward */
    for (i = v; i < vertices - 1; i++)
    {
        for (j = 0; j < vertices; j++)
            graph[i][j] = graph[i + 1][j];
    }

    /* Shift columns leftward */
    for (j = v; j < vertices - 1; j++)
    {
        for (i = 0; i < vertices - 1; i++)
            graph[i][j] = graph[i][j + 1];
    }

    vertices--;

    /* Clear unused row and column */
    for (i = 0; i < MAX; i++)
    {
        graph[vertices][i] = 0;
        graph[i][vertices] = 0;
    }

    printf("Vertex deleted successfully.\n");
}

/* BFS: Breadth-First Search */
void BFS()
{
    int start;
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int current, i;

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter starting vertex (1 to %d): ", vertices);
    scanf("%d", &start);

    if (start < 1 || start > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    queue[rear++] = start;
    visited[start - 1] = 1;

    printf("BFS Traversal: ");

    while (front < rear)
    {
        current = queue[front++];
        printf("%d ", current);

        for (i = 0; i < vertices; i++)
        {
            if (graph[current - 1][i] == 1 &&
                visited[i] == 0)
            {
                queue[rear++] = i + 1;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

/* DFS helper function */
void DFS_Visit(int v, int visited[])
{
    int i;

    visited[v - 1] = 1;
    printf("%d ", v);

    for (i = 0; i < vertices; i++)
    {
        if (graph[v - 1][i] == 1 &&
            visited[i] == 0)
        {
            DFS_Visit(i + 1, visited);
        }
    }
}

/* DFS: Depth-First Search */
void DFS()
{
    int start;
    int visited[MAX] = {0};

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter starting vertex (1 to %d): ", vertices);
    scanf("%d", &start);

    if (start < 1 || start > vertices)
    {
        printf("Invalid vertex number!\n");
        return;
    }

    printf("DFS Traversal: ");
    DFS_Visit(start, visited);
    printf("\n");
}

/* Main function */
int main()
{
    int choice;

    do
    {
        printf("\n--- GRAPH CRUD MENU ---\n");
        printf("1. Create Vertex\n");
        printf("2. Create Edge\n");
        printf("3. Read Graph\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Delete Vertex\n");
        printf("7. BFS Traversal\n");
        printf("8. DFS Traversal\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                createVertex();
                break;

            case 2:
                createEdge();
                break;

            case 3:
                readGraph();
                break;

            case 4:
                updateEdge();
                break;

            case 5:
                deleteEdge();
                break;

            case 6:
                deleteVertex();
                break;

            case 7:
                BFS();
                break;

            case 8:
                DFS();
                break;

            case 9:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 9);

    return 0;
}
