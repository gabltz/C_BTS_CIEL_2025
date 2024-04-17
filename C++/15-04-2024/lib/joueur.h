// ------------------------ joueur.h ------------------------
// ce fichier contient la d´eclaration de la classe Joueur
#ifndef JOUEUR_H
#define JOUEUR_H
class Joueur
{
public:
	Joueur(); // initialise un joueur
	int Propose(int diag); // re¸coit le diagnostic du pr´ec´edent essai
	// renvoie une nouvelle proposition
private:
	int min, max, // fourchette pour la recherche
		proposition; // dernier nombre propos´e
};
#endif // JOUEUR_H