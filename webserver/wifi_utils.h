#pragma once
#include <vector>
#include <Arduino.h>
#include <FS.h>

struct WifiCredential {
    String ssid;
    String password;
};

// Carrega lista de redes do arquivo no SPIFFS
std::vector<WifiCredential> loadWifiList(const char* filename = "/wifi_list.txt") {
    std::vector<WifiCredential> wifiList;
    File file = SPIFFS.open(filename, "r");
    if (!file) return wifiList;

    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim();
        int sep = line.indexOf(';');
        if (sep > 0) {
            WifiCredential cred;
            cred.ssid = line.substring(0, sep);
            cred.password = line.substring(sep + 1);
            wifiList.push_back(cred);
        }
    }
    file.close();
    return wifiList;
}

// Adiciona nova rede ao arquivo
bool addWifiCredential(const String& ssid, const String& password, const char* filename = "/wifi_list.txt") {
    File file = SPIFFS.open(filename, "a");
    if (!file) return false;
    file.println(ssid + ";" + password);
    file.close();
    return true;
}

// Tenta conectar em todas as redes da lista
bool tryConnectAllNetworks(const std::vector<WifiCredential>& wifiList, int maxTries = 10) {
    for (const auto& cred : wifiList) {
        WiFi.begin(cred.ssid.c_str(), cred.password.c_str());
        Serial.printf("Tentando conectar na rede: %s\n", cred.ssid.c_str());
        for (int i = 0; i < maxTries; ++i) {
            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("WiFi conectado!");
                return true;
            }
            delay(1000);
        }
        WiFi.disconnect();
    }
    return false;
}