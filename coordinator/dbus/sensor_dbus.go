package dbus

import "github.com/godbus/dbus"


const DBUS_SENSOR_INTERFACE_PATH = "io.smart.SSensor"
const DBUS_SENSOR_OBJECT_PATH = "/io/smart/OSensor"




func DBus_append_sensor(name string,unit string,readings []float64){
	conn, err := dbus.SessionBus()
	if err != nil {
		panic(err)
	}
	obj := conn.Object(DBUS_SENSOR_INTERFACE_PATH, DBUS_SENSOR_OBJECT_PATH)
	call := obj.Call("io.smart.Sensor.appendSensor", 0, name,unit,readings)
	if call.Err != nil {
		panic(call.Err)
	}
}

func DBus_add_reading(name string,reading float64){
	conn, err := dbus.SessionBus()
	if err != nil {
		panic(err)
	}
	obj := conn.Object(DBUS_SENSOR_INTERFACE_PATH, DBUS_SENSOR_OBJECT_PATH)
	call := obj.Call(DBUS_SENSOR_OBJECT_PATH+"addReading", 0, name,reading)
	if call.Err != nil {
		panic(call.Err)
	}
}

func Dbus_remove_sensor(name string){
	conn, err := dbus.SessionBus()
	if err != nil {
		panic(err)
	}
	obj := conn.Object(DBUS_SENSOR_INTERFACE_PATH, DBUS_SENSOR_OBJECT_PATH)
	call := obj.Call(DBUS_SENSOR_OBJECT_PATH+"removeSensor", 0, name)
	if call.Err != nil {
		panic(call.Err)
	}
}