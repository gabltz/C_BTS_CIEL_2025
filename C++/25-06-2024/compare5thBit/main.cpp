// main.cpp

#include "Compare5thBit.h"
#include <iostream>

int main() {
    unsigned int conf, mask;

    // Demander et lire les valeurs hexadécimales
    std::cout << "Entrez la valeur hexadécimale de conf (par exemple 0x1A): ";
    std::cin >> std::hex >> conf;

    std::cout << "Entrez la valeur hexadécimale de mask (par exemple 0x08): ";
    std::cin >> std::hex >> mask;

    Compare5thBit compare(conf, mask);
    compare.comparer5eBit();

    return 0;
}
