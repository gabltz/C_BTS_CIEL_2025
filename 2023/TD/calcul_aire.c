#include <stdio.h>
#include <stdlib.h>

// Calculer l'aire d'un rectangle avec longueur et largeur en entrée


int main(){
    int longueur = 0;
    int largeur = 0;
    int aire = 0;
    printf("Entrer la largeur : ");
    scanf("%d",&largeur);
    printf("\nEntrer la longueur : ");
    scanf("%d",&longueur);
    aire = longueur * largeur;
    printf("L'aire de ce rectangle est de : %d\n", aire);
}