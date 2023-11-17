#include <stdio.h>
#include <stdlib.h>

int main(){
    int tableau[4] = {10, 23, 505, 8};
    int i;

    for (i = 0 ; i < 4 ; i++){
        printf("élément n°d %d : %d\n", i, tableau[i]++);
    }
    return 0;
}