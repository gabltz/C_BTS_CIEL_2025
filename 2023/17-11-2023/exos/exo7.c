 

int chercherValeur(int valeur, int tableau[], int taille) {
    for (int i = 0; i < taille; ++i) {
        if (tableau[i] == valeur) {
            return i;
        }
    }
    return -1;
}

int main() {
    int tableau[] = {10, 5, 8, 12, 3};
    int taille = sizeof(tableau) / sizeof(tableau[0]);
    int valeur;

    printf("Entrez la valeur à rechercher : ");
    scanf("%d", &valeur);

    int position = chercherValeur(valeur, tableau, taille);

    if (position != -1) {
        printf("La valeur %d est présente à la position %d dans le tableau.\n", valeur, position);
    } else {
        printf("La valeur %d n'est pas présente dans le tableau.\n", valeur);
    }

    return 0;
}

/*
 * Filename: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos/exo7.c
 * Path: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos
 * Created Date: Monday, November 20th 2023, 9:26:05 am
 * Author: gab
 * 
 * Copyright (c) 2023 Gabin L.
 */

