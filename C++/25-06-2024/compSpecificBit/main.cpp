#include <iostream>
#include <limits>
#include "CompSpecificBit.h"

int main() {
    unsigned int conf, mask;
    int bitIndex;

    // Demander et lire les valeurs hexadécimales
    std::cout << "Entrez la valeur hexadécimale de conf (par exemple 0x1A): ";
    while (!(std::cin >> std::hex >> conf)) {
        std::cout << "Valeur hexadécimale invalide. Veuillez réessayer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Entrez la valeur hexadécimale de mask (par exemple 0x08): ";
    while (!(std::cin >> std::hex >> mask)) {
        std::cout << "Valeur hexadécimale invalide. Veuillez réessayer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Afficher les valeurs pour vérifier qu'elles sont lues correctement
    std::cout << "Conf lue : 0x" << std::hex << conf << std::dec << " (" << conf << ")" << std::endl;
    std::cout << "Mask lu : 0x" << std::hex << mask << std::dec << " (" << mask << ")" << std::endl;

    // Demander quel bit comparer
    std::cout << "Entrez l'index du bit à comparer (0 à 31): ";
    while (!(std::cin >> std::dec >> bitIndex) || bitIndex < 0 || bitIndex > 31) {
        std::cout << "Index de bit invalide. Veuillez entrer un nombre entre 0 et 31: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Afficher l'index pour vérification
    std::cout << "Index du bit à comparer: " << bitIndex << std::endl;

    try {
        CompSpecificBit comparator(conf, mask, bitIndex);
        comparator.comparerBitSpecifique();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;  // Quitte le programme si l'index est invalide
    }

    return 0;
}
