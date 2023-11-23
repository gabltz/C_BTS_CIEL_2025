#include <stdio.h>
#include <stdlib.h>


int main(){
    //methode pour passer à 1 utilisant | (ou)
    char monC = 0x2, masque = 0x1, res;
    res = monC | masque;
    printf("%x\n", res);

    char monE = 0x7, masque2 = 0x4, res2;
  

  // methode pour passer à 0 utilisant & (et)
    res2 = monE & masque2;
    if(res2 == 0x00)
        printf("dans 0x%x, le bit n°2 est à 0.\n", monE);
    else
        printf("dans 0x%x, le bit n°2 est à 1.\n",monE);

    int a;
    printf("Entrer a :");
    scanf("%d",&a);
    printf("%d en hexadécimal: %x\n",a,a);
    return 0;
}