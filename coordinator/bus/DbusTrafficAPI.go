package bus

import (
	"errors"
	"log"
	"strings"
)

const _TRAFFIC_INTERFACE_PATH = "io.smart.Traffic"
const _TRAFFIC_OBJECT_PATH = "/io/smart/Traffic"

type DbusTraffic struct {
	_InterfacePath string
	_ObjectPath    string
	Method         string
}

type DbusTrafficAPI []DbusTraffic

var DbusTrafficAPIImpl = DbusTrafficAPI{
	{
		_InterfacePath: _TRAFFIC_INTERFACE_PATH,
		_ObjectPath:    _TRAFFIC_OBJECT_PATH,
		Method:         ".appendTraffic",
	},
	{
		_InterfacePath: _TRAFFIC_INTERFACE_PATH,
		_ObjectPath:    _TRAFFIC_OBJECT_PATH,
		Method:         ".appendTrafficIncidentsAsJsonArray",
	},
	{
		_InterfacePath: _TRAFFIC_INTERFACE_PATH,
		_ObjectPath:    _TRAFFIC_OBJECT_PATH,
		Method:         ".numberOfIncidents",
	},
	{
		_InterfacePath: _TRAFFIC_INTERFACE_PATH,
		_ObjectPath:    _TRAFFIC_OBJECT_PATH,
		Method:         "removeIncident",
	},
}



func (d *DbusTraffic) AppendTraffic(incidentId string,latitude float64, longitude float64,description string,roadClosed bool ) bool {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, incidentId,latitude,longitude,description,roadClosed)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			return EndDbusCall(call, d.Method)
		}
	}
	return false
}

func (d *DbusTraffic) AppendTrafficAsJson(str string) bool {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if strings.Contains(str, "error") {
		DbusNotififyError(str)
	}
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, str)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			return EndDbusCall(call, d.Method)
		}
	}
	return false
}

func (d *DbusTraffic) NumberOfIncidents() (int32) {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
		var result int32
		call.Store(&result)
		return result
	}
	return -1
}

func (d *DbusTraffic) RemoveIncident(incidentId string) bool {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, incidentId)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			return EndDbusCall(call, d.Method)
		}
	}
	return false
}

func (d *DbusTrafficAPI) FindDbusCall(methodName string) (DbusTraffic, error) {
	for _, call := range DbusTrafficAPIImpl {
		if strings.EqualFold(call.Method, methodName) {
			return call, nil
		}
	}
	return DbusTraffic{}, errors.New("Dbus Call Not Found")
}
