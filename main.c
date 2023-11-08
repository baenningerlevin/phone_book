#include <stdio.h>
#include <stdlib.h>

int menu();

int main()
{
    menu();

    return 0;
}

int menu()
{
    int choice;

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
        // Erste Funktion verlinken
        break;

    case 2:
        // Zweite Funktion verlinken
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
        printf("Programm schliessen ...\n");
        return EXIT_SUCCESS;
        break;
    }
}
