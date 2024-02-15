#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>     /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h>  /* pour htons, htonl et inet_aton */
#define PORT_SERVEUR IPPORT_USERRESERVED // = 5000
#define LG_MESSAGE 256
int main()
{
    int descripteurSocket;
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreServeur;
    socklen_t longueurAdresse;
    char messageEnvoi[LG_MESSAGE]; /* le message de la couche Application ! */
    char messageReception[LG_MESSAGE];
    int ecrits, lus;
    // Crée un socket de communication
    descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0); /* 0 indique que l’on utilisera le
    protocole par défaut associé à SOCK_DGRAM soit UDP */
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
    pointDeRencontreLocal.sin_port = htons(0); // l’OS choisira un numéro de port libre
    // On demande l’attachement local de la socket
    if ((bind(descripteurSocket, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse)) < 0)
    {
        perror("bind");
        exit(-2);
    }
    printf("Socket attachée avec succès !\n");
    //<-- Début de l’étape n°3
    // Initialise à 0 la structure sockaddr_in
    memset(&pointDeRencontreServeur, 0x00, longueurAdresse);
    pointDeRencontreServeur.sin_family = PF_INET;
    // On choisit le numéro de port d’écoute du serveur
    pointDeRencontreServeur.sin_port = htons(PORT_SERVEUR); // = 5000
    // On choisit l’adresse IPv4 du serveur
    inet_aton("172.18.30.169", &pointDeRencontreServeur.sin_addr); // à modifier selon le serveur
    // Initialise à 0 le message
    memset(messageEnvoi, 0x00, LG_MESSAGE * sizeof(char));
    // Envoie un message au serveur
    sprintf(messageEnvoi, "Bonjour !");
    ecrits = sendto(descripteurSocket, messageEnvoi, strlen(messageEnvoi), 0, (struct sockaddr *)&pointDeRencontreServeur, longueurAdresse);
    switch (ecrits)
    {
    case -1: /* une erreur ! */
        perror("sendto");
        close(descripteurSocket);
        exit(-3);
    case 0:
        fprintf(stderr, "Aucune donnée n’a été envoyée !\n\n");
        close(descripteurSocket);
        return 0;
    default: /* envoi de n octets */
        if (ecrits != strlen(messageEnvoi))
            fprintf(stderr, "Erreur dans l’envoi des données !\n\n");
        else
            printf("Message : %s envoyé avec succès(%d octets)\n\n", messageEnvoi, ecrits);
    }

    // Attendre la réponse du serveur
    lus = recvfrom(descripteurSocket, messageReception, sizeof(messageReception), 0, (struct sockaddr *)&pointDeRencontreServeur, &longueurAdresse);
    switch (lus)
    {
    case -1: /* une erreur ! */
        perror("recvfrom");
        close(descripteurSocket);
        exit(-4);
    case 0:
        fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
        close(descripteurSocket);
        return 0;
    default: /* réception de n octets */
        printf("Message reçu du serveur : %s (%d octets)\n\n", messageReception, lus);
    }

    // On ferme la ressource avant de quitter
    close(descripteurSocket);
    return 0;
}
