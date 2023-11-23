#include <stdio.h>

/*
            Ecrire un programme tri2 qui trie par ordre croissant deux valeurs float lues au clavier. 
            Une execution de ce programme donnera a l'écran ce qui suit :
            Entrez deux valeurs flottantes : 4.4 3.3 
            Vous avez entre les valeurs 4.400000, 3.300000 qui triees par ordre croissant sont 3.300000, 4.400000
*/

int main() {
    float v1, v2, tmp;
    printf("Entrez deux valeurs flottantes : ");
    scanf("%f %f", &v1, &v2);
    if (v1 > v2) {
        tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    printf("Vous avez entré les valeurs %.6f, %.6f qui, triées par ordre croissant, sont %.6f, %.6f\n", v1, v2, v1, v2);
    return 0;
}
