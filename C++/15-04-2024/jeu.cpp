// ------------------------ jeu.cpp ---------------------
// programme de simulation du jeu "c’est plus, c’est moins"
#include <iostream> // pour les entr´ees-sorties
#include "lib/joueur.h" // pour la d´eclaration de la classe Joueur
#include "lib/meneur.h" // pour la d´eclaration de la classe Meneur
using namespace std;
#pragma execution_character_set("utf-8")

void main() // g`ere une partie ...
{
	Joueur j; // ... avec un joueur ...
	Meneur m; // ... et un meneur
	int p, d = 1, // variables auxiliaires
		cpt = 0; // nombre d’essais
	do // simulation du d´eroulement du jeu
	{
		p = j.Propose(d); // proposition du joueur
		d = m.Reponds(p); // diagnostic du meneur
		cpt++;
	} while (d && cpt < 6);
	if (d) // d´efaite du joueur
		cout << "\nLe joueur a perdu !";
	else // victoire du joueur
		cout << "\nLe joueur a gagn´e !";
}

//print hello world

