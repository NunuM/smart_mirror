package bus

import (
	"errors"
	"github.com/godbus/dbus"
	"log"
)

func DbusNotififyError(str string){
	//TODO Notify Gui on error - must be hardcoded path
}

func OpenDbusCall(interfacePath string,objectPath string) (dbus.BusObject,error){
	var bus dbus.BusObject
	conn,err := dbus.SessionBus()
	if err != nil {
		log.Printf("Unable to open session bus")
	} else{
		bus = conn.Object(interfacePath,dbus.ObjectPath(objectPath))
		return bus,nil
	}
	return bus,errors.New("session bus failed to open")
}


func EndDbusCall(call *dbus.Call,method string){
	var reply bool
	call.Store(&reply)
	log.Printf("method %s invoked. reply %t",method,reply)
}

