#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure for .csv entries
typedef struct Entry
{
    char firstName[40];
    char lastName[50];
    char number[17];
    char information[200];
} entry;

// Global variables
char inputCheck;

// Function prototpyes
int menu();
void newEntry(entry *userEntry);
void showEntries();
void deleteEntry(entry *userEntry);
void editEntry(entry *userEntry);

// Main function
int main()
{
    menu();

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
    printf("| -4- Eintrag löschen            |\n");
    printf("| -5- Eintrag suchen             |\n");
    printf("| -6- Programm verlassen         |\n");
    printf("+--------------------------------+\n\n");

    // Get userinput and check if it's a number
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
        printf("Bitte geben Sie eine gültige Zahl ein: ");
        scanf("%d", &choice);
        fflush(stdin);
    }

    // Call function based on input
    switch (choice)
    {
    case 1:
        showEntries();
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
        // Fünfte Funktion verlinken
        break;

    case 6:
        printf("\nProgramm schliessen ...\n");

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
    printf("Was ist der Vorname von deinem Kontakt? ");
    fflush(stdin);
    scanf("%[^\n]s", &userEntry->firstName);

    // Using fflush(stdin) to clear input buffer
    fflush(stdin);

    printf("Was ist der Nachname von deinem Kontakt? ");
    scanf("%[^\n]s", &userEntry->lastName);
    fflush(stdin);

    printf("Was lautet die Telefonnummer von deinem Kontakt? ");
    scanf("%[^\n]s", &userEntry->number);
    fflush(stdin);

    printf("Sonstige Informationen? ");
    scanf("%[^\n]s", &userEntry->information);
    fflush(stdin);

    printf("Möchtest du diesen Kontakt speichern (j/n)? ");
    scanf("%c", &inputCheck);
    fflush(stdin);

    while (inputCheck != 'j' && inputCheck != 'n')
    {
        printf("Ungültige Eingabe! Möchtest du diesen Kontakt speichern (j/n)? ");
        scanf("%c", &inputCheck);
        fflush(stdin);
    }

    if (inputCheck == 'j')
    {
        // Save data in .csv file using append
        printf("\nKontakt wird gespeichert ...");
        FILE *fptr = fopen("contacts.csv", "a");
        fprintf(fptr, "%s;%s;%s;%s\n", userEntry->firstName, userEntry->lastName, userEntry->number, userEntry->information);
        fclose(fptr);
    }
    else if (inputCheck == 'n')
    {
        printf("\nKontakt wird nicht gespeichert ...");
    }

    menu();
}

// Function to show all entries
void showEntries()
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
        printf("\nDatei exisitiert nicht! Bitte zuerst neue Einträge erstellen.");
    }
    else
    {
        // Read every line of the .csv file
        while (fgets(lineRead, 307, fptr) != NULL)
        {
            printf("%d: %s", counter, lineRead);
            counter++;
        }
    }

    // Close file
    fclose(fptr);

    // After function finishes go back to menu
    menu();
}

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

    // if Error output ERROR 404 (file not found)
    if (file == NULL || temp == NULL)
    {
        printf("\nDatei exisitiert nicht! Bitte zuerst neue Einträge erstellen.");
        menu();
    }

    printf("Bist du dir sicher, dass du Eintrag #%d löschen möchtest (j/n)? ", deleteLine);
    scanf("%c", &inputCheck);
    fflush(stdin);

    while (inputCheck != 'j' && inputCheck != 'n')
    {
        printf("Ungültige Eingabe! Bist du dir sicher, dass du Eintrag #%d löschen möchtest (j/n)? ", deleteLine);
        scanf("%c", &inputCheck);
        fflush(stdin);
    }

    if (inputCheck == 'j')
    {
        printf("Eintrag #%d wird gelöscht ...", deleteLine);

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
    else if (inputCheck == 'n')
    {
        printf("Eintrag #%d wird nicht gelöscht ...", deleteLine);

        fclose(file);
        fclose(temp);

        remove(tempFile);
    }

    // When function finishes go back to menu
    menu();
}

void editEntry(entry *userEntry)
{
    // Create variable for temporary file and contacts file
    // Variable declaration
    char buffer[2048];
    int editLine = 0;
    bool keepGoing = true;
    int currentLine = 1;

    printf("\nEintrag bearbeiten");
    printf("\n-------------------------------------------------------------------------\n\n");

    // enter the line to be edited
    printf("Welche Linie willst du bearbeiten? ");
    scanf("%d", &editLine);
    fflush(stdin);

    // open original file to read and temporary file to write
    FILE *file = fopen("contacts.csv", "r");
    FILE *new = fopen("new.csv", "w");

    // if Error output ERROR 404 (file not found)
    if (file == NULL || new == NULL)
    {
        printf("Datei exisitiert nicht! Bitte zuerst neue Einträge erstellen.");
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
            printf("Du kannst den Eintrag von Linie %d jetzt bearbeiten\n\n", editLine);

            // Get user input, working with scanf() because of the formatting of the .csv file
            printf("Was ist der Vorname von deinem Kontakt? ");
            fflush(stdin);
            scanf("%[^\n]s", &userEntry->firstName);
            fflush(stdin);

            printf("Was ist der Nachname von deinem Kontakt? ");
            scanf("%[^\n]s", &userEntry->lastName);
            fflush(stdin);

            printf("Was lautet die Telefonnummer von deinem Kontakt? ");
            scanf("%[^\n]s", &userEntry->number);
            fflush(stdin);

            printf("Sonstige Informationen? ");
            scanf("%[^\n]s", &userEntry->information);
            fflush(stdin);

            // Save data in .csv file using append
            FILE *fptr = fopen("contacts.csv", "a");
            fprintf(fptr, "%s;%s;%s;%s\n", userEntry->firstName, userEntry->lastName, userEntry->number, userEntry->information);
            fclose(fptr);
        }

        currentLine++;

    } while (keepGoing == true);

    // close all open files
    fclose(file);
    fclose(new);

    // remove original file and rename temporary file to the name of original file
    remove("contacts.csv");
    rename("new.csv", "contacts.csv");

    // When function finishes go back to menu
    menu();
}