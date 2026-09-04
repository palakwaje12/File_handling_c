#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct StudentInfo
{
    unsigned int rollNo;
    char name[50];
    char email[50];

    struct StudentInfo *next;
};

struct StudentInfo *head = NULL;

unsigned int choice, roll;


// ---------- FUNCTION DECLARATIONS ----------

int isNumber(const char *str);

void createStudents();
void displayStudents();
void updateStudent(unsigned int searchRollNo);
void deleteStudent(unsigned int deleteRollNo);

void saveToFile();
void loadFromFile();

void freeStudents();


// check whether string contains only numbers

int isNumber(const char *str)
{
    if(*str == '\0')
        return 0;

    while(*str)
    {
        if(!isdigit(*str))
            return 0;

        str++;
    }

    return 1;
}


// ---------- MAIN ----------

int main()
{
    char input[100];

    // Load existing students from file when program starts
    loadFromFile();

    while(1)
    {
        printf("\n========== STUDENT MENU ==========\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("Enter Choice : ");

        if(!fgets(input, sizeof(input), stdin))
        {
            printf("Invalid Error\n");
            continue;
        }

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

                createStudents();

                break;


            case 2:

                displayStudents();

                break;


            case 3:

                printf("Enter Roll Number to Update : ");

                if(fgets(input, sizeof(input), stdin))
                {
                    input[strcspn(input, "\n")] = '\0';

                    if(isNumber(input))
                    {
                        roll = (unsigned int)atoi(input);

                        updateStudent(roll);
                    }
                    else
                    {
                        printf("Invalid Roll Number!\n");
                    }
                }

                break;


            case 4:

                printf("Enter Roll Number to Delete : ");

                if(fgets(input, sizeof(input), stdin))
                {
                    input[strcspn(input, "\n")] = '\0';

                    if(isNumber(input))
                    {
                        roll = (unsigned int)atoi(input);

                        deleteStudent(roll);
                    }
                    else
                    {
                        printf("Invalid Roll Number!\n");
                    }
                }

                break;


            case 5:

                freeStudents();

                printf("\nProgram Exited.\n");

                return 0;


            default:

                printf("Invalid Choice\n");
        }
    }
}

// ---------- CREATE / ADD STUDENT ----------

void createStudents()
{
    struct StudentInfo *student;
    struct StudentInfo *last;

    char buffer[100];


    student = (struct StudentInfo *)
              malloc(sizeof(struct StudentInfo));


    if(student == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return;
    }


    // Roll Number

    printf("\nEnter Roll Number : ");

    if(fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        free(student);
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    if(!isNumber(buffer))
    {
        printf("Invalid Roll Number!\n");
        free(student);
        return;
    }
    student->rollNo=(unsigned int)atoi(buffer);

    //to check if duplicate number exists
    last=head;
    while(last!=NULL){
        if(last->rollNo==student->rollNo){
            printf("roll number of the student already exists");
            free(student);
            return;
        }
    }

    // Name
    printf("Enter Name : ");
    if(fgets(buffer, sizeof(buffer), stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(student->name, buffer);
    }
    // Email

    printf("Enter Email : ");
    if(fgets(buffer, sizeof(buffer), stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(student->email, buffer);
    }

    student->next = NULL;

    // Add to linked list
    if(head == NULL)
    {
        head = student;
    }
    else
    {
        last = head;

        while(last->next != NULL)
        {
            last = last->next;
        }

        last->next = student;
    }

    // Save updated list to file
    saveToFile();
    printf("\nStudent Added Successfully.\n");
}

// ---------- DISPLAY STUDENTS ----------

void displayStudents()
{
    struct StudentInfo *last;
    if(head == NULL)
    {
        printf("\nNo Student Found.\n");
        return;
    }

    last = head;
    printf("\n========== STUDENT LIST ==========\n");
    while(last != NULL)
    {
        printf("\nRoll Number : %u", last->rollNo);
        printf("\nName        : %s", last->name);
        printf("\nEmail       : %s\n", last->email);
        printf("\n------\n");
        last = last->next;
    }
    
}


// ---------- UPDATE STUDENT ----------

void updateStudent(unsigned int searchRollNo)
{
    struct StudentInfo *last;
    char buffer[100];

    if(head == NULL)
    {
        printf("\nNo Student Found.\n");
        return;
    }

    last = head;

    while(last != NULL)
    {
        if(last->rollNo == searchRollNo)
        {
            printf("\nEnter New Name : ");
            if(fgets(buffer, sizeof(buffer), stdin))
            {
                buffer[strcspn(buffer, "\n")] = '\0';

                strcpy(last->name, buffer);
            }


            printf("Enter New Email : ");

            if(fgets(buffer, sizeof(buffer), stdin))
            {
                buffer[strcspn(buffer, "\n")] = '\0';

                strcpy(last->email, buffer);
            }


            //update text file
            saveToFile();

            printf("\nStudent Updated Successfully.\n");

            return;
        }


        last = last->next;
    }


    printf("\nStudent Not Found.\n");
}


// ---------- DELETE STUDENT ----------

void deleteStudent(unsigned int deleteRollNo)
{
    struct StudentInfo *current;
    struct StudentInfo *previous;


    if(head == NULL)
    {
        printf("\nNo Student Found.\n");
        return;
    }


    current = head;

    previous = NULL;

    while(current != NULL)
    {
        if(current->rollNo == deleteRollNo)
        {
            // Delete first node
            if(previous == NULL)
            {
                head = current->next;
            }
            // Delete middle/last node

            else
            {
                previous->next = current->next;
            }

            free(current);

            // Save updated list to file

            saveToFile();

            printf("\nStudent Deleted Successfully.\n");

            return;
        }
        previous = current;
        current = current->next;
    }


    printf("\nStudent Not Found.\n");
}

// ---------- SAVE LINKED LIST TO FILE ----------

void saveToFile()
{
    FILE *fp;

    struct StudentInfo *current;

    fp = fopen("students.txt", "w");

    if(fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    current = head;

    while(current != NULL)
    {
        fprintf(fp, "%u|%s|%s\n",
                current->rollNo,
                current->name,
                current->email);

        current = current->next;
    }

    fclose(fp);
}

// ---------- LOAD DATA FROM FILE ----------

void loadFromFile()
{
    FILE *fp;
    struct StudentInfo *student;
    struct StudentInfo *last;
    char line[150];
    fp = fopen("students.txt", "r");
    // If file doesn't exist, simply start with empty list

    if(fp == NULL)
    {
        return;
    }

    while(fgets(line, sizeof(line), fp))
    {
        student = (struct StudentInfo *)
                  malloc(sizeof(struct StudentInfo));

        if(student == NULL)
        {
            printf("Memory Allocation Failed.\n");
            fclose(fp);
            return;
        }
        /*
            File format:

            RollNo|Name|Email
        */
        if(sscanf(line,
                  "%u|%49[^|]|%49[^\n]",
                  &student->rollNo,
                  student->name,
                  student->email) == 3)
        {
            student->next = NULL;
            if(head == NULL)
            {
                head = student;
            }
            else
            {
                last = head;

                while(last->next != NULL)
                {
                    last = last->next;
                }
                last->next = student;
            }
        }
        else
        {
            free(student);
        }
    }
    fclose(fp);
}

// ---------- FREE MEMORY ----------
void freeStudents()
{
    struct StudentInfo *current;
    struct StudentInfo *next;
    current = head;
    while(current != NULL)
    {
        next = current->next;

        free(current);

        current = next;
    }
    head = NULL;
    printf("\nAll Student Records Freed From Memory.\n");
}