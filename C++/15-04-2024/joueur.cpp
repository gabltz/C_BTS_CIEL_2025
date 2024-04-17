// ------------------------ joueur.cpp ---------------------
// ce fichier contient la d�finition de la classe Joueur
// le r�le du joueur est tenu par l�ordinateur
#include <iostream>
#include "lib/joueur.h"
using namespace std;
Joueur::Joueur()
{
	min = 1; // fixe la fourchette dans laquelle
	max = 100; // se trouve le num�ro � deviner
	proposition = 0; // premi�re proposition fictive
}
int Joueur::Propose(int diag)
{
	if (diag == 1) // ajuste la fourchette
		min = proposition + 1;
	else
		max = proposition - 1;
	proposition = (min + max) / 2; // proc�de par dichotomie
	cout << "\nJe propose : " << proposition;
	return proposition;
}