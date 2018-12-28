package dispatcher

import (
	"bytes"
	"coordinator/bus"
	"coordinator/structs"
	"log"
	"os/exec"
)

func traffic_execute(traffic structs.Traffic) string{
	var cmd exec.Cmd
	var trafficServerityParam string
	if traffic.Severity != nil && len(*traffic.Severity) > 0 {
		for i,sev := range *traffic.Severity{
			trafficServerityParam += string(sev)
			if i != len(*traffic.Severity)-1{
				trafficServerityParam=","
			}
		}
	}
	var typeParam string
	if traffic.TypeV != nil && len(*traffic.TypeV) > 0 {
		for i,t := range *traffic.TypeV{
			typeParam += string(t)
			if i != len(*traffic.TypeV)-1{
				typeParam=","
			}
		}
	}
	if traffic.Severity != nil && traffic.TypeV != nil && len(*traffic.Severity)>0 && len(*traffic.TypeV)>0{
		cmd = *exec.Command("trafficz","-location",traffic.Location,"-severity",trafficServerityParam,"-type",typeParam)
	} else if traffic.Severity != nil && len(*traffic.Severity) > 0 {
		cmd = *exec.Command("trafficz","-location",traffic.Location,trafficServerityParam)
	} else if traffic.TypeV != nil && len(*traffic.TypeV)>0{
		cmd = *exec.Command("trafficz","-location",traffic.Location,typeParam)
	} else{
		cmd = *exec.Command("trafficz","-location",traffic.Location)
	}
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()
	str := parse_output(err1,"trafficz",*out)
	log.Print("Traffic Call Executed")
	return str
}


func AppendTraffic(traffic structs.Traffic){
	//go switchToTrafficView()
	go appendTrafficAsJson(traffic)
}

func appendTrafficAsJson(traffic structs.Traffic){
	call,err := bus.DbusTrafficAPIImpl.FindDbusCall(".appendTrafficIncidentsAsJsonArray")
	if err == nil {
		result := call.AppendTrafficAsJson(traffic_execute(traffic))
		if !result {
			parseReplyError("Traffic.AppendTrafficIncidentsAsJsonArray")
		}
	}else{
		parseInitError("Traffic.AppendTrafficIncidentsAsJsonArray")
	}
}


func NumberOfIncidents() int32{
	call,err := bus.DbusTrafficAPIImpl.FindDbusCall(".numberOfIncidents")
	if err == nil {
		return call.NumberOfIncidents()
	} else{
		go parseInitError("Traffic.numberOfIncidents")
	}
	return -1
}


func RemoveIncident(incidentId string){
	go switchToTrafficView()
	go removeIncident(incidentId)
}

func removeIncident(incidentId string){
	call,err := bus.DbusTrafficAPIImpl.FindDbusCall(".removeIncident")
	if err == nil {
		result := call.RemoveIncident(incidentId)
		if !result {
			parseReplyError("Traffic.RemoveIncident")
		}
	}else{
		parseInitError("Traffic.RemoveIncident")
	}
}

func switchToTrafficView(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setTrafficViewAsRoot")
	if err == nil {
		call.SetTrafficViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to News")
	}
}
