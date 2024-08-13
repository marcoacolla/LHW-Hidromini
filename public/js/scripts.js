 // Função para atualizar o valor na página
 function updateVariables(resp_data) {
    document.getElementById('pressure1').textContent = resp_data.pressure1 + " Bar";
    document.getElementById('pressure2').textContent = resp_data.pressure2 + " Bar";
    document.getElementById('pressure3').textContent = resp_data.pressure3 + " Bar";

    document.getElementById('motor_rpm').textContent = resp_data.motor_rpm + " RPM";
    document.getElementById('gen_rpm').textContent = resp_data.gen_rpm + " RPM";

    document.getElementById('dc_cur').textContent = resp_data.dc_cur + " RPM";
    
}

// Função para buscar o valor atualizado do servidor via GET
async function getUpdatedValues() {
    try {
        const response = await fetch('/api/variables', {
            method: 'GET', // Muda o método para GET
        });

        if (response.ok) {
            const data = await response.json();
            updateVariables(data);
        } else {
            console.error('Falha ao receber o valor:', response.statusText);
        }
    } catch (error) {
        console.error('Erro na requisição:', error);
    }
}

// Chama a função para buscar o valor atualizado quando a página é carregada
getUpdatedValues();

// Se quiser verificar o valor em intervalos regulares, use setInterval
setInterval(getUpdatedValues, 5000); // Checa a cada 5 segundos