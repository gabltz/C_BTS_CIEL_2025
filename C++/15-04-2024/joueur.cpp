// ------------------------ joueur.cpp ---------------------
// ce fichier contient la définition de la classe Joueur
// le rôle du joueur est tenu par l’ordinateur
#include <iostream>
#include "lib/joueur.h"
using namespace std;
Joueur::Joueur()
{
	min = 1; // fixe la fourchette dans laquelle
	max = 100; // se trouve le numéro à deviner
	proposition = 0; // première proposition fictive
}
int Joueur::Propose(int diag)
{
	if (diag == 1) // ajuste la fourchette
		min = proposition + 1;
	else
		max = proposition - 1;
	proposition = (min + max) / 2; // procède par dichotomie
	cout << "\nJe propose : " << proposition;
	return proposition;
}