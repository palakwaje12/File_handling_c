#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<limits.h>

struct Student
{
    int rollNo;
    char name[50];
    char email[50];
};
//validate roll no
#include <limits.h>

int validateRollNumber(char input[])
{
    int rollNo = 0;
    int digit;

    if (strlen(input) == 0)
        return 0;

    // Check whether input contains only digits
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)input[i]))
        {
            printf("Please enter number only.\n");
            return 0;
        }

        digit = input[i] - '0';   //this lets us know that input is digit only

        // Check INT limit BEFORE storing the digit
        if (rollNo > (INT_MAX - digit) / 10)
        {
            printf("Enter a number within the int limit (0 to %d).\n", INT_MAX);
            return 0;
        }

        rollNo = rollNo * 10 + digit;
    }

    if (rollNo <= 0)
    {
        printf("Please enter positive number only.\n");
        return 0;
    }

    return 1;
}
//validate name
int validateName(char name[])
{
    int hasLetter = 0;

    if (strlen(name) == 0)
        return 0;

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (isalpha(name[i]))
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
//email validation
int validateEmail(char email[])
{
    int atCount = 0;
    int atPosition = -1;
    int dotPosition = -1;

    if (strlen(email) == 0)
        return 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (isspace((unsigned char)email[i]))
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

    if (atCount != 1)
        return 0;

    if (atPosition == 0)
        return 0;

    if (email[atPosition + 1] == '\0')
        return 0;

    if (dotPosition <= atPosition + 1)
        return 0;

    if (email[dotPosition + 1] == '\0')
        return 0;

    if (dotPosition == atPosition - 1)
        return 0;

    return 1;
}
// GET ROLL NUMBER 
int getRollNumber()
{
    char input[100];

    while (1)
    {
        printf("Enter Roll Number: ");

        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (validateRollNumber(input))
        {
            return atoi(input);
        }
    }
}
//get name
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
        printf("Name should contain alphabets only.\n");
    }
}
//GET EMAIL
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
//CHECK  for DUPLICATE ROLL NUMBER 
int rollNumberExists(long roll)
{
    FILE *fp;
    struct Student s;

    fp = fopen("ass1.txt", "r");

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d|%49[^|]|%49[^\n]",
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
        printf("----STUDENT FILE CRUD SYSTEM----\n");

        printf("1. Create / Add Student\n");
        printf("2. Read / Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

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
        switch (choice)
        {

            case 1:

                fp = fopen("ass1.txt", "a");

                if (fp == NULL)
                {
                    printf("Error opening file!\n");
                    break;
                }

                printf("\n========== ADD STUDENT ==========\n");

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

                getName(s.name);

                getEmail(s.email);

                //Save into file
                fprintf(fp, "%d|%s|%s\n",
                        s.rollNo,
                        s.name,
                        s.email);

                fclose(fp);

                printf("\nStudent added successfully!\n");

                break;


            // ================= READ =================

            case 2:

                fp = fopen("ass1.txt", "r");

                if (fp == NULL)
                {
                    printf("\nNo student records found!\n");
                    break;
                }

                printf("\n========== STUDENT RECORDS ==========\n");

                int count = 0;

                while (fscanf(fp, "%d|%49[^|]|%49[^\n]",    //\n removed
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

                break;


            // ================= UPDATE =================

            case 3:
            {
                FILE *temp;

                found = 0;

                printf("\n========== UPDATE STUDENT ==========\n");

                roll = getRollNumber();


                fp = fopen("ass1.txt", "r");

                if (fp == NULL)
                {
                    printf("\nNo student records found!\n");
                    break;
                }


                temp = fopen("temp.txt", "w");

                if (temp == NULL)
                {
                    printf("\nError creating temporary file!\n");

                    fclose(fp);

                    break;
                }


                while (fscanf(fp, "%d|%49[^|]|%49[^\n]",
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

                break;
            }
            //delete
            case 4:
            {
                FILE *temp;

                found = 0;

                printf("\n========== DELETE STUDENT ==========\n");

                roll = getRollNumber();
                fp = fopen("ass1.txt", "r");
                if (fp == NULL)
                {
                    printf("\nNo student records found!\n");
                    break;
                }
                temp = fopen("temp.txt", "w");

                if (temp == NULL)
                {
                    printf("\nError creating temporary file!\n");

                    fclose(fp);

                    break;
                }

                while (fscanf(fp, "%d|%49[^|]|%49[^\n]",
                              &s.rollNo,
                              s.name,
                              s.email) == 3)
                {
                    if (s.rollNo == roll)
                    {
                        found = 1;

                        // Do not copy this student
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
                break;
            }

            case 5:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}