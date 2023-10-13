#include <stdio.h>
#include <stdlib.h>

int main(){
    int age = 8; // Initialisation de la variable
    unsigned char garcon = 0; // équivalent d'un booléen initialisé à faux

    if(age<12 && garcon){ // si j'ai moins de 12 ans et que je suis un garçon
        printf("Bonjour Jeune Homme");
    }
    else{
        if(age<12 && !garcon){ // si j'ai moins de 12 ans et que je ne suis pas un garçon.
            printf("Bonjour Mademoiselle");
        }
    }
    return 0;
}