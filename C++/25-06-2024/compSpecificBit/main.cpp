#include <iostream>
#include "CompSpecificBit.h"

int main() {
    unsigned int conf, mask;
    int bitIndex;

    // Demander et lire les valeurs hexadécimales
    std::cout << "Entrez la valeur hexadécimale de conf (par exemple 0x1A): ";
    std::cin >> std::hex >> conf;

    std::cout << "Entrez la valeur hexadécimale de mask (par exemple 0x08): ";
    std::cin >> std::hex >> mask;

    // Demander quel bit comparer
    std::cout << "Entrez l'index du bit à comparer (0 à 31): ";
    std::cin >> bitIndex;

    try {
        CompSpecificBit comparator(conf, mask, bitIndex);
        comparator.comparerBitSpecifique();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;  // Quitte le programme si l'index est invalide
    }

    return 0;
}
