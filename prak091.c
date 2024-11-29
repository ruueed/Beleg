#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buf[128];

typedef struct {
char *name;
int day;
int mon;
int year;
char* note;

}tPers;

tPers eingabe(){

tPers person;

printf("Eingabe Gedanktag\n");
printf("Name eingeben:\n");
fgets(buf,128,stdin);
buf[strlen(buf)-1]='\0';
// Hier entferne ich das Absatzzeichen welches nach der eingabe im string einen absatz generieren würde(also bei der ausgabe siehts hässlich aus)
person.name=malloc(strlen(buf)+1);
strcpy(person.name,buf);
printf("Tag eingeben:\n");
person.day=atoi(fgets(buf,128,stdin));
printf("Monat eingeben:\n");
person.mon=atoi(fgets(buf,128,stdin));
printf("Jahr eingeben:\n");
person.year=atoi(fgets(buf,128,stdin));
printf("Notitz eingeben:\n");
fgets(buf,128,stdin);
buf[strlen(buf)-1]='\0';
person.note=malloc(strlen(buf)+1);
strcpy(person.note,buf);

return person;
}

void ausgabe(tPers *p){
    printf("%s,%d,%d,%d,%s\n",
            p->name,
            p->day,
            p->mon,
            p->year,
            p->note);
}

int main(){

char proceed='j';
int count=0;
tPers *pData=NULL;
tPers *tmp;
pData=malloc(sizeof(tPers)*count);

do{
tmp=realloc(pData,sizeof(tPers)*(count+1));
    if(tmp){
        pData=tmp;
        pData[count]=eingabe();
        count++;
}
printf("Weitere Eingabe?(j/n): \n");
fgets(buf,128,stdin);

proceed=buf[0];
}
while(proceed=='j');

for(int i=0; i<count;i++){
    ausgabe(pData+i);
}
free(pData);


    return 0;
}




