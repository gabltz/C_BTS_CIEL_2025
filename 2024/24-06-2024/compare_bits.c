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
    //Extraire le 5e bit de chaque octet
    unsigned char res = conf & mask;
    
    

    printf("Octet Conf:  ");
    print_bits(conf);
    printf("Octet Mask:  ");
    print_bits(mask);
    
    // Comparer les 5e bits
    if (res) {
        printf("on\n");
    } else {
            printf("off\n");
    }
}

int main() {
    unsigned char conf = 0b01011010; // Example byte 1
    unsigned char mask = 0b00001000; // Example byte 2

    comparer5ebit(conf, mask);
    
    return 0;
}
