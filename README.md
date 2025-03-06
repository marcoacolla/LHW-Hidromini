## Abrindo o Website

Para abrir o website a partir da pasta *source*, usa-se os seguintes comandos:

    cd Website
    node .\server.js

Se tudo estiver nos conformes, o terminal devolverá as seguintes mensagens:

    Servidor rodando em http://localhost:3000

Para acessar o site, basta entrar no [link devolvido](http://localhost:3000).

> Para acessar em qualquer dispositivo, é necessário estar na mesma rede Wi-Fi e conhecer o IP do computador host do website e acessar o URL no formato `http://[IpV4_host]:3000`
> 
> É possível saber o IPV4 do computador usando o comando `ipconfig` no `cmd`.

## Abrindo Servidor MQTT

Para que os dados do site sejam atualizados, é necessário que a Raspberry Pi esteja ligada e com o servidor de dados funcionando. Para fazer isso, siga os seguintes passos:

### Passo 1: Ligar a Raspi

Basta conectá-la na tomada ou em um computador através do cabo USB-C.

### Passo 2: Acessando a Raspi no computador

Acessar a Raspberry Pi pelo computador não é necessário, mas altamente recomendado. Isso porque é possível realizar todos os passos exclusivamente na Raspberry Pi com um teclado e mouse, mas é muito mais fácil e organizado realizar todos os comandos e acessar os logs no mesmo dispositivo.

Para acessar a Raspberry Pi, primeiro certifique-se de que o computador está na mesma rede que o dispositivo. 
> A rede configurada atualmente é a rede `LHW TERREO 2,4GHz`.

Abra o `cmd` e execute o comando:

    > ssh marcocolla@10.0.1.119
    marcocolla@10.0.1.119's password: 
    > onepiece
    
> 10.0.1.119 é o IPv4 da Raspberry Pi. Para verificar isso, deve-se conectar um teclado à ela e executar o comando `ifconfig`.

A resposta no terminal deve se parecer com isso:

    The programs included with the Debian GNU/Linux system are free software;
    the exact distribution terms for each program are described in the
    individual files in /usr/share/doc/*/copyright.
    
    Debian GNU/Linux comes with ABSOLUTELY NO WARRANTY, to the extent
    permitted by applicable law.
    Last login: Thu Nov 21 14:09:49 2024 from 10.0.0.181
    
    marcocolla@hidromini:~ $

### Passo 3: Abrindo o servidor

Esse documento visa esclarecer como acessar o servidor em um ambiente já configurado. Em caso de uma nova Raspberry Pi ainda não configurada, recomenda-se a criação de um ambiente virtual Python para a execução dos arquivos.

Para fazer tudo que é necessário na Raspberry Pi, execute os seguintes comandos:

    source ~/hidro_server/virtual_env/bin/activate
    cd ~/hidro_server/LHW-Hidromini/Raspi/
    python3 mini_server.py

Isso acessa o ambiente virtual, acessa o local dos arquivos e executa o arquivo do servidor. Se tudo estiver configurado como deve, o terminal deve responder com isso:

    MQTT to InfluxDB bridge
    Status Code: 200

Seguido de diversas respostas do ESP8266.