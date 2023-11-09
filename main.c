#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for .csv entries
typedef struct Entry
{
    char firstName[40];
    char lastName[50];
    char number[17];
    char information[200];
} entry;

// Function prototpyes
int menu();
void newEntry(entry *userEntry);
void showEntries();

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
        // Dritte Funktion verlinken
        break;

    case 4:
        // Vierte Funktion verlinken
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

    // Save data in .csv file using append
    FILE *fptr = fopen("contacts.csv", "a");
    fprintf(fptr, "%s;%s;%s;%s\n", userEntry->firstName, userEntry->lastName, userEntry->number, userEntry->information);
    fclose(fptr);

    // After function is finished return to the menu
    menu();
}

// Function to show all entries
void showEntries()
{
    // Variable Declaration
    FILE *fptr;
    char lineRead[307], temp[307];
    int counter = 1;

    printf("\n\nAlle Eintraege anzeigen");
    printf("\n-----------------------------------------\n\n");

    // Check if file exists
    if ((fptr = fopen("contacts.csv", "r")) == NULL)
    {
        // Go back to menu, if it doesn't exist
        printf("Datei exisitiert nicht! Bitte zuerst neue Einträge erstellen.");
        menu();
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

    // After function finishes go back to menu
    menu();
}