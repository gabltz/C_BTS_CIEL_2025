// Définition d'une fonction pour rafraîchir la page toutes les 2 secondes
function rafraichirPage() {
    setTimeout(function() {
        // Actualiser la page
        location.reload();
    }, 2000); // 2000 milliseconds = 2 secondes
}

// Appeler la fonction pour la première fois
rafraichirPage();
