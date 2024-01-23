import os
import uuid
from dotenv import load_dotenv

from mqtt.conn import MQTT_MANAGER

load_dotenv()

# Ponto de entrada do programa
if __name__ == '__main__':
    # # Cria uma instância da classe MQTT_Model e executa o método run
    mqtt = MQTT_MANAGER(
        client_id = str(uuid.uuid4()),
        broker = os.environ.get('BROKER_IP'),
        username = os.environ.get('BROKER_USERNAME'),
        password = os.environ.get('BROKER_PASSWORD'),
        port = int(os.environ.get('BROKER_PORT'))
    )
    mqtt.run()
