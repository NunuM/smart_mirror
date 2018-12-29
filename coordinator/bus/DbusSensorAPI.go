package bus

import (
	"errors"
	"log"
	"strings"
)

const _SENSOR_INTERFACE_PATH = "io.smart.Notes"
const _SENSOR_OBJECT_PATH = "/io/sensor/Notes"

type DbusSensor struct {
	_InterfacePath string
	_ObjectPath string
	Method string
}

type DbusSensorAPI  []DbusSensor

var DbusSensorImpl = DbusSensorAPI{
	{
		_InterfacePath:_SENSOR_INTERFACE_PATH,
		_ObjectPath:_SENSOR_OBJECT_PATH,
		Method:".addReading",
	},
	{
		_InterfacePath:_SENSOR_INTERFACE_PATH,
		_ObjectPath:_SENSOR_OBJECT_PATH,
		Method:".appendSensor",
	},
	{
		_InterfacePath:_SENSOR_INTERFACE_PATH,
		_ObjectPath:_SENSOR_OBJECT_PATH,
		Method:".numberOfSensors",
	},
	{
		_InterfacePath:_SENSOR_INTERFACE_PATH,
		_ObjectPath:_SENSOR_OBJECT_PATH,
		Method:".removeSensor",
	},
}



func (d *DbusSensor) AddReading(name string,value float64) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, name,value)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}

func (d *DbusSensor) AppendSensor(name string,unit string,values []float64) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, name,unit,values)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}


func (d *DbusSensor) NumberOfSensors() int32{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
		var result int32
		call.Store(&result)
		return result
	}
	return -1
}


func (d *DbusSensor) RemoveSensor(name string) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, name)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}


func (d *DbusSensorAPI) FindDbusCall(methodName string) (DbusSensor,error){
	for _, call := range DbusSensorImpl{
		if strings.EqualFold(call.Method,methodName){
			return call,nil
		}
	}
	return DbusSensor{},errors.New("Dbus Call Not Found")
}