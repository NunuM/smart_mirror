import RPi.GPIO as GPIO
import time

pin_sensor = 14
GPIO.setmode(GPIO.BCM)

GPIO.setup(pin_sensor, GPIO.IN) #PIR

try:
    time.sleep(2) # to stabilize sensor
    while True:
        if GPIO.input(pin_sensor):
            print("Motion Detected...")
            time.sleep(5) #to avoid multiple detection
        time.sleep(0.1) #loop delay, should be less than detection delay

except:
    GPIO.cleanup()