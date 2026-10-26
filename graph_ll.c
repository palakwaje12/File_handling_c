#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct Node
{
    int vertex;
    struct Node *next;
};

struct Node *head[MAX] = {NULL};
int vertices = 0;

/* Create a new adjacency-list node */
struct Node *createNode(int v)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = v;
    newNode->next = NULL;

    return newNode;
}

//to check if an edge exists in between two vertices
int edgeExists(int u, int v)
{
    struct Node *temp = head[u - 1];

    while (temp != NULL)
    {
        if (temp->vertex == v)
            return 1;
        temp = temp->next;
    }

    return 0;
}

/* Add an edge to one adjacency list */
void addConnection(int u, int v)
{
    struct Node *newNode = createNode(v);

    newNode->next = head[u - 1];
    head[u - 1] = newNode;
}

/* Remove an edge from one adjacency list */
void removeConnection(int u, int v)
{
    struct Node *temp = head[u - 1];
    struct Node *prev = NULL;

    while (temp != NULL)
    {
        if (temp->vertex == v)
        {
            if (prev == NULL)
                head[u - 1] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

/* Create Vertex */
void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }

    vertices++;
    head[vertices - 1] = NULL;

    printf("Vertex %d added successfully.\n", vertices);
}

/* Create Edge */
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

    if (edgeExists(u, v))
    {
        printf("Edge already exists!\n");
        return;
    }

    addConnection(u, v);
    addConnection(v, u);

    printf("Edge added successfully.\n");
}

/* Read Graph */
void readGraph()
{
    int i, isolatedVertex = 0;
    struct Node *temp;

    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }

    /* Check whether every vertex has at least one connection */
    for (i = 0; i < vertices; i++)
    {
        if (head[i] == NULL)
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

        temp = head[i];

        while (temp != NULL)
        {
            printf("%d", temp->vertex);

            if (temp->next != NULL)
                printf(" -> ");

            temp = temp->next;
        }
        printf(" -> NULL\n");
    }
}

void BFS()
{
    int start, visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int current;
    struct Node *temp;

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

        temp = head[current - 1];

        while (temp != NULL)
        {
            if (visited[temp->vertex - 1] == 0)
            {
                queue[rear++] = temp->vertex;
                visited[temp->vertex - 1] = 1;
            }

            temp = temp->next;
        }
    }

    printf("\n");
}


void DFS_Visit(int v, int visited[])
{
    struct Node *temp;

    visited[v - 1] = 1;
    printf("%d ", v);

    temp = head[v - 1];

    while (temp != NULL)
    {
        if (visited[temp->vertex - 1] == 0)
        {
            DFS_Visit(temp->vertex, visited);
        }

        temp = temp->next;
    }
}

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


/* Update Edge */
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

    if (edgeExists(u, v))
    {
        printf("Edge already exists between %d and %d.\n", u, v);
        printf("1. Remove Edge\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            removeConnection(u, v);
            removeConnection(v, u);
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
            addConnection(u, v);
            addConnection(v, u);
            printf("Edge added successfully.\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

/* Delete Edge */
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

    if (!edgeExists(u, v))
    {
        printf("No edge exists between %d and %d.\n", u, v);
        return;
    }

    removeConnection(u, v);
    removeConnection(v, u);

    printf("Edge deleted successfully.\n");
}

/* Delete Vertex */
void deleteVertex()
{
    int v, i;
    struct Node *temp, *nextNode;

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

    /* Remove all outgoing connections of the vertex */
    temp = head[v - 1];

    while (temp != NULL)
    {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    head[v - 1] = NULL;

    /* Remove references to the deleted vertex */
    for (i = 0; i < vertices; i++)
    {
        if (i != v - 1)
            removeConnection(i + 1, v);
    }

    /* Shift adjacency-list heads to maintain consecutive numbering */
    for (i = v - 1; i < vertices - 1; i++)
        head[i] = head[i + 1];

    head[vertices - 1] = NULL;
    vertices--;

    /* Decrease vertex labels greater than the deleted vertex */
    for (i = 0; i < vertices; i++)
    {
        temp = head[i];

        while (temp != NULL)
        {
            if (temp->vertex > v)
                temp->vertex--;

            temp = temp->next;
        }
    }

    printf("Vertex deleted successfully.\n");
}

/* Free all remaining memory */
void freeGraph()
{
    int i;
    struct Node *temp, *nextNode;

    for (i = 0; i < vertices; i++)
    {
        temp = head[i];

        while (temp != NULL)
        {
            nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }

        head[i] = NULL;
    }
}

/* Main Menu */
int main()
{
    int choice;

    do
    {
        printf("\n--- GRAPH CRUD MENU (LINKED LIST) ---\n");
        printf("1. Create Vertex\n");
        printf("2. Create Edge\n");
        printf("3. Read Graph\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Delete Vertex\n");
        printf("7. BFS traversal\n");
        printf("8. DFS traversal\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            freeGraph();
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
                freeGraph();
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 9);

    return 0;
}
