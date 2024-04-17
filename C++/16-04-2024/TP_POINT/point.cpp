#include "point.h"
#include <iostream>
#include <cmath> // Pour la fonction sqrt()

// Constructeur par défaut
Point::Point() {
	// Initialisation des coordonnées à zéro par défaut
	x = 0.0;
	y = 0.0;
}

// Constructeur prenant deux paramètres doubles
Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}

// Accesseur pour la coordonnée x
double Point::getX() const {
	return x;
}

// Accesseur pour la coordonnée y
double Point::getY() const {
	return y;
}

// Mutateur pour la coordonnée x
void Point::setX(double x) {
	this->x = x;
}

// Mutateur pour la coordonnée y
void Point::setY(double y) {
	this->y = y;
}

// Fonction pour afficher les coordonnées du point
void Point::affiche() const {
	std::cout << "<" << x << ", " << y << ">" << std::endl;
}

// Fonction pour calculer la distance entre deux points
double Point::distance(const Point& other) const {
	double dx = x - other.x;
	double dy = y - other.y;
	return sqrt(dx * dx + dy * dy);
}

// Fonction pour calculer le point milieu entre deux points
Point Point::milieu(const Point& other) const {
	double midX = (x + other.x) / 2.0;
	double midY = (y + other.y) / 2.0;
	return Point(midX, midY);
}