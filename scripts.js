let numero = 0;

function atualizarContador() {
    numero++; // Incrementa o número
    document.getElementById('pressure_1').textContent = numero + " Bar"; // Atualiza o texto do elemento HTML
}

// Configura o intervalo para chamar a função a cada 1 segundo (1000 ms)
setInterval(atualizarContador, 1000);