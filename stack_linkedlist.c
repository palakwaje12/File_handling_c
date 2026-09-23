#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Stack
{
    int data;       //stores the actual value
    struct Stack *next;      //stores address of next node
};

struct Stack *top = NULL;      //initially top is pointing to null which means stack is empty

int isNumber(const char *str)
{
    if(*str == '\0')    //if =\0 means string is empty
        return 0;

    while(*str)
    {
        if(!isdigit(*str))
            return 0;

        str++;
    }

    return 1;
}

void push();
void pop();
void peek();
void update();
void display();
void freeStack();

int main()
{
    char input[100];
    int choice;

    while(1)
    {
        printf("\n====== STACK MENU ======\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Update\n");
        printf("5. Display\n");
        printf("6. Exit\n");

        printf("Enter Choice : ");

        if(!fgets(input, sizeof(input), stdin))
        {
            printf("Invalid Error.\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        if(!isNumber(input))
        {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }

        choice = atoi(input);

        switch(choice)
        {
            case 1:
                push();
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                update();
                break;

            case 5:
                display();
                break;

            case 6:
                freeStack();
                return 0;

            default:
                printf("Invalid Choice! Please select 1-5.\n");
        }
    }
}

void push()    //adds new element at the top of stack
{
    struct Stack *node;
    char input[100];

    node = (struct Stack *)malloc(sizeof(struct Stack));   //memory allocation

    if(node == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return;
    }

    printf("Enter Data : ");

    if(!fgets(input, sizeof(input), stdin))
    {
        printf("Invalid Error.\n");
        free(node);
        return;
    }

    input[strcspn(input, "\n")] = '\0';

    if(!isNumber(input))
    {
        printf("Invalid Data! Please enter a valid number.\n");
        free(node);
        return;
    }

    node->data = atoi(input);

    node->next = top;

    top = node;

    printf("Element Pushed Successfully.\n");
}

void pop()
{
    struct Stack *temp;

    if(top == NULL)
    {
        printf("Stack Underflow.\n");     //stack is empty
        return;
    }

    temp = top;

    printf("Deleted Element : %d\n", top->data);

    top = top->next;   //now the element deleted is no longer part of stack

    free(temp);     //releases the memory occupied by old node
}   

void peek()
{
    if(top == NULL)
    {
        printf("Stack is Empty.\n");
        return;
    }

    printf("Top Element : %d\n", top->data);
}

void update()
{
    struct Stack *temp;
    char input[100];
    int oldValue;
    int newValue;

    if(top == NULL)
    {
        printf("Stack is Empty. Nothing to update.\n");
        return;
    }

    printf("Enter Value to Update : ");

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

    oldValue = atoi(input);

    temp = top;

    while(temp != NULL)
    {
        if(temp->data == oldValue)
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

        temp = temp->next;
    }

    printf("Element %d Not Found.\n", oldValue);
}

void display()
{
    struct Stack *temp;

    if(top == NULL)
    {
        printf("Stack is Empty.\n");
        return;
    }

    temp = top;

    printf("\nStack Elements :\n");

    while(temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

void freeStack()
{
    struct Stack *current;
    struct Stack *next;

    current = top;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    top = NULL;

    printf("\nStack Freed From Memory.\n");
}