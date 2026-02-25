# Gabarito – Questões de IoT, Sistemas Embarcados e Arquitetura

---

## 1. Por que controle em malha fechada é essencial em sistemas IoT críticos?

a) Elimina necessidade de sensores  
b) Reduz consumo energético do hardware  
c) Compensa perturbações automaticamente  
d) Dispensa comunicação em rede  
e) Simplifica firmware do microcontrolador  

**Resposta correta:** c

---

## 2. Por que MQTT é preferido em IoT distribuído?

a) Comunicação síncrona obrigatória  
b) Modelo publish/subscribe desacoplado  
c) Forte acoplamento entre dispositivos  
d) Maior consumo de banda garantido  
e) Dependência direta de HTTP  

**Resposta correta:** b

---

## 3. Por que motores DC são comuns em sistemas embarcados?

a) Funcionam apenas em corrente alternada  
b) Controle simples de velocidade e torque  
c) Não exigem drivers externos  
d) Alta precisão sem feedback  
e) Imunes a variações de carga  

**Resposta correta:** b

---

## 4. Em uma arquitetura IoT típica, qual é o principal motivo para introduzir um gateway entre sensores e a nuvem?

a) Reduzir necessidade de autenticação  
b) Centralizar lógica de controle determinístico  
c) Garantir latência zero na nuvem  
d) Eliminar processamento no edge  
e) Agregar dados, traduzir protocolos e aplicar segurança  

**Resposta correta:** e

---

## 5. Por que protocolos industriais como Profinet ou EtherCAT continuam relevantes quando integrados a plataformas IoT modernas?

a) Substituem completamente MQTT  
b) Diminuem riscos no chão de fábrica  
c) Eliminam a necessidade de gateways  
d) Funcionam apenas sobre Wi-Fi  
e) São mais simples que protocolos IoT  

**Resposta correta:** b

---

## 6. Em plataformas IoT modernas, a arquitetura orientada a eventos é adotada principalmente porque:

a) Simplifica hardware dos sensores  
b) Permite acoplamento forte entre serviços  
c) Aumenta escalabilidade e resiliência  
d) Elimina gateways  
e) Reduz necessidade de testes  

**Resposta correta:** c

---

## 7. Um requisito como “operar por dois anos com bateria de 2400 mAh” é classificado como:

a) Funcional de aplicação  
b) Funcional de comunicação  
c) Requisito de arquitetura de software  
d) Não funcional de energia  
e) Caso de uso  

**Resposta correta:** d

---

## 8. Qual decisão de arquitetura teria evitado comprometimento físico via interface de debug?

a) Ativar secure boot e lockdown de debug  
b) Implementar firewall na nuvem apenas  
c) Exigir TLS com certificados mTLS  
d) Aumentar frequência de envio MQTT  
e) Usar banco criptografado na cloud  

**Resposta correta:** a

---

## 9. Qual alternativa representa corretamente um trade-off clássico em IoT a bateria?

a) Aumentar clock sempre reduz consumo energético  
b) Melhorar eficiência energética aumenta latência do sistema  
c) Mais memória sempre melhora confiabilidade  
d) Reduzir código aumenta modularidade e manutenção  
e) Otimizar recursos elimina necessidade de testes  

**Resposta correta:** b

---

## 10. Qual decisão corrigiria simultaneamente não conformidade EMC e IEC 62368-1?

a) Aumentar redundância na nuvem e QoS MQTT  
b) Atualizar firmware com watchdog mais agressivo  
c) Migrar processamento crítico para cloud pública  
d) Aplicar filtros EMI, isolamento adequado e gestão térmica  
e) Trocar protocolo MQTT por HTTP  

**Resposta correta:** d

---

## 11. No MQTT, qual afirmação descreve corretamente a diferença entre broker e client?

a) Broker subscreve e cliente apenas publica  
b) Ambos publicam e subscrevem sem distinção  
c) Cliente apenas repassa pacotes  
d) Broker gerencia conexões, roteia mensagens e controla QoS  
e) Broker realiza criptografia ponta a ponta  

**Resposta correta:** d

---

## 12. Qual é a principal limitação do HTTP para telemetria de alta frequência?

a) Baixa compatibilidade com JSON  
b) Necessidade de broker centralizado  
c) Falta de suporte a TLS  
d) Falta de compatibilidade com firewalls  
e) Latência maior devido à natureza stateless e overhead  

**Resposta correta:** e

---

## 13. Em arquiteturas IoT modernas, a jornada do dado normalmente segue:

a) Sensor → Broker → Gateway → Nuvem → Aplicação  
b) Sensor → Edge → Gateway → Nuvem → Aplicação  
c) Sensor → Cliente MQTT → Servidor HTTP → Broker → Aplicação  
d) Sensor → Nuvem → Edge → Broker → Cliente  
e) Aplicação → Gateway → Edge → Sensor → Nuvem  

**Resposta correta:** b

---

## 14. A escolha entre protocolos industriais deve priorizar principalmente:

a) Compatibilidade com Modbus RTU  
b) Disponibilidade de APIs REST  
c) Requisitos de determinismo, desempenho e ferramenta de engenharia  
d) Custo dos cabos  
e) Existência de broker MQTT compatível  

**Resposta correta:** c

---

## 15. Sensores MEMS requerem fusão sensorial principalmente para:

a) Reduzir consumo de energia  
b) Eliminar filtros digitais  
c) Melhorar estimativa de orientação e compensar drift  
d) Aumentar faixa de medição  
e) Permitir comunicação UART  

**Resposta correta:** c

---

## 16. Maior vantagem do WebSocket em HMI embarcada:

a) Compressão obrigatória de pacotes  
b) Canal full-duplex persistente com baixa latência  
c) Broadcast automático  
d) Menor autenticação necessária  
e) Menor uso de TLS  

**Resposta correta:** b

---

## 17. Em arquiteturas IoT com redundância, o failover ocorre quando:

a) Dispositivo envia dados para dois brokers simultaneamente  
b) Sistema alterna automaticamente para um nó reserva após falha  
c) Broker força reinicialização do cliente  
d) Nuvem substitui sensores defeituosos  
e) Firewall fecha portas inativas  

**Resposta correta:** b

---

## 18. Gateways IoT com edge computing trazem vantagem principalmente por:

a) Eliminar necessidade de nuvem  
b) Aumentar uso de energia  
c) Tornar protocolos industriais desnecessários  
d) Exigir hardware caro obrigatório  
e) Reduzir latência e tráfego com pré-processamento local  

**Resposta correta:** e

---

## 19. Em segurança de rede IoT, TLS/SSL garante:

a) Autenticação e criptografia ponta a ponta  
b) Proteção contra invasão física  
c) Eliminação de ataques replay  
d) Segurança sem certificados  
e) Varredura automática de vírus  

**Resposta correta:** a

---

## 20. Sobre certificações para dispositivos IoT, qual afirmação é correta?

a) CE e FCC são equivalentes mundialmente  
b) ANATEL cobre apenas segurança elétrica  
c) CE e FCC tratam principalmente de requisitos EMC/EMI e radiofrequência  
d) Não é possível certificar dispositivos Bluetooth  
e) Certificações não exigem documentação técnica  

**Resposta correta:** c

---
