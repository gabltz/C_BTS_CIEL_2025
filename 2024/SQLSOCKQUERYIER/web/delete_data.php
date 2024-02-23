<?php
$mysqli = new mysqli("127.0.0.1", "user", "user", "test");

// Vérifier la connexion
if ($mysqli->connect_error) {
    die("Erreur de connexion à la base de données: " . $mysqli->connect_error);
}

// Requête SQL pour supprimer toutes les données de la table
$sql = "DELETE FROM test";
if ($mysqli->query($sql) === TRUE) {
    echo "Données supprimées avec succès";
} else {
    echo "Erreur lors de la suppression des données: " . $mysqli->error;
}

// Fermer la connexion
$mysqli->close();
?>