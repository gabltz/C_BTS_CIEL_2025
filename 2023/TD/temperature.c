#include <stdio.h>
#include <stdlib.h>

int main(){
    float temp = 0;
    printf("Donner la temperature : ");
    scanf("%f", &temp);

    if (temp<=0){
        printf("L'eau est à l'état de glace. \n");
    }else if (temp >0 && temp<100){
        printf("L'eau est à l'état liquide. \n");
    }else if (temp>=100){
        printf("L'eau est à l'état gazeux.\n");
    }
    return 0;
}