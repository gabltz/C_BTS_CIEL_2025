#include <stdio.h>
#include <stdlib.h>

int main(){
    char nom[21] = ""; // On initialise la variable à une chaine vide
    int age = 0; // On initialise la variable a 0
    printf("Comment vous appellez-vous ?"); //Les caractères saisis pointent directement sur le tableau
    scanf("%s", nom);
    printf("\n Quel age avez-vous ?"); // le caractère & fait pointer la saisie sur la variable age.
    scanf("%d", &age);
    printf("Bonjour %s, vous avez %d ans.\n", nom, age);

    return 0;
}