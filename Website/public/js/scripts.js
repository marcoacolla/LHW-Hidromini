const socket = new WebSocket('ws://10.0.0.181:3000');


 // Função para atualizar o valor na página
    function updateVariables(resp_data) {
        document.getElementById('pressure1').textContent = resp_data.pressure1.value + " Bar";
        document.getElementById('pressure2').textContent = resp_data.pressure2.value + " Bar";
        document.getElementById('pressure3').textContent = resp_data.pressure3.value + " Bar";

        document.getElementById('motor_rpm').textContent = resp_data.motor_rpm.value + " RPM";
        document.getElementById('gen_rpm').textContent = resp_data.gen_rpm.value + " RPM";

        document.getElementById('dc_cur').textContent = resp_data.dc_cur.value + " A";
        document.getElementById('dc_volt').textContent = resp_data.dc_volt.value + " V";
 }
 function updateValves(resp_data) {
    // Supondo que o número de válvulas seja conhecido ou esteja em resp_data
    const numValves = 2; // Substitua pelo número total de válvulas

    for (let i = 1; i <= numValves; i++) {
        const valveId = `valve${i}`;
        const valveElement = document.getElementById(valveId);
        
        // Acessa a propriedade da válvula no resp_data dinamicamente
        const valveState = resp_data[valveId];
        
        if (valveState === false) {
            valveElement.textContent = "CLOSED";
            valveElement.style.backgroundColor = '#AD3C1C';
        } else {
            valveElement.textContent = "OPEN";
            valveElement.style.backgroundColor = '#1CAD84';
        }
    }
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
    updateValves(data);
};

// Se o WebSocket fechar
socket.onclose = function() {
    console.error('Conexão WebSocket fechada');
};