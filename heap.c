#include <stdio.h>

#define MAX 100

int heap[MAX];
int size = 0;

/* Swap two elements */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Move an element upward */
void moveUp(int index)
{
    int parent;

    while (index > 0)
    {
        parent = (index - 1) / 2;

        if (heap[index] > heap[parent])
        {
            swap(&heap[index], &heap[parent]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

/* Move an element downward */
void moveDown(int index)
{
    int largest = index;
    int left, right;

    while (1)
    {
        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index)
        {
            swap(&heap[index], &heap[largest]);
            index = largest;
        }
        else
        {
            break;
        }
    }
}

/* CREATE: Insert an element */
void insertElement()
{
    int value;

    if (size == MAX)
    {
        printf("Heap is full!\n");
        return;
    }

    printf("Enter value to insert: ");
    if (scanf("%d", &value) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    heap[size] = value;
    moveUp(size);
    size++;

    printf("Element inserted successfully.\n");
}

/* READ: Display the heap */
void displayHeap()
{
    int i;

    if (size == 0)
    {
        printf("Heap is empty!\n");
        return;
    }

    printf("Heap elements: ");

    for (i = 0; i < size; i++)
        printf("%d ", heap[i]);

    printf("\n");
}

/* UPDATE: Change an element at a given index */
void updateElement()
{
    int index, value, oldValue;

    if (size == 0)
    {
        printf("Heap is empty!\n");
        return;
    }

    printf("Enter index to update (0 to %d): ", size - 1);
    if (scanf("%d", &index) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    if (index < 0 || index >= size)
    {
        printf("Invalid index!\n");
        return;
    }

    printf("Enter new value: ");
    if (scanf("%d", &value) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    oldValue = heap[index];
    heap[index] = value;

    if (value > oldValue)
        moveUp(index);
    else if (value < oldValue)
        moveDown(index);

    printf("Element updated successfully.\n");
}

/* DELETE: Delete an element at a given index */
void deleteElement()
{
    int index;

    if (size == 0)
    {
        printf("Heap is empty!\n");
        return;
    }

    printf("Enter index to delete (0 to %d): ", size - 1);
    if (scanf("%d", &index) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    if (index < 0 || index >= size)
    {
        printf("Invalid index!\n");
        return;
    }

    heap[index] = heap[size - 1];
    size--;

    if (index < size)
    {
        if (index > 0 &&
            heap[index] > heap[(index - 1) / 2])
        {
            moveUp(index);
        }
        else
        {
            moveDown(index);
        }
    }

    printf("Element deleted successfully.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- MAX HEAP CRUD MENU ---\n");
        printf("1. Create (Insert Element)\n");
        printf("2. Read (Display Heap)\n");
        printf("3. Update Element\n");
        printf("4. Delete Element\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            break;
        }

        switch (choice)
        {
            case 1:
                insertElement();
                break;

            case 2:
                displayHeap();
                break;

            case 3:
                updateElement();
                break;

            case 4:
                deleteElement();
                break;

            case 5:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
