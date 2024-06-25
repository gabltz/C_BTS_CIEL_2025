#include <stdio.h>

// Fonction pour afficher les bits d'un entier
void print_bits(unsigned int value) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 8 == 0)  // Ajouter un espace tous les 8 bits pour la lisibilité
            printf(" ");
    }
    printf("\n");
}

void comparer5ebit(unsigned int conf, unsigned int mask) {
    // Extraire le 5e bit (bit indexé à 4) en utilisant un masque
    unsigned int bitConf = (conf >> 4) & 1;  // Décalage de 4 et masquage
    unsigned int bitMask = (mask >> 4) & 1;

    printf("Valeur Conf:  ");
    print_bits(conf);
    printf("Valeur Mask:  ");
    print_bits(mask);

    // Comparer les 5e bits extraits
    if (bitConf == bitMask) {
        printf("Les 5e bits sont identiques.\n");
    } else {
        printf("Les 5e bits sont différents.\n");
    }
}

int main() {
    unsigned int conf, mask;

    // Demander et lire les valeurs hexadécimales
    printf("Entrez la valeur hexadécimale de conf (par exemple 0x1A): ");
    scanf("%x", &conf);

    printf("Entrez la valeur hexadécimale de mask (par exemple 0x08): ");
    scanf("%x", &mask);

    comparer5ebit(conf, mask);

    return 0;
}
