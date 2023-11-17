#include <stdio.h>
#include <stdlib.h>

int longueurChaine(char texte[]) {
    int longueur = 0;

    while (texte[longueur] != '\0') {
        longueur++;
    }

    return longueur;
}

int main() {
    
    char nom[100];
    printf("Entrez votre nom : ");
    scanf("%s", nom);

    int longueur = longueurChaine(nom);

    printf("La longueur de la chaine \"%s\" est : %d\n", nom, longueur);

    return 0;
}



/*
 * Filename: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos/exo3.c
 * Path: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos
 * Created Date: Friday, November 17th 2023, 4:26:51 pm
 * Author: gab
 * 
 * Copyright (c) 2023 Gabin L.
 */
