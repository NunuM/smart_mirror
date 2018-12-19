package main

import (
	"coordinator/http_service"
	"log"
	"net/http"
)

func main(){

	/*
	//just a dbus test
	var arr = [...]float64{0.3,0.4}
	dbus.DBus_append_sensor("test","meters",arr[:])
	*/

	router := http_service.New_router()
	log.Fatal(http.ListenAndServe(":8080",router))
}
