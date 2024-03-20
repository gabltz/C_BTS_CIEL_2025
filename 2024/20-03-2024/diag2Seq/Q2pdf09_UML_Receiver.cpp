#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class Communication {
public:
    std::string recevoirTrame(int port) {
        // Initialisation de Winsock
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);
        int wsOK = WSAStartup(ver, &wsData);
        if (wsOK != 0) {
            std::cerr << "Impossible d'initialiser Winsock" << std::endl;
            return "";
        }

        // Création du socket UDP
        SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sockfd == INVALID_SOCKET) {
            std::cerr << "Erreur lors de la création du socket" << std::endl;
            WSACleanup();
            return "";
        }

        // Liaison du socket à l'adresse locale
        sockaddr_in localAddr;
        localAddr.sin_family = AF_INET;
        localAddr.sin_port = htons(port);
        localAddr.sin_addr.S_un.S_addr = INADDR_ANY;

        if (bind(sockfd, (sockaddr*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR) {
            std::cerr << "Erreur lors de la liaison du socket" << std::endl;
            closesocket(sockfd);
            WSACleanup();
            return "";
        }

        // Réception de la trame
        char buffer[1024];
        sockaddr_in senderAddr;
        int senderAddrSize = sizeof(senderAddr);
        int bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer), 0, (sockaddr*)&senderAddr, &senderAddrSize);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Erreur lors de la réception de la trame" << std::endl;
            closesocket(sockfd);
            WSACleanup();
            return "";
        }

        // Fermeture du socket et libération des ressources
        closesocket(sockfd);
        WSACleanup();

        return std::string(buffer, bytesReceived);
    }
};

int main() {
    Communication comm;
    int port = 5000; // Port sur lequel écouter les trames

    std::string trame = comm.recevoirTrame(port);

    if (!trame.empty()) {
        std::cout << "Trame reçue : " << trame << std::endl;
    } else {
        std::cerr << "Aucune trame reçue." << std::endl;
    }

    return 0;
}
