<h1>🌐 Webserver com NodeMCU (ESP8266)</h1>
<p>Este projeto demonstra como criar um servidor web utilizando o microcontrolador <strong>NodeMCU ESP8266</strong>, permitindo o controle de dispositivos conectados via Wi-Fi através de uma interface web.</p>

<h2>🧰 Requisitos</h2>
<ul>
    <li><strong>Placa:</strong> NodeMCU ESP8266</li>
    <li><strong>IDE:</strong> Arduino IDE (versão 1.8.x ou superior)</li>
    <li><strong>Bibliotecas:</strong>
        <ul>
          <li>ESP8266WiFi</li>
          <li>ESPAsyncWebServer</li>
          <li>SPIFFS (para armazenamento de arquivos)</li>
        </ul>
    </li>
</ul>

<h2>🛠️ Configuração do Ambiente</h2>
<h3>1. Instalar o Suporte ao ESP8266 na Arduino IDE</h3>
<ol>
    <li>Abra a Arduino IDE.</li>
    <li>Vá em <strong>Arquivo > Preferências</strong>.</li>
    <li>Adicione o link: <code>http://arduino.esp8266.com/stable/package_esp8266com_index.json</code></li>
    <li>Vá em <strong>Ferramentas > Placa > Gerenciador de Placas</strong>, procure por <strong>esp8266</strong> e instale.</li>
</ol>

<h3>2. Selecionar a Placa e Porta Correta</h3>
<ul>
    <li>Vá em <strong>Ferramentas > Placa</strong> e selecione <strong>NodeMCU 1.0 (ESP-12E Module)</strong>.</li>
    <li>Em <strong>Ferramentas > Porta</strong>, selecione a porta COM correspondente ao seu dispositivo.</li>
</ul>

<h3>3. Carregar Arquivos para o Sistema de Arquivos SPIFFS</h3>
<ol>
    <li>Instale a ferramenta <strong>ESP8266 Sketch Data Upload</strong> (tutorial: <a href="https://www.youtube.com/watch?v=vgmZpv47Dj0">YouTube</a>).</li>
    <li>Organize seus arquivos web (ex: <code>index.html</code>, <code>style.css</code>) na pasta <strong>data</strong> do sketch Arduino.</li>
    <li>Use <strong>Ferramentas > ESP8266 Sketch Data Upload</strong> para enviar os arquivos.</li>
</ol>

<h3>4. Configurar o Wi-Fi no arquivo config.h</h3>
<ol>
    <li>Abra o arquivo <strong>config.h</strong> no seu projeto.</li>
    <li>Defina o nome da rede Wi-Fi (SSID) e a senha (PASSWORD) da sua rede:</li>
    <pre><code>#define WIFI_SSID "Seu_SSID"
#define WIFI_PASSWORD "Sua_Senha"
</code></pre>
    <li>Salve o arquivo.</li>
    <li>Remova do nome do arquivo o trecho <strong>"(removeMe)"</strong> e renomeie para <strong>config.h</strong></li>
</ol>

<h2>✅ Testando o Projeto</h2>
<ol>
    <li>Conecte o NodeMCU ao computador via USB.</li>
    <li>Envie o sketch <code>Webserver_NodeMCU.ino</code> para o dispositivo.</li>
    <li>Abra o Monitor Serial para obter o endereço IP.</li>
    <li>Acesse o IP no navegador para interagir com o webserver.</li>
</ol>
