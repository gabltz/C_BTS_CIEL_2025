#include <stdio.h>

/*
                Ecrire un programme tru3 qui trie parordre croissant trois valeurs 'double' lues au clavier.
                Une exécution de ce programme donnera à l'écran ce qui suit :
                Entrez trois valeurs flottantes : 4.4 1.1 3.3
                Vous avez entré les valeurs 4.400000, 1.100000, 3.300000 qui, triées par odre croissant sont 1.100000, 3.300000, 4.400000.
*/

int main() {
    double v1, v2, v3, tmp;
    printf("Entrez trois valeurs flottantes : ");
    scanf("%lf %lf %lf", &v1, &v2, &v3);
    if (v1 > v2) {
        tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    if (v2 > v3) {
        tmp = v2;
        v2 = v3;
        v3 = tmp;
    }
    if (v1 > v2) {
        tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    printf("Vous avez entré les valeurs %.6lf, %.6lf, %.6lf qui ont été triées par ordre croissant.\n", v1, v2, v3);
    return 0;
}
