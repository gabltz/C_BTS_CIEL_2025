/***********************************************************************
 *    
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 **********************************************************************
 */




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

// debut code LS
#define  NBR_ETAT_AUTOM  6   // nombre d'etats dans l'automate
#define  NBR_TRANSITION  6   // nombre de transition 
// fin code LS

MYSQL  *conn; // Objet de connexion MySQL
char   *server   = "127.0.0.1";
char   *user     = "user";
char   *password = "user";
char   *database = "test";


void klaxon(){
    int sockfd;
    struct sockaddr_in servaddr;

    // Création et initialisation du socket d'envoi : 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'accès au serveur via la socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5001);
    if (inet_pton(AF_INET, "172.18.30.38", &servaddr.sin_addr) <= 0){
        perror("Adresse IP non-valide.");
        exit(EXIT_FAILURE);
    }

    // Envoi sur le socket des valeurs afin d'actionner le klaxon
    const char *message = "1,1,1";
    if (sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("Erreur lors de l'envoi des données sur le socket.");
        exit(EXIT_FAILURE);
    }

    printf("Données envoyées sur le socket.");

    close(sockfd);
}


void envoiEtaAutomateSurBDD(int);



int main() {
    int    descripteurSocket;
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreDistant;
    socklen_t longueurAdresse;
    char   messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
    int    lus; /* nb d’octets lus */


    // debut code LS==================================================
    int etatAutomate = 0;   // variable contenant l'etat de l'automate
    
        // verticalement: les transistion,  horizontalement les les etats
    int automate[NBR_ETAT_AUTOM][NBR_TRANSITION]={{1,0,0,0,0,0},
                                                 {1,2,1,1,1,1},
                                                 {2,2,3,2,2,2},
                                                 {3,3,3,4,3,3},
                                                 {4,4,4,4,5,4},
                                                 {5,5,5,5,5,0}};
    // fin code LS ===================================================



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
                int numModule = 0;
                int numEntree = 0;
                int numSortie = 0;
                int ETAT      = 0;
                
                sscanf(token, "%d", &numModule);
                token = strtok(NULL, ",");
                sscanf(token, "%d", &numEntree);
                token = strtok(NULL, ",");
                sscanf(token, "%d", &numSortie);
                token = strtok(NULL, ",");
                sscanf(token, "%d", &ETAT);

                // Construire la requête SQL d'insertion avec la date et l'heure actuelles
                char query[1000];
                sprintf(query, "INSERT INTO test (dateHeure, numModule, numEntree, numSortie, ETAT) VALUES (NOW(), %d, %d, %d, %d)",
                        numModule, numEntree, numSortie, ETAT);

                // Exécutez la requête SQL
                if (mysql_query(conn, query)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    exit(1);
                }
                printf("Données insérées avec succès dans la base de données.\n");



                //===== DEBUT DE TRAITEMENT ============================
/*
 * il sagit ici de traiter l'automatisation du focntionnement
 * la variable etatAutomate contient l'etat de l'automate initialisé à 0
 * 
 * 
 * 
 */
                etatAutomate = automate[etatAutomate][numModule]; // si l'on a le bon module (la bonne transition, on passe à l'etatAutomate suivant

                // ecrire dans la table ETATAUTOMATE à l'id 1 l'etat de l'automate soit: 0
                // ce qui va produire l'affichage en HTML PHP des consigne pour les jouenrs
                envoiEtaAutomateSurBDD(2);


                  
                // en fonction de l'état on active ou desactive les sorties.  
                switch(etatAutomate)
                {

              // lancement du jeu
                  case 0:  // etat d'attente avant de lancer le jeu.
                    // Mettre tourtes les sortie à off.
                    // afficher l'ecran d'accueil " "vous etes dans l'escape game...."
                    // on demare le chirono
                    // klaxon 0,2 s
                    
                    
                  break;      

              // START  de l'animateur

                  case 1:  //  On attend la reponse du module 1
                           // affichage de l'emplacement de l'objet à trouver
                           // affichage de l'objectif                      
                           
                           klaxon();  // envoi la commande pour un coup de klaxon
                  break;      

                           
              // module 2 reçu

                  case 2:  //  On attend la reponse du module 2
                           // affichage de l'emplacement de l'objet à trouver
                           // affichage de l'objectif                      
                           klaxon();  // envoi la commande pour un coup de klaxon
                  break;      

              // module 3 reçu

                  case 3:  //  On attend la reponse du module 3
                           // affichage de l'emplacement de l'objet à trouver
                           // affichage de l'objectif                      
                           klaxon();  // envoi la commande pour un coup de klaxon
                  break;      
                  
              // module 4 recu  

                  case 4:  //  On attend la reponse du module 4
                           // affichage de l'emplacement de l'objet à trouver
                           // affichage de l'objectif                      
                           klaxon();  // envoi la commande pour un coup de klaxon
                  break;      

              // Fin de l'escape Game

                  case 5:  //  On attend le rearmement pour une nouvelle partie
                           // affichage de l'emplacement de l'objet à trouver
                           // affichage de l'objectif                      
                           klaxon();  // envoi la commande pour un coup de klaxon
                  break;      

                  default:
                    
                    printf("\n\n    >>>>>>>>>>>>>>>>  Erreur dans le numéro d'etatAutomate\n\n");
                  break;      

                }
                  
                  
                  





                //===== FIN DE TRAITEMENT ==============================

                break;
        }
    }

    // Fermer la connexion MySQL et la ressource avant de quitter (ce code ne sera jamais atteint dans cette configuration)
    mysql_close(conn);
    close(descripteurSocket);
    return 0;
}
/*
int retourneEtat(int numModule)
{
//    automate[NBR_ETAT_AUTOM,NBBR_TRANSITION]
            
    
}*/

//======================================================================
// MET à jour ETATAUTOMATE le n° de l'etat actif
void envoiEtaAutomateSurBDD(int monEtatAutom)
{
    char query[1000];
      //sprintf(query, "INSERT INTO ETATAUTOMAE (dateHeure, numModule, numEntree, numSortie, ETAT) VALUES (NOW(), %d, %d, %d, %d)",   rtie, ETAT);
     sprintf(query,  "UPDATE 'ETEAUTOMATE SET etatAutomate ='%d'  WHERE repere = 0;", monEtatAutom); 
 
 
    // Exécutez la requête SQL
    if (mysql_query(conn, query)) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}
//======================================================================


