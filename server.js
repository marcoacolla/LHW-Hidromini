const express = require('express');
const path = require('path'); // Módulo para lidar com caminhos de diretórios

const app = express();
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

    dc_cur: 0 
};

app.post('/api/variables', (req, res) => {
    const newVariables = req.body;

    variables = { ...variables, ...newVariables };

    console.log(`Valor recebido:`, variables);
    res.json(variables); // Retorna o valor atualizado
});

// Nova rota GET para obter o valor atual
app.get('/api/variables', (req, res) => {
    res.json(variables); // Retorna o valor armazenado
});

app.listen(port, () => {
    console.log(`Servidor rodando em http://localhost:${port}`);
});