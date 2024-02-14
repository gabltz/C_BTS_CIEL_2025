#include <stdio.h>
#include <stdlib.h>

int main(){
    char *jour = "mercredi";

    //début de la semaine
    if (!strcmp(jour, "lundi") || !strcmp(jour, "mardi")){
        printf("courage !!!!\n");
    }
    // Milieu de la semaine
    else if (!strcmp(jour, "mercredi")){
        printf("C'est le jour des enfants.\n");
    }
    // fin de la semaine
    else if (!strcmp(jour, "jeudi") || !strcmp(jour, "vendredi")){
        printf("Bientot le we!\n");
    }
    else{
        printf("vive le week-end !");
    }
    return 0;
}