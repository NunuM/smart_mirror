"""
    :location  =>
    :key => 0b7eddd87a43720fb9cfb6faf26758af
    :url => http://api.openweathermap.org/data/2.5/weather?q=:id&APPID=:key
"""

#!/usr/bin/python
from urllib.request import urlopen
import json
import sys
import datetime

def main(argv):

  #print('Number of arguments:', len(sys.argv), 'arguments.')
  #print('Argument List:', str(sys.argv))

  try:
    _location = argv  #
    key = '0b7eddd87a43720fb9cfb6faf26758af'   # api key


    # multiple days
    forecast_url = 'http://api.openweathermap.org/data/2.5/forecast?q=' + \
      _location + '&APPID=' + key + '&units=metric' # full url

    response = urlopen(forecast_url).read().decode('utf-8')
    parsed = json.loads(response)

    current_day = 0;

    output_5_days = '{\n'

    for val in parsed["list"]:
      # print(val)
      d = datetime.datetime.strptime(val["dt_txt"] , "%Y-%m-%d %H:%M:%S")
      #print(d.day)
      if d.day != current_day :
          output_5_days += json.dumps(val, indent=4, sort_keys=True) + '\n'
          current_day = d.day

    output_5_days += '}'
    print(output_5_days)

    # print(json.dumps(parsed["list"], indent=4, sort_keys=True))

    # example format
    # d = datetime.datetime.strptime("2018-12-20 12:00:00" , "%Y-%m-%d %H:%M:%S")


    #print(json.dumps(parsed, indent=4, sort_keys=True))

  except :
      print("{\"error\": \"Something went wrong :(\"}")




if __name__ == "__main__":
  try:
      sys.argv[1]
  except :
      print("{\"error\": \"Location undifined\"}")
  else:
      main(sys.argv[1])
