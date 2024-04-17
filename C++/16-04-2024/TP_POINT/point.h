// Fichier de d�finition de la classe point

#ifndef POINT_H
#define POINT_H

/*La classe Point devra disposer de deux constructeurs : un constructeur par d�faut qui initialisera
x et y � z�ro et un autre constructeur qui recevra en param�tres l�abscisse et l�ordonn�e du point �
initialiser.
Tous les attributs de la classe Point seront priv�s par respect du principe d�encapsulation.On
veut n�anmoins pouvoir conna�tre son abscisse et son ordonn�e, et �ventuellement les modifier.Il faudra
donc cr�er les accesseurs et mutateurs correspondants.
Un point pourra s�afficher.On aura donc une m�thode affiche() qui produira un affichage de ce
type : <x, y>*/

class Point
{
public:
	// Constructeurs
	Point(); // Constructeur par d�faut
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