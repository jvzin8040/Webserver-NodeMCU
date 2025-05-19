#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "wifi_utils.h"
#include <FS.h>
#include <ESP8266mDNS.h>

void startCaptivePortal(ESP8266WebServer& server) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Jvzin_NodeMCU", "662607015");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // Servir página captive.html
    server.on("/", HTTP_GET, [&server]() {
        File file = SPIFFS.open("/captive.html", "r");
        if (file) {
            server.streamFile(file, "text/html");
            file.close();
        } else {
            server.send(500, "text/plain", "Erro ao carregar captive.html");
        }
    });

    // Servir CSS separado
    server.on("/captiveStyle.css", HTTP_GET, [&server]() {
        File file = SPIFFS.open("/captiveStyle.css", "r");
        if (file) {
            server.streamFile(file, "text/css");
            file.close();
        } else {
            server.send(404, "text/plain", "CSS não encontrado");
        }
    });

    server.on("/save", HTTP_POST, [&server]() {
        if (server.hasArg("ssid") && server.hasArg("password")) {
            String ssid = server.arg("ssid");
            String password = server.arg("password");
            if (addWifiCredential(ssid, password)) {
                server.send(200, "text/html", "<h3>Salvo! O dispositivo irá reiniciar.</h3>");
                delay(500); // Garante que o navegador recebe a resposta
                ESP.restart();
            } else {
                server.send(500, "text/html", "Erro ao salvar.");
            }
        } else {
            server.send(400, "text/html", "Dados inválidos.");
        }
    });

    server.begin();
}