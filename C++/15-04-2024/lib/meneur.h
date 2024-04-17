// ------------------------ meneur.h ------------------------
// ce fichier contient la d´eclaration de la classe Meneur
#ifndef MENEUR_H
#define MENEUR_H
class Meneur
{
public:
	Meneur(); // initialise un meneur
	int Reponds(int prop); // recoit la proposition du joueur
	// renvoie 0 si c’est exact, 1 si c’est plus
	// et 2 si c’est moins
private:
	int numsecret; // num´ero secret choisi au d´epart
};

#endif // MENEUR_H