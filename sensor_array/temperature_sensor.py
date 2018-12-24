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
try: 
     while True:
          json_to_print = {}
          # Efetua a leitura do sensor
          humidity, temperature = Adafruit_DHT.read_retry(sensor, pino_sensor);
          # Caso leitura esteja ok, mostra os valores
          if humidity is not None and temperature is not None:
               current_time=datetime.datetime.now()
               
               json_to_print["temperature"] = temperature
               json_to_print["humidity"] = humidity
               json_to_print["time"] = str(current_time)
               
          else:
               json_to_print["error"] = "Falha ao ler dados do DHT11 !!!"
          
          print(json.dumps(json_to_print, indent=4, sort_keys=True))	      
          time.sleep(1)
except KeyboardInterrupt:          
     print("Interrompido pelo utilizador!!!")
except:
    GPIO.cleanup()
