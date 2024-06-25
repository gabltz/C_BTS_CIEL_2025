#include "CompSpecificBit.h"

// Constructeur
CompSpecificBit::CompSpecificBit(unsigned int conf, unsigned int mask, int bitIndex)
    : conf(conf), mask(mask), bitIndex(bitIndex) {
    if (bitIndex < 0 || bitIndex > 31) {
        throw std::invalid_argument("Index de bit invalide. L'index doit être entre 0 et 31.");
    }
}

void CompSpecificBit::print_bits_colored(unsigned int value, int bitIndex, unsigned int bitValue) const {
    for (int i = 31; i >= 0; i--) {
        unsigned int bit = (value >> i) & 1;
        if (i == bitIndex) { // Si le bit actuel est le bit à comparer
            if (bit == bitValue) {
                std::cout << ANSI_COLOR_GREEN << bit << ANSI_COLOR_RESET;
            } else {
                std::cout << ANSI_COLOR_RED << bit << ANSI_COLOR_RESET;
            }
        } else {
            std::cout << bit;
        }

        if (i % 8 == 0 && i != 0) { // Ajouter un espace tous les 8 bits pour la lisibilité
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void CompSpecificBit::comparerBitSpecifique() const {
    // Extraire le bit spécifié en utilisant un masque
    unsigned int bitConf = (conf >> bitIndex) & 1;  // Décalage de bitIndex et masquage
    unsigned int bitMask = (mask >> bitIndex) & 1;

    std::cout << "Valeur Conf:  ";
    print_bits_colored(conf, bitIndex, bitMask);
    std::cout << "Valeur Mask:  ";
    print_bits_colored(mask, bitIndex, bitConf);

    // Comparer les bits extraits
    if (bitConf == bitMask) {
        std::cout << "Les bits à la position " << bitIndex << " sont identiques." << std::endl;
    } else {
        std::cout << "Les bits à la position " << bitIndex << " sont différents." << std::endl;
    }
}
