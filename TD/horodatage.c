#include <stdio.h>
#include <stdlib.h>

int main(){
    int seconde = 0;
    int heures = 0;
    int minutes = 0;
    int secondes = 0;
    printf("Entrer le nombre de secondes à convertir en heures, minutes et secondes : ");
    scanf("%d", &seconde);
    heures = seconde / 3600;
    seconde = seconde % 3600;
    minutes = seconde / 60;
    secondes = seconde % 60;
    printf("Voici vos secondes converties en : \nHeures : %d\nMinutes : %d\nSecondes : %d\n", heures, minutes, secondes);
    return 0;
}