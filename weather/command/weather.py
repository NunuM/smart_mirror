#!/usr/bin/python
from urllib.request import urlopen
import json
import datetime
import argparse

REQUIRED_KEYS = ['date',
                 'humidity',
                 'pressure',
                 'temp',
                 'temp_max',
                 'temp_min',
                 'description',
                 'icon',
                 'wind_deg',
                 'wind_speed']


def main():
    parser = argparse.ArgumentParser(description='Weather CLI Param Options')
    parser.add_argument('location')
    parser.add_argument('--forecast', action='store_true')

    args = parser.parse_args()
    key = '0b7eddd87a43720fb9cfb6faf26758af'
    _location = args.location

    if args.forecast:
        weather_url = 'http://api.openweathermap.org/data/2.5/forecast?q=' + \
                      _location + '&APPID=' + key + '&units=metric'  # full url
    else:
        weather_url = 'http://api.openweathermap.org/data/2.5/weather?q=' + \
                      _location + '&APPID=' + key + '&units=metric'  # full url

    try:

        response = urlopen(weather_url).read().decode('utf-8')
        parsed = json.loads(response)
        current_day = 0
        output = []

        if args.forecast:
            for val in parsed["list"]:
                # print(val)
                d = datetime.datetime.strptime(val["dt_txt"], "%Y-%m-%d %H:%M:%S")
                # print(d.day)
                if d.day != current_day:
                    val['main']['date'] = d.strftime("%Y-%m-%d %H:%M")
                    val['main']['description'] = val['weather'][0]['description']
                    val['main']['icon'] = val['weather'][0]['icon']
                    val['main']['wind_deg'] = val['wind']['deg']
                    val['main']['wind_speed'] = val['wind']['speed']
                    del val['main']['temp_kf']
                    del val['main']['grnd_level']
                    del val['main']['sea_level']

                    object_to_send = val['main']

                    diff = set(object_to_send.keys()) - set(REQUIRED_KEYS)

                    if len(diff) is not 0:
                        raise ValueError("Not a valid object")

                    output.append(val['main'])

                    current_day = d.day
        else:
            parsed['main']['date'] = str(datetime.datetime.now().date())
            parsed['main']['description'] = parsed['weather'][0]['description']
            parsed['main']['icon'] = parsed['weather'][0]['icon']
            parsed['main']['wind_deg'] = parsed['wind']['deg']
            parsed['main']['wind_speed'] = parsed['wind']['speed']

            output.append(parsed['main'])

        print(json.dumps(output, sort_keys=True))

    except Exception as e:
        print(json.dumps({'error': str(e)}))


if __name__ == "__main__":
    main()
