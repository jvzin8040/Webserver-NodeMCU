#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "wifi_utils.h"
#include "captive_portal.h"

ESP8266WebServer server(80);

#define LED_PIN LED_BUILTIN // LED onboard do NodeMCU

void blinkLed(int times = 1, int delayMs = 100) {
    for(int i = 0; i < times; i++) {
        digitalWrite(LED_PIN, LOW);   // Acende (inverter se necessário)
        delay(delayMs);
        digitalWrite(LED_PIN, HIGH);  // Apaga
        delay(delayMs);
    }
}

void setup() {
    Serial.begin(115200);
    delay(3000);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // Garante LED apagado (inverter se necessário)

    if (!SPIFFS.begin()) {
        Serial.println("Erro ao montar o SPIFFS!");
        return;
    }

    // Tenta conectar nas redes salvas
    auto wifiList = loadWifiList();
    bool connected = tryConnectAllNetworks(wifiList);

    if (!connected) {
        Serial.println("Nenhuma rede encontrada. Iniciando Captive Portal.");
        startCaptivePortal(server);
        // Aguarda cadastro de nova rede
        while (true) {
            server.handleClient();
            delay(10);
        }
    }

    Serial.println("Conectado ao Wi-Fi");
    Serial.print("IP do NodeMCU: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, []() {
        blinkLed(3, 80); // Pisca 3 vezes toda vez que alguém acessa "/"
        File file = SPIFFS.open("/index.html", "r");
        
        if (file) {
            server.streamFile(file, "text/html");
            file.close();
        } else {
            server.send(404, "text/plain", "Arquivo não encontrado");
        }
    });

    server.begin();
    Serial.println("Servidor iniciado!");
}

void loop() {
    server.handleClient();
}
