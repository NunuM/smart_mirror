package bus

import (
	"coordinator/structs"
	"errors"
	"log"
	"strings"
)

const _WEATHER_INTERFACE_PATH = "io.smart.Weather"
const _WEATHER_OBJECT_PATH = "/io/smart/Weather"

type DbusWeather struct {
	_InterfacePath string
	_ObjectPath string
	Method string
}

type DbusWeatherAPI  []DbusWeather

var DbusWeatherAPIImp = DbusWeatherAPI{
	{
		_InterfacePath:_WEATHER_INTERFACE_PATH,
		_ObjectPath:_WEATHER_OBJECT_PATH,
		Method:".appendWeather",
	},
	{
		_InterfacePath:_WEATHER_INTERFACE_PATH,
		_ObjectPath:_WEATHER_OBJECT_PATH,
		Method:".appendWeatherAsJson",
	},
	{
		_InterfacePath:_WEATHER_INTERFACE_PATH,
		_ObjectPath:_WEATHER_OBJECT_PATH,
		Method:".removeWeather",
	},
}


func (d *DbusWeather) AppendWeather(weather structs.OutWeather){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, weather.Date,weather.Humidity,weather.Pressure,weather.Temp,weather.TempMax,weather.TempMin,
			weather.Description,weather.Icon,weather.WindDeg,weather.WindSpeed)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}

func (d *DbusWeather) AppendWeatherAsJson(json string){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if strings.Contains(json,"error"){
		DbusNotififyError(json)
	}
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, json)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}


func (d *DbusWeather) RemoveWeather(date string){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, date)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}



func (d *DbusWeatherAPI) FindDbusCall(methodName string) (DbusWeather,error){
	for _, call := range DbusWeatherAPIImp{
		if strings.EqualFold(call.Method,methodName){
			return call,nil
		}
	}
	return DbusWeather{},errors.New("Dbus Call Not Found")
}