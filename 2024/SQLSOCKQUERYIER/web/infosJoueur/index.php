<?php

// Connexion à la base de données
$servername = "172.18.30.150"; // ou l'adresse IP de ton serveur MySQL
$username = "user"; // ton nom d'utilisateur MySQL
$password = "user"; // ton mot de passe MySQL
$dbname = "test"; // le nom de ta base de données

// Création de la connexion
$conn = new mysqli($servername, $username, $password, $dbname);

// Vérification de la connexion
if ($conn->connect_error) {
    die("La connexion a échoué: " . $conn->connect_error);
}

// Fonction pour envoyer un message sur le socket UDP
function sendMessage($message) {
    $socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
    socket_sendto($socket, $message, strlen($message), 0, '172.18.30.155', 5001);
    socket_close($socket);
}

// Fonction pour récupérer l'état d'une épreuve
function getEtat($numModule) {
    global $conn;
    $sql = "SELECT etat FROM progress WHERE numModule = $numModule";
    $result = $conn->query($sql);
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        return $row["etat"];
    } else {
        return null;
    }
}

// Fonction pour afficher la popup et passer à l'épreuve suivante
function afficherPopup($numEpreuveSuivante, $enigme) {
    echo "<script>";
    echo "alert('Félicitations pour avoir passé l'épreuve n°$numEpreuveSuivante!');";
    echo "setTimeout(function() { window.location.href = 'page.php?epreuve=$numEpreuveSuivante'; }, 5000);";
    echo "</script>";
    echo "<p>$enigme</p>";
}

// Fonction principale pour afficher l'épreuve et gérer la progression
function afficherEpreuve($numEpreuve, $enigme) {
    $numModule = $numEpreuve; // Les numéros d'épreuve commencent à 1, alors que les numéros de module commencent à 0 dans la base de données

    // Tant que l'épreuve n'est pas validée, on affiche l'épreuve actuelle
    while (getEtat($numModule) != 1) {
        echo "<p>Épreuve n°$numEpreuve en cours...</p>";
        sleep(1); // On vérifie toutes les secondes si l'épreuve est validée
    }

    // Une fois que l'épreuve est validée, on envoie le message sur le socket UDP et affiche la popup pour passer à l'épreuve suivante
    sendMessage("1,1,1");
    afficherPopup($numEpreuve + 1, $enigme);
}

// Appel de la fonction pour afficher chaque épreuve
afficherEpreuve(1, "Énigme de l'épreuve 2");
afficherEpreuve(2, "Énigme de l'épreuve 3");
afficherEpreuve(3, "Énigme de l'épreuve 4");
afficherEpreuve(4, "Énigme de l'épreuve 5");
afficherEpreuve(5, "Félicitations, vous avez terminé toutes les épreuves!");

// Fermeture de la connexion à la base de données
$conn->close();

?>
