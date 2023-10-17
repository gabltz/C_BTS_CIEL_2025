#include <stdio.h>
#include <stdlib.h>

int main(){
    int nombre = 0;
    int centaines = 0;
    int dizaines = 0;
    int unites = 0;
    int reste = 0;
    printf("Choissisez un nombre entre 1 et 999\t");
    scanf("%d", &nombre);
    if(nombre<1 && nombre>999) {
        printf("Le nombre n'est pas valide");
    } else {
        centaines = nombre / 100;
        reste = nombre % 100;
        dizaines = reste / 100;
        unites = reste % 100;
    }
    printf("Le nombre de centaines est de:%d, de dizaines est:%d, et d'unités:%d\n", centaines, dizaines, unites);
    return 0;
}