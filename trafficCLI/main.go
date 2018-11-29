package main

import (
	"flag"
	"fmt"
	"os"
)




func main(){
	var point pointSlice
	var types typeSlice
	var severity severitySlice
	flag.Var(&types,"type","Optional: list of comma separated integers that represent the following types " +
		"1:Accident," +
		"2:Congestion," +
		"3:DisabledVehicle," +
		"4:MassTransit," +
		"5:Misc," +
		"6:OtherNews," +
		"7:PlannedEvent," +
		"8:RoadHazard," +
		"9:Construction," +
		"10:Alert," +
		"11:Weather")
	flag.Var(&severity,"severity",
		"Optional: list of comma separated integers that represent: " +
		"1:LowImpact, " +
		"2:Minor, " +
		"3:Moderate: " +
		"4:Serious")

	flag.Var(&point, "point", "Required : list of 2 floats representing Latitude and Longitude")
	boolPtr := flag.Bool("locationCodes",false,"Optional: Include Location Codes. Default: false")
	intPtr := flag.Int("distance",-1,"Required: Int value > 0 and <500")
	var required = []string{"point","distance"}
	flag.Parse()
	seen := make(map[string]bool)
	flag.Visit(func(f *flag.Flag) { seen[f.Name] = true })
	for _, req := range required {
		if !seen[req] {
			fmt.Fprintf(os.Stderr, "missing required -%s argument/flag\n", req)
			os.Exit(2)
		}
	}

	var bbox = getBoundsFromLatLng(point,intPtr)
	var traffic = TrafficIncident{bbox,*boolPtr,severity,types}
	resp,err := traffic.makeRequest()
	if err == nil {
		fmt.Print(resp.ResourceSets)
	}else{
		fmt.Print(err)
	}
}



