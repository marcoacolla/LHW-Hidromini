#include <ESP8266WiFi.h>

// Substitua pelas suas credenciais de rede.
const char* ssid     = "LAB LHWC";
const char* password = "MOBILIDADELHWC";
float bar1 = 0.0;
float bar2 = 0.0;
float bar3 = 0.0;

float dcA = 0.0;
float dcV = 0.0;
float rpm = 0.0;
float rpmMotor = 0.0;
float facRead = 0.0;
float acV = 0.0;

// Defina um servidor com a porta 80.
WiFiServer server(80);

// Variável para armazenar a solicitação HTTP.
String header;

// Variável para armazenar o estado de saída atual.
String outputState = "Desligado";

unsigned long currentTime = millis();
unsigned long previousTime = 0;
// Defina um timeout de 2000 milisegundos.
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  delay(5000);
  // Conecte com a rede Wi-Fi com SSID e senha.
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  //Inicie o servidor.
  server.begin();
}

void loop() {
  // Leia dados da Serial do Arduino Mega
  if (Serial.available()) {
    String data = Serial.readString();
    sscanf(data.c_str(), "%f,%f,%f", &bar1, &bar2, &bar3);
  }

  WiFiClient client = server.available();   // Escute os clientes conectados 
  if (client) {                             // Se um novo cliente se conectar
    String currentLine = "";                // Faça uma String para armazenar dados recebidos do cliente
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop enquanto cliente estiver conectado.
      currentTime = millis();
      if (client.available()) {             // Se houver bytes para ler do cliente,
        char c = client.read();             // faça a leitura.
        header += c;
        if (c == '\n') {                    // Se o byte é um caractere de nova linha,                                // é o fim da solicitação HTML,entao envie uma resposta.
          if (currentLine.length() == 0) {  
            // Envie um cabeçalho HTTP de resposta.
            // Envie um cabeçalho HTTP de resposta.
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Pagina HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            // CSS para estilizar a pagina
            client.println("<style>");
            client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("h1 {font-weight: bold; color: #126e54; font-size: 32px;}");
            client.println(".container {display: flex; flex-wrap: wrap; justify-content: center;}");
            client.println(".button-container {display: flex; flex-direction: column; align-items: center; margin: 10px;}");
            client.println(".button { background-color: #1BAE85; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; width: 200px;}");
            client.println(".button-title {text-align: center; font-weight: bold; margin-bottom: 5px;}");
            client.println("#footer {margin-top: 20px; font-size: 16px; color: #555;}");
            client.println("</style></head>");

            client.println("<body><h1>HIDROmini Dados - Arduino Mega WiFi Web Server</h1>");
            client.println("<div class=\"container\">");

            // Botão 1
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Sensor de Pressao 1</p>");
            client.print("<button class=\"button\">");
            client.print(bar1);
            client.println(" Bar</button>");
            client.println("</div>");

            // Botão 2
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Sensor de Pressao 2</p>");
            client.print("<button class=\"button\">");
            client.print(bar2);
            client.println(" Bar</button>");
            client.println("</div>");

            // Botão 3
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Sensor de Pressao 3</p>");
            client.print("<button class=\"button\">");
            client.print(bar3);
            client.println(" Bar</button>");
            client.println("</div>");

            // Botão 4
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Frequencia da Turbina</p>");
            client.print("<button class=\"button\">");
            client.print(rpm);
            client.println(" RPM</button>");
            client.println("</div>");

            // Botão 5
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Frequencia do Gerador</p>");
            client.print("<button class=\"button\">");
            client.print(rpm * 1.258);
            client.println(" RPM</button>");
            client.println("</div>");

            // Botão 6
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Frequencia da Tensao Alternada</p>");
            client.print("<button class=\"button\">");
            client.print(facRead);
            client.println(" Hz</button>");
            client.println("</div>");

            // Botão 7
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Vmax da Tensao Alternada</p>");
            client.print("<button class=\"button\">");
            client.print(acV);
            client.println(" VAC</button>");
            client.println("</div>");

            // Botão 8
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Tensao DC</p>");
            client.print("<button class=\"button\">");
            client.print(dcV);
            client.println(" VDC</button>");
            client.println("</div>");

            // Botão 9
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Corrente DC</p>");
            client.print("<button class=\"button\">");
            client.print(dcA);
            client.println(" A</button>");
            client.println("</div>");

            // Botão 10
            client.println("<div class=\"button-container\">");
            client.println("<p class=\"button-title\">Potencia</p>");
            client.print("<button class=\"button\">");
            client.print(dcV * dcA);
            client.println(" W</button>");
            client.println("</div>");

            client.println("</div>"); // Fim do container

            // Rodapé com data e hora
            client.println("<div id=\"footer\"></div>");
            client.println("<script>");
            client.println("function updateTime() {");
            client.println("  var now = new Date();");
            client.println("  var datetime = now.getDate().toString().padStart(2, '0') + '/' + (now.getMonth()+1).toString().padStart(2, '0') + '/' + now.getFullYear() + ' ' + now.getHours().toString().padStart(2, '0') + ':' + now.getMinutes().toString().padStart(2, '0') + ':' + now.getSeconds().toString().padStart(2, '0');");
            client.println("  document.getElementById('footer').innerHTML = 'Pagina atualizada em: ' + datetime;");
            client.println("}");
            client.println("updateTime();");
            client.println("</script>");

            client.println("</body></html>");
            // A resposta HTTP termina com outra linha em branco.
            client.println();
            break;

          } else { // Se você recebeu uma nova linha, limpe currentLine
            currentLine = "";
          }
        }else if (c != '\r') {  // Se você tiver mais alguma coisa além de um caractere de retorno de carro,
          currentLine += c;      // Adicione-o ao final do currentLine.
        }
      }
      // Limpe a variável de cabeçalho
      header = "";
      // Feche a conexão.
      client.stop();
    }
  }
}
