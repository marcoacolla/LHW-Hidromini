const socket = new WebSocket('ws://10.0.0.181:3000');


 // Função para atualizar o valor na página
 function updateVariables(resp_data) {
    document.getElementById('pressure1').textContent = resp_data.pressure1 + " Bar";
    document.getElementById('pressure2').textContent = resp_data.pressure2 + " Bar";
    document.getElementById('pressure3').textContent = resp_data.pressure3 + " Bar";

    document.getElementById('motor_rpm').textContent = resp_data.motor_rpm + " RPM";
    document.getElementById('gen_rpm').textContent = resp_data.gen_rpm + " RPM";

    document.getElementById('dc_cur').textContent = resp_data.dc_cur + " A";
    
}

function updateTime() {
    var now = new Date();
    var datetime = now.getDate().toString().padStart(2, '0') + '/' + (now.getMonth()+1).toString().padStart(2, '0') + '/' + now.getFullYear() + ' ' + now.getHours().toString().padStart(2, '0') + ':' + now.getMinutes().toString().padStart(2, '0') + ':' + now.getSeconds().toString().padStart(2, '0');
    document.getElementById('update_time').textContent = datetime;
}



socket.onmessage = function(event) {
    const data = JSON.parse(event.data);
    updateTime();
    updateVariables(data);
};

// Se o WebSocket fechar
socket.onclose = function() {
    console.error('Conexão WebSocket fechada');
};