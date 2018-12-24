import RPi.GPIO as GPIO 
import time 
import json 
import datetime 

pino_sensor = 4 

def getValues():
	
	try:
		#while True:
		GPIO.setmode(GPIO.BCM)
		GPIO.setup(pino_sensor, GPIO.IN)
		result = GPIO.input(pino_sensor)
		detected_flag = (result==0) #detected gas
		
		data = {}
		data['gas_detected'] = detected_flag
		return json.dumps(data, indent=4, sort_keys=True)
       
	except KeyboardInterrupt as e:
		print("Interrompido pelo utilizador!!!")
		return e
	except Exception as e:
		GPIO.cleanup()
		return e
