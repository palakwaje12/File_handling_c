#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Student
{
    int rollNo;
    char name[50];
    char email[50];
};

//to validate rollno,name and email

int validateRollNumber(char input[])
{
    if (strlen(input) == 0)    //if input length=0 return invalid number 
        return 0;

    for (int i = 0; input[i] != '\0'; i++)     //starts from 0 move until last digit is 0 
    {
        if (!isdigit((unsigned char)input[i]))            //isdigit belongs to <ctype.h> library
            return 0;
    }

    if (atoi(input) <= 0)                    //atoi-converts string to integer
        return 0;                    //input cant be negative

    return 1;       //exits from the code
}

int validateName(char name[])
{
    int hasLetter = 0;

    if (strlen(name) == 0)
        return 0;

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)name[i]))               //checks whether entered input is alphabet or not
        {
            hasLetter = 1;
        }
        else if (name[i] != ' ')
        {
            return 0;
        }
    }

    if (!hasLetter)
        return 0;

    return 1;
}

int validateEmail(char email[])
{
    int atCount = 0;
    int atPosition = -1;
    int dotPosition = -1;

    if (strlen(email) == 0)
        return 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (isspace((unsigned char)email[i]))     //email should not contain any spaces
            return 0;

        if (email[i] == '@')
        {
            atCount++;
            atPosition = i;
        }

        if (email[i] == '.')
        {
            dotPosition = i;
        }
    }

    if (atCount != 1)              //should contain only 1 @ 
        return 0;

    if (atPosition == 0)           //@ should not be at 1st position
        return 0;

    if (email[atPosition + 1] == '\0')           //after @ gmail.com should be there
        return 0;

    if (dotPosition <= atPosition + 1)          // . must be after @
        return 0;

    if (email[dotPosition + 1] == '\0')        //after . com should be there
        return 0;

    if (dotPosition == atPosition - 1)        // . must not be before @
        return 0;

    return 1;
}
//input functions
int getRollNumber()
{
    char buffer[100];

    while (1)
    {
        printf("Enter Roll Number: ");
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = '\0';             //strcspn-Find length before specified characters

        if (validateRollNumber(buffer))
        {
            return atoi(buffer);
        }

        printf("Invalid roll number!\n");
        printf("Please enter a positive number only.\n");
    }
}

void getName(char name[])
{
    while (1)
    {
        printf("Enter Name: ");
        fgets(name, 50, stdin);

        name[strcspn(name, "\n")] = '\0';

        if (validateName(name))
        {
            return;
        }

        printf("Invalid name!\n");
        printf("Name should contain alphabets and spaces only.\n");
    }
}

void getEmail(char email[])
{
    while (1)
    {
        printf("Enter Email: ");
        fgets(email, 50, stdin);

        email[strcspn(email, "\n")] = '\0';

        if (validateEmail(email))
        {
            return;
        }

        printf("Invalid email!\n");
        printf("Example: student@gmail.com\n");
    }
}

// CHECKS FOR DUPLICATE ROLL NUMBER 

int rollNumberExists(int roll)
{
    FILE *fp;
    struct Student s;

    fp = fopen("ass1.txt", "r");

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d|%49[^|]|%49[^\n]\n",
                  &s.rollNo,
                  s.name,
                  s.email) == 3)
    {
        if (s.rollNo == roll)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}



int main()
{
    FILE *fp;
    int choice;
    int roll;
    int found;
    struct Student s;
    char buffer[100];

    do
    {
        printf("\n========================================\n");
        printf("        STUDENT FILE CRUD SYSTEM\n");
        printf("========================================\n");
        printf("1. Create / Add Student\n");
        printf("2. Read / Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("========================================\n");

        while (1)
        {
            printf("Enter your choice: ");

            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            if (strlen(buffer) == 1 &&
                buffer[0] >= '1' &&
                buffer[0] <= '5')
            {
                choice = buffer[0] - '0';
                break;
            }

            printf("Invalid choice!\n");
            printf("Please enter a number between 1 and 5.\n");
        }

        //create/add

        if (choice == 1)
        {
            fp = fopen("ass1.txt", "a");

            if (fp == NULL)
            {
                printf("\nError opening file!\n");
                continue;
            }

            printf("\n========== ADD STUDENT ==========\n");

            //Roll Number

            while (1)
            {
                s.rollNo = getRollNumber();

                if (rollNumberExists(s.rollNo))
                {
                    printf("Roll number already exists!\n");
                    printf("Please enter a different roll number.\n");
                }
                else
                {
                    break;
                }
            }

            // Name 

            getName(s.name);

            // Email 

            getEmail(s.email);

            // Save 

            fprintf(fp, "%d|%s|%s\n",
                    s.rollNo,
                    s.name,
                    s.email);

            fclose(fp);

            printf("\nStudent added successfully!\n");
        }

        /* ---------- READ / DISPLAY ---------- */

        else if (choice == 2)
        {
            fp = fopen("ass1.txt", "r");

            if (fp == NULL)
            {
                printf("\nNo student records found!\n");
                continue;
            }

            printf("\n========== STUDENT RECORDS ==========\n");

            int count = 0;

            while (fscanf(fp, "%d|%49[^|]|%49[^\n]\n",
                        &s.rollNo,
                        s.name,
                        s.email) == 3)
            {
                count++;

                printf("\nRoll Number : %d", s.rollNo);
                printf("\nName        : %s", s.name);
                printf("\nEmail       : %s", s.email);
                printf("\n-------------------------------------\n");
            }

            if (count == 0)
            {
                printf("No student records found!\n");
            }

            fclose(fp);
        }

        /* ---------- UPDATE ---------- */

        else if (choice == 3)
        {
            FILE *temp;
            found = 0;

            printf("\n========== UPDATE STUDENT ==========\n");

            roll = getRollNumber();

            fp = fopen("ass1.txt", "r");

            if (fp == NULL)
            {
                printf("\nNo student records found!\n");
                continue;
            }

            temp = fopen("temp.txt", "w");

            if (temp == NULL)
            {
                printf("\nError creating temporary file!\n");
                fclose(fp);
                continue;
            }

            while (fscanf(fp, "%d|%49[^|]|%49[^\n]\n",
                          &s.rollNo,
                          s.name,
                          s.email) == 3)
            {
                if (s.rollNo == roll)
                {
                    found = 1;

                    printf("\nStudent found!\n");

                    printf("Current Name  : %s\n", s.name);
                    printf("Current Email : %s\n", s.email);

                    printf("\nEnter new details:\n");

                    getName(s.name);
                    getEmail(s.email);
                }

                fprintf(temp, "%d|%s|%s\n",
                        s.rollNo,
                        s.name,
                        s.email);
            }

            fclose(fp);
            fclose(temp);

            if (found)
            {
                remove("ass1.txt");

                if (rename("temp.txt", "ass1.txt") != 0)
                {
                    printf("\nError updating file!\n");
                }
                else
                {
                    printf("\nStudent updated successfully!\n");
                }
            }
            else
            {
                remove("temp.txt");
                printf("\nStudent not found!\n");
            }
        }

        /* ---------- DELETE ---------- */

        else if (choice == 4)
        {
            FILE *temp;
            found = 0;

            printf("\n========== DELETE STUDENT ==========\n");

            roll = getRollNumber();

            fp = fopen("ass1.txt", "r");

            if (fp == NULL)
            {
                printf("\nNo student records found!\n");
                continue;
            }

            temp = fopen("temp.txt", "w");

            if (temp == NULL)
            {
                printf("\nError creating temporary file!\n");
                fclose(fp);
                continue;
            }

            while (fscanf(fp, "%d|%49[^|]|%49[^\n]\n",
                          &s.rollNo,
                          s.name,
                          s.email) == 3)
            {
                if (s.rollNo == roll)
                {
                    found = 1;

                    /* Do not write this student */
                    continue;
                }

                fprintf(temp, "%d|%s|%s\n",
                        s.rollNo,
                        s.name,
                        s.email);
            }

            fclose(fp);
            fclose(temp);

            if (found)
            {
                remove("ass1.txt");

                if (rename("temp.txt", "ass1.txt") != 0)
                {
                    printf("\nError deleting student!\n");
                }
                else
                {
                    printf("\nStudent deleted successfully!\n");
                }
            }
            else
            {
                remove("temp.txt");
                printf("\nStudent not found!\n");
            }
        }

        /* ---------- EXIT ---------- */

        else if (choice == 5)
        {
            printf("\nExiting program...\n");
        }

    } while (choice != 5);

    return 0;
}