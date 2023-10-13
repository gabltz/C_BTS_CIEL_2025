#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    float volume = 0;
    float rayon = 5.2;
    float profondeur = 2.8;
    float pi = 3.14159;
    volume = pi * pow(rayon, 2) * profondeur;
    printf("Le volume du cylindre est : %f\n", volume);
    return 0;
}