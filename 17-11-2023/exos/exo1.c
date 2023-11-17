#include <stdio.h>
#include <stdlib.h>

float calculPrixTTC(float prixHT) {
    float prixTTC = prixHT * 1.20;
    return prixTTC;
}

int main() {
    float prixHT, prixTTC;
    printf("Entrez le prix HT : ");
    scanf("%f", &prixHT);
    prixTTC = calculPrixTTC(prixHT);
    printf("Le prix TTC est : %.2f\n", prixTTC);

    return 0;
}

/*
 * Filename: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos/exo1.c
 * Path: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos
 * Created Date: Friday, November 17th 2023, 4:15:38 pm
 * Author: gab
 * 
 * Copyright (c) 2023 Gabin L.
 */
