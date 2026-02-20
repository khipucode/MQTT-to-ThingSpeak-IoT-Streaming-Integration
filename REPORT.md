# 🛡️ Sistema de Monitoramento IoT para Data Centers

## 📖 Sobre o Projeto

Este projeto apresenta um sistema de monitoramento ambiental e de segurança para data centers baseado em Internet das Coisas (IoT) utilizando ESP32, protocolo MQTT e integração com serviços em nuvem.

O sistema simula, através do ambiente Wokwi, o monitoramento de racks de servidores críticos, coletando dados ambientais e eventos de segurança física em tempo real. As informações são exibidas localmente em um display LCD e transmitidas por meio do protocolo MQTT para uma arquitetura distribuída baseada em broker intermediário e gateway de integração.

O objetivo principal é demonstrar uma arquitetura IoT desacoplada e escalável, semelhante às utilizadas em ambientes industriais e sistemas reais de telemetria.

---

## 🎯 Objetivos do Sistema

- Monitorar temperatura e umidade do ambiente do rack;
- Detectar movimentação física próxima ao servidor;
- Exibir informações localmente em display LCD;
- Permitir acionamento remoto de atuadores;
- Implementar comunicação segura via MQTT;
- Validar uma arquitetura distribuída IoT com gateway intermediário.

---

## 🏗️ Arquitetura Distribuída do Sistema

O sistema não envia dados diretamente para a plataforma final. Em vez disso, utiliza uma arquitetura desacoplada baseada em broker MQTT intermediário.

### Fluxo de Comunicação

<img width="1269" height="433" alt="Captura de tela de 2026-02-19 02-57-36" src="https://github.com/user-attachments/assets/58de27f7-9d3c-4e3d-9618-0eb3388a50cc" />

### Descrição da Arquitetura

#### 🔹 Device Layer — ESP32 (Wokwi)
O ESP32 coleta dados dos sensores e publica mensagens MQTT contendo informações ambientais e eventos de segurança.

#### 🔹 Broker Layer — HiveMQ
O HiveMQ atua como broker MQTT central responsável por:

- Receber mensagens do dispositivo;
- Gerenciar tópicos publish/subscribe;
- Permitir múltiplos consumidores simultâneos;
- Servir como ponto de debug e monitoramento.

#### 🔹 Gateway Layer — Script Python
Um script Python utilizando a biblioteca `paho-mqtt` atua como gateway IoT:

- Subscreve os tópicos MQTT;
- Processa os dados recebidos;
- Encaminha informações ao ThingSpeak via API HTTP.

Essa abordagem simula gateways industriais reais.

#### 🔹 Cloud Layer — ThingSpeak
Responsável por:

- Armazenamento histórico;
- Visualização gráfica;
- Análise dos dados coletados.

---

## ✅ Por que usar Arquitetura Distribuída?

Esta arquitetura foi escolhida para demonstrar conceitos profissionais de sistemas IoT:

### 🔸 Desacoplamento
O dispositivo não depende diretamente do ThingSpeak. Outras plataformas podem ser adicionadas sem alterar o firmware do ESP32.

### 🔸 Interoperabilidade
Múltiplos sistemas podem consumir os dados simultaneamente:

- dashboards
- scripts analíticos
- sistemas de alerta
- aplicações mobile

### 🔸 Debug e Observabilidade
O broker permite verificar se os dados chegaram corretamente antes da integração com a nuvem.

### 🔸 Simulação Industrial
Replica o modelo real:

Sensores → Gateway Edge → Cloud




muito utilizado em automação industrial.

### 🔸 Controle de Fluxo
O gateway pode filtrar ou reduzir frequência de envio respeitando limitações do ThingSpeak.


---

## 📡 Funcionalidades Principais

- ✅ Monitoramento térmico utilizando sensor DHT22  
- ✅ Detecção de presença via sensor PIR  
- ✅ Visualização local em display LCD 16x2  
- ✅ Comunicação segura via protocolo MQTT (SSL/TLS)  
- ✅ Controle remoto de atuador (Cooler/Alarme)  
- ✅ Integração com plataforma ThingSpeak  
- ✅ Arquitetura IoT distribuída baseada em Broker + Gateway  

---

## 🛠️ Hardware Utilizado (Simulação Wokwi)

| Componente | Função | GPIO ESP32 |
| :--- | :--- | :--- |
| **ESP32 DevKit** | Microcontrolador principal | - |
| **DHT22** | Sensor de temperatura e umidade | GPIO 15 |
| **PIR (AS312)** | Sensor de movimento | GPIO 13 |
| **LED Vermelho** | Atuador (Cooler/Alarme simulado) | GPIO 2 |
| **LCD 16x2 (I2C)** | Interface visual local | SDA: 21 / SCL: 22 |

---

## ⚙️ Bibliotecas Utilizadas

### Firmware ESP32 (Arduino Framework)

- `PubSubClient` — Comunicação MQTT
- `DHT Sensor Library` — Leitura do sensor DHT22
- `LiquidCrystal I2C` — Controle do display LCD
- `WiFiClientSecure` — Comunicação MQTT com SSL/TLS

### Gateway Python

- `paho-mqtt` — Cliente MQTT para subscrição e processamento
- `requests` — Envio de dados para ThingSpeak via HTTP API

---

## ☁️ Arquitetura MQTT

### 📤 Publicação (ESP32 → HiveMQ Broker)

| Tópico | Descrição | Exemplo de Payload |
| :--- | :--- | :--- |
| `fiap/datacenter/rack01/temperatura` | Temperatura atual | `24.5` |
| `fiap/datacenter/rack01/umidade` | Umidade atual | `60.0` |
| `fiap/datacenter/rack01/alerta_presenca` | Evento de segurança | `MOVIMENTO DETECTADO` |

---

### 📥 Subscrição (Broker → ESP32)

| Tópico | Descrição | Comandos Aceitos |
| :--- | :--- | :--- |
| `fiap/datacenter/rack01/cooler/comando` | Controle do atuador | `ON` / `OFF` |

---

## 🔐 Segurança

A comunicação MQTT utiliza:

- Criptografia SSL/TLS (porta 8883)
- Autenticação no broker HiveMQ
- Comunicação segura ponta a ponta

---

## 📊 Visualização de Dados

Os dados recebidos pelo Gateway Python são encaminhados ao ThingSpeak, permitindo:

- geração automática de gráficos;
- armazenamento histórico das medições;
- monitoramento remoto em tempo real;
- análise temporal das variáveis ambientais.

---

## 🎥 Demonstração

O projeto inclui um vídeo demonstrando:

1. Publicação MQTT pelo ESP32 (Wokwi);
2. Recepção das mensagens no broker HiveMQ;
3. Processamento pelo Gateway Python (`paho-mqtt`);
4. Atualização automática dos gráficos no ThingSpeak.

---

## 📌 Conclusão

Este projeto demonstra que sistemas IoT modernos devem ser projetados como arquiteturas distribuídas e desacopladas.

A utilização de um broker MQTT intermediário e de um gateway programável permite:

- maior escalabilidade;
- flexibilidade tecnológica;
- facilidade de manutenção;
- observabilidade do sistema;
- alinhamento com arquiteturas industriais reais de IoT.
