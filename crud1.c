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
//validate roll no
int validateRollNumber(char input[])
{
    int rollNo;

    if (strlen(input) == 0)      //no input is given return 0
        return 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)input[i]))
            return 0;
    }    
    rollNo = atoi(input);   //atoi converts string to integer i.e. ASCII to integer becoz fgets stores input as string nd rollno is int
    if (rollNo == 0)
        return 0;
    if (rollNo >= 100 && rollNo <= 999)
        return 0;

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
        if (isalpha((unsigned char)name[i]))
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
    char buffer[100];

    while (1)
    {
        printf("Enter Roll Number: ");

        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (validateRollNumber(buffer))
        {
            return atoi(buffer);
        }

        printf("Invalid roll number!\n");
        printf("Please enter a positive number only.\n");
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
//CHECK DUPLICATE ROLL NUMBER 
int rollNumberExists(int roll)
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


            // ================= EXIT =================

            case 5:

                printf("\nExiting program...\n");

                break;


            default:

                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);


    return 0;
}