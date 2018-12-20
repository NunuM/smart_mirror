import RPi.GPIO as GPIO
import time
import datetime

pin_sensor = 14
pin_relay = 15

GPIO.setmode(GPIO.BCM)

GPIO.setup(pin_sensor, GPIO.IN) #PIR
GPIO.setup(pin_relay, GPIO.OUT) #RELAY
GPIO.setup(pin_relay, GPIO.LOW) #RELAY off

try:
    time.sleep(2) # to stabilize sensor
    while True:
        current_time=datetime.datetime.now()
        print(current_time)
        if GPIO.input(pin_sensor):
            print("Motion Detected...")
            GPIO.setup(pin_relay, GPIO.LOW) #RELAY off            
        else:
            print("nothing...")
            GPIO.setup(pin_relay, GPIO.HIGH) #RELAY on
        time.sleep(1) #to avoid multiple detection

except:
    GPIO.cleanup()
