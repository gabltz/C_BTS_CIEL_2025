#include <stdio.h>
#include <stdlib.h>

int main(){
    float coutLocationJour = 65;
    float kmParLitre = 16;
    float coutParLitreEssence = 1.5;
    float coutKm = 0.1;

    float dureeVoyage = 0;
    float kmParcouru = 0;
    float coutLocation = 0;
    float litreRequis = 0;
    float coutEssence = 0;
    float coutKmTotal = 0;
    float coutTotal = 0;
    printf("Durée du voyage : ");
    scanf("%f", &dureeVoyage);
    printf("Kilometrage parcouru au total : ");
    scanf("%f", &kmParcouru);
    coutLocation = dureeVoyage * coutLocationJour;
    litreRequis = kmParcouru / kmParLitre;
    coutEssence = litreRequis * coutParLitreEssence;
    coutKmTotal = kmParcouru * coutKm;

    coutTotal = coutLocation + coutEssence + coutKmTotal;

    printf("Cout de la location (en euros) : %f\n", coutLocation);
    printf("Cout de l'essence (en euros) : %f\n", coutEssence);
    printf("Cout au km (en euros) : %f\n", coutKmTotal);
    printf("Cout total (en euros) : %f\n", coutTotal);
}