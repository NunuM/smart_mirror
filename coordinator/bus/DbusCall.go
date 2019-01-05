package bus

import (
	"errors"
	"github.com/godbus/dbus"
	"log"
)

func DbusNotififyError(str string){
	obj,err := OpenDbusCall("io.smart.Notification","/io/smart/Notification")
	if err == nil {
		call := obj.Call("io.smart.Notification.notification", 0, 0,str)
		if call.Err != nil {
			log.Printf("Invocation on interface io.smart.Notification method notification failed with error %v", call.Err)
		} else{
			EndDbusCall(call,"notification")
		}
	}
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


func EndDbusCall(call *dbus.Call,method string) bool{
	var reply bool
	call.Store(&reply)
	log.Printf("method %s invoked. reply %t",method,reply)
	return reply
}

