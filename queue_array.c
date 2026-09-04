#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

int queue[SIZE];   //defines the max capacity of an array 
int front = -1;        //queue is empty
int rear = -1;

int isNumber(const char *str)       //checks if the given string contains numbers
{
    if(*str == '\0')       //checks if the string is empty
        return 0;

    while(*str)
    {
        if(!isdigit(*str))         //if that character is not a number return 0
            return 0;
        str++;        //move to the next character
    }
    return 1;
}

void enqueue();
void dequeue();
void display();

int main()
{
    char input[100];        //taken the input as character
    unsigned int choice;

    while(1)
    {
        printf("\n====== QUEUE MENU ======\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter Choice : ");

        if(!fgets(input, sizeof(input), stdin))   //fgets() is safer for input validation than scanf("%d")
        {
            printf("Invalid Error.\n");
            continue;
        }            //what fgets do is after pressing enter it stores \n at the end to prevent tht we use strcspn to replace \n by \0 

        input[strcspn(input, "\n")] = '\0';

        if(!isNumber(input))
        {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }

        choice = (unsigned int)atoi(input);

        switch(choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("\nProgram Exited Successfully.\n");
                return 0;

            default:
                printf("Invalid Choice! Please select 1-4.\n");
        }
    }
}

void enqueue()
{
    char input[100];
    int value;

    if(rear == SIZE - 1)       //say size=5 nd if rear=4(5-1) queue is full
    {
        printf("\nQueue Overflow.\n");
        return;
    }

    printf("Enter Value : ");

    if(!fgets(input, sizeof(input), stdin))
    {
        printf("Invalid Error.\n");
        return;
    }

    input[strcspn(input, "\n")] = '\0';
    if(!isNumber(input))
    {
        printf("Invalid Value! Please enter a number.\n");
        return;
    }
    value = atoi(input);
    if(front == -1)
    {
        front = 0;
    }
    rear++;
    queue[rear] = value;

    printf("Element Inserted Successfully.\n");
}

void dequeue()
{
    if(front == -1 || front > rear)
    {
        printf("\nQueue Underflow.\n");
        return;
    }

    printf("Deleted Element : %d\n", queue[front]);

    front++;

    if(front > rear)
    {
        front = -1;
        rear = -1;     //queue is empty
    }
}

void display()
{
    int i;
    if(front == -1)
    {
        printf("\nQueue is Empty.\n");
        return;
    }
    printf("\nQueue Elements : ");
    for(i = front; i <= rear; i++)      //to access every element of queue
    {
        printf("%d ", queue[i]);
    }
    printf("\n");
}