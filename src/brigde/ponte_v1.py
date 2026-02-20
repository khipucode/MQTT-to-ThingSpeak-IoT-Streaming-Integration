import paho.mqtt.client as mqtt
import time

# --- CONFIGURAÇÕES HIVEMQ (Origem - Wokwi) ---
HIVEMQ_BROKER = "6e30ed916c6c44668c70e7d2351cd0c1.s1.eu.hivemq.cloud"
HIVEMQ_USER   = "aluno_iot"
HIVEMQ_PASS   = "123456IoT"

TOPICOS_HIVE = {
    "fiap/datacenter/rack01/temperatura": "field1",
    "fiap/datacenter/rack01/umidade": "field2",
    "fiap/datacenter/rack01/alerta_presenca": "field3"
}

# --- CONFIGURAÇÕES THINGSPEAK (Destino) ---
TS_BROKER     = "mqtt3.thingspeak.com"
TS_CHANNEL_ID = "3269220"
TS_CLIENT_ID  = "KDEtIxUQERwwHi4CNgYANhs"
TS_USER       = "KDEtIxUQERwwHi4CNgYANhs"
TS_PASS       = "DGF2VlaPESbD2bpH4wt9V//p"
TS_TOPIC      = f"channels/{TS_CHANNEL_ID}/publish"

def on_message(client, userdata, msg):
    valor = msg.payload.decode()
    topico_origem = msg.topic
    
    # Identifica qual field do ThingSpeak corresponde ao tópico do HiveMQ
    field = TOPICOS_HIVE.get(topico_origem)
    
    if field:
        print(f"\n[LOG {time.strftime('%H:%M:%S')}]")
        print(f" -> Recebido do HiveMQ [{topico_origem}]: {valor}")
        
        # Formata o payload para o ThingSpeak: ex "field1=25.5"
        payload_ts = f"{field}={valor}"
        
        # Publica no ThingSpeak
        ts_client.publish(TS_TOPIC, payload=payload_ts, qos=0)
        print(f" -> Repassado ao ThingSpeak ({field}): {payload_ts}")

# --- SETUP CLIENTES ---
# Se der erro de 'CallbackAPIVersion', remova o argumento dentro de mqtt.Client()
hive_client = mqtt.Client(callback_api_version=mqtt.CallbackAPIVersion.VERSION2)
hive_client.username_pw_set(HIVEMQ_USER, HIVEMQ_PASS)
hive_client.tls_set() 
hive_client.on_message = on_message

ts_client = mqtt.Client(callback_api_version=mqtt.CallbackAPIVersion.VERSION2, client_id=TS_CLIENT_ID)
ts_client.username_pw_set(TS_USER, TS_PASS)

try:
    print("Conectando aos Brokers...")
    hive_client.connect(HIVEMQ_BROKER, 8883)
    ts_client.connect(TS_BROKER, 1883)
    
    # Inscreve em todos os tópicos definidos no dicionário
    for t in TOPICOS_HIVE.keys():
        hive_client.subscribe(t)
        print(f"Inscrito no tópico: {t}")

    print("\n[PONTE ATIVA] Aguardando fluxo do Datacenter...")
    hive_client.loop_forever()

except Exception as e:
    print(f"Erro: {e}")
