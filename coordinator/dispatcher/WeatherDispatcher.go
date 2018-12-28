package dispatcher

import (
	"bytes"
	"coordinator/bus"
	"coordinator/structs"
	"encoding/json"
	"log"
	"os/exec"
)

func callWeather(weather structs.Weather) structs.OutWeatherSlice{
	var cmd exec.Cmd
	if *weather.Forecast {
		cmd = *exec.Command("weather",weather.Location,"--forecast")
	} else {
		cmd = *exec.Command("weather",weather.Location)
	}
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err := cmd.Run()
	log.Print("Weather Call Executed")

	var w structs.OutWeatherSlice
	err1 := json.Unmarshal(out.Bytes()[:],&w)

	if err != nil {
		return structs.OutWeatherSlice{}
	} else if err1 != nil {
		return structs.OutWeatherSlice{}
	}
	return w
}


func AppendWeather(weather structs.Weather){
	go switchToWeatherView()
	if *weather.Forecast {
		go appendWeatherForecastAsync(weather)
	} else{
		go appendWeatherNoForecastAsync(weather)
	}
}

func appendWeatherNoForecastAsync(weather structs.Weather){
	call,err := bus.DbusWeatherAPIImp.FindDbusCall(".appendWeather")
	if err == nil {
		var w = callWeather(weather)
		if len(w) == 1 {
			result := call.AppendWeather(w[0])
			if !result {
				parseReplyError("Weather.AppendWeather")
			}
		} else{
			notifyError("Weather Service responded to a no forecast call with invalid output")
		}
	}else{
		parseInitError("Weather.AppendWeather")
	}
}

func appendWeatherForecastAsync(weather structs.Weather){
	call,err := bus.DbusWeatherAPIImp.FindDbusCall(".appendWeather")
	if err == nil {
		var w = callWeather(weather)
		if len(w) >= 1 {
			res,err1 := json.Marshal(w)
			if err1 == nil {
				result := call.AppendWeatherAsJson(string(res))
				if !result {
					parseReplyError("Weather.AppendWeather")
				}
			} else{
				notifyError("Failed to Marshal weather service response")
			}
		} else{
			notifyError("Weather Service responded to a forecast call with no output")
		}
	}else{
		parseInitError("Weather.AppendWeather")
	}
}

func RemoveWeather(date string){
	go switchToWeatherView()
	go removeWeather(date)
}

func removeWeather(date string){
	call,err := bus.DbusWeatherAPIImp.FindDbusCall(".removeWeather")
	if err == nil {
		result := call.RemoveWeather(date)
		if !result {
			parseReplyError("Weather.RemoveWeather")
		}
	}else{
		parseInitError("Weather.RemoveWeather")
	}
}


func switchToWeatherView(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setWeatherViewAsRoot")
	if err == nil {
		call.SetWeatherViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to Weather")
	}
}



