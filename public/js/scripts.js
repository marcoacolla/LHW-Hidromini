 // Função para atualizar o valor na página
 function atualizarValor(valor) {
    document.getElementById('pressure_1').textContent = valor + " Bar";
}

// Função para buscar o valor atualizado do servidor via GET
async function obterValorAtualizado() {
    try {
        const response = await fetch('/api/valor', {
            method: 'GET', // Muda o método para GET
        });

        if (response.ok) {
            const data = await response.json();
            atualizarValor(data.valor);
        } else {
            console.error('Falha ao receber o valor:', response.statusText);
        }
    } catch (error) {
        console.error('Erro na requisição:', error);
    }
}

// Chama a função para buscar o valor atualizado quando a página é carregada
obterValorAtualizado();

// Se quiser verificar o valor em intervalos regulares, use setInterval
setInterval(obterValorAtualizado, 5000); // Checa a cada 5 segundos