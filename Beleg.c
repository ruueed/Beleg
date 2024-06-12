
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 30
char buf[128];

typedef struct datum{
    int tag;
    int monat;
    int jahr;
}datum;

typedef struct node{
    char artname[50];
    int artnr;
    int anzahl;
    datum date;
    struct node* next;
}node;

node *next=NULL;
node *anfang=NULL;


void anhaengen(char *nam,int nr, int anz, int ct, int cm, int cj,char *datname){

    node* zeiger;
    if (anfang==NULL){
        if((anfang=malloc(sizeof(node)))==NULL)
        {
            fprintf(stderr,"Kein Speicherplatz fuer anfang vorhanden\n");
            return ;
        }
        strcpy(anfang->artname,nam);
        anfang->artnr=nr;
        anfang->anzahl=anz;
        anfang->date.tag=ct;
        anfang->date.monat=cm;
        anfang->date.jahr=cj;
        anfang->next=NULL;
// Schreiben in Datei
        FILE * file=fopen(datname,"a+");
        if (file == NULL){
            fprintf(stderr,"Fehler beim öffnen\n");
            exit(EXIT_FAILURE);
        }
        fprintf(file,"%s,%d,%d,%02d,%02d,%d",anfang->artname, anfang->artnr, anfang->anzahl, anfang->date.tag, anfang->date.monat, anfang->date.jahr);
        fclose(file);
    }
    else{
        zeiger = anfang;
         while (zeiger->next != NULL)
            zeiger=zeiger->next;
        if((zeiger->next=malloc(sizeof(node)))==NULL){
            fprintf(stderr,"Kein Speicherplatz fuer das letzte Element vorhanden\n");
            return;
        }
        zeiger=zeiger->next;
        strcpy(zeiger->artname,nam);
        zeiger->artnr=nr;
        zeiger->anzahl=anz;
        zeiger->date.tag=ct;
        zeiger->date.monat=cm;
        zeiger->date.jahr=cj;
        zeiger->next=NULL;
// Schreiben in Datei
        FILE * file=fopen(datname,"a+");
        if (file == NULL){
            fprintf(stderr,"Fehler beim öffnen\n");
            exit(EXIT_FAILURE);
        }
        fprintf(file,"%s,%d,%d,%02d,%02d,%d\n",zeiger->artname, zeiger->artnr, zeiger->anzahl, zeiger->date.tag, zeiger->date.monat, zeiger->date.jahr);
        fclose(file);
    }
}

void eingabe(char *dtnm){
    char nam[MAX];
    int nr,az,ct,cm,cj;
    printf("Eingabe Artikelname:\n");
    fgets(nam,MAX,stdin);
    printf("Eingabe Artikelnummer\n");
    fgets(buf,128,stdin);
    nr=atoi(buf);
    printf("Eingabe Anzahl\n");
    fgets(buf,128,stdin);
    az=atoi(buf);
    printf("Eingabe Datum(TT/MM/JJJJ einzeln):\n");
    fgets(buf,128,stdin);
    ct=atoi(buf);
    fgets(buf,128,stdin);
    cm=atoi(buf);
    fgets(buf,128,stdin);
    cj=atoi(buf);

    anhaengen(nam,nr,az,ct,cm,cj,dtnm);
}

void ausgabe(){
    node*zeiger=anfang;
    while(zeiger!=NULL){
        printf("%s %d %d %02d %02d %d\n",zeiger->artname, zeiger->artnr, zeiger->anzahl, zeiger->date.tag, zeiger->date.monat, zeiger->date.jahr);
        zeiger=zeiger->next;
    }
}

void bearbeiten(char *datname){
    node*zeiger=anfang;
    printf("Artikelnummer des zu bearbeitenden Materials eingeben:\n");
    fgets(buf,128,stdin);
    int nummer=atoi(buf);
    printf("Materialnamen des zu bearbeitenden Materials eingeben:\n");
    char name[30];
    fgets(name,30,stdin);
    

//  Schleife bis Materialnummer gefunden wurde
    while(1){
        if(nummer==zeiger->artnr&& strcmp(name,zeiger->artname)==0){
            int anzneu;
            int anzvorher=zeiger->anzahl;
            printf("Mit der Materialnummer uebereinstimmendes Material:%s\n",zeiger->artname);
            printf("Bitte geben Sie die Aenderungen ein:(neue Anzahl d Artikels / Aenderungsdatum)\n");
            fgets(buf,128,stdin);
            zeiger->anzahl=atoi(buf);
            anzneu=atoi(buf);
            fgets(buf,128,stdin);
            zeiger->date.tag=atoi(buf);
            fgets(buf,128,stdin);
            zeiger->date.monat=atoi(buf);
            fgets(buf,128,stdin);
            zeiger->date.jahr=atoi(buf);
//Schreiben in Datei
            FILE * file=fopen(datname,"a+");
            if (file == NULL){
            fprintf(stderr,"Fehler beim öffnen\n");
            exit(EXIT_FAILURE);
            }
            fprintf(file,"%s,%d,%d,%02d,%02d,%d\n",zeiger->artname, zeiger->artnr,anzneu-anzvorher, zeiger->date.tag, zeiger->date.monat,
            zeiger->date.jahr);
            fclose(file);
            break;
        }
        // Fehlermeldung falls Materialnummer nicht existiert
        else if(zeiger->next==NULL){
            fprintf(stderr,"Kein Artikel mit passender Artikelnummer gefunden!\n");
            break;
        }
        else
        zeiger=zeiger->next;
    }
}

int main(){
int auswahl=0;

printf("------Materialverwaltung-----------------------------------------------------------\n"
       "moechten Sie eine neue Textdatei zum speichern der erfassten Daten erstellen?\n"
       "(nur nötig wenn Sie an diesem Tag noch keinen Verlauf haben) (j/n)\n"
       "-----------------------------------------------------------------------------------\n");
//      Variablen zur Erstellung oder verwendung eines Dateinamen
        char datname[50];
        time_t rawtime;
        struct tm *timeinfo;
        fgets(buf,128,stdin);

        if(buf[0]=='n'){
            printf("In welcher Datei möchten Sie die Daten speichern? (Bitte geben Sie den genauen namen an)\n");
            fgets(buf,128,stdin);
            strcpy(datname,buf);
            for(int i=0;i<sizeof(datname);i++){
                if(datname[i]=='\n'){
                    datname[i]='\0';
                }
            }
        }
        else if(buf[0]=='j'){
            time(&rawtime);
            timeinfo=localtime(&rawtime);
            strftime(datname, sizeof(datname), "verlauf_%Y%m%d.txt", timeinfo);
        }
        else fprintf(stderr,"Falsche wahl, bitte wählen Sie zwischen j oder n!\n");

    do{

        printf("------Materialverwaltung------\n"
               "1. Artikel hinzufügen\n2. Artikel anzeigen\n3. Lagerbestand bearbeiten\n4. Beenden\n"
               "----------------------------------------------------------------------------------\n");
        fgets(buf,128,stdin);
        auswahl=atoi(buf);

            switch(auswahl){
                case 1: eingabe(datname);
                        break;
                case 2: ausgabe();
                        break;
                case 3: bearbeiten(datname);
                        break;
                case 4: break;
                default: printf("falsche Eingabe!\n");
            }
        }while(auswahl!=4);

    return EXIT_SUCCESS;
}
