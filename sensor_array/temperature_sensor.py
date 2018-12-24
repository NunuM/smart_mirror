import Adafruit_DHT
import RPi.GPIO as GPIO
import time
import json
import datetime
 
# tipo de sensor
sensor = Adafruit_DHT.DHT11
 
# Define a GPIO ligada ao pino de dados do sensor
pino_sensor = 25

def getValues():
	try: 
		#while True:
		#GPIO.setmode(GPIO.BOARD)		
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
			json_to_print["error"] = "error reading data from DHT11!!!"

		return json.dumps(json_to_print, indent=4, sort_keys=True)    
		
		#time.sleep(1)
	except KeyboardInterrupt as e:          
		print("Interrompido pelo utilizador!!!")
		return e
	except Exception as e:
		GPIO.cleanup()
		return e
