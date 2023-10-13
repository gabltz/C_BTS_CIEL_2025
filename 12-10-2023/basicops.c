#include <stdio.h>
#include <stdlib.h>

int main(){
    int a =5, b=2;
    float c =(float)a/(float)b; // conversion des int en float (technique du cast)
    printf("%.2f\n",c); // On affiche avec 2 chiffres après la virgule
    return 0;
}