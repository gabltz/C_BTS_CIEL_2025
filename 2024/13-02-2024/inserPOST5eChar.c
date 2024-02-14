#include <stdio.h>
#include <string.h>

void inserer_XTZ_apres_5eme_caractere(char *chaine) {
    char nouvelle_chaine[strlen(chaine) + 4]; // +4 pour la longueur de "XTZ"
    int i, j;
    
    // Copie des 5 premiers caractères
    for (i = 0; i < 5; i++) {
        nouvelle_chaine[i] = chaine[i];
    }
    
    // Insertion de "XTZ" après le 5ème caractère
    nouvelle_chaine[5] = 'X';
    nouvelle_chaine[6] = 'T';
    nouvelle_chaine[7] = 'Z';
    
    // Copie des caractères restants de la chaîne d'origine
    for (i = 5; chaine[i] != '\0'; i++) {
        nouvelle_chaine[i + 3] = chaine[i];
    }
    nouvelle_chaine[i + 3] = '\0'; // Ajout du caractère de fin de chaîne
    
    // Copie de la nouvelle chaîne dans la chaîne d'origine
    strcpy(chaine, nouvelle_chaine);
}

int main() {
    char chaine[] = "z0abcab";
    
    printf("Chaine initiale : %s\n", chaine);
    
    inserer_XTZ_apres_5eme_caractere(chaine);
    
    printf("Chaine modifiée : %s\n", chaine);
    
    return 0;
}
