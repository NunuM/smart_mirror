#!/usr/bin/python
from urllib.request import urlopen
import json
import datetime
import argparse

def main():

  parser = argparse.ArgumentParser(description='Weather CLI Param Options')
  parser.add_argument('location')
  parser.add_argument('--forecast',action='store_true')
  
  args = parser.parse_args()
  key = '0b7eddd87a43720fb9cfb6faf26758af'
  _location = args.location

  if args.forecast:
    weather_url = 'http://api.openweathermap.org/data/2.5/forecast?q=' + \
    _location + '&APPID=' + key + '&units=metric' # full url
  else:
    weather_url = 'http://api.openweathermap.org/data/2.5/weather?q=' + \
    _location + '&APPID=' + key +'&units=metric'  # full url

  response = urlopen(weather_url).read().decode('utf-8')
  parsed = json.loads(response)

  current_day = 0;


  
  if args.forecast:
   output = '[\n'
   for val in parsed["list"]:
      # print(val)
      d = datetime.datetime.strptime(val["dt_txt"] , "%Y-%m-%d %H:%M:%S")
      #print(d.day)
      if d.day != current_day :
          val['main']['date']=d.isoformat()
          val['main']['description'] = val['weather'][0]['description']
          val['main']['icon'] = val['weather'][0]['icon']
          val['main']['wind_deg'] = val['wind']['deg']
          val['main']['wind_speed'] = val['wind']['speed']
          del val['main']['temp_kf']
          del val['main']['grnd_level']
          del val['main']['sea_level']
          output += json.dumps(val['main'], indent=4, sort_keys=True) + '\n'
          current_day = d.day
   output += ']'
  else:
      parsed['main']['date'] = datetime.datetime.now().isoformat()
      parsed['main']['description'] = parsed['weather'][0]['description']
      parsed['main']['icon'] = parsed['weather'][0]['icon']
      parsed['main']['wind_deg'] = parsed['wind']['deg']
      parsed['main']['wind_speed'] = parsed['wind']['speed']
      output = '[\n'
      output += json.dumps(parsed['main'], indent=4, sort_keys=True) + '\n]'
   

  print(output)

if __name__ == "__main__":
   main()
