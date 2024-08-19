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

let variables = {
    pressure1: 0,
    pressure2: 0,
    pressure3: 0,

    motor_rpm: 0,
    gen_rpm: 0,

    dc_cur: 0,
    dc_volt: 0,

    valve1: true,
    valve2: true
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
    variables = { ...variables, ...req.body };
    console.log('Variáveis atualizadas:', variables);

    // Envia as variáveis atualizadas para todos os clientes conectados via WebSocket
    broadcast(variables);

    res.json(variables);
});

// Rota GET para obter o estado atual das variáveis
app.get('/api/sensors', (req, res) => {
    res.json(variables);
});

// Servidor WebSocket para comunicação em tempo real
wss.on('connection', ws => {
    ws.send(JSON.stringify(variables)); // Envia os valores atuais quando um cliente se conecta
});

server.listen(port, () => {
    console.log(`Servidor rodando em http://localhost:${port}`);
})