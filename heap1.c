#include <stdio.h>
#define MAX 100
int maxHeap[MAX + 1], minHeap[MAX + 1];
int maxSize = 0, minSize = 0;

// INSERT INTO MAX HEAP
void insertMax()
{
    int value, i, parent, temp; 
    if (maxSize == MAX)
    {
        printf("Max Heap is full!\n");
        return;
    }
    printf("Enter value: ");
    scanf("%d", &value);
    i = maxSize + 1;
    maxHeap[i] = value;
    maxSize++;
    while (i > 1)
    {
        // parent = i / 2; 
        // if (maxHeap[parent] < maxHeap[i])
        // {
        //     temp = maxHeap[parent];
        //     maxHeap[parent] = maxHeap[i];
        //     maxHeap[i] = temp; 
        //     i = parent;
        // }
        parent = i / 2; 
        if (maxHeap[parent] >= maxHeap[i]){
            i=1;
        }
        temp = maxHeap[parent];
        maxHeap[parent] = maxHeap[i];
        maxHeap[i] = temp; 
        i = parent;
          
        // else
        //     i=1;
    }
    printf("Inserted into Max Heap.\n");
}

// DELETE FROM MAX HEAP
void deleteMax()
{
    int i = 1, left, right, largest, temp;
    if (maxSize == 0)
    {
        printf("Max Heap is empty!\n");
        return;
    }
    printf("Deleted: %d\n", maxHeap[1]);  //in max heap largest element is deleted
    maxHeap[1] = maxHeap[maxSize];
    maxSize--;
    while (1)
    {
        left = 2 * i;
        right = 2 * i + 1; 
        largest = i;

        if (left <= maxSize && maxHeap[left] > maxHeap[largest])
            largest = left;

        if (right <= maxSize && maxHeap[right] > maxHeap[largest])
            largest = right;

        if (largest != i)
        {
            temp = maxHeap[i];
            maxHeap[i] = maxHeap[largest];
            maxHeap[largest] = temp;
            i = largest;
        }
        else
            break;
    }
}

// DISPLAY MAX HEAP
void readMax()
{
    int i;
    if (maxSize == 0)
    {
        printf("Max Heap is empty!\n");
        return;
    }
    printf("Max Heap: ");
    for (i = 1; i <= maxSize; i++)
        printf("%d ", maxHeap[i]);

    printf("\n");
}

// UPDATE MAX HEAP
void updateMax()
{
    int index, value, parent, left, right, largest, temp;

    if (maxSize == 0)
    {
        printf("Max Heap is empty!\n");
        return;
    }

    printf("Max Heap: ");
    for (int i = 1; i <= maxSize; i++)
        printf("%d ", maxHeap[i]);

    printf("\nEnter index to update: ");
    scanf("%d", &index);

    if (index < 1 || index > maxSize)
    {
        printf("Invalid index!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &value);

    int oldValue = maxHeap[index];
    maxHeap[index] = value;

    if (value > oldValue)
    {
        // move UP
        while (index > 1)
        {
            parent = index / 2;

            if (maxHeap[parent] < maxHeap[index])
            {
                temp = maxHeap[parent];
                maxHeap[parent] = maxHeap[index];
                maxHeap[index] = temp;

                index = parent;
            }
            else
                break;
        }
    }
    else
    {
        while (1)
        {
            left = 2 * index;
            right = 2 * index + 1;
            largest = index;

            if (left <= maxSize && maxHeap[left] > maxHeap[largest])
                largest = left;

            if (right <= maxSize && maxHeap[right] > maxHeap[largest])
                largest = right;

            if (largest != index)
            {
                temp = maxHeap[index];
                maxHeap[index] = maxHeap[largest];
                maxHeap[largest] = temp;

                index = largest;
            }
            else
                break;
        }
    }
    printf("Max Heap updated successfully!\n");
}

// INSERT INTO MIN HEAP
void insertMin()
{
    int value, i, parent, temp;

    if (minSize == MAX)
    {
        printf("Min Heap is full!\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &value);

    i = minSize + 1;
    minHeap[i] = value;
    minSize++;

    while (i > 1)
    {
        parent = i / 2;
        if (minHeap[parent] > minHeap[i])
        {
            temp = minHeap[parent];
            minHeap[parent] = minHeap[i];
            minHeap[i] = temp;
            i = parent;
        }
        else
            break;
    }
    printf("Inserted into Min Heap.\n");
}

// DELETE FROM MIN HEAP
void deleteMin()
{
    int i = 1, left, right, smallest, temp;

    if (minSize == 0)
    {
        printf("Min Heap is empty!\n");
        return;
    }

    printf("Deleted: %d\n", minHeap[1]);

    minHeap[1] = minHeap[minSize];
    minSize--;

    while (1)
    {
        left = 2 * i;
        right = 2 * i + 1;
        smallest = i;

        if (left <= minSize && minHeap[left] < minHeap[smallest])
            smallest = left;

        if (right <= minSize && minHeap[right] < minHeap[smallest])
            smallest = right;

        if (smallest != i)
        {
            temp = minHeap[i];
            minHeap[i] = minHeap[smallest];
            minHeap[smallest] = temp;
            i = smallest;
        }
        else
            break;
    }
}

// DISPLAY MIN HEAP
void readMin()
{
    int i;
    if (minSize == 0)
    {
        printf("Min Heap is empty!\n");
        return;
    }
    printf("Min Heap: ");

    for (i = 1; i <= minSize; i++)
        printf("%d ", minHeap[i]);

    printf("\n");
}

// UPDATE MIN HEAP
void updateMin()
{
    int index, value, parent, left, right, smallest, temp;

    if (minSize == 0)
    {
        printf("Min Heap is empty!\n");
        return;
    }

    printf("Min Heap: ");
    for (int i = 1; i <= minSize; i++)
        printf("%d ", minHeap[i]);

    printf("\nEnter index to update: ");
    scanf("%d", &index);

    if (index < 1 || index > minSize)
    {
        printf("Invalid index!\n");
        return;
    }

    printf("Enter new value: ");
    scanf("%d", &value);

    int oldValue = minHeap[index];
    minHeap[index] = value;

    if (value < oldValue)
    {
        while (index > 1)
        {
            parent = index / 2;

            if (minHeap[parent] > minHeap[index])
            {
                temp = minHeap[parent];
                minHeap[parent] = minHeap[index];
                minHeap[index] = temp;

                index = parent;
            }
            else
                break;
        }
    }
    else
    {
        while (1)
        {
            left = 2 * index;
            right = 2 * index + 1;
            smallest = index;

            if (left <= minSize && minHeap[left] < minHeap[smallest])
                smallest = left;

            if (right <= minSize && minHeap[right] < minHeap[smallest])
                smallest = right;

            if (smallest != index)
            {
                temp = minHeap[index];
                minHeap[index] = minHeap[smallest];
                minHeap[smallest] = temp;

                index = smallest;
            }
            else
                break;
        }
    }
    printf("Min Heap updated successfully!\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- HEAP MENU ---");
        printf("\n1. Insert into Max Heap");
        printf("\n2. Delete from Max Heap");
        printf("\n3. Display Max Heap");
        printf("\n4. Update Max Heap");
        printf("\n5. Insert into Min Heap");
        printf("\n6. Delete from Min Heap");
        printf("\n7. Display Min Heap");
        printf("\n8. Update Min Heap");
        printf("\n9. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insertMax();
                break;

            case 2:
                deleteMax();
                break;

            case 3:
                readMax();
                break;

            case 4:
                updateMax();
                break;

            case 5:
                insertMin();
                break;

            case 6:
                deleteMin();
                break;

            case 7:
                readMin();
                break;

            case 8:
                updateMin();
                break;

            case 9:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}