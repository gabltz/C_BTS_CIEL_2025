#include <stdio.h>
#include <string.h>

void remplacer_abc_par_123(char *chaine) {
    int i, j;
    int longueur = strlen(chaine);
    
    for (i = 0; i < longueur - 2; i++) {
        if (chaine[i] == 'a' && chaine[i + 1] == 'b' && chaine[i + 2] == 'c') {
            chaine[i] = '1';
            chaine[i + 1] = '2';
            chaine[i + 2] = '3';
        }
    }
}

int main() {
    char chaine[] = "z0abcab";
    
    printf("Chaine initiale : %s\n", chaine);
    
    remplacer_abc_par_123(chaine);
    
    printf("Chaine modifiée : %s\n", chaine);
    
    return 0;
}
