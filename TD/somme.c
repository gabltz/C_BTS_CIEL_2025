#include <stdio.h>
#include <stdlib.h>
/* Ecrire un algorithme qui calcule et affiche la somme de trois nombres entrés au clavier :
        - en utilisant 5 variables 
        - en utilisant 2 variables.
*/

int main(){
    /*
    En utilisant 5 variables : 

    int nombre1 = 0;
    int nombre2 = 0;
    int nombre3 = 0;
    int somme = 0;
    int resultat = 0;
    printf("Nombre 1 : ");
    scanf("%d", &nombre1);
    printf("Nombre 2 : ");
    scanf("%d", &nombre2);
    printf("Nombre 3 : ");
    scanf("%d", &nombre3);
    somme = nombre1 + nombre2 + nombre3;
    resultat = somme;
    printf("La somme de ces trois nombres est : %d\n", resultat); */

    // En utilisant deux variables : 

    int somme = 0;
    int nbEntre = 0;
    printf("Nombre 1 : ");
    scanf("%d", &nbEntre);
    somme = nbEntre;
    nbEntre = 0;
    printf("Nombre 2 : ");
    scanf("%d", &nbEntre);
    somme = somme + nbEntre;
    nbEntre = 0;
    printf("Nombre 3 : ");
    scanf("%d", &nbEntre);
    somme = somme + nbEntre;
    nbEntre = 0;
    printf("La somme de ces trois nombres est : %d\n", somme); 
    return 0;
}