#include <stdio.h>
#include <stdlib.h>

char buf[128];

char* crtBitStr(unsigned int x){

    int mask=1,count=0;
    char *bitmuster = (char*) malloc(sizeof(x)*8+1); 
    // Malloc gibt einen Pointer zurück(der wird dann der char variable bitmuster
    //  zugeordne)  und der pointer muss vom ja vom typ char sein deshalb 
    // das (char*) davor
    // 
        if(bitmuster==NULL){
            printf("Es konnte kein Speicher ueber malloc freigemacht werden!\n");
            return;
        } 
    // Wenn bitmuster einen NULLPtr erhalten hat ist etwas schief gelaufen
    // return verlässt die aktuelle funktion, also die crtBitStr funktion
    for(count=0;count<=sizeof(x)*8;count++){
        if(x&mask) bitmuster[sizeof(x)*8-1]
        {
            
        }

    }
            
    return bitmuster;
}

int main(){
    unsigned int eingabe;

    printf("Eingabe  einer int Zahl:\n");
    eingabe = atoi(fgets(buf,128,stdin));

    crtBitStr(eingabe);



    return 0;
}





// Das ist fuer die ausgabe später
printf("***"
           "dez: %d"
           "hex: %X",x,x);