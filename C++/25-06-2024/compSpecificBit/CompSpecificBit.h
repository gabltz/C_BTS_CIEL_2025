#ifndef COMPSPECIFICBIT_H
#define COMPSPECIFICBIT_H

#include <iostream>
#include <string>

class CompSpecificBit {
public:
    // Constructeur
    CompSpecificBit(unsigned int conf, unsigned int mask, int bitIndex);

    // Méthode pour comparer les bits
    void comparerBitSpecifique() const;

private:
    unsigned int conf;
    unsigned int mask;
    int bitIndex;

    // Méthode pour afficher les bits avec des couleurs
    void print_bits_colored(unsigned int value, int bitIndex, unsigned int bitValue) const;

    // Définir des codes de couleur ANSI pour la sortie dans le terminal
    const std::string ANSI_COLOR_RED = "\x1b[31m";
    const std::string ANSI_COLOR_GREEN = "\x1b[32m";
    const std::string ANSI_COLOR_RESET = "\x1b[0m";
};

#endif // COMPSPECIFICBIT_H
