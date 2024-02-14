#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mariadb/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "172.18.30.169";
    char *user = "remote"; // Utilisateur de la base de données
    char *password = "remote"; // Mot de passe de la base de données
    char *database = "tp_bdd"; // Nom de la base de données

    conn = mysql_init(NULL);

    // Connexion à la base de données
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Demander à l'utilisateur d'entrer la requête SQL
    char query[1000];
    printf("Entrez votre requête SQL : ");
    fgets(query, sizeof(query), stdin);

    // Supprimer le saut de ligne à la fin de la requête
    int len = strlen(query);
    if (query[len - 1] == '\n')
        query[len - 1] = '\0';

    // Exécution de la requête SQL
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Récupération et affichage des résultats
    res = mysql_use_result(conn);
    if (res) {
        while ((row = mysql_fetch_row(res)) != NULL) {
            for (int i = 0; i < mysql_num_fields(res); i++) {
                printf("%s ", row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
        mysql_free_result(res);
    }

    // Fermeture de la connexion
    mysql_close(conn);

    return 0;
}
