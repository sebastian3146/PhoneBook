//---------------------------------------------------------------------------
/*
Entwickler: Sebastian M.
Datum: 21.02.2023
Name: Adressbuch
Beschreibung: Ein simples Adressbuch mit Benutzteroberflaeche
Version: 1.1
*/
//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/console.h"

#define LEN 100
#define MAXENTRY 14
#define ROWS 7

struct person {
    char name[LEN];
    char telNr[LEN];
}personData[MAXENTRY];

void showMenu(void);
// what4: present a simple menu
// In: -
// Pre: -
// Post: the menu is presented
// Return: -

void showNames(int index);
// what4: present the names
// In: -
// Pre: -
// Post: the names are presented
// Return: -

void enterNames(void);
// what4: to enter a new name
// In: -
// Pre: -
// Post: the new name is stored
// Return: -

void deleteNames(int index);
// what4: to delete all names
// In: -
// Pre: -
// Post: all names and numbers are deleted
// Return: -

void deleteParticularNames(int index);
// what4: to delete particular names
// In: int index
// Pre: -
// Post: one name and number are deleted
// Return: -

void storeNewNameAndNumber(char * newName, char * newNumber, int index);
// what4: to store a new Name and a new tle Number in the array
// In: newName and newNumber, and the index
// Pre: index must be lower than N !!!
// Post: the new name and the new number is stored in the arry on position index
// Return: -

void generateNamesAndNumbers(int number, int index);
// what4: auto generate new Names and Numbers 
// In: number, index
// Pre: number must be lower than i (14)
// Post: -
// Return: -

void showManual(void);
// what4: Show the manual
// In: -
// Pre: -
// Post: -
// Return: -

int main() {

    initConsole();
    int i = 0;  // how many names are already stored!
    unsigned int key;
    int entry;
    char newName[LEN];
    char newTelNumber[LEN];
    char confirmation;
    int check;
    char ckey[LEN];


    // first name and Tel-Nummern:
    i = 1;
    sprintf(personData[i].name,"Michael");
    sprintf(personData[i].telNr,"065098989898");
    i = 2;
    sprintf(personData[i].name,"Brigitte");
    sprintf(personData[i].telNr,"065097979797");

    do {
        do {
            showMenu();
            key = getch();

            switch(key) { 

            case '1':
                showNames(i);
                getch();
                break;

            case '2':
                clrscr();
                if (i >= MAXENTRY) {
                        gotoxy(10,10); printf("Speicher ist voll!");
                        gotoxy(10, 12); printf("press any key to jump back");
                        getch();
                        break;
                    }
                while(1) {
                    closeConsole();
                    enterNames();

                    fflush(stdin);
                    gotoxy(10, 4); printf("Name(max. 15 Zeichen): "); scanf("%s", newName);  // newNames ist die Startadresse des Arrays!
                    if(*newName == '<') break;
                    
                    fflush(stdin);
                    gotoxy(10, 6); printf("TelNr(max. 15 Zeichen): "); scanf("%s", newTelNumber);
                    
                    
                    if(strlen(newName) <= 15 && strlen(newTelNumber) <= 15) break;
                    else {
                        initConsole();
                        gotoxy(10, 8); printf("Es dürfen maximal nur 15 Zeichen eingegeben werden!");
                        getch();
                        clrscr();
                    }
                }
                initConsole();
                if(*newName == '<') break;
                i++; // Index fuer die neue Person vorbereiten!
                storeNewNameAndNumber(newName, newTelNumber, i);

                gotoxy(10,8);printf("danke!");
                break;

            case '3':
                deleteNames(i);
                clrscr();
                gotoxy(20, 10); printf("Alle Nummer und Namen wurden gelöscht");
                gotoxy(10, 12); printf("press any key to jump back!");
                key = getch();
                break;

            case '4':
                clrscr();              
                while (1) {
                    strcpy(ckey, "");
                    key = 0;
                    check = 1;
                    closeConsole();
                    clrscr();
                    gotoxy(10, 2); printf("Einen Eintrag löschen");
                    gotoxy(10, 12); printf("press < and enter to jump back!");
                    gotoxy(10, 4); printf("Zeile: ");
                    
                    scanf("%s", ckey);
                    
                    if(*ckey == '<') break;
                    key = atoi(ckey);
                                 

                    for (int j = 0; j < strlen(ckey); j++) {
                      
                        if ((ckey[j] < '0' || ckey[j] > '9')) check = 0;
                    }
                    if(check == 1 && i >= key)  break;
                    initConsole();
                    if (i <= key && check == 1) {
                        clrscr();
                        gotoxy(10, 8); printf("Auf dieser Zeile ist kein Name gespeichert");
                        gotoxy(10, 12); printf("press any key to jump back!");
                        getch();
                    }else if(check == 0) {
                        clrscr();
                        gotoxy(10, 8); printf("Bitte Ganzzahlen eingeben!");
                        gotoxy(10, 12); printf("press any key to jump back!");
                        getch();
                    }
                }
                initConsole();

                if(*ckey == '<') break;
                deleteParticularNames(key);
                for (int j = 0; j <= i; j++) {
                    sprintf(personData[key + j].name, "%s", personData[key + j + 1].name);
                    sprintf(personData[key + j].telNr, "%s", personData[key + j + 1].telNr);
                }
                i--;
   
                break;
            case '5':
                clrscr();
                gotoxy(10, 2); printf("Einen Schritt zurück");
                gotoxy(10, 12); printf("press any key to jump back!");
                gotoxy(10, 4); printf("Noch nicht verfügbar :(");
                getch();
                break;

            case '6':
                while (1) {
                    strcpy(ckey, "");
                    key = 0;
                    check = 0;
                    closeConsole();
                    clrscr();
                    gotoxy(10, 2); printf("Namen und Nummern generieren");
                    gotoxy(10, 12); printf("press < and enter to jump back!");
                    gotoxy(10, 6); printf("Es sind %d Einträge gespeichert", i);
                    gotoxy(10, 4); printf("Anzahl zum generieren:");
                    
                    scanf("%s", ckey);
                    initConsole();

                    if(*ckey == '<') break;
                    key = atoi(ckey);

                    for (int j = 0; j < strlen(ckey); j++) {
                        if ((ckey[j] < '0' || ckey[j] > '9')) check = 1;
                    }

                    
                    if(check == 1) {
                        clrscr();
                        gotoxy(10, 8); printf("Bitte Ganzzahlen eingeben!");
                        gotoxy(10, 12); printf("press any key to jump back!");
                        getch();
                    }else if(i + key > MAXENTRY) {
                        clrscr();
                        gotoxy(10, 8); printf("Es können nur max. 14 Einträge gespeichert werden!");
                        gotoxy(10, 12); printf("press any key to jump back!");
                        getch();
                    }else break;
                    
                }
                if(*ckey == '<') break;
                generateNamesAndNumbers(key, i);
                i += key;
                break;

            case '7':
                clrscr();
                showManual();
                getch();
                break;
            }
        } while (key != ESC);

        clrscr();
        gotoxy(20, 5);printf("ACHTUNG!");
        gotoxy(15, 7);printf("Beim Beenden dieses Programmes gehen alle Daten verloren");
        gotoxy(5,12);printf("Fortfahren? (yes(y)/no(alles andere)):"); confirmation = getch();

    }while (confirmation != 'y');

    clrscr();
    closeConsole();
    return 0;
}

void showMenu(void) {

    clrscr();
    gotoxy(10,2); printf("Menue");
    gotoxy(10, 4); printf("(1) Anzeigen aller Namen und Nummern");
    gotoxy(10, 5); printf("(2) neuen Namen speichern");
    gotoxy(10, 6); printf("(3) Alle loeschen");
    gotoxy(10, 7); printf("(4) Bestimmten Eintrag loeschen");
    gotoxy(10, 8); printf("(5) Einen Schritt rueckgaengig machen");
    gotoxy(10, 9); printf("(6) Namen und Nummern automatisch generieren");
    gotoxy(10, 10); printf("(7) Benutzter Hilfe");

    gotoxy(10, 12); printf("ESC: Beenden!");
}

void showNames(int index) {
    clrscr();
    gotoxy(10,2); printf("Namen:");
    int count = 0;
    for(int j = 1; j <= index; j++) {
        gotoxy(10, 3 + j); printf("%d. %s", j, personData[j].name);
        gotoxy(30, 3 + j); printf("%s", personData[j].telNr);
            if(j >= ROWS) {
            j++;
            for (; j <= index; j++) {
                count++;
                gotoxy(50, 3 + count); printf("%d. %s", j , personData[j].name);
                gotoxy(70, 3 + count); printf("%s", personData[j].telNr);
                
            }
        }
    }
        gotoxy(10, 12); printf("press any key to jump back!");
}

void enterNames(void) {
    clrscr();

    gotoxy(10,2); printf("neuen Namen und Nummer eingeben");
    gotoxy(10, 12); printf("press < and enter to jump back");
    gotoxy(10,4);
}

void storeNewNameAndNumber(char * newName, char * newNumber, int index) {

    if (index < MAXENTRY) {
        sprintf(personData[index].name,"%s",newName);
        sprintf(personData[index].telNr, "%s", newNumber);
    }

}

void deleteNames(int index) {
    for(int j = 0; j < MAXENTRY; j++) {
        sprintf(personData[j].name, "%s", "");
        sprintf(personData[j].telNr, "%s", "");
    }
    index = 0;
}

void deleteParticularNames(int index) {
    sprintf(personData[index].name, "%s", "");
    sprintf(personData[index].telNr, "%s", "");
}

void generateNamesAndNumbers(int numbers, int index) { //rand(); Random Names with array of strings
    for (int j = 1; numbers >= j; j++) {
        sprintf(personData[index + j].name, "%s", "xxxxxxxxxxxxxx");
        sprintf(personData[index + j].telNr, "%s", "1111111111111");
        
    }
}

void showManual() {
    clrscr();
    gotoxy(10, 2); printf("Benutzter Hilfe");
    gotoxy(10, 12); printf("press any key to jump back!");

    gotoxy(10, 4); printf("- Ein einfaches Adressbuch, womit man Namen und Telefonnummer speichern kann\n    - Maximal koennen 14 Einträge gespeichert werden. Beim Verlassen des Programmes wird alles geloescht\n\
    - Es werden nur die Tasten benoetigt zum steuern dieses Programmes\n\
    - Welche Taste was macht steht dabei\n\
    - Bei (2), (4) und (6) muss man die Taste < und enter druecken um ins Menue zurueck zu kommen, \n      bei den anderen Funktionen nicht\n \
    (Wegen der Eingabe funktioniert die einfachere Methode nicht)\n");
}
