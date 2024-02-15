#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>     /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h>  /* pour htons, htonl et inet_aton */
#include <signal.h>     /* pour le gestionnaire de signal */
#include <sys/select.h> /* pour select */
#define PORT_SERVEUR IPPORT_USERRESERVED // = 5000
#define LG_MESSAGE 256

int descripteurSocket;

void handle_signal(int sig) { // si Ctrl+C pressé, alors fermeture du socket
    close(descripteurSocket);
    exit(0);
}

void handle_user_input(int descripteurSocket, struct sockaddr_in pointDeRencontreServeur, socklen_t longueurAdresse) {
    char messageEnvoi[LG_MESSAGE];
    int ecrits;

    memset(messageEnvoi, 0x00, LG_MESSAGE * sizeof(char));
    // Demander à l'utilisateur d'entrer le message à envoyer
    printf("Entrez votre message à envoyer au serveur : ");
    fflush(stdout); // Assurer que le message est affiché immédiatement
    fgets(messageEnvoi, LG_MESSAGE, stdin);
    // Supprimer le retour à la ligne ajouté par fgets
    messageEnvoi[strcspn(messageEnvoi, "\n")] = '\0';

    // Envoie un message au serveur
    ecrits = sendto(descripteurSocket, messageEnvoi, strlen(messageEnvoi), 0, (struct sockaddr *)&pointDeRencontreServeur, longueurAdresse);
    switch (ecrits)
    {
    case -1: /* une erreur ! */
        perror("sendto");
        break;
    case 0:
        fprintf(stderr, "Aucune donnée n’a été envoyée !\n\n");
        break;
    default: /* envoi de n octets */
        if (ecrits != strlen(messageEnvoi))
            fprintf(stderr, "Erreur dans l’envoi des données !\n\n");
        else
            printf("Message : %s envoyé avec succès(%d octets)\n\n", messageEnvoi, ecrits);
    }
}


void handle_server_response(int descripteurSocket, struct sockaddr_in pointDeRencontreServeur, socklen_t longueurAdresse) {
    char messageReception[LG_MESSAGE];
    int lus;

    memset(messageReception, 0x00, LG_MESSAGE * sizeof(char));
    // Attendre la réponse du serveur
    lus = recvfrom(descripteurSocket, messageReception, sizeof(messageReception), 0, (struct sockaddr *)&pointDeRencontreServeur, &longueurAdresse);
    switch (lus)
    {
    case -1: /* une erreur ! */
        perror("recvfrom");
        break;
    case 0:
        fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
        break;
    default: /* réception de n octets */
        messageReception[lus] = '\0';
        printf("Message reçu du serveur : %s (%d octets)\n\n", messageReception, lus);
    }
}

int main()
{
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreServeur;
    socklen_t longueurAdresse;
    fd_set readfds;
    struct timeval timeout;
    int maxfd;

    // Crée un socket de communication
    descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (descripteurSocket < 0)
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

    // Gestion du signal Ctrl+C
    signal(SIGINT, handle_signal);

    //<-- Début de l’étape n°3
    // Initialise à 0 la structure sockaddr_in
    memset(&pointDeRencontreServeur, 0x00, longueurAdresse);
    pointDeRencontreServeur.sin_family = PF_INET;
    // On choisit le numéro de port d’écoute du serveur
    pointDeRencontreServeur.sin_port = htons(PORT_SERVEUR); // = 5000
    // On choisit l’adresse IPv4 du serveur
    inet_aton("172.18.30.169", &pointDeRencontreServeur.sin_addr); // à modifier selon le serveur

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(descripteurSocket, &readfds);

        // Trouver le plus grand descripteur de fichier
        maxfd = descripteurSocket > STDIN_FILENO ? descripteurSocket : STDIN_FILENO;

        // Définir le timeout à 1 seconde
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Attendre jusqu'à ce qu'il y ait des données prêtes à être lues
        if (select(maxfd + 1, &readfds, NULL, NULL, &timeout) < 0)
        {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // Si l'entrée standard est prête à être lue (l'utilisateur a saisi un message)
        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            handle_user_input(descripteurSocket, pointDeRencontreServeur, longueurAdresse);
        }

        // Si le socket est prêt à être lu (un message est reçu du serveur)
        if (FD_ISSET(descripteurSocket, &readfds))
        {
            handle_server_response(descripteurSocket, pointDeRencontreServeur, longueurAdresse);
        }
    }

    return 0;
}
