const express = require('express');
const path = require('path'); // Módulo para lidar com caminhos de diretórios

const app = express();
const port = 3000;

// Configura o Express para servir arquivos estáticos da pasta "public"
app.use(express.static(path.join(__dirname, 'public')));

app.use(express.json());

let valorRecebido = 0; // Valor inicial

app.post('/api/valor', (req, res) => {
    valorRecebido = req.body.valor; // Atualiza o valor recebido
    console.log(`Valor recebido: ${valorRecebido}`);
    res.json({ valor: valorRecebido }); // Retorna o valor atualizado
});

// Nova rota GET para obter o valor atual
app.get('/api/valor', (req, res) => {
    res.json({ valor: valorRecebido }); // Retorna o valor armazenado
});

app.listen(port, () => {
    console.log(`Servidor rodando em http://localhost:${port}`);
});