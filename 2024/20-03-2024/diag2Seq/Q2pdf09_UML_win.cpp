#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

// Malheureux retour sur windaube après avoir cassé mon Linux (tuez moi.)

class Communication {
public:
    void envoyerTrame(const std::string& trame) {
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
        destAddr.sin_port = htons(5000);
        inet_pton(AF_INET, "127.0.0.1", &destAddr.sin_addr);

        // Envoi de la trame
        sendto(sockfd, trame.c_str(), trame.length(), 0, (sockaddr*)&destAddr, sizeof(destAddr));

        // Fermeture du socket et libération des ressources
        closesocket(sockfd);
        WSACleanup();
    }

    std::string recevoirTrame() {
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
        localAddr.sin_port = htons(5000);
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

class Thermometre {
private:
    double temperature;

    double genererTemperature() {
        // Génération d'une température aléatoire pour simulation
        return (rand() % 100) - 50; // Température entre -50°C et 50°C
    }

    std::string fabriquerTrame() {
        // Code pour fabriquer la trame avec une température réelle
        double temp = genererTemperature();
        return "TEMP:" + std::to_string(temp);
    }

    bool verifierTrame(const std::string& trame) {
        // Code pour vérifier la trame reçue
        // Par exemple, vérifier le format ou la signature
        // Dans cet exemple, on suppose que toute trame commençant par "TEMP:" est valide
        return trame.substr(0, 5) == "TEMP:";
    }

    double extraireTemperature(const std::string& trame) {
        // Code pour extraire la température de la trame
        // Dans cet exemple, on extrait la température après "TEMP:"
        double temp;
        try {
            temp = std::stod(trame.substr(5));
        } catch (...) {
            std::cerr << "Erreur lors de l'extraction de la température" << std::endl;
            temp = -1;
        }
        return temp;
    }

public:
    double acquerir() {
        std::string trame = fabriquerTrame();

        Communication comm;
        comm.envoyerTrame(trame);

        trame = comm.recevoirTrame();

        if (verifierTrame(trame)) {
            return extraireTemperature(trame);
        } else {
            std::cerr << "Erreur : Trame invalide" << std::endl;
            return -1; // Valeur d'erreur
        }
    }
};

int main() {
    srand(time(nullptr)); // Initialisation du générateur de nombres aléatoires
    Thermometre thermometre;
    double temperature = thermometre.acquerir();
    if (temperature != -1) {
        std::cout << "Température acquise : " << temperature << "°C" << std::endl;
    }
    return 0;
}
