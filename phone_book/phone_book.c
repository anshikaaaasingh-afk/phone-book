#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// Define KeyWords
#define ENTER '\n'
#define TAB 9
#define BKSP 8

// Function ProtoType
void password(void);
void menu(void);
void add(void);
void search(void);
void modify(void);
void list(void);
void delete(void);
void end(void);

int main(void)
{
    password();
    return 0;
}

// Explained the password function in proper detailed.
void password()
{
    system("clear");

    char pwd[255];
    char code[255] = {"Anshi"};
    int i = 0;
    char ch;

    printf("Enter your password. Hit ENTER to confirm. \n");
    printf("Password:");

    while (1)
    {

        ch = getchar(); // get key

        if (ch == ENTER || ch == TAB)
        {
            pwd[i] = '\0';
            break;
        }
        else if (ch == BKSP)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); // for backspace
            }
        }
        else
        {
            pwd[i++] = ch;
            printf("* \b"); // to replace password character with *
        }

        // printf("\n\nPassword:%s\nLength:%d\n\n", pwd, i);  -- prints the user input & lenght of string

        // verifies the password
        if (strcmp(code, pwd) == 0)
        {
            printf("\nCorrect Password!");
            sleep(2);
            menu();
            break;
        }
        else
        {

            printf("\nInvaild Password!");
            sleep(2);
        }
    }
}

void menu()
{
    // clears the terminal screen
    system("clear");

label1:

    // clears the input stream - prevents the program from going into infinite loop

    printf(">>> Phone Book Main Menu <<< \n");
    printf("> 1. Add Record\n");
    printf("> 2. Search Record\n");
    printf("> 3. Modify Record\n");
    printf("> 4. List Record\n");
    printf("> 5. Delete Record\n");
    printf("> 6. Close the Phone Book \n\n");

    int input;
    printf("Please enter a number to proceed: ");
    scanf("%d", &input);
    while (getchar() != '\n')
        ;

    switch (input)
    {
    case 1:
        add();
        break;
    case 2:
        search();
        break;

    case 3:
        modify();
        break;

    case 4:
        list();
        break;

    case 5:
        delete();
        break;

    case 6:
        end();
        break;

    default:
        printf("\nXXX - Invaild input - XXX\n\n");
        goto label1;
        break;
    }
}

void add()
{

label1:

    // clears the input stream - prevents the program from going into infinite loop

    system("clear");

    // opening file -- ab+ -- it will create the file if its not there, also used for writing.
    FILE *pF = fopen("record.txt", "ab+");

    char name[255];
    char address[255];
    char mail[255];
    char number[20];

    if (pF != NULL)
    {
        printf("Enter Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        printf("Enter Address (City): ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = '\0';

        printf("Enter Mail-ID: ");
        fgets(mail, sizeof(mail), stdin);
        mail[strcspn(mail, "\n")] = '\0';

        printf("Enter Phone No.: ");
        fgets(number, sizeof(number), stdin);
        number[strcspn(number, "\n")] = '\0';
        ;

        fprintf(pF, "%s %s %s %s \n",
                name,
                address,
                mail,
                number);
    }
    else
        printf("Unable to open/locate the file.");

    // closes the file
    fclose(pF);

    // retry screen
    char input;
    printf("Do you wanna enter more records [y/N]: ");
    scanf(" %c", &input);
    while (getchar() != '\n')
        ;

    if (input == 'y' || input == 'Y')
        goto label1;
    else if (input == 'n' || input == 'N')
    {
        printf("\nRedirecting to main menu.");
        sleep(2);
        menu();
    }
    else
    {
        printf("\nInvaild input. Redirecting to main menu.");
        sleep(2);
        menu();
    }
}

void search()
{

label2:

    system("clear");

    FILE *pF = fopen("record.txt", "r");
    if (pF == NULL)
    {
        printf("No records found.\n");
        return;
    }

    char name[255];
    char address[255];
    char mail[255];
    char number[20];

    int flag = 0;
    int compare;

    char find[255];
    printf("Enter the name of the person you want to see the detail: ");
    fgets(find, sizeof(find), stdin);
    find[strcspn(find, "\n")] = '\0';

    while (fscanf(pF, "%s %s %s %s \n", name, address, mail, number) != EOF)
    {
        // strcmp(variable, variable1) -- if both the strings are equal then it will return 0 otherwise a random number.
        compare = strcmp(find, name);

        if (compare == 0)
        {
            printf("\n>>> Record Found <<< \n\n");

            printf("> Name: %s \n", name);
            printf("> Address: %s \n", address);
            printf("> Mail ID: %s \n", mail);
            printf("> Phone No.: %s \n", number);

            flag = 1;
        }
    }

    fclose(pF);

    if (flag == 0)
        printf("\n>>> Record Not Found <<< \n");

    char input;
    printf("\nDo you wanna search for more records [y/N]: ");
    scanf(" %c", &input);
    while (getchar() != '\n')
        ;

    if (input == 'y' || input == 'Y')
        goto label2;
    else if (input == 'n' || input == 'N')
    {
        printf("\nRedirecting to main menu.");
        sleep(2);
        menu();
    }
    else
    {
        printf("\nInvaild input. Redirecting to main menu.");
        sleep(2);
        menu();
    }
}

void modify()
{
    system("clear");

    // opening main record file & a temporary file s
    FILE *pF = fopen("record.txt", "r");
    if (pF == NULL)
    {
        printf("No records found.\n");
        return;
    }
    FILE *pTemp = fopen("temporary.txt", "w");

    char name[255], address[255], mail[255];
    char name1[255], address1[255], mail1[255];
    char number[20], number1[20];

    int compare, flag = 0;

    printf("Enter the name of the person you want to see the detail: ");
    fgets(name1, sizeof(name1), stdin);
    name1[strcspn(name1, "\n")] = '\0';

    system("clear");

    while (fscanf(pF, "%s %s %s %s \n", name, address, mail, number) != EOF)
    {
        compare = strcmp(name1, name);
        if (compare == 0)
        {
            printf("-------------------------------\n");
            printf(">>> Record Modification <<< \n");
            printf("-------------------------------\n\n");

            printf("Enter Name: ");
            fgets(name1, sizeof(name1), stdin);
            name1[strcspn(name1, "\n")] = '\0';

            printf("Enter Address (City): ");
            fgets(address1, sizeof(address1), stdin);
            address1[strcspn(address1, "\n")] = '\0';

            printf("Enter Mail-ID: ");
            fgets(mail1, sizeof(mail1), stdin);
            mail1[strcspn(mail1, "\n")] = '\0';

            printf("Enter Phone No.: ");
            fgets(number1, sizeof(number1), stdin);
            number1[strcspn(number1, "\n")] = '\0';
            ;

            fprintf(pTemp, "%s %s %s %s \n", name1, address1, mail1, number1);

            flag = 1;
        }
        else
            fprintf(pTemp, "%s %s %s %s \n", name, address, mail, number);
    }

    if (flag == 0)
    {
        printf("-------------------------------\n");
        printf(">>> Record Not Found <<< \n");
        printf("-------------------------------\n\n");
    }

    fclose(pF);
    fclose(pTemp);

    // deletes everything from main record file
    pF = fopen("record.txt", "w");
    fclose(pF);

    pF = fopen("record.txt", "a");
    pTemp = fopen("temporary.txt", "r");

    // copies records from temporary file to main record file
    while (fscanf(pTemp, "%s %s %s %s \n", name, address, mail, number) != EOF)
    {
        fprintf(pF, "%s %s %s %s \n", name, address, mail, number);
    }

    fclose(pF);
    fclose(pTemp);

    // deletes everything from temporary file
    pTemp = fopen("temporary.txt", "w");
    fclose(pTemp);

    printf("\n\nProcessing your changes....");
    sleep(3);
    menu();
}

void list()
{
    system("clear");
    FILE *pF = fopen("record.txt", "r");
    if (pF == NULL)
    {
        printf("No records found.\n");
        return;
    }

    char name[255];
    char address[255];
    char mail[255];
    char number[20];

    // lists all the records from main record files
    while (fscanf(pF, "%254s %254s %254s %19s",
                  name,
                  address,
                  mail,
                  number) == 4)
    {
        printf("-------------------------------\n");
        printf("> Name: %s \n", name);
        printf("> Address: %s \n", address);
        printf("> Mail-ID: %s \n", mail);
        printf("> Phone No.: %s \n", number);
        printf("-------------------------------\n\n\n");
    }

    fclose(pF);

    printf("Press any key to get back to main menu.\n");
    getchar();
    menu();
}

void delete()
{
    system("clear");

    FILE *pF = fopen("record.txt", "r");
    if (pF == NULL)
    {
        printf("No records found.\n");
        return;
    }
    FILE *pTemp = fopen("temporary.txt", "w");

    char name[255], name1[255], address[255], mail[255];
    char number[20];

    int compare, flag = 0;

    system("clear");

    printf("Enter the name of the person you want to see the detail: ");
    fgets(name1, sizeof(name1), stdin);
    name1[strcspn(name1, "\n")] = '\0';

    system("clear");

    while (fscanf(pF, "%s %s %s %s \n", name, address, mail, number) != EOF)
    {
        compare = strcmp(name1, name);
        if (compare == 0)
        {
            // this time the record won't be copied to temporary file and this record will be skipped.
            printf("-------------------------------\n");
            printf(">>> Record Deleted Successfully <<< \n");
            printf("-------------------------------\n\n");
            flag = 1;
        }
        else
        {
            // it will copy the records from main file to temporary file one by one.
            fprintf(pTemp, "%s %s %s %s \n", name, address, mail, number);
        }
    }

    if (flag == 0)
    {
        printf("-------------------------------\n");
        printf(">>> Record Not Found <<< \n");
        printf("-------------------------------\n\n");
    }

    fclose(pF);
    fclose(pTemp);

    // deletes everything from main record file
    pF = fopen("record.txt", "w");
    fclose(pF);

    pF = fopen("record.txt", "a");
    pTemp = fopen("temporary.txt", "r");

    while (fscanf(pTemp, "%s %s %s %s \n", name, address, mail, number) != EOF)
    {
        fprintf(pF, "%s %s %s %s \n", name, address, mail, number);
    }

    fclose(pF);
    fclose(pTemp);
    // deletes everything from temporary file
    pTemp = fopen("temporary.txt", "w");
    fclose(pTemp);

    printf("\n\nProcessing your changes....");
    sleep(3);
    menu();
}

void end()
{
    system("clear");

    printf(">>> Phone Book in C <<< \n\n");
    printf("> Creator: @Alkaison (Ganesh Mourya) \n\n");
    printf("> Github: https://github.com/Alkaison \n");
    printf("> Twitter: https://twitter.com/Alkaison \n");
    printf("> LinkedIn: https://www.linkedin.com/in/Alkaison \n\n");
    printf("Press any key to exit. \n");

    getchar();
    exit(0);
}