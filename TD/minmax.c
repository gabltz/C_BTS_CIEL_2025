#include <stdio.h>
#include <stdlib.h>

int main(){
    int a = 0;
    int b = 0;
    int c = 0;
    int max = 0;
    int min = 0;

    printf("Entrez a : ");
    scanf("%d", &a);
    printf("Entrez b : ");
    scanf("%d", &b);
    printf("Entrez c : ");
    scanf("%d", &c);

    max = a;
    min = a;

    if (b>max){
        max = b;
    }
    if (c>max){
        max = c;
    }
    if (b<min){
        min = b;
    }
    if (c<min){
        min = c;
    }

    printf("La valeur max est : %d\t", max);
    printf("La valeur min est : %d\n", min);
    return 0;
}