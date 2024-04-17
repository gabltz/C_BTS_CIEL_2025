// Fichier de définition de la classe point

#ifndef POINT_H
#define POINT_H

/*La classe Point devra disposer de deux constructeurs : un constructeur par défaut qui initialisera
x et y à zéro et un autre constructeur qui recevra en paramètres l’abscisse et l’ordonnée du point à
initialiser.
Tous les attributs de la classe Point seront privés par respect du principe d’encapsulation.On
veut néanmoins pouvoir connaître son abscisse et son ordonnée, et éventuellement les modifier.Il faudra
donc créer les accesseurs et mutateurs correspondants.
Un point pourra s’afficher.On aura donc une méthode affiche() qui produira un affichage de ce
type : <x, y>*/

class Point
{
public:
	// Constructeurs
	Point(); // Constructeur par défaut
	Point(double x, double y);

	// Accesseurs
	double getX() const;
	double getY() const;

	// Mutateurs
	void setX(double x);
	void setY(double y);

	// Autre fonction
	void affiche() const;
	double distance(const Point& other) const;
	Point milieu(const Point& other) const;
private:
	double x;
	double y;
};
#endif // !POINT_H