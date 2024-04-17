// ------------------------ meneur.cpp ---------------------
// ce fichier contient la définition de la classe Meneur
// le rôle du meneur est tenu par l’utilisateur du programme
#include <iostream>
#include "lib/meneur.h"
using namespace std;
#pragma execution_character_set("utf-8")
Meneur::Meneur()
{
	cout << "\nBonjour ! Vous allez jouer le rôle du meneur.";
	cout << "\nChoisissez un numéro secret entre 1 et 100";
}
int Meneur::Reponds(int prop) // la valeur de prop est ignorée
{
	int r;
	cout << "\n0 - C’est exact";
	cout << "\n1 - C’est plus";
	cout << "\n2 - C’est moins";
	cout << "\nVotre réponse (0,1,2) ? ";
	cin >> r;
	return r;
}
