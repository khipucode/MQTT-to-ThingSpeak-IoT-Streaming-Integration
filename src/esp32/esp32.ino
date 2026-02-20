#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h> // Obrigatório para HiveMQ Cloud (Porta 8883)
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

// ==== CONFIGURAÇÕES WI-FI ====
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ==== CONFIGURAÇÕES MQTT (HIVEMQ CLOUD) ====
const char* MQTT_BROKER    = "6e30ed916c6c44668c70e7d2351cd0c1.s1.eu.hivemq.cloud";
const int   MQTT_PORT      = 8883; // Porta Segura (SSL)
const char* MQTT_CLIENT_ID = "ESP32_HiveMQ_Client_01"; // ID único
const char* MQTT_USER      = "aluno_iot";
const char* MQTT_PASS      = "123456IoT";

WiFiClientSecure espClient; // Cliente Seguro para SSL
PubSubClient client(espClient);

// ==== HARDWARE ====
#define DHTPIN 15
#define DHTTYPE DHT22
#define PIR_PIN 13
#define LED_COOLER 2

// Endereço I2C do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

// ==== TÓPICOS (Mantidos conforme solicitado) ====
const char* topicTemp = "fiap/datacenter/rack01/temperatura";
const char* topicHum  = "fiap/datacenter/rack01/umidade";
const char* topicMov  = "fiap/datacenter/rack01/alerta_presenca";
const char* topicCmd  = "fiap/datacenter/rack01/cooler/comando";

unsigned long lastMsg = 0;

// Função auxiliar para escrever no LCD
void showLCD(String linha0, String linha1) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha0);
  lcd.setCursor(0, 1);
  lcd.print(linha1);
}

void setup_wifi() {
  delay(100);
  showLCD("PROJETO HIVEMQ", "INICIANDO...");
  delay(2000);
  Serial.print("Conectando WiFi");
  showLCD("Conectando WiFi", "Aguarde...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!");
  showLCD("WiFi OK!", "IP Obtido");
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  
  Serial.print("MSG Recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(msg);

  showLCD("CMD HiveMQ:", "Processando...");

  // Verifica se o tópico é o de comando
  if (String(topic) == topicCmd) {
    
    // Procura "ON" ou "OFF" na mensagem
    if (msg.indexOf("ON") >= 0) {
      digitalWrite(LED_COOLER, HIGH);
      Serial.println(">> ATUADOR: LIGADO (Via HiveMQ)");
      showLCD("STATUS:", "COOLER ON");
    } 
    else if (msg.indexOf("OFF") >= 0) {
      digitalWrite(LED_COOLER, LOW);
      Serial.println(">> ATUADOR: DESLIGADO (Via HiveMQ)");
      showLCD("STATUS:", "COOLER OFF");
    }
  }
  delay(2000); 
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao HiveMQ Cloud...");
    showLCD("Conectando", "HiveMQ Cloud...");
    
    // Gera um Client ID aleatório para evitar conflitos se reiniciar rápido
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Tenta conectar
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
      Serial.println("Conectado!");
      showLCD("HiveMQ Online!", "Aguardando...");
      
      // Assina o tópico de comando
      client.subscribe(topicCmd);
      delay(1000);
    } else {
      Serial.print("Falha rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s");
      showLCD("Erro Conexao", "Retentando...");
      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(115200);
  
  pinMode(LED_COOLER, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();

  setup_wifi();

  // IMPORTANTE: Permite conexão SSL sem verificar certificado (Ideal para Wokwi/Testes)
  espClient.setInsecure(); 

  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  
  // Intervalo de envio (4 segundos)
  //if (now - lastMsg > 4000) {
  if (now - lastMsg > 4000) {
    lastMsg = now;
    
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    int movimento = digitalRead(PIR_PIN);

    if (!isnan(t) && !isnan(h)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.printf("T:%.1fC H:%.0f%%", t, h);
      
      lcd.setCursor(0, 1);
      if (movimento) lcd.print("MOVIMENTO!    ");
      else           lcd.print("Ambiente OK   ");

      // Publica nos tópicos originais
      client.publish(topicTemp, String(t).c_str());
      client.publish(topicHum, String(h).c_str());
      
      Serial.printf("Enviado HiveMQ -> T: %.1f, H: %.1f\n", t, h);
      
      // Feedback visual (piscada no canto do LCD)
      lcd.setCursor(15, 0); 
      lcd.print("*"); 
      delay(200);
      lcd.setCursor(15, 0); 
      lcd.print(" ");

      if (movimento == HIGH) {
        client.publish(topicMov, "1");
        Serial.println(">> ALERTA DE SEGURANÇA ENVIADO");
        showLCD("ALERTA CRITICO", "INVASAO DETECT.");
        delay(1500); 
      }
    }
  }
}
