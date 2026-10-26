#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 10

struct HashMap {
    char name[50];
    char email[50];
    int status;
};

struct HashMap table[SIZE];

// Function declarations
int isNumber(const char *str);
int isValidName(const char *str);
int isValidEmail(const char *str);
int readInput(char str[], int size);
int hashFunction(const char name[]);

void insert();
void search();
void update();
void deleteRecord();
void display();

// Numeric validation
int isNumber(const char *str) {
    if (*str == '\0')   //checks if the string is empty
        return 0;

    while (*str) {
        if (!isdigit((unsigned char)*str))
            return 0;
        str++;
    }

    return 1;
}

// Name validation
int isValidName(const char *str) {
    if (*str == '\0')
        return 0;

    int hasLetter = 0;

    while (*str) {
        if (!isalpha((unsigned char)*str) && *str != ' ')  //if the char is neither an alpha nor a space reject the name
            return 0;
        if (isalpha((unsigned char)*str))
            hasLetter = 1;
        str++;
    }
    return hasLetter;
}

// Email validation
int isValidEmail(const char *str) {
    const char *at = strchr(str, '@');

    if (!at || at == str)      //did not found @
        return 0;

    if (strchr(at + 1, '@'))   //should not be at the first position
        return 0;

    const char *dot = strchr(at + 1, '.');

    if (!dot || dot == at + 1)
        return 0;

    if (*(dot + 1) == '\0')
        return 0;

    // No spaces allowed
    for (const char *p = str; *p; p++) {
        if (isspace((unsigned char)*p))
            return 0;
    }

    // Validate domain
    size_t domainLen = dot - (at + 1);
    char domain[20];

    if (domainLen >= sizeof(domain))
        return 0;

    strncpy(domain, at + 1, domainLen);
    domain[domainLen] = '\0';

    if (strcmp(domain, "gmail") != 0 &&
        strcmp(domain, "vit") != 0)
        return 0;

    if (strcmp(dot + 1, "com") == 0 ||
        strcmp(dot + 1, "in") == 0 ||
        strcmp(dot + 1, "edu") == 0)
        return 1;

    return 0;
}

// Safe input function
int readInput(char str[], int size) {
    if (!fgets(str, size, stdin))
        return 0;

    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        return 0;
    }

    return 1;
}

// Hash function
int hashFunction(const char name[]) {
    unsigned int sum = 0;

    for (int i = 0; name[i] != '\0'; i++) {
        sum += (unsigned char)name[i];
    }

    return sum % SIZE;
}

// Insert record
void insert() {
    char name[50], email[50];
    int index, start;
    int firstDeleted = -1;

    do {
        printf("\nEnter Name : ");

        if (!readInput(name, sizeof(name))) {
            printf("Invalid Input or Name Too Long!\n");
            continue;
        }

        if (!isValidName(name)) {
            printf("Invalid Name! Only letters and spaces allowed.\n");
            continue;
        }

        break;
    } while (1);

    index = hashFunction(name);
    start = index;

    // Check duplicate and find available slot
    do {
        if (table[index].status == 1 &&    //checks if current posn is occupied
            strcmp(table[index].name, name) == 0) {    //when two strings are equal return 0
            printf("\nName Already Exists!\n");
            return;
        }

        if (table[index].status == 2 &&    //deleted position
            firstDeleted == -1) {
            firstDeleted = index;
        }

        if (table[index].status == 0)     //empty position
            break;

        index = (index + 1) % SIZE;

    } while (index != start);   //until it returns to its original position

    if (firstDeleted != -1) {
        index = firstDeleted;
    } else if (table[index].status != 0) {
        printf("\nHashMap is Full!\n");
        return;
    }

    do {
        printf("Enter Email : ");

        if (!readInput(email, sizeof(email))) {
            printf("Invalid Input or Email Too Long!\n");
            continue;
        }

        if (!isValidEmail(email)) {
            printf("Invalid Email! Use gmail/vit with com/in/edu.\n");
            continue;
        }

        break;
    } while (1);

    strcpy(table[index].name, name);
    strcpy(table[index].email, email);
    table[index].status = 1;

    printf("\nRecord Inserted Successfully at Index %d!\n",
           index);
}

// Search record
void search() {
    char name[50];
    int index, start;

    do {
        printf("\nEnter Name to Search : ");

        if (!readInput(name, sizeof(name)) ||
            !isValidName(name)) {
            printf("Invalid Name!\n");
            continue;
        }
        break;
    } while (1);

    index = hashFunction(name);
    start = index;

    while (table[index].status != 0) {   //continue searching until current posn is not a never-used empty slot
        if (table[index].status == 1 &&    //check if posn is occupied and stored name matches the name we r looking for
            strcmp(table[index].name, name) == 0) {
            printf("\nRecord Found!\n");
            printf("Index : %d\n", index);
            printf("Name  : %s\n", table[index].name);
            printf("Email : %s\n", table[index].email);
            return;
        }

        index = (index + 1) % SIZE;

        if (index == start)   //if we came back to the starting posn means entire table has been checked
            break;        //but we didn't found the record
    }

    printf("\nRecord Not Found!\n");
}

// Update email
void update() {
    char name[50], email[50];
    int index, start;

    do {
        printf("\nEnter Name to Update : ");

        if (!readInput(name, sizeof(name)) ||
            !isValidName(name)) {
            printf("Invalid Name!\n");
            continue;
        }

        break;
    } while (1);

    index = hashFunction(name);
    start = index;

    while (table[index].status != 0) {
        if (table[index].status == 1 &&
            strcmp(table[index].name, name) == 0) {

            do {
                printf("Enter New Email : ");

                if (!readInput(email, sizeof(email)) ||
                    !isValidEmail(email)) {
                    printf("Invalid Email!\n");
                    continue;
                }

                break;
            } while (1);

            strcpy(table[index].email, email);

            printf("\nEmail Updated Successfully!\n");
            return;
        }

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    printf("\nRecord Not Found!\n");
}

// Delete record
void deleteRecord() {
    char name[50];
    int index, start;

    do {
        printf("\nEnter Name to Delete : ");

        if (!readInput(name, sizeof(name)) ||
            !isValidName(name)) {
            printf("Invalid Name!\n");
            continue;
        }

        break;
    } while (1);

    index = hashFunction(name);
    start = index;

    while (table[index].status != 0) {
        if (table[index].status == 1 &&
            strcmp(table[index].name, name) == 0) {

            table[index].status = 2;
            table[index].name[0] = '\0';
            table[index].email[0] = '\0';

            printf("\nRecord Deleted Successfully!\n");
            return;
        }

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    printf("\nRecord Not Found!\n");
}

// Display all records
void display() {
    int found = 0;

    printf("\n========== HASHMAP RECORDS ==========\n");

    for (int i = 0; i < SIZE; i++) {
        if (table[i].status == 1) {
            printf("\nIndex : %d\n", i);
            printf("Name  : %s\n", table[i].name);
            printf("Email : %s\n", table[i].email);
            found = 1;
        }
    }

    if (!found)
        printf("\nNo Records Found!\n");
}

// Main function
int main() {
    char input[100];
    unsigned int choice;

    while (1) {
        printf("\n========== HASHMAP MENU ==========\n");
        printf("1. Insert Record\n");
        printf("2. Search Record\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Display Records\n");
        printf("6. Exit\n");

        printf("Enter Choice : ");

        if (!readInput(input, sizeof(input))) {
            printf("Invalid Input!\n");
            continue;
        }

        if (!isNumber(input)) {
            printf("Invalid Choice! Enter Numbers Only.\n");
            continue;
        }

        choice = (unsigned int)atoi(input);

        switch (choice) {
            case 1:
                insert();
                break;

            case 2:
                search();
                break;

            case 3:
                update();
                break;

            case 4:
                deleteRecord();
                break;

            case 5:
                display();
                break;

            case 6:
                printf("\nExiting Program...\n");
                return 0;

            default:
                printf("\nInvalid Choice!\n");
        }
    }
}