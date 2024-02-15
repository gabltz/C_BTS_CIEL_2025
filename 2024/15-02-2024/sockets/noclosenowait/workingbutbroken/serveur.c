#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>              /* pour memset */
#include <netinet/in.h>          /* pour struct sockaddr_in */
#include <arpa/inet.h>           /* pour htons, htonl et inet_aton */
#include <signal.h>              /* pour le gestionnaire de signal */
#include <sys/select.h>          /* pour select */
#define PORT IPPORT_USERRESERVED // = 5000
#define LG_MESSAGE 256

int descripteurSocket;

void handle_signal(int sig) { // si Ctrl+C pressé, alors fermeture du socket
    close(descripteurSocket);
    exit(0);
}

int main()
{
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreClient;
    socklen_t longueurAdresse;
    char messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
    char reponseServeur[LG_MESSAGE]; /* le message de réponse du serveur */
    int lus, ecrits;
    fd_set readfds;
    struct timeval timeout;
    int maxfd;

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

    // Gestion du signal Ctrl+C
    signal(SIGINT, handle_signal);

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(descripteurSocket, &readfds);
        // Trouver le plus grand descripteur de fichier
        maxfd = descripteurSocket;

        // Définir le timeout à 1 seconde
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Attendre jusqu'à ce qu'il y ait des données prêtes à être lues
        if (select(maxfd + 1, &readfds, NULL, NULL, &timeout) < 0)
        {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // Si le socket est prêt à être lu (un message est reçu du client)
        if (FD_ISSET(descripteurSocket, &readfds))
        {
            memset(messageRecu, 0x00, LG_MESSAGE * sizeof(char));
            // Réception d’un message du client
            lus = recvfrom(descripteurSocket, messageRecu, sizeof(messageRecu), 0, (struct sockaddr *)&pointDeRencontreClient, &longueurAdresse);
            switch (lus)
            {
            case -1: /* une erreur ! */
                perror("recvfrom");
                break;
            case 0:
                fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
                break;
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
                break;
            case 0:
                fprintf(stderr, "Aucune donnée n’a été envoyée !\n\n");
                break;
            default: /* envoi de n octets */
                if (ecrits != strlen(reponseServeur))
                    fprintf(stderr, "Erreur dans l’envoi des données !\n\n");
                else
                    printf("Réponse \"%s\" envoyée au client (%d octets)\n\n", reponseServeur, ecrits);
            }
        }
    }

    return 0;
}
