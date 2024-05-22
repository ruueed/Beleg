//Rudi Freudenberg 55201
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 30

char buf[128];


typedef struct datum{
    int jahr;
    int monat;
    int tag;
}datum;

typedef struct angestellt{
    char name[20];
    char vorname[20];
    datum alter;
    datum eingestellt;
    long gehalt;
    struct angestellt *next;
}angestellt;

angestellt *next=NULL;
angestellt *anfang=NULL;

void anhaengen(char *n,char *v, int at, int am, int aj,
               int et, int em, int ej,long g)
{
    angestellt *zeiger;
    if (anfang==NULL){
        if((anfang=malloc(sizeof(angestellt)))==NULL)
        {
            fprintf(stderr,"Kein Speicherplatz fuer anfang vorhanden\n");
            return ;
        }
        strcpy(anfang->name,n);
        strcpy(anfang->vorname,v);
        anfang->alter.tag=at;
        anfang->alter.monat=am;
        anfang->alter.jahr=aj;
        anfang->eingestellt.tag=et;
        anfang->eingestellt.monat=em;
        anfang->eingestellt.jahr=ej;
        anfang->next=NULL;
    }
    else{
        zeiger=anfang;
        while (zeiger->next != NULL)
            zeiger=zeiger->next;
        if((zeiger->next=malloc(sizeof(angestellt)))==NULL){
            fprintf(stderr,"Kein SPeicherplatz fuer das letzte Element vorhanden\n");
            return;
        }
        zeiger=zeiger->next;
        strcpy(zeiger->name,n);
        strcpy(zeiger->vorname,v);
        zeiger->alter.tag=at;
        zeiger->alter.monat=am;
        zeiger->alter.jahr=aj;
        zeiger->eingestellt.tag=et;
        zeiger->eingestellt.monat=em;
        zeiger->eingestellt.jahr=ej;
        zeiger->gehalt=g;
        zeiger->next=NULL;

    }
}

// Dateneingabe

void eingabe(void){
    char nam[MAX],vorn[MAX];
    int atag,amon,ajahr,etag,emon,ejahr;
    long gehalt;

    printf("Name.........................\n");
    fgets(nam,MAX,stdin);
    printf("Vorname......................\n");
    fgets(vorn,MAX,stdin);
    printf("Alter............(tt.mm.jjjj)\n");
    fgets(buf,128,stdin);
    atag=atoi(buf);
    fgets(buf,128,stdin);
    amon=atoi(buf);
    fgets(buf,128,stdin);
    ajahr=atoi(buf);
    printf("Einstellungsdatum(tt.mm.jjjj)\n");
    fgets(buf,128,stdin);
    atag=atoi(buf);
    fgets(buf,128,stdin);
    amon=atoi(buf);
    fgets(buf,128,stdin);
    ajahr=atoi(buf);
    printf("Monatsgehalt.................\n");
    fgets(buf,128,stdin);
    gehalt=atol(buf);

    anhaengen(nam,vorn,atag,amon,ajahr,etag,emon,ejahr,gehalt);

}

// Funktion zum löschen des ersten Datensatzes

void loesche(char *wen){
    angestellt *zeiger,*zeiger1;
    if (anfang !=NULL){
        if(strcmp(anfang->name,wen)==0){
            zeiger=anfang->next;
            free (anfang);
            anfang =zeiger;
        }
        else{
            zeiger=anfang;
            while(zeiger->next != NULL){
                zeiger1=zeiger->next;
                if(strcmp(zeiger1->name,wen)==0){
                    zeiger->next=zeiger1->next;
                    free (zeiger1);
                    break;
                }
                zeiger=zeiger1;
            }
        }
    }
    else
        printf("Es sind keine Daten zum löschen vorhanden!!\n\n\n");
}

void ausgabe(void){
    angestellt*zeiger =anfang;
    printf("--------------------------------------\n");
    while (zeiger != NULL){
        printf("|%s %s| %02d.%02d.%04d|"
        "%02d.%02d.%04d|%06ld|\n",
        zeiger->name, zeiger->vorname, zeiger->alter.tag, zeiger->alter.monat, zeiger->alter.jahr,
        zeiger->eingestellt.tag, zeiger->eingestellt.monat, zeiger->eingestellt.jahr, zeiger->gehalt);
        printf("--------------------------------------\n");
        zeiger=zeiger->next;
    }
}

int main(){
    int wahl;
    char dname[MAX];
    do{
        printf("1 = Eingabe\n");
        printf("2 = Ausgabe\n");
        printf("3 = Name loeschen\n");
        printf("9 = Ende\n");
        printf("Bitte wählen sie: \n");
        fgets(buf,128,stdin);
        wahl = atoi(buf);

        switch(wahl){
            case 1 : eingabe();
                     break;
            case 2 : ausgabe();
                     break;
            case 3 : printf("Name zum loeschen:\n");
                     fgets(dname,MAX,stdin);
                     loesche(strtok(dname, "\n"));
                     break;
            case 9 : break;
            default: printf("falsche Eingabe!!!\n");
        }

    }while(wahl!=9);
    return EXIT_SUCCESS;
}
