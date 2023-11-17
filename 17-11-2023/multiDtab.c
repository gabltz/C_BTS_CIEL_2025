#include <stdio.h>
#include <stdlib.h>

int main(){
    int premiersNombres[2][5] = {
        {0, 2, 4, 6, 8},
        {1, 3, 5, 7, 9}
    };

    int i, j;

    for (i = 0; i < 2; i++){
        for (j = 0; j < 5; j++){
            printf("élément n° (%d,%d) : %d\n", i, j, premiersNombres[i][j]);
        }
    }
    return 0;
}