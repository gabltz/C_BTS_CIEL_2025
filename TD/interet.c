#include <stdio.h>
#include <stdlib.h>

int main(){
    int valeur_du_pret =0;
    float interet = 0;
    float taux = 2.5 / 100;
    printf("Entrer la valeur du pret : ");
    scanf("%d", &valeur_du_pret);
    interet = valeur_du_pret * taux;
    printf("L'intérêt fixe du prêt est de : %f\n", interet);
    return 0;
}