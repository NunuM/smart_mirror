package bus

import (
	"errors"
	"github.com/godbus/dbus"
	"log"
)

func (d *_DbusCall) DbusStringCall(str string){
	obj,err := d.openCall()
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, str)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			d.endCall(call)
		}
	}
}

func (d *_DbusCall) DbusEmptyCall(str string){
	obj,err := d.openCall()
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, str)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			d.endCall(call)
		}
	}
}


func (d *_DbusCall) openCall() (dbus.BusObject,error){
	var bus dbus.BusObject
	conn,err := dbus.SessionBus()
	if err != nil {
		log.Printf("Unable to open session bus")
	} else{
		bus = conn.Object(d._InterfacePath,dbus.ObjectPath(d._ObjectPath))
		return bus,nil
	}
	return bus,errors.New("session bus failed to open")
}


func (d *_DbusCall) endCall(call *dbus.Call){
	var reply bool
	call.Store(&reply)
	log.Printf("method %s invoked. reply %t",d.Method,reply)
}

