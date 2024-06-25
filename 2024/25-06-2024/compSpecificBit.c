#include <stdio.h>

// Définir des codes de couleur ANSI pour la sortie dans le terminal
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Fonction pour afficher les bits d'un entier avec des couleurs pour indiquer des différences pour un bit spécifique
void print_bits_colored(unsigned int value, int bitIndex, unsigned int bitValue) {
    for (int i = 31; i >= 0; i--) {
        unsigned int bit = (value >> i) & 1;
        if (i == bitIndex) { // Si le bit actuel est le bit à comparer
            if (bit == bitValue) {
                printf(ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET, bit);
            } else {
                printf(ANSI_COLOR_RED "%d" ANSI_COLOR_RESET, bit);
            }
        } else {
            printf("%d", bit);
        }

        if (i % 8 == 0 && i != 0) { // Ajouter un espace tous les 8 bits pour la lisibilité
            printf(" ");
        }
    }
    printf("\n");
}

void comparerBitSpecifique(unsigned int conf, unsigned int mask, int bitIndex) {
    // Extraire le bit spécifié en utilisant un masque
    unsigned int bitConf = (conf >> bitIndex) & 1;  // Décalage de bitIndex et masquage
    unsigned int bitMask = (mask >> bitIndex) & 1;

    printf("Valeur Conf:  ");
    print_bits_colored(conf, bitIndex, bitMask);
    printf("Valeur Mask:  ");
    print_bits_colored(mask, bitIndex, bitConf);

    // Comparer les bits extraits
    if (bitConf == bitMask) {
        printf("Les bits à la position %d sont identiques.\n", bitIndex);
    } else {
        printf("Les bits à la position %d sont différents.\n", bitIndex);
    }
}

int main() {
    unsigned int conf, mask;
    int bitIndex;

    // Demander et lire les valeurs hexadécimales
    printf("Entrez la valeur hexadécimale de conf (par exemple 0x1A): ");
    scanf("%x", &conf);

    printf("Entrez la valeur hexadécimale de mask (par exemple 0x08): ");
    scanf("%x", &mask);

    // Demander quel bit comparer
    printf("Entrez l'index du bit à comparer (0 à 31): ");
    scanf("%d", &bitIndex);

    if (bitIndex < 0 || bitIndex > 31) {
        printf("Index de bit invalide. L'index doit être entre 0 et 31.\n");
        return 1;  // Quitte le programme si l'index est invalide
    }

    comparerBitSpecifique(conf, mask, bitIndex);

    return 0;
}
