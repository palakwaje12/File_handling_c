//FIFO--queue using linked list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Queue
{
    int data;         //stores the actual value
    struct Queue *next;       //stores address of next node
};

struct Queue *front = NULL;    //front pts to first node
struct Queue *rear = NULL;     //rear pts to last node so initially queue is empty

int isNumber(const char *str)      //str is a ptr to a character
{
    if(*str == '\0')    //checks whether the string is empty
        return 0;     //invalid input

    while(*str)
    {
        if(!isdigit(*str))    //if the i/p is not a digit return 0
            return 0;

        str++;   //move to the next character thn
    }

    return 1;    //valid number
}

void enqueue();
void dequeue();
void update();
void display();
void freeQueue();

int main()
{
    char input[100];          //a character array to store user i/p
    int choice;

    while(1)
    {
        printf("\n====== QUEUE MENU ======\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Update\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter Choice : ");

        if(!fgets(input, sizeof(input), stdin))    //i/p is stored,max size of i/p(here=100),usually the keyboard 
        {
            printf("Invalid Error.\n");
            continue;        //skips the current iteration nd goes back to the start of while loop
        }

        input[strcspn(input, "\n")] = '\0';

        if(!isNumber(input))   //checks if the i/p contains only digits
        {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }

        choice = atoi(input);

        switch(choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                update();
                break;

            case 4:
                display();   //to release all allocated nodes
                break;

            case 5:
                freeQueue();
                return 0;

            default:
                printf("Invalid Choice! Please select 1-4.\n");
        }
    }
}

void enqueue()         //adds a new node in the queue
{
    struct Queue *node;   //creates a ptr node
    char input[100];

    node = (struct Queue *)malloc(sizeof(struct Queue));   //sizeof(struct queue) becoz we need enough memory to store entire struct

    if(node == NULL)    //if malloc cant allocate memeory it returns null
    {
        printf("Memory Allocation Failed.\n");
        return;
    }

    printf("Enter Data(numbers only) : ");

    if(!fgets(input, sizeof(input), stdin))     //if fgets unable to read print invalid
    {
        printf("Invalid Error.\n");
        free(node);   //we allocated memory using malloc but if i/p fails we dont use tht node so thats why we free memory
        return;
    }

    input[strcspn(input, "\n")] = '\0';

    if(!isNumber(input))
    {
        printf("Invalid Data! Please enter a valid number.\n");
        free(node);   //again free becoz memory is already allocated
        return;
    }

    node->data = atoi(input);  //convert the i/p into integer nd store it into the node's data pointed by the node pointer

    node->next = NULL;

    if(front == NULL)    //checks whether queue is empty
    {
        front = node;
        rear = node;
    }
    else
    {
        rear->next = node;
        rear = node;   //becoz now the newly added node is the last node 
    }

    printf("Element Inserted Successfully.\n");
}

void dequeue()
{
    struct Queue *temp;

    if(front == NULL)
    {
        printf("Queue Underflow.\n");      //there is no element to be removed
        return;
    }

    temp = front;

    printf("Deleted Element : %d\n", front->data);

    front = front->next;

    if(front == NULL)
    {
        rear = NULL;
    }

    free(temp);    //frees the memory occupied by deleted node
}

void update()
{
    struct Queue *temp;
    char input[100];
    int oldValue;    //the value tht user wants to find
    int newValue;     //to store the value which will be updated

    if(front == NULL)
    {
        printf("Queue is Empty. Nothing to update.\n");
        return;
    }

    printf("Enter Value to Update : ");

    if(!fgets(input, sizeof(input), stdin))    //if fgets fails to read then print invalid 
    {
        printf("Invalid Error.\n");
        return;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if(!isNumber(input))
    {
        printf("Invalid Value! Please enter a valid number.\n");
        return;
    }

    oldValue = atoi(input);

    temp = front;

    while(temp != NULL)     //traverse until comes node i.e. traverse each node
    {
        if(temp->data == oldValue)    //if the data in temp = value user mentioned then true
        {
            printf("Enter New Value : ");

            if(!fgets(input, sizeof(input), stdin))
            {
                printf("Invalid Error.\n");
                return;
            }

            input[strcspn(input, "\r\n")] = '\0';

            if(!isNumber(input))
            {
                printf("Invalid Value! Please enter a valid number.\n");
                return;
            }

            newValue = atoi(input);

            temp->data = newValue;

            printf("Element Updated Successfully.\n");
            return;
        }
        temp = temp->next;   //now the temp moves to the next place
    }
    //nd if searching all through the queue still don't find the value thn print element not found
    printf("Element %d Not Found.\n", oldValue);
}

void display()
{
    struct Queue *temp;

    if(front == NULL)
    {
        printf("Queue is Empty.\n");
        return;
    }

    temp = front;

    printf("\nQueue Elements : ");

    while(temp != NULL)        //continue until there are no nodes
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

void freeQueue()    //to free all the nodes currently present in queue
{
    struct Queue *current;   
    struct Queue *next;    //saves the address of next node

    current = front;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    front = NULL;
    rear = NULL;

    printf("\nQueue Freed From Memory.\n");
}