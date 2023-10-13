#include <stdio.h>
#include <stdlib.h>

int main(){
    const int LUNDI = 0, MARDI = 1, MERCREDI = 2, JEUDI = 3, VENDREDI = 4, SAMEDI = 5, DIMANCHE = 6;
    int jour = MERCREDI;
    char *texte;

    switch(jour){
        case 0: // dans le cas où c'est le début de la semaine 
        case 1: // on peut tester deux valeurs à la suite
            texte = "courage!!!";
        break;
        case 2: // dans le cas où c'est le milieu de la semaine
            texte= "C'est le jour des enfants";
        break;
        case 3: // dans le cas où c'est la fin de semaine
        case 4:
            texte= "bientot le we !";
        break;
        default:
            texte = "vive le weeek-end !";
        break;
    }
    printf("%s\n", texte);
    return 0;
}