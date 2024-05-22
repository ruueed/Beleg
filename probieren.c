//Struktur Ein und Ausgabe mittels Switch Case

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

char buf[128];

struct datum{
    int Jahr;
    int Monat;
    int Tag;
};

struct angestellt{
    char name[20];
    char vorname[20];
    struct datum alter;
    struct datum eingestellt;
    int gehalt;
    struct angestellt *next;
}angestellt;

//Ausgabefunktion
void ausgabe(struct angestellt* l){
    printf("%s%s%d\n",l->name,l->vorname,l->gehalt);
}

char buf[128];

int main(){

    // struct angestellt *eingabe;
    //
    // printf("Name eingeben:\n");
    // fgets(buf,128,stdin);
    // strcpy(eingabe->name, buf);
    // printf("Vorname eingeben:\n");
    // fgets(buf,128,stdin);
    // strcpy(eingabe->vorname, buf);
    // printf("Gehalt eingeben:\n");
    // fgets(buf,128,stdin);
    // eingabe->gehalt=atoi(buf);
    //
    // //Ausgabefunktion
    // ausgabe(eingabe);
    //
    //
    // printf("Zahl von 1-6 eingeben\n1=Nachname\n2=Vorname\n3=Alter\n4=Einstellungsdatum\n5=Gehalt\n6=Alles\n7=Beenden\n");
    // fgets(buf,128,stdin);
    // int zahl=atoi(buf);
    // //Fallunterscheidung
    // switch(zahl){
    //     case 1:printf("%s\n",eingabe->name);break;
    //     case 2:printf("%s\n",eingabe->vorname);break;
    //     case 5:printf("%d\n",eingabe->gehalt);break;
    //     case 6:ausgabe(eingabe);break;
    //     case 7:break;
    // }

    // char string[]=" Rudi ";
    // printf("%s\n",string);

    time_t rawtime;
    struct tm *timeinfo;
    char datname[50];

    time(&rawtime);
    timeinfo=localtime(&rawtime);
    strftime(datname, sizeof(datname), "verlauf_%Y%m%d.txt", timeinfo);

    FILE * file=fopen(datname,"a+");
    if (file == NULL){
        printf("Fehler beim öffnen\n");
        return 1;
    }
    printf("Eingabe einer Zahl:\n");
    fgets(buf,128,stdin);
    int x=atoi(buf);

    fprintf(file,"%d",x);

    printf("Eingabe Eines Strings:\n");
    fgets(buf,128,stdin);
    char *txt=buf;
    fprintf(file,"%s",txt);
    fclose(file);


    return 0;
}


