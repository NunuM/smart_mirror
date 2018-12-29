package dispatcher

import (
	"coordinator/bus"
	"coordinator/structs"
	"encoding/json"
	"log"
	"net/http"
	"net/url"
	"strings"
)

const SENSOR_BASE_URL = "http://127.0.0.1:8091"

type httpSensorRoute struct {
	route string
}

type operation string

const (
	APPEND operation = "append"
	ADD operation = "ADD"
)


type httpSensorRoutes []httpSensorRoute

var sensorRoutes = httpSensorRoutes{
	{
		route: "/temperature",
	},
	{
		route: "/gas",
	},
	{
		route: "/luminosity",
	},
}

func AddReading(sensor structs.Sensor) {
	if strings.Contains(sensor.Name, "temperature") {
		go makeTempRequest(ADD)
	} else if strings.Contains(sensor.Name, "gas") {
		go makeGasRequest(ADD)
	} else if strings.Contains(sensor.Name, "luminosity") {
		go makeLuminosityRequest(ADD)
	}
}

func RemoveSensor(sensor structs.Sensor){
	go switchToSensorView()
	go removeSensor(sensor)
}

func AppendReading() {
	go makeRequests()
	go switchToSensorView()
}

func NumberOfSensors() int32 {
	call,err := bus.DbusSensorImpl.FindDbusCall(".numberOfSensors")
	if err == nil {
		return call.NumberOfSensors()
	} else{
		go parseInitError("News.numberOfNews")
	}
	return -1
}

func removeSensor(sensor structs.Sensor){
	call,err := bus.DbusSensorImpl.FindDbusCall(".removeSensor")
	if err == nil {
		result := call.RemoveSensor(sensor.Name)
		if !result {
			parseReplyError("Sensor.removeSensor")
		}
	}else{
		parseInitError("Sensor.removeSensor")
	}
}


func makeRequests(){
	go makeLuminosityRequest(APPEND)
	go makeGasRequest(APPEND)
	go makeTempRequest(APPEND)
}


func makeLuminosityRequest(op operation){
	reply2,err2 := makeSensorRequest(2)
	if err2 == nil{
		if op == APPEND {
			appendReading(reply2)
		} else{
			addSensorReading(reply2[0].Name,reply2[0].Values[0])
		}
	} else{
		notifyError(err2.Error())
	}
}

func makeGasRequest(op operation){
	reply1,err1 := makeSensorRequest(1)
	if err1 == nil{
		if op == APPEND {
			appendReading(reply1)
		} else{
			addSensorReading(reply1[0].Name,reply1[0].Values[0])
		}
	} else{
		notifyError(err1.Error())
	}
}

func makeTempRequest(op operation){
	reply,err := makeSensorRequest(0)
	if err == nil {
		if op == APPEND {
			appendReading(reply)
		} else{
			addSensorReading(reply[0].Name,reply[0].Values[0])
		}
	} else{
		notifyError(err.Error())
	}
}

func makeSensorRequest(index uint8) (structs.SensorReply, error) {
	var Url *url.URL
	Url, err := url.Parse(SENSOR_BASE_URL)
	if err != nil {
		log.Print("Failed to parse " + SENSOR_BASE_URL + " :addReading method")
	} else {
		Url.Path += sensorRoutes[index].route
		params := url.Values{}
		Url.RawQuery = params.Encode()
		resp, httpErr := http.Get(Url.String())
		if httpErr != nil {
			log.Print("Failed to make request to get " + Url.String())
		} else {
			defer resp.Body.Close()
			decoder := json.NewDecoder(resp.Body)
			var reply structs.SensorReply
			if decErr := decoder.Decode(&reply); decErr != nil {
				log.Print("Failed to decode sensor reply")
				var err1 structs.SensorErrorReply
				if decErr := decoder.Decode(&err1); decErr != nil {
					notifyError(err1.Error)
				}
			} else {
				return reply, nil
			}
		}
	}
	return nil, err
}

func appendReading(reply structs.SensorReply) {
	for _, v := range reply {
		appendSensorReading(v.Name, v.Unit, v.Values)
	}
}

func addSensorReading(name string,value float64){
	call, err := bus.DbusSensorImpl.FindDbusCall(".addReading")
	if err == nil {
		result := call.AddReading(name, value)
		if !result {
			parseReplyError(".addReading")
		}
	} else {
		parseInitError("Sensor.addReading")
	}
}

func appendSensorReading(name string, unit string, values []float64) {
	call, err := bus.DbusSensorImpl.FindDbusCall(".appendSensor")
	if err == nil {
		result := call.AppendSensor(name, unit, values)
		if !result {
			parseReplyError(".appendSensor")
		}
	} else {
		parseInitError("Sensor.appendSensor")
	}
}


func switchToSensorView(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setSensorsViewAsRoot")
	if err == nil {
		call.SetWeatherViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to Sensors")
	}
}