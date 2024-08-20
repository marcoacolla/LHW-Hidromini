const express = require('express');
const path = require('path'); // Módulo para lidar com caminhos de diretórios
const http = require('http');
const WebSocket = require('ws');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });



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

function broadcast(data) {
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(data));
        }
    });
}

// Rota POST para atualizar uma ou mais variáveis
app.post('/api/sensors', (req, res) => {
    const novosDados = req.body;
    for (let key in novosDados) {
        if (measures.hasOwnProperty(key) && novosDados[key].hasOwnProperty('value')) {
            // Atualiza apenas o campo 'value'
            measures[key].value = novosDados[key].value;
        }
    }
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