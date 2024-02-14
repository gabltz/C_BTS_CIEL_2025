#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int n1, n2, n3;
    double res;
    printf("Entrez trois entiers positifs : ");
    scanf("%d %d %d", &n1, &n2, &n3);
    res = n1 + 2 * n2 - pow(n3, 3);
    printf("Pour n1=%d, n2=%d, n3=%d, on calcule %.2lf.\n", n1, n2, n3, res);
    return 0;
}


// cc main.c -lm