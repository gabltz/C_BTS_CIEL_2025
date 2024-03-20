#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class Communication {
public:
    void envoyerTrame(const std::string& trame, const char* destinataireIP, int port) {
        // Initialisation de Winsock
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);
        int wsOK = WSAStartup(ver, &wsData);
        if (wsOK != 0) {
            std::cerr << "Impossible d'initialiser Winsock" << std::endl;
            return;
        }

        // Création du socket UDP
        SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sockfd == INVALID_SOCKET) {
            std::cerr << "Erreur lors de la création du socket" << std::endl;
            WSACleanup();
            return;
        }

        // Paramètres de l'adresse du destinataire
        sockaddr_in destAddr;
        destAddr.sin_family = AF_INET;
        destAddr.sin_port = htons(port);
        inet_pton(AF_INET, destinataireIP, &destAddr.sin_addr);

        // Envoi de la trame
        sendto(sockfd, trame.c_str(), trame.length(), 0, (sockaddr*)&destAddr, sizeof(destAddr));

        // Fermeture du socket et libération des ressources
        closesocket(sockfd);
        WSACleanup();
    }
};

int main() {
    Communication comm;
    std::string trame = "TEMP:25.5"; // Exemple de trame à envoyer
    const char* destinataireIP = "127.0.0.1"; // Adresse IP du destinataire
    int port = 5000; // Port sur lequel envoyer la trame

    comm.envoyerTrame(trame, destinataireIP, port);

    std::cout << "Trame envoyée avec succès." << std::endl;

    return 0;
}
