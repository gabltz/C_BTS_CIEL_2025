#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compterOccurrences(char *chaine, char caractere) {
    int occurrences = 0;

    while (*chaine) {
        if (*chaine == caractere) {
            occurrences++;
        }
        chaine++;
    }

    printf("Le caractère '%c' apparaît %d fois dans la chaîne.\n", caractere, occurrences);
}

int main() {
    char Chaine1[100]; 
    char caractere;

    printf("Entrez une phrase : ");
    fgets(Chaine1, sizeof(Chaine1), stdin);

    if (Chaine1[strlen(Chaine1) - 1] == '\n') {
        Chaine1[strlen(Chaine1) - 1] = '\0';
    }

    printf("Entrez le caractère à rechercher : ");
    scanf(" %c", &caractere);

    compterOccurrences(Chaine1, caractere);

    return 0;
}

/*
 * Filename: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos/exo6.c
 * Path: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos
 * Created Date: Monday, November 20th 2023, 8:50:43 am
 * Author: gab
 * 
 * Copyright (c) 2023 Gabin L.
 */
