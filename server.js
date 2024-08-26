const fs = require('fs');
const express = require('express');
const path = require('path'); // Módulo para lidar com caminhos de diretórios
const http = require('http');
const WebSocket = require('ws');
const createCsvWriter = require('csv-writer').createObjectCsvWriter;

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

const csvFilePath = path.join(__dirname, 'CSV/sensor_measures.csv');

const port = 3000;

// Configura o Express para servir arquivos estáticos da pasta "public"
app.use(express.static(path.join(__dirname, 'public')));

app.use(express.json());


let measures = {
    "pressure1": {"value": 0.0},
    "pressure2": {"value": 0.0},
    "pressure3": {"value": 0.0},
    "motor_rpm": {"value": 0.0},
    "gen_rpm": {"value": 0.0},
    "dc_cur": {"value": 0.0},
    "dc_volt": {"value": 0.0},
    "valve1": {"value": false},
    "valve2": {"value": false}
};

// Configuração do CSV Writer
const csvWriter = createCsvWriter({
    path: csvFilePath,
    header: [
        {id: 'timestamp', title: 'Timestamp'},
        {id: 'pressure1', title: 'Pressure 1'},
        {id: 'pressure2', title: 'Pressure 2'},
        {id: 'pressure3', title: 'Pressure 3'},
        {id: 'motor_rpm', title: 'Motor RPM'},
        {id: 'gen_rpm', title: 'Generator RPM'},
        {id: 'dc_cur', title: 'DC Current'},
        {id: 'dc_volt', title: 'DC Voltage'},
        {id: 'valve1', title: 'Valve 1'},
        {id: 'valve2', title: 'Valve 2'}
    ],
    append: fs.existsSync(csvFilePath) // Adiciona dados ao final do arquivo existente
});

function broadcast(data) {
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(data));
        }
    });
}
function writeCSV(data){
    const timestamp = new Date().toISOString();
    const reg = {
        timestamp: timestamp,
        pressure1: data.pressure1.value,
        pressure2: data.pressure2.value,
        pressure3: data.pressure3.value,
        motor_rpm: data.motor_rpm.value,
        gen_rpm: data.gen_rpm.value,
        dc_cur: data.dc_cur.value,
        dc_volt: data.dc_volt.value,
        valve1: data.valve1.value,
        valve2: data.valve2.value
    };

    csvWriter.writeRecords([reg])
        .then(() => {
            console.log('Dados salvos no CSV com sucesso.');
        })
        .catch(err => {
            console.error('Erro ao salvar dados no CSV:', err);
        });
}

fs.unlink(csvFilePath,function(err){
    if(err) return console.log(err);
    console.log('file deleted successfully');
}); 

// Rota POST para atualizar uma ou mais variáveis
app.post('/api/sensors', (req, res) => {
    const novosDados = req.body;
    for (let key in novosDados) {
        if (measures.hasOwnProperty(key) && novosDados[key].hasOwnProperty('value')) {
            // Atualiza apenas o campo 'value'
            measures[key].value = novosDados[key].value;
        }
    }
    writeCSV(measures);
    broadcast(measures);

    res.json(measures);
});

// Rota GET para obter o estado atual das variáveis
app.get('/api/sensors', (req, res) => {
    res.json(measures);
});

// Servidor WebSocket para comunicação em tempo real
wss.on('connection', ws => {
    ws.send(JSON.stringify(measures)); // Envia os valores atuais quando um cliente se conecta
});

server.listen(port, () => {
    console.log(`Servidor rodando em http://localhost:${port}`);
})