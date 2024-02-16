#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>     /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h>  /* pour htons, htonl et inet_aton */
#include <signal.h>     /* pour le gestionnaire de signal */
#define PORT_SERVEUR IPPORT_USERRESERVED // = 5000
#define LG_MESSAGE 256

int descripteurSocket;

void handle_signal(int sig) { // si Ctrl+C pressé, alors fermeture du socket
    close(descripteurSocket);
    exit(0);
}

int main()
{
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreServeur;
    socklen_t longueurAdresse;
    char messageEnvoi[LG_MESSAGE]; 
    char messageReception[LG_MESSAGE];
    int ecrits, lus;
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
    inet_aton("172.18.30.7", &pointDeRencontreServeur.sin_addr); // à modifier selon le serveur
    // Initialise à 0 le message

    while (1) {
        memset(messageEnvoi, 0x00, LG_MESSAGE * sizeof(char));

        // Demander à l'utilisateur d'entrer le message à envoyer
        printf("Entrez votre message à envoyer au serveur : ");
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

    return 0;
}
