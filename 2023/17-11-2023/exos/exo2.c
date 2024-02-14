#include <stdio.h>
#include <stdlib.h>

int estImpair(int nb) {
    return nb % 2 != 0;
}

int main(){
    int nombre;

    printf("Entrez un nombre entier : ");
    scanf("%d", &nombre);

    if (estImpair(nombre)) {
        printf("%d est impair.\n", nombre);
    }else {
        printf("%d n'est pas impair.\n", nombre);
    }
    return 0;
}

/*
 * Filename: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos/exo2.c
 * Path: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos
 * Created Date: Friday, November 17th 2023, 4:19:34 pm
 * Author: gab
 * 
 * Copyright (c) 2023 Gabin L.
 */

