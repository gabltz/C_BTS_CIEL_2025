#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n1, n2, n3, restart;

    do {
        double res;
        printf("Entrez trois entiers positifs : ");
        scanf("%d %d %d", &n1, &n2, &n3);
        res = n1 + 2 * n2 - pow(n3, 3);
        printf("Pour n1=%d, n2=%d, n3=%d, on calcule %.2lf.\n", n1, n2, n3, res);

        printf("Voulez-vous recommencer ?\nSi oui, entrez 0 (zéro).\n");
        scanf("%d", &restart);

    } while (restart == 0);

    return 0;
}