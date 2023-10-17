#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char str1[] = {'a','b','c','d','e','f','\0'};
    char str2[] = {'1','2','3','4','5','6','\0'};

    printf("AFFICHAGE DE LA LONGUEUR D'UNE CHAINE : \n");
    printf("voici la longueur de la chaine 1 : %d\n", strlen(str1));
    printf("voici la longueur de la chaine 2 : %d\n\n", strlen(str2));
    printf("######################################\n\n");

    // COPIE DE CHAINES

    char str3[7];
    char str4[7];

    strcpy(str3, str1);
    strcpy(str4, str2);

    printf("COPIE DE STR1 DANS STR3 ET STR2 DANS STR 4 : \n");
    printf("str3 : %s\n", str3);
    printf("str4 : %s\n\n", str4);
    printf("######################################\n\n");

    // CONCATENATION 

    char str5[14];

    strcpy(str5, str3);
    strcat(str5, str4);
    printf("CONCATENATION DE STR3 ET STR4 DANS STR5\n");
    printf("str5 : %s\n\n", str5);
    printf("######################################\n\n");

    // COMPARAISON

    printf("COMPARAISON DE DEUX CHAINES DE CARACTERES (STR3/STR4 PUIS STR3/STR5)\n");
    int comparison = strcmp(str3, str4);

    if (comparison < 0) {
        printf("str3 est plus petite que str4.\n");
    } else if (comparison > 0) {
        printf("str3 est plus grande que str4.\n");
    } else {
        printf("str3 est égale à str4.\n");
    }

    int comparison2 = strcmp(str3, str5);

    if (comparison2 < 0) {
        printf("str3 est plus petite que str5.\n");
    } else if (comparison2 > 0) {
        printf("str3 est plus grande que str5.\n");
    } else {
        printf("str3 est égale à str5.\n\n");
    }

    printf("######################################\n\n");

    // RECHERCHE D'UN CARACTERE DANS UNE CHAINE

    printf("RECHERCHE D'UN CARACTERE DANS UNE CHAINE\n");

    char strCherche1 = 'b';
    char strCherche2 = '5';

    char* res1 = strchr(str1, strCherche1);
    char* res2 = strchr(str2, strCherche2);


    if (res1 != NULL) {
        printf("Le caractère '%c' a été trouvé dans str1 à la position %ld.\n\n", strCherche1, res1 - str1);
    } else {
        printf("Le caractère '%c' n'a pas été trouvé dans str1.\n\n", strCherche1);
    }

    if (res2 != NULL) {
        printf("Le caractère '%c' a été trouvé dans str2 à la position %ld.\n\n", strCherche2, res2 - str2);
    } else {
        printf("Le caractère '%c' n'a pas été trouvé dans str2.\n\n", strCherche2);
    }

    printf("######################################\n\n");

    // UTILISATION DE STRPBRK

    char charCherche2 = 'c';

    char* res3 = strpbrk(str1, &charCherche2);

    if (res3 != NULL) {
        printf("Le caractère '%c' a été trouvé dans str1 à la position %ld.\n", charCherche2, res3 - str1);
    } else {
        printf("Le caractère '%c' n'a pas été trouvé dans str1.\n", charCherche2);
    }

    



    return 0;
}