#include <stdio.h>
#include <stdlib.h>

typedef struct Entry
{
    char firstName[40];
    char lastName[50];
    char number[17];
    char information[200];
} entry;

int menu();
void newEntry(entry *userEntry);

int main()
{
    menu();

    return 0;
}

int menu()
{
    int choice;
    entry userEntry;

    printf("\n\n+----------------------------+\n");
    printf("| -1- Alle Einträge anzeigen |\n");
    printf("| -2- Neuer Eintrag          |\n");
    printf("| -3- Eintrag bearbeiten     |\n");
    printf("| -4- Eintrag löschen        |\n");
    printf("| -5- Eintrag suchen         |\n");
    printf("| -6- Programm verlassen     |\n");
    printf("+----------------------------+\n\n");

    printf("Bitte treffen Sie eine Auswahl: ");
    while (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Falsches Format. Bitte geben Sie eine der oberen Zahlen ein: ");
    }

    // Falsche Eingaben die nicht im Bereich sind abfangen
    while (choice > 6 || choice < 1)
    {
        printf("Bitte geben Sie eine gültige Zahl ein: ");
        scanf("%d", &choice);
        fflush(stdin);
    }

    switch (choice)
    {
    case 1:
        
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
        return EXIT_SUCCESS;
        break;
    }
}

void newEntry(entry *userEntry)
{
    printf("\n\nNeuer Eintrag (Fuer Umlaute: ae, ue, oe!)");
    printf("\n----------------------------------------------------------\n\n");

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

    FILE *fptr = fopen("contacts.csv", "a");
    fprintf(fptr, "%s;%s;%s;%s\n", userEntry->firstName, userEntry->lastName, userEntry->number, userEntry->information);
}