
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX 256

typedef struct
{
    char name[MAX];
    char address[MAX];
    char email[MAX];
    char phone[MAX];
} Contact;

int getch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clear_screen()
{
    system("clear");
}

void read_line(char *buffer, int size)
{
    if (fgets(buffer, size, stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void save_contact(Contact c)
{
    FILE *fp = fopen("record.txt", "a");
    if (!fp)
        return;
    fprintf(fp, "%s|%s|%s|%s\n", c.name, c.address, c.email, c.phone);
    fclose(fp);
}

int load_contact(FILE *fp, Contact *c)
{
    char line[1024];
    if (!fgets(line, sizeof(line), fp))
        return 0;

    line[strcspn(line, "\n")] = '\0';

    char *token = strtok(line, "|");
    if (!token)
        return 0;
    strcpy(c->name, token);

    token = strtok(NULL, "|");
    if (!token)
        return 0;
    strcpy(c->address, token);

    token = strtok(NULL, "|");
    if (!token)
        return 0;
    strcpy(c->email, token);

    token = strtok(NULL, "|");
    if (!token)
        return 0;
    strcpy(c->phone, token);

    return 1;
}

void add_record()
{
    Contact c;

    clear_screen();
    printf("=== Add Record ===\n");

    printf("Name: ");
    read_line(c.name, MAX);

    printf("Address: ");
    read_line(c.address, MAX);

    printf("Email: ");
    read_line(c.email, MAX);

    printf("Phone: ");
    read_line(c.phone, MAX);

    save_contact(c);

    printf("\nRecord added successfully.\n");
    printf("Press Enter...");
    getchar();
}

void list_records()
{
    clear_screen();

    FILE *fp = fopen("record.txt", "r");
    if (!fp)
    {
        printf("No records found.\n");
        getchar();
        return;
    }

    Contact c;
    int count = 0;

    while (load_contact(fp, &c))
    {
        printf("---------------------------\n");
        printf("Name    : %s\n", c.name);
        printf("Address : %s\n", c.address);
        printf("Email   : %s\n", c.email);
        printf("Phone   : %s\n", c.phone);
        count++;
    }

    fclose(fp);

    if (count == 0)
        printf("No records available.\n");

    printf("\nPress Enter...");
    getchar();
}

void search_record()
{
    clear_screen();

    char target[MAX];
    printf("Enter name to search: ");
    read_line(target, MAX);

    FILE *fp = fopen("record.txt", "r");
    if (!fp)
    {
        printf("No records found.\n");
        getchar();
        return;
    }

    Contact c;
    int found = 0;

    while (load_contact(fp, &c))
    {
        if (strcasecmp(c.name, target) == 0)
        {
            printf("\nRecord Found\n");
            printf("Name    : %s\n", c.name);
            printf("Address : %s\n", c.address);
            printf("Email   : %s\n", c.email);
            printf("Phone   : %s\n", c.phone);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nRecord not found.\n");

    printf("\nPress Enter...");
    getchar();
}

void modify_record()
{
    clear_screen();

    char target[MAX];
    printf("Enter name to modify: ");
    read_line(target, MAX);

    FILE *fp = fopen("record.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");

    if (!fp || !tmp)
    {
        printf("File error.\n");
        getchar();
        return;
    }

    Contact c;
    int found = 0;

    while (load_contact(fp, &c))
    {
        if (strcasecmp(c.name, target) == 0)
        {
            found = 1;

            Contact n;

            printf("\nNew Name: ");
            read_line(n.name, MAX);

            printf("New Address: ");
            read_line(n.address, MAX);

            printf("New Email: ");
            read_line(n.email, MAX);

            printf("New Phone: ");
            read_line(n.phone, MAX);

            fprintf(tmp, "%s|%s|%s|%s\n",
                    n.name, n.address, n.email, n.phone);
        }
        else
        {
            fprintf(tmp, "%s|%s|%s|%s\n",
                    c.name, c.address, c.email, c.phone);
        }
    }

    fclose(fp);
    fclose(tmp);

    remove("record.txt");
    rename("temp.txt", "record.txt");

    printf(found ? "\nRecord updated.\n" : "\nRecord not found.\n");
    printf("Press Enter...");
    getchar();
}

void delete_record()
{
    clear_screen();

    char target[MAX];
    printf("Enter name to delete: ");
    read_line(target, MAX);

    FILE *fp = fopen("record.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");

    if (!fp || !tmp)
    {
        printf("File error.\n");
        getchar();
        return;
    }

    Contact c;
    int found = 0;

    while (load_contact(fp, &c))
    {
        if (strcasecmp(c.name, target) == 0)
        {
            found = 1;
            continue;
        }

        fprintf(tmp, "%s|%s|%s|%s\n",
                c.name, c.address, c.email, c.phone);
    }

    fclose(fp);
    fclose(tmp);

    remove("record.txt");
    rename("temp.txt", "record.txt");

    printf(found ? "\nRecord deleted.\n" : "\nRecord not found.\n");
    printf("Press Enter...");
    getchar();
}

int password()
{
    char correct[] = "Anshi";

    while (1)
    {
        char entered[100];
        int i = 0;
        char ch;

        printf("Enter your password. Hit ENTER to confirm.\n");
        printf("Password: ");

        while ((ch = getch()) != '\n' && ch != '\r')
        {
            if ((ch == 127 || ch == 8) && i > 0)
            {
                i--;
                printf("\b \b");
            }
            else
            {
                entered[i++] = ch;
                printf("*");
            }
        }

        entered[i] = '\0';

        if (strcmp(entered, correct) == 0)
        {
            printf("\nCorrect Password!\n");
            sleep(1);
            return 1;
        }

        printf("\nInvalid Password!\n");
        sleep(1);
        clear_screen();
    }
}

int main()
{
    if (!password())
    {
        printf("\n\nInvalid password.\n");
        return 0;
    }

    int choice;
    char input[20];

    while (1)
    {
        clear_screen();

        printf("=== PHONE BOOK ===\n");
        printf("1. Add Record\n");
        printf("2. Search Record\n");
        printf("3. Modify Record\n");
        printf("4. List Records\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n\n");

        printf("Enter choice: ");
        read_line(input, sizeof(input));
        choice = atoi(input);

        switch (choice)
        {
        case 1:
            add_record();
            break;
        case 2:
            search_record();
            break;
        case 3:
            modify_record();
            break;
        case 4:
            list_records();
            break;
        case 5:
            delete_record();
            break;
        case 6:
            printf("Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice.\n");
            sleep(1);
        }
    }
}
