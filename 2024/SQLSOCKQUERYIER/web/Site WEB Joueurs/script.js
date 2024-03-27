document.addEventListener('DOMContentLoaded', function() {
    const timerElement = document.querySelector('.timer');

    let delay = 60000;

    const timerInterval = setInterval(function() {
        const minutes = Math.floor((delay / 1000) / 60);
        const seconds = Math.floor((delay / 1000) % 60);

        const formattedTime = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;

        timerElement.textContent = formattedTime;

        delay -= 1000;

        if (delay < 0) {
            clearInterval(timerInterval);
            window.location.href = './bdd.php';
        }
    }, 1000); 
});