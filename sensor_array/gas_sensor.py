import RPi.GPIO as GPIO
import time
import json
import datetime

pino_sensor = 4
GPIO.setmode(GPIO.BCM)
GPIO.setup(pino_sensor, GPIO.IN)

try:
     while True:
          result = GPIO.input(pino_sensor)
          detected_flag = (result==0) #detected gas
          
          data = {}
          data['gas_detected'] = detected_flag
          
          print(json.dumps(data))
          time.sleep(1)

except KeyboardInterrupt:          
     print("Interrompido pelo utilizador!!!")

except:
    GPIO.cleanup()
