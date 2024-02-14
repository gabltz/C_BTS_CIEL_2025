#include <stdio.h>
#include <stdlib.h>

int main(){
    float a = 0;
    float b = 0;
    float sol = 0;
    printf("Donner a : ");
    scanf("%f", &a);
    printf("Donner b : ");
    scanf("%f", &b);
    if (a==0 && b==0){
        printf("Solutions infinies");
    }else if (a==0){
        printf("L'équation n'a pas de solutions");
    }else{
        sol = -b/a;
        printf("La solution de l'équation est : %f\n", sol);
    }
    return 0;
}