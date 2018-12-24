package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"os"
)

func main() {
	var types typeSlice
	var severity severitySlice
	var location string
	flag.Var(&types, "type", "Optional: list of comma separated integers that represent the following types "+
		"1:Accident,"+
		"2:Congestion,"+
		"3:DisabledVehicle,"+
		"4:MassTransit,"+
		"5:Misc,"+
		"6:OtherNews,"+
		"7:PlannedEvent,"+
		"8:RoadHazard,"+
		"9:Construction,"+
		"10:Alert,"+
		"11:Weather")
	flag.Var(&severity, "severity",
		"Optional: list of comma separated integers that represent: "+
			"1:LowImpact, "+
			"2:Minor, "+
			"3:Moderate,"+
			"4:Serious")

	flag.StringVar(&location, "location", "", "Required: The name of the local to check the traffic for")
	boolPtr := flag.Bool("locationCodes", false, "Optional: Include Location Codes. Default: false")
	var required = []string{"location"}

	flag.Parse()
	seen := make(map[string]bool)
	flag.Visit(func(f *flag.Flag) { seen[f.Name] = true })
	for _, req := range required {
		if !seen[req] || location == "" {
			fmt.Fprintf(os.Stderr, "missing required -%s argument/flag\n", req)
			os.Exit(2)
		}
	}


	var bbox, err = GetBBox(location)
	if err == nil {
		var traffic = TrafficIncident{bbox, *boolPtr, severity, types}
		resp, err1 := traffic.makeRequest()
		if err1 == nil {
			res, err1 := json.MarshalIndent(resp.ResourceSets, "", "    ")
			if err1 == nil {
				fmt.Println(string(res))
			} else {
				fmt.Println(err1)
			}
		} else {
			fmt.Print(err1)
		}
	} else {
		fmt.Print(err)
	}
}
