// Compare5thBit.cpp

#include "Compare5thBit.h"
#include <cstdio>

Compare5thBit::Compare5thBit(unsigned int conf, unsigned int mask)
    : conf(conf), mask(mask) {}

void Compare5thBit::printBits(unsigned int value, unsigned int bitConf, unsigned int bitMask) {
    for (int i = 31; i >= 0; i--) {
        unsigned int bit = (value >> i) & 1;
        if (i == 4) { // 5th bit (index 4)
            if (bitConf == bitMask) {
                std::cout << "\033[1;32m" << bit << "\033[0m"; // Green for identical bits
            } else {
                std::cout << "\033[1;31m" << bit << "\033[0m"; // Red for different bits
            }
        } else {
            std::cout << bit;
        }
        if (i % 8 == 0)  // Ajouter un espace tous les 8 bits pour la lisibilité
            std::cout << " ";
    }
    std::cout << std::endl;
}

void Compare5thBit::comparer5eBit() {
    unsigned int bitConf = (conf >> 4) & 1;  // Décalage de 4 et masquage
    unsigned int bitMask = (mask >> 4) & 1;

    std::cout << "Valeur Conf:  ";
    printBits(conf, bitConf, bitMask);
    std::cout << "Valeur Mask:  ";
    printBits(mask, bitConf, bitMask);

    // Comparer les 5e bits extraits
    if (bitConf == bitMask) {
        std::cout << "Les 5e bits sont identiques." << std::endl;
    } else {
        std::cout << "Les 5e bits sont différents." << std::endl;
    }
}
