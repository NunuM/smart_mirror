"""
    :id  =>
    :key => 0b7eddd87a43720fb9cfb6faf26758af
    :url => http://api.openweathermap.org/data/2.5/weather?q=:id&APPID=:key
"""

#!/usr/bin/python

from urllib.request import urlopen
import json
import sys

def main(argv):

  #print('Number of arguments:', len(sys.argv), 'arguments.')
  #print('Argument List:', str(sys.argv))

  _id = argv  #
  key = '0b7eddd87a43720fb9cfb6faf26758af'   # api key
  url = 'http://api.openweathermap.org/data/2.5/weather?q=' + \
      _id + '&APPID=' + key   # full url

  response = urlopen(url).read().decode('utf-8')
  parsed = json.loads(response)

  print(json.dumps(parsed, indent=4, sort_keys=True))


if __name__ == "__main__":
   main(sys.argv[1])
