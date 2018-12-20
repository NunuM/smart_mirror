
location = name of the city or contry

e.g.  Porto, Portugal, etc

## Run
```sh
python weather.py $location
```

## Output

The output is a list with the weather prediction for the current day and the next 4 days in metric units

###### Format of a single day e.g.

```json
{
    "clouds": {
        "all": 92
    },
    "dt": 1545318000,
    "dt_txt": "2018-12-20 15:00:00",
    "main": {
        "grnd_level": 1009.37,
        "humidity": 100,
        "pressure": 1009.37,
        "sea_level": 1039.91,
        "temp": 13.98,
        "temp_kf": 2.09,
        "temp_max": 13.98,
        "temp_min": 11.89
    },
    "rain": {
        "3h": 0.605
    },
    "sys": {
        "pod": "d"
    },
    "weather": [
        {
            "description": "light rain",
            "icon": "10d",
            "id": 500,
            "main": "Rain"
        }
    ],
    "wind": {
        "deg": 228.503,
        "speed": 1.52
    }
}
```
