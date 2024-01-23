from paho.mqtt import client as mqtt_client
import asyncio
from mqtt.model import MQTT_Model
from datetime import datetime

import nest_asyncio
nest_asyncio.apply()

# Classe que gerencia a lógica do MQTT
class MQTT_MANAGER:
    def __init__(self, client_id, broker, username, password, port) -> None:
        self.client_id = client_id
        self.__username = username
        self.__password = password
        self.__broker = broker
        self.__port = port

    # Método para criar um log com base nas informações recebidas
    def create_log(self, id_gps, lat, long):
        print(id_gps)
        # Obtém informações sobre os ativos de transporte
        ativos_transp = asyncio.run(MQTT_Model.get_ativo(int(id_gps), 'gps'))
        print(ativos_transp)
        now = datetime.now()
        timestamp = datetime.timestamp(now)
        # Verifica o estado do ativo e cria o log correspondente
        for ativo in ativos_transp:
            print(ativo)
            if ativo['state'] == 'parado':
                asyncio.run(MQTT_Model.create_log_db(ativo['id_ativo'],timestamp,  lat, long,id_gps))
            else:
                asyncio.run(MQTT_Model.create_log_db(ativo['id_ativo'],timestamp,  lat, long,id_gps))


    # Método para finalizar um transporte com base nas informações recebidas
    def finalizar(self, esp_tag, ativos):
        id_transportador = asyncio.run(MQTT_Model.get_esp(int(esp_tag)))[0]['id']
        status = "parado"

        # Para cada ativo, atribui ao transporte e verifica o estado
        for ativo in ativos:
            ativo_info = asyncio.run(MQTT_Model.get_ativo(str(ativo), 'tag'))
            asyncio.run(MQTT_Model.atribuir_transporte_db(int(id_transportador), str(ativo)))

            print(ativo_info)

            # Atualiza o estado com base no estado do ativo
            if ativo_info[0]['state'] == 'parado':
                asyncio.run(MQTT_Model.change_state_db("movimento", "ativos", int(id_transportador), str(ativo)))
                status = "movimento"
            else:
                asyncio.run(MQTT_Model.change_state_db("parado", "ativos", int(id_transportador), str(ativo)))

        # Atualiza o estado do transporte
        asyncio.run(MQTT_Model.change_state_db(status, "gps", int(id_transportador), 122))

    # Método para conectar ao MQTT Broker
    def connect_mqtt(self) -> mqtt_client:
        def on_connect(client, userdata, flags, rc):
            if rc == 0:
                print("Connected to MQTT Broker!")
            else:
                print(f"Failed to connect, return code {rc}")

        client = mqtt_client.Client(self.client_id)
        client.username_pw_set(self.__username, self.__password)
        client.on_connect = on_connect
        client.connect(self.__broker, self.__port)
        return client

    # Método para se inscrever em tópicos MQTT e definir callbacks
    def subscribe(self, client: mqtt_client):
        client.subscribe('log_transp')
        client.subscribe("identificador")
        client.subscribe("finalizar")

        def on_message_callback(client, userdata, msg):
            if msg.topic == 'identificador':
                # Lida com mensagens de identificador
                dict = eval(msg.payload.decode())
                print(dict['rfid'])
                ativo = asyncio.run(MQTT_Model.get_ativo(str(dict['rfid']), 'tag'))
                print(ativo)
                response = {
                    'boardFullName': ativo[0]['boardFullName'],
                    'SN_barCode': ativo[0]['SN_barCode'],
                    'leitor_id': dict['leitor_id']
                }
                client.publish('ident', str(response))

            if msg.topic == 'finalizar':
                # Lida com mensagens de finalização
                dict = eval(msg.payload.decode())
                print(dict)
                self.finalizar(dict['esp_tag'], dict['lista_ativos'])
                print('changed')

            if msg.topic == 'log_transp':
                # Lida com mensagens de log de transporte
                dict = eval(msg.payload.decode())
                self.create_log(dict['id_transporte'], str(dict['lat']), str(dict['long']))

        client.on_message = on_message_callback

    # Método principal para executar a lógica MQTT
    def run(self):
        client = self.connect_mqtt()
        self.subscribe(client)
        client.loop_forever()
