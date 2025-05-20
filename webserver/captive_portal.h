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

    // Salvar credenciais e mostrar confirmação com CSS embutido
    server.on("/save", HTTP_POST, [&server]() {
        if (server.hasArg("ssid") && server.hasArg("password")) {
            String ssid = server.arg("ssid");
            String password = server.arg("password");
            if (addWifiCredential(ssid, password)) {
                // Página estilizada de confirmação (CSS embutido)
                server.send(200, "text/html",
                    "<html><head>"
                    "<meta charset='UTF-8'>"
                    "<meta name='viewport' content='width=device-width,initial-scale=1'>"
                    "<title>Wi-Fi Salvo</title>"
                    "<style>"
                    "body{min-height:100vh;margin:0;padding:0;display:flex;align-items:center;justify-content:center;font-family:'Segoe UI','Arial','Helvetica Neue',Arial,sans-serif;background:linear-gradient(120deg,#43cea2 0%,#185a9d 100%);} "
                    ".card{background:rgba(255,255,255,0.84);border-radius:22px;border:1.5px solid #e3e9f0;box-shadow:0 12px 48px 0 rgba(24,90,157,0.13),0 2px 8px #43cea225;max-width:380px;width:96vw;padding:2.2rem 2rem 2rem 2rem;display:flex;flex-direction:column;align-items:center;backdrop-filter:blur(2.5px);animation:fadeInPop 0.7s cubic-bezier(.39,.575,.565,1) both;} "
                    "@keyframes fadeInPop{0%{opacity:0;transform:scale(0.8) translateY(60px);}100%{opacity:1;transform:scale(1) translateY(0);}} "
                    "h3{text-align:center;margin-top:0;margin-bottom:2.1rem;color:#0e4e7a;letter-spacing:0.04em;font-size:1.8em;font-weight:800;text-shadow:0 2px 12px #185a9d22;} "
                    ".info{color:#0e4e7a;font-size:1em;text-align:center;margin-top:2rem;background:rgba(67,206,162,0.11);border-radius:10px;padding:0.9em 1em;box-shadow:0 1px 8px #185a9d19;width:100%;max-width:320px;}"
                    "</style>"
                    "</head><body>"
                    "<div class='card'>"
                    "<h3>Wi-Fi Configurado</h3>"
                    "<div class='info'>O dispositivo irá reiniciar em breve.</div>"
                    "</div>"
                    "</body></html>"
                );
                delay(1000); // Tempo para navegador mostrar estilização antes do reboot
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
