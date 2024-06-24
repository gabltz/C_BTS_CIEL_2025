#include <stdio.h>


// Fonction pour afficher les bits d'un octet
void print_bits(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
    printf("\n");
}

void comparer5ebit(unsigned char byte1, unsigned char byte2) {
    // Masque isolant le 5e bit (bit 4, car les bits sont indexés à partir de 0)
    unsigned char mask = 1 << 4;

    // Extraire le 5e bit de chaque octet
    unsigned char bit1 = byte1 & mask;
    unsigned char bit2 = byte2 & mask;
    

    printf("Octet Conf:  ");
    print_bits(byte1);
    printf("Octet Mask: ");
    print_bits(byte2);
    
    // Comparer les 5e bits
    if (bit1 == bit2) {
        printf("Statut du 5e bit: ");
        if (bit1) {
            printf("on\n");
        } else {
            printf("off\n");
        }
    } else { // Si problème de comparaison
        printf("Statut du 5e bit: off\n");
    }
}

int main() {
    unsigned char byte1 = 0b00010010; // Example byte 1
    unsigned char byte2 = 0b00010110; // Example byte 2

    comparer5ebit(byte1, byte2);
    
    return 0;
}
