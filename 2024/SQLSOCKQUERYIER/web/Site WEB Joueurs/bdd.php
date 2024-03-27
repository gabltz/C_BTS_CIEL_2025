<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./bdd.css">
    <title>BDD Semaine Projet</title>
</head>
<header>
        <h1>ESCAPE GAME</h1>
</header>
<body>
<?php
// Connexion à la base de données
$servername = "localhost"; // ou l'adresse IP de votre serveur MySQL
$username = "user"; // votre nom d'utilisateur MySQL
$password = "user"; // votre mot de passe MySQL
$dbname = "test"; // le nom de votre base de données

try {
    $bdd = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    // Définir le mode d'erreur PDO à exception
    $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
    // Requête SQL pour récupérer la valeur de la colonne etatAutomate
    $sql = "SELECT etatAutomate FROM ETATAUTOMATE";
    $result = $bdd->query($sql);
    
    // Vérifier si des résultats ont été trouvés
    if ($result->rowCount() > 0) {
        // Boucler à travers les lignes de résultat
        while ($row = $result->fetch()) {
            // Récupérer la valeur de la colonne etatAutomate
            $etatAutomate = $row['etatAutomate'];
            
            // Faire quelque chose en fonction de la valeur de la colonne etatAutomate
            switch ($etatAutomate) {
                case 0:
                    echo "<p>Sur la table vous trouverez une boîte, ceci est la première énigme.
                          Trouvez le code pour passer à l'étape suivante (et vous rapprochez un peu plus de la liberté).</p>";
                    break;
                case 1:
                    echo "<p>Emplacement : Au coeur de la tour numérique, parmi les gardiens de données, une énigme se dissimule, attendant d'être découverte.</p>
                          <p style='color: #ff0000;'>Enigme : Le côté obscur trouble tout, la clef est la lumière.</p>";
                    break;
                case 2:
                    echo "<p>Emplacement : Sous la table, parmi les compagnons de carton, une énigme attend patiemment d'être dévoilée.</p>
                    <p style='color: #ff0000;'>Enigme : Quand je suis faible, je murmure à peine, mais quand je suis fort, je peux éteindre une flamme.
                            Je suis invisible, mais mon impact est palpable. Je permets de résoudre l’énigme en effectuant l’action, qui suis-je ? </p>";
                    break;
                case 3:
                    echo "<p>Emplacement : Au coin de la salle, parmi les ordinateurs muets et éteins, une boîte se cache discrètement, attendant son dénouement. </p>
                    <p style='color: #ff0000;'>Enigme : Je suis l’ennemi de la chaleur, mais je suis adoré par les pingouins. Qui suis-je ?</p>
                          <p>Une fois la réponse obtenue, vous trouverez votre outil pour résoudre cette énigme sous vos yeux.</p>";
                    break;
                case 4:
                    echo "<p>La toile tissée par vos esprits agiles a été traversée avec brio. La porte est désormais ouverte. Vous êtes libres de quitter ce royaume d’énigmes… pour l’instant. </p>";
                    break;
                default:
                    echo "<p>Initialisez la BDD à 0 pour pouvoir commencer l'escape game...</p>";
                    break;
            }
        }
    } else {
        echo "<p>Aucun résultat trouvé.</p>";
    }
} catch(PDOException $e) {
    echo "Erreur : " . $e->getMessage();
}

// Fermer la connexion à la base de données
$bdd = null;
?>
    
    <footer>
    <p style="font-size: 20px;" class="footer-text">© 2024 - BTS CIEL 2025 - Semaine projet S8</p>
</footer>
    <script src="./bdd.js"></script>
</body>
</html>