#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "config.h"  // Insira sua rede e senha no arquivo config.h

ESP8266WebServer server(80); 

void setup() {
  Serial.begin(115200);
  delay(3000);

  // Iniciar SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Erro ao montar o SPIFFS!");
    return;
  }
  Serial.println("SPIFFS iniciado com sucesso!");

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi");
  Serial.print("IP do NodeMCU: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    Serial.println("Acessando o arquivo /pagina.html");
    File file = SPIFFS.open("/pagina.html", "r");
    
    if (file) {
      Serial.println("Arquivo encontrado, enviando conteúdo...");
      server.streamFile(file, "text/html");
      file.close();
    } else {
      Serial.println("Erro: Arquivo não encontrado");
      server.send(404, "text/plain", "Arquivo não encontrado");
    }
  });

  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  server.handleClient();  
}
