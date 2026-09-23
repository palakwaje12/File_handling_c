//stack- LIFO
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5      //determines the no. of elements which can be stored

int stack[SIZE];
int top = -1;      //initializing it with -1 which means stack is empty
                //it stores the idx of topmost el
int isNumber(const char *str)  //if entered str is only number/digit return 1 nd if some string return 0
{                               //user-defined funct
    if(*str == '\0')       //checks whether string is empty \0 means end of string
        return 0;

    while(*str)        //now it checks every element of the string
    {
        if(!isdigit(*str))       //if any of the no. is not a digit return 0 
            return 0;

        str++;          //else move to the next character
    }

    return 1;
}

void push();
void pop();
void peek();
void display();

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
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter Choice : ");

        if(!fgets(input, sizeof(input), stdin))     //used fgets to validate the input instead of scanf
        {                                      //if it fails tht means i/p cannot be successfully read
            printf("Invalid Error.\n");    //!fgets() means if it fails to read print invalid error
            continue;
        }
        input[strcspn(input, "\n")] = '\0';     //fgets normally stores \n when pressed enter so to avoid it we replace it with \0

        if(!isNumber(input))          //if input is not a number print invalid
        {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }
        choice = atoi(input);     //converts validated string into integer

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
                display();
                break;

            case 5:
                printf("\nProgram Exited Successfully.\n");
                return 0;

            default:
                printf("Invalid Choice! Please select 1-5.\n");
        }
    }
}
void push()
{
    char input[100];
    int value;

    if(top == SIZE - 1)   //here size is 5 if top==5-1 i.e. 4 then stack is full
    {
        printf("Stack Overflow.\n");
        return;
    }
    printf("Enter Value : ");

    if(!fgets(input, sizeof(input), stdin))
    {
        printf("Invalid Error.\n");
        return;
    }
    input[strcspn(input, "\n")] = '\0';
    if(!isNumber(input))     //checks whether entered value contains only digits
    {
        printf("Invalid Value! Please enter a valid number.\n");
        return;
    }

    value = atoi(input);

    top++;
    stack[top] = value;

    printf("Element Pushed Successfully.\n");
}

void pop()
{
    if(top == -1)          //means there is no element to remove stack is empty
    {
        printf("Stack Underflow i.e. stack is empty.\n");
        return;
    }

    printf("Deleted : %d\n", stack[top]);

    top--;
}

void peek()
{
    if(top == -1)
    {
        printf("Stack Empty.\n");
        return;
    }

    printf("Top Element : %d\n", stack[top]);
}

void display()
{
    int i;

    if(top == -1)
    {
        printf("Stack Empty.\n");
        return;
    }

    printf("Stack : ");

    for(i = top; i >= 0; i--)
    {
        printf("%d ", stack[i]);
    }

    printf("\n");
}