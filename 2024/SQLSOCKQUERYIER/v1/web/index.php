<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./styles.css">
    <title>BDD Semaine Projet</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <header>
    <h1>Données de la base de données</h1>
    </header>
    <button id="deleteButton">Supprimer toutes les données</button>

    <?php
    $mysqli = new mysqli("127.0.0.1", "user", "user", "test");

    // Vérifier la connexion
    if ($mysqli->connect_error) {
        die("Erreur de connexion à la base de données: " . $mysqli->connect_error);
    }

    // Requête SQL pour sélectionner les données
    $sql = "SELECT idES, dateHeure, numModule, numEntree, numSortie, ETAT FROM test";
    $result = $mysqli->query($sql);

    // Vérifier si la requête a réussi
    if ($result->num_rows > 0) {
        // Afficher les données dans un tableau
        echo "<table border='1'>";
        echo "<tr><th>idES</th><th>dateHeure</th><th>numModule</th><th>numEntree</th><th>numSortie</th><th>ETAT</th></tr>";
        while($row = $result->fetch_assoc()) {
            echo "<tr><td>".$row["idES"]."</td><td>".$row["dateHeure"]."</td><td>".$row["numModule"]."</td><td>".$row["numEntree"]."</td><td>".$row["numSortie"]."</td><td>".$row["ETAT"]."</td></tr>";
        }
        echo "</table>";
    } else {
        echo "Aucun résultat trouvé";
    }

    // Fermer la connexion
    $mysqli->close();
    ?>

    <script src='./refresh.js'></script>
    <br></br>
    <br></br>
    <footer>
        <p>© 2024 - BTS CIEL 2025 - Semaine projet semaine 8</p>
    </footer>
    <script>
        $(document).ready(function () {
            $("#deleteButton").click(function () {
                if (confirm("Voulez-vous vraiment supprimer toutes les données ?")) {
                    $.ajax({
                        url: './delete_data.php', // Fichier PHP pour le traitement de la suppression
                        type: 'POST',
                        success: function (response) {
                            location.reload(); // Rechargement de la page après suppression
                        }
                    });
                }
            });
        });
    </script>
</body>

</html>
