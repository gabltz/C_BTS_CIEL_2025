#include <stdio.h>
#include <stdlib.h>



void inverserMot(char mot[]) {
    int longueur = strlen(mot);
    for (int i = 0, j = longueur - 1; i < j; i++, j--) {

        char temp = mot[i];
        mot[i] = mot[j];
        mot[j] = temp;
    }
}

int main() {
    char mot[100];  

    printf("Entrez un mot : ");
    scanf("%s", mot);

    inverserMot(mot);

    printf("Mot inversé : %s\n", mot);

    return 0;
}

/*
 * Filename: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos/exo4.c
 * Path: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos
 * Created Date: Friday, November 17th 2023, 4:32:15 pm
 * Author: gab
 * 
 * Copyright (c) 2023 Gabin L.
 */
