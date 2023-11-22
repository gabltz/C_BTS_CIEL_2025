#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceVoySpace(char *chaine){
    while (*chaine) {
        if (*chaine == 'a' || *chaine == 'A' || *chaine == 'e' || *chaine == 'E' || *chaine == 'i' || *chaine == 'I' || *chaine == 'o' || *chaine == 'O' || *chaine == 'u' || *chaine == 'U') {
            *chaine = ' ';
        }
        chaine++;
    }
}

int main() {
    char Chaine2[100];

    printf("Entrez une phrase (100 char max):");
    fgets(Chaine2, sizeof(Chaine2), stdin);

    if (Chaine2[strlen(Chaine2) - 1] == '\n'){
        Chaine2[strlen(Chaine2) - 1] = '\0';
    }

    replaceVoySpace(Chaine2);

    printf("OUTPUT : \n %s\n\n", Chaine2);
    
    return 0;
}

/*
 * Filename: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos/exo5.c
 * Path: /home/gab/Documents/GitHub/C_BTS_CIEL_2025/17-11-2023/exos
 * Created Date: Monday, November 20th 2023, 8:38:11 am
 * Author: gab
 * 
 * Copyright (c) 2023 Gabin L.
 */
