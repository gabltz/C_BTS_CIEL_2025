#include <stdio.h>
#include <stdlib.h>

int main(){
    int age =8; // Initialisation de la variable age à 8.
    int *ptrAge = &age;

    printf("adresse de la variable age %ld et du pointeur %p\n", &age, ptrAge);

    printf("valeur de la variable age %d et du pointeur %d\n", age, *ptrAge);

    return 0;
}