#include <stdio.h>
#include <stdlib.h>

int main(){
    int nb = 0;
    printf("Entrez un nombre entier : ");
    scanf("%d", &nb);
    if (nb % 3 == 0){
        printf("L'entier est divisible par 3. \n");
    }else{
        printf("L'entier n'est pas divisible par 3.\n");
    };
}