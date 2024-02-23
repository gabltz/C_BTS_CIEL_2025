#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> /* pour close */
int main()
{
int descripteurSocket;
//<-- Début de l’étape n°1 !
// Crée un socket de communication
descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0); /* 0 indique que l’on utilisera le
protocole par défaut associé à SOCK_DGRAM soit UDP */
// Teste la valeur renvoyée par l’appel système socket()
if (descripteurSocket < 0) /* échec ? */
{
perror("socket"); // Affiche le message d’erreur
exit(-1); // On sort en indiquant un code erreur
}
//--> Fin de l’étape n°1 !
printf("Socket créée avec succès ! (%d)\n", descripteurSocket);
// On ferme la ressource avant de quitter
close(descripteurSocket);
return 0;
}