#include <stdio.h>
#include <stdlib.h>

int main(){
    double nb;
    double valAbs;

    printf("Entrez un nombre réel :");
    scanf("%lf", &nb);
    if (nb < 0){
        valAbs = -nb;
    }else{
        valAbs = nb;
    }

    printf("La valeur absolue du réel est : %lf\n", valAbs);

    return 0;
}