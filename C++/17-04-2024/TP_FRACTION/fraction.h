//fraction.h
// fraction.h
#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
	int num;  // Numérateur
	int den;  // Dénominateur

public:
	Fraction(int num = 0, int den = 1);

	void simp();

	Fraction operator+(const Fraction& other);
	Fraction operator-(const Fraction& other);
	Fraction operator*(const Fraction& other);
	Fraction operator/(const Fraction& other);

	friend std::istream& operator>>(std::istream& in, Fraction& f);
	friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
};

#endif
