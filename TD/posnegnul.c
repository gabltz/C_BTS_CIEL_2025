#include <stdio.h>
#include <stdlib.h>

int main(){
    int nb = 0;
    printf("Entrer un entier : ");
    scanf("%d", &nb);
    if (nb > 0){
        printf("L'entier est positif.\n");
    }else if ( nb < 0){
        printf("L'entier est negatif.\n");
    }else{
        printf("L'entier est nul.\n");
    }
    return 0;
}