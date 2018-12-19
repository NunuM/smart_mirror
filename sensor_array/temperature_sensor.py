import Adafruit_DHT
import RPi.GPIO as GPIO
import time
import json
import datetime
 
# tipo de sensor
sensor = Adafruit_DHT.DHT11
 
GPIO.setmode(GPIO.BOARD)
 
# Define a GPIO ligada ao pino de dados do sensor
pino_sensor = 25
 
while True:
   # Efetua a leitura do sensor
   humidity, temperature = Adafruit_DHT.read_retry(sensor, pino_sensor);
   # Caso leitura esteja ok, mostra os valores
   if humidity is not None and temperature is not None:
     current_time=datetime.datetime.now()
     json_to_print = '{"temperature":'+str(temperature)+',"humidity":'+str(humidity)+',"time":"'+str(current_time)+'"}'
     json_parsed = json.loads(json_to_print)
     print(json.dumps(json_parsed, indent=4, sort_keys=True))	 
     time.sleep(5)
   else:
     print("Falha ao ler dados do DHT11 !!!")
