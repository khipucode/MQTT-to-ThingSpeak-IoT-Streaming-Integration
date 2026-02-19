# 🎯 Objetivo do Trabalho

O objetivo deste trabalho é projetar, implementar e validar uma arquitetura de transmissão de dados IoT baseada no protocolo MQTT, utilizando um broker intermediário (HiveMQ) entre o dispositivo e a plataforma em nuvem ThingSpeak, a fim de demonstrar uma abordagem desacoplada, interoperável e alinhada com arquiteturas industriais modernas.

O projeto implementa um pipeline completo de telemetria IoT, no qual um dispositivo simulado no Wokwi publica dados de sensores em um broker MQTT (HiveMQ). A integração com a plataforma ThingSpeak é realizada por meio de um script em Python utilizando a biblioteca `paho-mqtt`, responsável por consumir as mensagens do broker e encaminhá-las ao canal configurado na nuvem.

Além da implementação funcional, o foco principal do trabalho é validar as vantagens arquiteturais do uso de um broker intermediário em sistemas IoT distribuídos.

---

# 🏗 Fundamentação Arquitetural

## 1️⃣ Desacoplamento e Interoperabilidade

Em sistemas IoT reais, dispositivos não devem depender diretamente de uma única plataforma de nuvem. Ao utilizar um broker externo como o HiveMQ:

- O dispositivo publica os dados apenas uma vez.
- Múltiplos consumidores podem se inscrever simultaneamente no mesmo tópico:
  - ThingSpeak para armazenamento histórico;
  - Scripts Python para processamento;
  - Dashboards móveis;
  - Sistemas de análise ou inteligência artificial.

Essa arquitetura permite substituir a plataforma final (por exemplo, trocar o ThingSpeak por outra nuvem) sem necessidade de reprogramar o firmware dos dispositivos. Isso garante maior escalabilidade e redução de custos operacionais.

---

## 2️⃣ Visibilidade e Debug (Monitoramento do Fluxo)

O broker intermediário funciona como ponto central de inspeção do tráfego MQTT.

Ferramentas como:
- MQTT Explorer
- Clientes MQTT de linha de comando
- Logs do HiveMQ

permitem verificar:

- Se o dispositivo está publicando corretamente;
- Se as mensagens estão chegando ao broker;
- Se o consumidor (Python) está recebendo os dados;
- Se o envio para o ThingSpeak está funcionando.

Sem o broker intermediário, problemas na visualização dos dados poderiam estar relacionados a código, rede ou API Key. Com o broker no meio, o processo de debug torna-se estruturado e rastreável.

---

## 3️⃣ Simulação de Arquitetura Industrial

Na indústria, sensores de campo normalmente publicam dados para um broker local ou gateway edge (ex.: Mosquitto em um Raspberry Pi). Esse gateway realiza:

- Filtragem de dados;
- Agregação de informações;
- Controle de segurança;
- Encaminhamento para a nuvem.

A arquitetura implementada neste projeto simula esse cenário profissional:





Esse modelo representa uma arquitetura típica de Gateway IoT utilizada em ambientes industriais e sistemas distribuídos.

---

## 4️⃣ Controle de Fluxo e Tratamento de Dados

O ThingSpeak possui limitações de frequência de envio de dados (por exemplo, intervalo mínimo de aproximadamente 15 segundos na conta gratuita).

O uso de um broker externo permite:

- Receber dados em alta frequência;
- Processar ou agregar informações no script Python;
- Enviar apenas dados consolidados para o ThingSpeak;
- Implementar filtros, tratamento ou validações antes do envio à nuvem.

Dessa forma, o broker e o script atuam como elementos estratégicos de controle do ecossistema IoT.

---

# 🛠 Tecnologias Utilizadas

## 🔹 HiveMQ (Broker MQTT)

O HiveMQ é utilizado como broker MQTT central da arquitetura. Ele é responsável por:

- Receber as mensagens publicadas pelo dispositivo;
- Gerenciar tópicos e subscrições;
- Distribuir as mensagens aos consumidores inscritos.

Ele atua como núcleo do sistema distribuído.

---

## 🔹 Paho-MQTT (Cliente Python)

A biblioteca `paho-mqtt` é utilizada no script Python para:

- Realizar a subscrição aos tópicos publicados pelo dispositivo;
- Receber as mensagens do broker;
- Processar e encaminhar os dados para o ThingSpeak via API.

Optou-se por utilizar um script em Python em vez de ferramentas visuais como Node-RED por diversos motivos:

- Maior controle sobre o tratamento das mensagens;
- Possibilidade de implementar lógica personalizada;
- Facilidade de integração com outras bibliotecas Python;
- Simulação mais próxima de um gateway programável industrial.

---

## 🔹 Alternativa: Node-RED

O Node-RED é uma ferramenta visual baseada em fluxos que poderia ser utilizada para realizar a integração entre MQTT e ThingSpeak.

Ele oferece:
- Interface gráfica de fácil configuração;
- Conexão simples com brokers MQTT;
- Nós prontos para integração com APIs.

Entretanto, neste projeto optou-se pelo uso de um script Python para enfatizar:

- Controle programático da arquitetura;
- Flexibilidade para expansão futura;
- Maior aderência a cenários de desenvolvimento profissional e acadêmico.

---

# 🎯 Síntese do Objetivo

Este trabalho não se limita à integração entre ferramentas, mas demonstra a importância de uma arquitetura IoT desacoplada, escalável e observável, baseada em boas práticas de engenharia de sistemas distribuídos.

Ao final do projeto, pretende-se comprovar:

- Funcionamento completo do fluxo Device → Broker → Gateway → Nuvem;
- Integridade e estabilidade da comunicação MQTT;
- Benefícios arquiteturais do uso de broker intermediário;
- Aplicabilidade do modelo em cenários industriais reais.

Em síntese, o broker externo ensina a gerenciar o ecossistema IoT como um sistema distribuído completo, e não apenas a utilizar uma plataforma específica.

