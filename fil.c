#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fil.h"
#include "strukturer.h"

#define MAX_FORDON 10
#define FILNAMN "register.txt"

Fordon registeret[MAX_FORDON];
int antalFordon = 0;

void initialiseraRegister() {
    FILE *fil = fopen(FILNAMN, "r");
    if (fil != NULL) {
        fread(registeret, sizeof(Fordon), MAX_FORDON, fil);
        fclose(fil);
        antalFordon = räknaFordon();
        printf("Register laddat från fil.\n");
    } else {
        printf("Skapar ett nytt register.\n");
    }
}

void laggTillFordon() {
    if (antalFordon < MAX_FORDON) {
        Fordon nyttFordon;

        printf("Ange fordonstyp: ");
        fgets(nyttFordon.fordonstyp, sizeof(nyttFordon.fordonstyp), stdin);
        strtok(nyttFordon.fordonstyp, "\n");

        printf("Ange märke: ");
        fgets(nyttFordon.marke, sizeof(nyttFordon.marke), stdin);
        strtok(nyttFordon.marke, "\n");

        printf("Ange registreringsnummer: ");
        fgets(nyttFordon.registreringsnummer, sizeof(nyttFordon.registreringsnummer), stdin);
        strtok(nyttFordon.registreringsnummer, "\n");

        printf("Ange ägarens namn: ");
        fgets(nyttFordon.agare.namn, sizeof(nyttFordon.agare.namn), stdin);
        strtok(nyttFordon.agare.namn, "\n");

        printf("Ange ägarens ålder: ");
        char ålderInput[5];
        fgets(ålderInput, sizeof(ålderInput), stdin);
        nyttFordon.agare.ålder = atoi(ålderInput);

        nyttFordon.ärOccupied = 1;

        registeret[antalFordon] = nyttFordon;

        printf("Fordonet har lagts till i registret.\n");
        antalFordon++;
    } else {
        printf("Fel: Register är fullt. Kan inte lägga till fler fordon.\n");
    }
}

void taBortFordon() {
    int position;
    printf("Ange positionen för fordonet att ta bort (1-%d): ", antalFordon);
    scanf("%d", &position);

    if (position >= 1 && position <= antalFordon) {
        for (int i = position - 1; i < antalFordon - 1; i++) {
            registeret[i] = registeret[i + 1];
        }

        antalFordon--;
        printf("Fordonet har tagits bort från registret.\n");
    } else {
        printf("Fel: Ogiltig position. Ange en giltig position.\n");
    }
}

void sorteraRegister() {
    // Enkel sortering med bubble sort efter fordonets märke
    for (int i = 0; i < antalFordon - 1; i++) {
        for (int j = 0; j < antalFordon - i - 1; j++) {
            if (strcmp(registeret[j].marke, registeret[j + 1].marke) > 0) {
                // Byt plats på fordon
                Fordon temp = registeret[j];
                registeret[j] = registeret[j + 1];
                registeret[j + 1] = temp;
            }
        }
    }

    printf("Registret sorterat efter fordonets märke.\n");
}

void visaFordon() {
    int position;
    printf("Ange positionen för fordonet att visa (1-%d): ", antalFordon);
    scanf("%d", &position);

    if (position >= 1 && position <= antalFordon) {
        Fordon fordon = registeret[position - 1];

        printf("Fordonets information:\n");
        printf("Typ: %s\n", fordon.fordonstyp);
        printf("Märke: %s\n", fordon.marke);
        printf("Registreringsnummer: %s\n", fordon.registreringsnummer);
        printf("Ägarens namn: %s\n", fordon.agare.namn);
        printf("Ägarens ålder: %d\n", fordon.agare.ålder);
    } else {
        printf("Fel: Ogiltig position. Ange en giltig position.\n");
    }
}

void visaRegister() {
    printf("Fordonsregister:\n");
    printf("%-20s %-20s %-20s\n", "Fordonstyp", "Märke", "Registreringsnummer");

    for (int i = 0; i < antalFordon; i++) {
        printf("%-20s %-20s %-20s\n", registeret[i].fordonstyp, registeret[i].marke, registeret[i].registreringsnummer);
    }
}

void sparaRegisterTillFil() {
    FILE *fil = fopen(FILNAMN, "w");
    if (fil != NULL) {
        fwrite(registeret, sizeof(Fordon), antalFordon, fil);
        fclose(fil);
        printf("Registret har sparats till fil.\n");
    } else {
        printf("Fel vid sparande av registret till fil.\n");
    }
}

int räknaFordon() {
    int count = 0;
    for (int i = 0; i < MAX_FORDON; i++) {
        if (registeret[i].ärOccupied) {
            count++;
        }
    }
    return count;
}
