const socket = new WebSocket('ws://10.0.0.181:3000');


 // Função para atualizar o valor na página
 function updateVariables(resp_data) {
    document.getElementById('pressure1').textContent = resp_data.pressure1 + " Bar";
    document.getElementById('pressure2').textContent = resp_data.pressure2 + " Bar";
    document.getElementById('pressure3').textContent = resp_data.pressure3 + " Bar";

    document.getElementById('motor_rpm').textContent = resp_data.motor_rpm + " RPM";
    document.getElementById('gen_rpm').textContent = resp_data.gen_rpm + " RPM";

    document.getElementById('dc_cur').textContent = resp_data.dc_cur + " RPM";
    
}

socket.onmessage = function(event) {
    const data = JSON.parse(event.data);
    updateVariables(data);
};

// Se o WebSocket fechar
socket.onclose = function() {
    console.error('Conexão WebSocket fechada');
};