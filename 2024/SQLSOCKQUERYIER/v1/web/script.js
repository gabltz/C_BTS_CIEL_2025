 // Fonction pour charger les données de la base de données et les afficher
 function loadData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("data-table").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "index.php", true);
    xhttp.send();
}

// Charger les données initiales
loadData();

// Actualiser toutes les 2 secondes
setInterval(function() {
    loadData();
}, 5000);
