#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mariadb/mysql.h>

#define PORT IPPORT_USERRESERVED // = 5000
#define LG_MESSAGE 256

int main() {
    int descripteurSocket;
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse;
    char messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
    int lus; /* nb d’octets lus */
    MYSQL *conn; // Objet de connexion MySQL
    char *server = "127.0.0.1";
    char *user = "user";
    char *password = "user";
    char *database = "test";

    // Créer un socket de communication
    descripteurSocket = socket(PF_INET, SOCK_DGRAM, 0);
    // Vérifier la valeur renvoyée par l’appel système socket()
    if (descripteurSocket < 0) {
        perror("socket");
        exit(-1);
    }
    printf("Socket créée avec succès ! (%d)\n", descripteurSocket);

    // Préparer l’adresse d’attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&pointDeRencontreLocal, 0x00, longueurAdresse);
    pointDeRencontreLocal.sin_family = PF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
    pointDeRencontreLocal.sin_port = htons(PORT);

    // Demander l’attachement local de la socket
    if ((bind(descripteurSocket, (struct sockaddr *)&pointDeRencontreLocal, longueurAdresse)) < 0) {
        perror("bind");
        exit(-2);
    }
    printf("Socket attachée avec succès !\n");

    // Connexion à la base de données MySQL
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    while(1) { // Boucle infinie pour continuer à recevoir les données
        // Réception d’un message du client
        lus = recvfrom(descripteurSocket, messageRecu, sizeof(messageRecu), 0, (struct sockaddr *)&pointDeRencontreDistant, &longueurAdresse);
        switch (lus) {
            case -1: /* une erreur ! */
                perror("recvfrom");
                close(descripteurSocket);
                mysql_close(conn); // Fermer la connexion MySQL en cas d'erreur
                exit(-3);
            case 0:
                fprintf(stderr, "Aucune donnée n’a été reçue !\n\n");
                break;
            default: /* réception de n octets */
                printf("Message %s reçu avec succès(%d octets)\n\n", messageRecu, lus);

                // Parsez les données reçues (séparées par des virgules)
                char *token;
                token = strtok(messageRecu, ",");
                int idES, numModule, numEntree, numSortie, ETAT;
                sscanf(token, "%d", &idES);
                token = strtok(NULL, ",");
                sscanf(token, "%d", &numModule);
                token = strtok(NULL, ",");
                sscanf(token, "%d", &numEntree);
                token = strtok(NULL, ",");
                sscanf(token, "%d", &numSortie);
                token = strtok(NULL, ",");
                sscanf(token, "%d", &ETAT);

                // Construire la requête SQL d'insertion avec la date et l'heure actuelles
                char query[1000];
                sprintf(query, "INSERT INTO test (idES, dateHeure, numModule, numEntree, numSortie, ETAT) VALUES (%d, NOW(), %d, %d, %d, %d)",
                        idES, numModule, numEntree, numSortie, ETAT);

                // Exécutez la requête SQL
                if (mysql_query(conn, query)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    exit(1);
                }
                printf("Données insérées avec succès dans la base de données.\n");

                break;
        }
    }

    // Fermer la connexion MySQL et la ressource avant de quitter (ce code ne sera jamais atteint dans cette configuration)
    mysql_close(conn);
    close(descripteurSocket);
    return 0;
}
