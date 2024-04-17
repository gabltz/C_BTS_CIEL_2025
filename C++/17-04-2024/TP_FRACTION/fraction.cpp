// fraction.cpp
#include "fraction.h"
#include <iostream>
#include <locale>
using namespace std;// Configurer la console pour utiliser UTF-8


Fraction::Fraction(int num, int den) : num(num), den(den) {
	if (den == 0) {
		std::wcout << "Erreur: Dénominateur ne peut pas être zéro." << std::endl;
		this->den = 1;  // Dénominateur par défaut
	}
}

// Fonction pour calculer le PGCD
int gcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

void Fraction::simp() {
	int gcd_value = gcd(num, den);  // Utilise la fonction gcd pour trouver le plus grand commun diviseur
	num /= gcd_value;
	den /= gcd_value;
}

Fraction Fraction::operator+(const Fraction& other) {
	return Fraction((num * other.den) + (other.num * den), den * other.den);
}

Fraction Fraction::operator-(const Fraction& other) {
	return Fraction((num * other.den) - (other.num * den), den * other.den);
}

Fraction Fraction::operator*(const Fraction& other) {
	return Fraction(num * other.num, den * other.den);
}

Fraction Fraction::operator/(const Fraction& other) {
	return Fraction(num * other.den, den * other.num);
}

std::istream& operator>>(std::istream& in, Fraction& f) {
	std::wcout << "Entrez le numérateur: ";
	in >> f.num;
	std::wcout << "Entrez le dénominateur: ";
	in >> f.den;
	if (f.den == 0) {
		std::wcout << "Erreur: Le dénominateur ne peut pas être zéro. Défini à 1 par défaut." << std::endl;
		f.den = 1;
	}
	f.simp(); // S'assurer que la fonction est simplifiée
	return in;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f) {
	out << f.num << "/" << f.den;
	return out;
}
