#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int vertices = 0;

void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }

    vertices++;
    printf("Vertex %d added successfully.\n", vertices - 1);
}

void createEdge()
{
    int u, v;

    printf("Enter two vertices: ");
    scanf("%d %d", &u, &v);

    if (u < 0 || v < 0 || u >= vertices || v >= vertices)
    {
        printf("Invalid vertices!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    graph[u][v] = 1;
    graph[v][u] = 1;

    printf("Edge added successfully.\n");
}

void readGraph()
{
    int i, j;

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("\nAdjacency Matrix:\n   ");
    for (i = 0; i < vertices; i++)
        printf("%d ", i);

    printf("\n");

    for (i = 0; i < vertices; i++)
    {
        printf("%d: ", i);

        for (j = 0; j < vertices; j++)
            printf("%d ", graph[i][j]);

        printf("\n");
    }
}

void updateEdge()
{
    int u, v, choice;

    printf("Enter two vertices: ");
    scanf("%d %d", &u, &v);

    if (u < 0 || v < 0 || u >= vertices || v >= vertices)
    {
        printf("Invalid vertices!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    printf("1. Add connection\n");
    printf("2. Remove connection\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        graph[u][v] = 1;
        graph[v][u] = 1;
        printf("Connection updated.\n");
    }
    else if (choice == 2)
    {
        graph[u][v] = 0;
        graph[v][u] = 0;
        printf("Connection removed.\n");
    }
    else
    {
        printf("Invalid choice!\n");
    }
}

void deleteEdge()
{
    int u, v;

    printf("Enter two vertices: ");
    scanf("%d %d", &u, &v);

    if (u < 0 || v < 0 || u >= vertices || v >= vertices)
    {
        printf("Invalid vertices!\n");
        return;
    }

    graph[u][v] = 0;
    graph[v][u] = 0;

    printf("Edge deleted successfully.\n");
}

void deleteVertex()
{
    int v, i, j;

    printf("Enter vertex to delete (0 to %d): ", vertices - 1);
    scanf("%d", &v);

    if (v < 0 || v >= vertices)
    {
        printf("Invalid vertex!\n");
        return;
    }

    /* Shift rows upward */
    for (i = v; i < vertices - 1; i++)
        for (j = 0; j < vertices; j++)
            graph[i][j] = graph[i + 1][j];

    /* Shift columns leftward */
    for (i = 0; i < vertices - 1; i++)
        for (j = v; j < vertices - 1; j++)
            graph[i][j] = graph[i][j + 1];

    vertices--;

    /* Clear unused matrix cells */
    for (i = 0; i < MAX; i++)
    {
        graph[vertices][i] = 0;
        graph[i][vertices] = 0;
    }

    printf("Vertex deleted successfully.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- GRAPH CRUD MENU ---\n");
        printf("1. Create Vertex\n");
        printf("2. Create Edge\n");
        printf("3. Read Graph\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Delete Vertex\n");
        printf("7. Exit\n");
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
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
