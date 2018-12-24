import RPi.GPIO as GPIO
import datetime
import os, subprocess, time


os.environ['DISPLAY'] = ":0"
displayison = False
maxidle = 0.25*60 # 15 seconds
lastsignaled = 0

pin_sensor = 14

GPIO.setmode(GPIO.BCM)

GPIO.setup(pin_sensor, GPIO.IN) #PIR


try:
    time.sleep(2) # to stabilize sensor
    while True:
        current_time=datetime.datetime.now()
        now = time.time()

        print(current_time)
        if GPIO.input(pin_sensor):
            print("Motion Detected...")
            if not displayison:
                subprocess.call('xset dpms force on', shell=True)
                displayison = True
            lastsignaled = now
        else:
            print("nothing...")
            if now-lastsignaled > maxidle:
                if displayison:
                    subprocess.call('xset dpms force off', shell=True)
                    displayison = False
        time.sleep(1) #to avoid multiple detection

except:
    GPIO.cleanup()
