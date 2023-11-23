#include <stdio.h>

int main() {
    int a, res;

    // Afficher la valeur en décimal et en hexadécimal
    printf("Entrer un entier a : ");
    scanf("%d", &a);
    printf("Vous avez entré la valeur a suivante. \na= %d = 0x%x\n", a, a);

    res = a & 0x3; // Masque pour obtenir les bits de position 0 et 1
    printf("\nAffichage des bits de position 0 et 1 :\n");
    printf("res = %d = 0x%x\n\n", res, res);

    printf("Les bits de position 0 et 1 de %d valent-ils 0 ?\n", a);
    if (res == 0) {
        printf("Vrai.\n");
    } else {
        printf("Faux.\n");
    }

    a = a & 0xFFFC; // Masque pour mettre à 0 les bits de position 0 et 1
    printf("\nOn met les bits de position 0 et 1 a zero.\n");
    printf("a = %d = 0x%x\n", a, a);

    res = a & 0x3; // Masque pour obtenir les bits de position 0 et 1
    printf("\nLes bits de position 0 et 1 de %d valent maintenant :\n", a);
    printf("res = %d = 0x%x\n\n", res, res);

    printf("Les bits de position 0 et 1 de %d valent-ils 0 ?\n", a);
    if (res == 0) {
        printf("Vrai.\n");
    } else {
        printf("Faux.\n");
    }


    return 0;
}
