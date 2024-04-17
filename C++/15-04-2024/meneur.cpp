// ------------------------ meneur.cpp ---------------------
// ce fichier contient la d�finition de la classe Meneur
// le r�le du meneur est tenu par l�utilisateur du programme
#include <iostream>
#include "lib/meneur.h"
using namespace std;
#pragma execution_character_set("utf-8")
Meneur::Meneur()
{
	cout << "\nBonjour ! Vous allez jouer le r�le du meneur.";
	cout << "\nChoisissez un num�ro secret entre 1 et 100";
}
int Meneur::Reponds(int prop) // la valeur de prop est ignor�e
{
	int r;
	cout << "\n0 - C�est exact";
	cout << "\n1 - C�est plus";
	cout << "\n2 - C�est moins";
	cout << "\nVotre r�ponse (0,1,2) ? ";
	cin >> r;
	return r;
}
