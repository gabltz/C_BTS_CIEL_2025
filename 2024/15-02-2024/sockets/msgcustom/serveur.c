#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>              /* pour memset */
#include <netinet/in.h>          /* pour struct sockaddr_in */
#include <arpa/inet.h>           /* pour htons, htonl et inet_aton */
#define PORT IPPORT_USERRESERVED // = 5000
#define LG_MESSAGE 256
int main()
{
    int descripteurSocket;
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreClient;
    socklen_t longueurAdresse;
    char messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
    char reponseServeur[LG_MESSAGE]; /* le message de réponse du serveur */
    int lus, ecrits;
    // Crée un socket de communication
    descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0);
    // Teste la valeur renvoyée par l’appel système socket()
    if (descripteurSocket < 0) /* échec ? */
    {
        perror("socket"); // Affiche le message d’erreur
        exit(-1);         // On sort en indiquant un code erreur
    }
    printf("Socket créée avec succès ! (%d)\n", descripteurSocket);
    // On prépare l’adresse d’attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
    pointDeRencontreLocal.sin_family = PF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // n’importe quelle interface
    // locale disponible
    pointDeRencontreLocal.sin_port = htons(PORT); // <- 5000
    // On demande l’attachement local de la socket
    if ((bind(descripteurSocket, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse)) < 0)
    {
        perror("bind");
        exit(-2);
    }
    printf("Socket attachée avec succès !\n");
    //<-- Début de l’étape n°4
    // Initialise à 0 le message
    memset(messageRecu, 0x00, LG_MESSAGE * sizeof(char));
    // Réception d’un message du client
    lus = recvfrom(descripteurSocket, messageRecu, sizeof(messageRecu), 0, (struct sockaddr *)&pointDeRencontreClient, &longueurAdresse);
    switch (lus)
    {
    case -1: /* une erreur ! */
        perror("recvfrom");
        close(descripteurSocket);
        exit(-3);
    case 0:
        fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
        close(descripteurSocket);
        return 0;
    default: /* réception de n octets */
        printf("Message \"%s\" reçu du client (%d octets)\n\n", messageRecu, lus);
    }

    // Demander à l'utilisateur d'entrer le message de réponse
    printf("Entrez votre message de réponse : ");
    fgets(reponseServeur, LG_MESSAGE, stdin);
    // Supprimer le retour à la ligne ajouté par fgets
    reponseServeur[strcspn(reponseServeur, "\n")] = '\0';

    // Envoi de la réponse au client
    ecrits = sendto(descripteurSocket, reponseServeur, strlen(reponseServeur), 0, (struct sockaddr *)&pointDeRencontreClient, longueurAdresse);
    switch (ecrits)
    {
    case -1: /* une erreur ! */
        perror("sendto");
        close(descripteurSocket);
        exit(-4);
    case 0:
        fprintf(stderr, "Aucune donnée n’a été envoyée !\n\n");
        close(descripteurSocket);
        return 0;
    default: /* envoi de n octets */
        if (ecrits != strlen(reponseServeur))
            fprintf(stderr, "Erreur dans l’envoi des données !\n\n");
        else
            printf("Réponse \"%s\" envoyée au client (%d octets)\n\n", reponseServeur, ecrits);
    }

    // On ferme la ressource avant de quitter
    close(descripteurSocket);
    return 0;
}
