# Projeto: Streaming MQTT do Device para ThingSpeak

## Descrição
Este projeto implementa uma arquitetura distribuída de streaming MQTT para o monitoramento simulado de um datacenter. O sistema coleta dados de temperatura, umidade e presença por meio de um ESP32 simulado no Wokwi, publica as métricas em um broker intermediário (HiveMQ) e utiliza um gateway programado em Python para encaminhar os dados para a plataforma em nuvem ThingSpeak.

## Organização de arquivos
```
Mqtt-thingspeak/
├── assets/              # Imagens do circuito, diagramas e prints do dashboard
├── docs/
│   ├── ABOUT.md         # Objetivos, arquitetura do sistema e aprendizados
│   └── REPORT.md        # Pinagem, esquema de ligação (DHT22/PIR) e especificações
├── src/              
│   ├── esp32/
│   │   └── esp32.ino    # Firmware do microcontrolador
│   └── bridge/
│       └── ponte_v1.py  # Script Python para integração MQTT/ThingSpeak
├── .gitignore           # Para ignorar arquivos como env/ e venv/
├── LICENSE              # Licença do projeto (ex: MIT)
└── README.md            # Guia rápido de instalação, requisitos e execução
```

---
## Links do projeto

### 🧪 Projeto no Wokwi
[Project_3](https://wokwi.com/projects/456353236925773825)

### 📊 Dashboard Público ThingSpeak
[ThingSpeak Channel](https://thingspeak.mathworks.com/channels/3269220)

### 📄 Relatório em PDF
[Documentação do Projeto](https://github.com/khipucode/MQTT-to-ThingSpeak-IoT-Streaming-Integration/blob/main/docs/projet_integration_mtqq_thingspeak.pdf)

---

## Arquitetura do Sistema
O fluxo de dados opera da seguinte maneira:
1. **Dispositivo IoT (Wokwi)**: Um microcontrolador ESP32 processa os dados dos sensores (DHT22 e PIR AS312) e os publica via MQTT seguro (SSL/TLS, porta 8883).
2. **Broker MQTT (HiveMQ)**: Recebe os dados e os retém nos tópicos hierárquicos `fiap/datacenter/rack01/temperatura`, `fiap/datacenter/rack01/umidade` e `fiap/datacenter/rack01/alerta_presenca`.
3. **Gateway (Python)**: O script `ponte_v1.py`, usando a biblioteca `paho-mqtt`, subscreve os tópicos do HiveMQ, traduz a estrutura de dados e atua como ponte para a nuvem.
4. **Nuvem (ThingSpeak)**: Armazena o histórico e exibe os dados graficamente via painéis (*dashboards*), atualizados pelo gateway.

## Requisitos
* Simulador online **Wokwi**.
* **Python 3.x** configurado com as bibliotecas `paho-mqtt` e `requests`.
* Instância ativa no **HiveMQ Cloud**.
* Conta configurada no **ThingSpeak** com os respectivos *Fields* e *Channel* ativados.

## Orientações de Funcionamento

### 1. Configuração e Inicialização do Dispositivo (Wokwi)
* Abra a simulação do circuito contendo o ESP32, o sensor DHT22 e o sensor de presença PIR.
* Inicie a simulação e verifique no display LCD integrado se a mensagem "Conectando HiveMQ Cloud..." aparece e se a conexão é concluída com êxito.

### 2. Configuração do Script de Gateway (Python)
* Abra o arquivo do gateway (`ponte_v1.py`) no seu editor de código.
* Atualize as credenciais do **HiveMQ** (`HIVEMQ_BROKER`, `HIVEMQ_USER`, `HIVEMQ_PASS`) com os dados do seu cluster.
* Atualize as credenciais do **ThingSpeak** (`TS_BROKER`, `TS_CHANNEL_ID`, `TS_CLIENT_ID`, `TS_USER`, `TS_PASS`) e garanta que a variável do tópico de publicação esteja formatada como `channels/<SEU_CHANNEL_ID>/publish`.

### 3. Execução da Integração
* Garanta que a simulação no Wokwi esteja rodando para gerar a telemetria.
* No seu terminal, inicie a ponte MQTT executando o script executando `python ponte_v1.py`.
* Utilize uma ferramenta como o **MQTT Explorer** conectada ao seu HiveMQ para depurar o fluxo de dados em tempo real e atestar que os tópicos estão sendo populados.

### 4. Monitoramento e Visualização
* Acesse o seu *dashboard* no painel de controle do **ThingSpeak**.
* Valide a recepção gráfica das informações em seus respectivos *fields*: Temperatura (`field1`), Umidade (`field2`) e Presença/Alerta (`field3`).
* **Atenção:** Devido a políticas de controle de fluxo do ThingSpeak, as atualizações dos gráficos ocorrerão com intervalos limitados a 15 segundos, refletindo uma amostragem de dados um pouco mais esparsa do que a visualizada no HiveMQ.

---
*Projeto desenvolvido para a disciplina de Sistemas Embarcados e Internet das Coisas (IoT).*
