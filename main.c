#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Structure for .csv entries
typedef struct Entry
{
    char firstName[40];
    char lastName[50];
    char number[17];
    char information[200];
    int lineNum;
} entry;

// Global variables
char inputCheck;

// Function prototpyes
int menu();
void newEntry(entry *userEntry);
bool is_valid_phone_number(char *input);
void showEntries(entry *userEntry);
void deleteEntry(entry *userEntry);
void editEntry(entry *userEntry);
void getUserInput(entry *userEntry);
void searchEntry(entry *userEntry);
int validateName(char *name);
void getInputAndValidate(char *prompt, char *input);

// Main function
int main()
{
    menu();

    system("pause");
    return 0;
}

// Menu function
int menu()
{
    // Variable declaration
    int choice;
    entry userEntry;

    // Print UI menu for user
    printf("\n\n+--------------------------------+\n");
    printf("| -1- Alle Eintraege anzeigen    |\n");
    printf("| -2- Neuer Eintrag              |\n");
    printf("| -3- Eintrag bearbeiten         |\n");
    printf("| -4- Eintrag loeschen           |\n");
    printf("| -5- Eintrag suchen             |\n");
    printf("| -6- Programm verlassen         |\n");
    printf("+--------------------------------+\n\n");

    // Get user input and check if it's a number
    printf("Bitte treffen Sie eine Auswahl: ");
    while (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Falsches Format. Bitte geben Sie eine der oberen Zahlen ein: ");
    }

    // Inputs which aren't in the range, will get asked again for a valid number.
    while (choice > 6 || choice < 1)
    {
        printf("Bitte geben Sie eine gueltige Zahl ein: ");
        scanf("%d", &choice);
        fflush(stdin);
    }

    // Call function based on input
    switch (choice)
    {
    case 1:
        showEntries(&userEntry);
        break;

    case 2:
        newEntry(&userEntry);
        break;

    case 3:
        editEntry(&userEntry);
        break;

    case 4:
        deleteEntry(&userEntry);
        break;

    case 5:
        searchEntry(&userEntry);
        break;

    case 6:
        printf("\nProgramm schliessen ...\n\n");

        // This closes the program
        return EXIT_SUCCESS;
        break;
    }
}

// Function for a new entry
void newEntry(entry *userEntry)
{
    printf("\n\nNeuer Eintrag (Fuer Umlaute: ae, ue, oe!)");
    printf("\n----------------------------------------------------------\n\n");

    // Get user input, working with scanf() because of the formatting of the .csv file
    getUserInput(userEntry);
    inputCheck = ' ';

    // Check if user types in a valid input
    while (inputCheck != 'j' && inputCheck != 'n')
    {
        if (inputCheck != ' ')
        {
            printf("Ungueltige Eingabe! ");
        }
        printf("Moechtest du diesen Kontakt speichern (j/n)? ");
        scanf("%c", &inputCheck);
        fflush(stdin);
    }

    // If user wants to save the entry
    if (inputCheck == 'j')
    {
        // Save data in .csv file using append
        printf("\nKontakt wird gespeichert ...");
        FILE *fptr = fopen("contacts.csv", "a");
        fprintf(fptr, "%s;%s;%s;%s\n", userEntry->firstName, userEntry->lastName, userEntry->number, userEntry->information);
        fclose(fptr);
    }

    // If user doesn't want to save the entry
    else
    {
        printf("\nKontakt wird nicht gespeichert ...");
    }

    menu();
}

// Function to get user input
void getUserInput(entry *userEntry)
{
    // Get user input and validate it (names)
    getInputAndValidate("Was ist der Vorname von deinem Kontakt? ", userEntry->firstName);
    getInputAndValidate("Was ist der Nachname von deinem Kontakt? ", userEntry->lastName);

    // Check if user types valid phone number
    printf("Wie lautet die Telefonnummer von deinem Kontakt (+41 XX XXX XX XX)? ");
    while (1)
    {
        char number[17];
        scanf("%[^\n]s", number);
        fflush(stdin);
        if (is_valid_phone_number(number))
        {
            strcpy(userEntry->number, number);
            break;
        }
        else
        {
            printf("Ungueltige Eingabe! Die Telefonnummer muss im Format +41 XX XXX XX XX angegeben werden. Bitte versuche es erneut: ");
        }
    }

    printf("Sonstige Informationen? ");
    scanf("%[^\n]s", &userEntry->information);
    fflush(stdin);
}

// Function to check if the phone number is valid
bool isValidPhoneNumber(char *input)
{
    char *mask = "+41 ## ### ## ##";
    if (strlen(input) != strlen(mask))
    {
        return false;
    }
    for (int i = 0; i < strlen(mask); i++)
    {
        if (mask[i] == '#')
        {
            if (!isdigit(input[i]))
            {
                return false;
            }
        }
        else if (input[i] != mask[i])
        {
            return false;
        }
    }
    return true;
}

// Function to validate the name
int validateName(char *name)
{
    int valid = 1;
    // Go through every character of the string and check if it's a letter
    for (int i = 0; i < strlen(name); i++)
    {
        // checks if character is a letter
        if (!isalpha(name[i]) && name[i] != '-')
        {
            valid = 0;
        }

        // checks if the first and last letter are a - or not
        if (name[i] == '-' && (i == 0 || i == strlen(name) - 1))
        {
            valid = 0;
        }
    }
    if (valid == 0)
    {
        printf("Fehler: Die Eingabe darf keine Zahlen oder Sonderzeichen enthalten. Bitte versuche es erneut: ");
        return 0;
    }
    else
    {
        return 1;
    }
}

// Function to get input and validate it
void getInputAndValidate(char *prompt, char *input)
{
    printf("%s", prompt);
    while (1)
    {
        fflush(stdin);
        scanf("%[^\n]s", input);
        fflush(stdin);
        if (validateName(input) == 0)
        {
            continue;
        }
        else
        {
            break;
        }
    }
}

// Function to show all entries
void showEntries(entry *userEntry)
{
    // Variable Declaration
    FILE *fptr;
    char lineRead[307];
    int counter = 1;

    printf("\n\nAlle Eintraege anzeigen");
    printf("\n-------------------------------------------------------------------------\n\n");

    // Check if file exists
    if ((fptr = fopen("contacts.csv", "r")) == NULL)
    {
        // Go back to menu, if it doesn't exist
        printf("\nDatei exisitiert nicht! Bitte zuerst neue Eintraege erstellen.");
    }
    else
    {
        // Read every line of the .csv file
        while (fgets(lineRead, 307, fptr) != NULL)
        {
            // Split the line into tokens separated by semicolons
            char *token = strtok(lineRead, ";");

            // Print the index and the first token
            printf("%d: %-20s", counter, token);

            // Print the rest of the tokens with a space character in between
            while (token = strtok(NULL, ";"))
            {
                printf(" %-20s", token);
            }

            // Print a newline character to move to the next line
            printf("\n");

            // Increment the counter
            counter++;
        }
    }

    // Close file
    fclose(fptr);

    // After function finishes go back to menu
    menu();
}

// Function to delete an entry
void deleteEntry(entry *userEntry)
{
    // Create variable for temporary file and contacts file
    FILE *file, *temp;

    // Variable declaration
    char filename[13] = "contacts.csv", tempFile[28];
    char buffer[2048];
    int deleteLine = 0;
    bool keepGoing = true;
    int currentLine = 1;
    inputCheck = ' ';

    // create (name for) temporary file
    strcpy(tempFile, "temp____");
    strcat(tempFile, filename);

    printf("\nEintrag loeschen");
    printf("\n-------------------------------------------------------------------------\n\n");

    // enter the line to be deleted
    printf("Zu loeschender Eintrag (Nummer): ");
    while (scanf("%d", &deleteLine) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Falsches Format. Bitte geben Sie eine Zahl ein: ");
    }
    fflush(stdin);

    // open original file to read and temporary file to write
    file = fopen(filename, "r");
    temp = fopen(tempFile, "w");

    // if Error output go back to menu
    if (file == NULL || temp == NULL)
    {
        printf("\nDatei exisitiert nicht! Bitte zuerst neue Eintraege erstellen.");
        menu();
    }

    // Check if user wants to delete the entry
    while (inputCheck != 'j' && inputCheck != 'n')
    {
        if (inputCheck != ' ')
        {
            printf("Ungueltige Eingabe! ");
        }

        printf("Bist du dir sicher, dass du Eintrag #%d loeschen moechtest (j/n)? ", deleteLine);
        scanf("%c", &inputCheck);
        fflush(stdin);
    }

    // If user wants to delete the entry
    if (inputCheck == 'j')
    {
        printf("Eintrag #%d wird geloescht ...", deleteLine);

        // copy the text from original file into the temporary file except the line to be deleted
        do
        {
            fgets(buffer, 2048, file);

            if (feof(file))
                keepGoing = false;
            else if (currentLine != deleteLine)
                fputs(buffer, temp);

            currentLine++;

        } while (keepGoing == true);

        // close all open files
        fclose(file);
        fclose(temp);

        // remove original file
        remove(filename);

        // rename temporary file to the name of original file
        rename(tempFile, filename);
    }

    // If user doesn't want to delete the entry
    else
    {
        printf("Eintrag #%d wird nicht geloescht ...", deleteLine);

        // Close all open files
        fclose(file);
        fclose(temp);

        // Remove temporary file
        remove(tempFile);
    }

    // When function finishes go back to menu
    menu();
}

// Function to edit an entry
void editEntry(entry *userEntry)
{
    // Create variable for temporary file and contacts file
    // Variable declaration
    char buffer[2048];
    int editLine = 0;
    bool keepGoing = true;
    int currentLine = 1;
    inputCheck = ' ';

    printf("\nEintrag bearbeiten (Fuer Umlaute: ae, ue, oe!)");
    printf("\n-------------------------------------------------------------------------\n\n");

    // enter the line to be edited
    printf("Welche Linie willst du bearbeiten? ");
    scanf("%d", &editLine);
    fflush(stdin);

    // open original file to read and temporary file to write
    FILE *file = fopen("contacts.csv", "r");
    FILE *new = fopen("new.csv", "w");

    // if Error go back to menu
    if (file == NULL || new == NULL)
    {
        printf("Datei exisitiert nicht! Bitte zuerst neue Eintraege erstellen.");
        menu();
    }

    // copy the text from original file into the new file except the edited line
    do
    {
        fgets(buffer, 2048, file);

        if (feof(file))
            keepGoing = false;
        else if (currentLine != editLine)
            fputs(buffer, new);
        else if (currentLine == editLine)
        {
            getUserInput(userEntry);

            // Check if user wants to save the entry
            printf("Moechtest du die Kontaktinformationen aendern (j/n)? ");
            scanf("%c", &inputCheck);
            fflush(stdin);

            // Check if user types in a valid input
            while (inputCheck != 'j' && inputCheck != 'n')
            {
                if (inputCheck != ' ')
                {
                    printf("Ungueltige Eingabe! ");
                }
                printf("Moechtest du diesen Kontakt speichern (j/n)? ");
                scanf("%c", &inputCheck);
                fflush(stdin);
            }

            // If user wants to save the entry
            if (inputCheck == 'j')
            {
                // Save data in .csv file using append
                printf("\nAenderungen werden gespeichert ...");
                fprintf(new, "%s;%s;%s;%s\n", userEntry->firstName, userEntry->lastName, userEntry->number, userEntry->information);
            }

            // If user doesn't want to save the entry
            else
            {
                printf("\nAenderungen werden nicht gespeichert ...");
                fputs(buffer, new);
            }
        }
        currentLine++;
    } while (keepGoing == true);

    fclose(file);
    fclose(new);

    remove("contacts.csv");
    rename("new.csv", "contacts.csv");

    menu();
}

// Function to search for an entry
void searchEntry(entry *userEntry)
{
    // pointer declaration
    FILE *fp;

    // variable declaration
    char word[100], filename[100] = "contacts.csv";
    char line[100];
    int counter = 0;
    int j = 0;

    printf("Wen suchst du?: ");
    fflush(stdin);
    scanf("%[^\n]", word);
    fflush(stdin);

    printf("Eintraege werden gesucht...\n");

    fp = fopen(filename, "r");

    // checks if pointer gets back nothing
    if (fp == NULL)
    {
        printf("Datei exisitiert nicht! Bitte zuerst neue Eintraege erstellen.");
        menu();
    }

    printf("Eintraege zu '%s' gefunden!\n\n", word);

    // reads every line of the file contacts.csv until the end is reached
    while (fgets(line, sizeof(line), fp))
    {

        line[strcspn(line, "\n")] = '\0'; // searchs for new lines and chaneges it to \0 (end of a string)

        if (strstr(line, word))
        {
            counter++;

            char *token = strtok(line, ";");

            printf("-%d-  ", counter);

            // loops through the string to extract all other tokens
            while (token != NULL)
            {
                printf("%-20s", token); // adjusts the buffer zone of each entry to 20 characers

                token = strtok(NULL, ";"); // sets the variable token to the delimiter ;
            }

            printf("\n");
        }
    }

    if (strstr(line, word) == NULL)
    {
        while (j < 1)
        {
            printf("\nKeine Eintraege gefunden! Bitte zuerst neue Eintraege erstellen!");
            j++;
        }
    }

    fclose(fp);

    menu();
}
