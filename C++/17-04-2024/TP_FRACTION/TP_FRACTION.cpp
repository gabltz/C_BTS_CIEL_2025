#include "fraction.h"
#include <iostream>
#include <locale>
#include <codecvt> 
#include <windows.h>


int main() {
	// Configurer la console pour utiliser UTF-8
	SetConsoleOutputCP(CP_UTF8);

	// Utiliser une locale avec le codec UTF-8 à UTF-16 pour wcout
	std::locale::global(std::locale(std::locale::classic(), new std::codecvt_utf8_utf16<wchar_t>));


	Fraction f1, f2, result;

	// Utiliser wcout pour les chaînes larges
	std::wcout << L"Entrée pour la première fraction\n";
	std::cin >> f1;
	std::wcout << "Entrée pour la deuxième fraction" << std::endl;
	std::cin >> f2;

	result = f1 + f2;
	std::cout << "Somme: " << result << std::endl;

	result = f1 - f2;
	std::cout << "Différence: " << result << std::endl;

	result = f1 * f2;
	std::cout << "Produit: " << result << std::endl;

	result = f1 / f2;
	std::cout << "Quotient: " << result << std::endl;

	return 0;
}
