import time
import json
import datetime

#from w1thermsensor import W1ThermSensor
#sensor = W1ThermSensor()

while True:
	current_time=datetime.datetime.now()
	temperature = sensor.get_temperature()
	json_to_print = '{"temperature":'+str(temperature)+',"time":"'+str(current_time)+'"}'
	json_parsed = json.loads(json_to_print)
	print(json.dumps(json_parsed, indent=4, sort_keys=True),flush=True)

	time.sleep(30)