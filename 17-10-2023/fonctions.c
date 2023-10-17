#include <stdio.h> 
#include <stdlib.h>

int cube(int valeur){
    return valeur*valeur*valeur;
}

int puissance(int valeur, int exposant){
    int i, total = 1;
    for(i=1; i<=exposant; i++){
        total *= valeur;
    }
    return total;
}


int main(){
    int i;
    for (i = 1; i <= 10; i++){
        printf("La valeur de %d³ est %d\n", i, cube(i));
    }
    i = 0;

    printf("############## PUISSANCE ##################\n");
    printf("Puissance de 2⁸: %d\n", puissance(2,8)); // faire boucle pour en afficher plusieurs..
    return 0;
}