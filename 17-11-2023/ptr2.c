#include <stdio.h>
#include <stdlib.h>

void decoupeMinutes(int* ptrHeures, int* ptrMinutes){
        *ptrHeures = *ptrHeures + *ptrMinutes / 60;
        *ptrMinutes = *ptrMinutes % 60;
    }

int main(){
    int heures = 0, minutes = 90;

    decoupeMinutes(&heures, &minutes);

    printf("%d heures et %d minutes\n", heures, minutes);
    return 0;
}