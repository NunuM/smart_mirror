package system_exec

import (
	"bytes"
	"coordinator/structs"
	"encoding/json"
	"fmt"
	"log"
	"os/exec"
)



//TODO Rework this entire file

func parse_output(err error,service_name string,buff bytes.Buffer) (string){
	var str string
	if err == nil {
		str = string(buff.Bytes()[:])
	} else{
		btarr,_ := json.Marshal(
			exec_error{
				error:err.Error(),
				service_name:service_name,
			})
		str = string(btarr[:])
	}
	return str
}

type exec_error struct {
	error string `json:"error"`
	service_name string `json:"service_name"`
}


func Blockbuster_execute(){
	cmd := exec.Command("blockbuster","-j -l 10")
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err := cmd.Run()
	str := parse_output(err,"blockbuster",*out)
	fmt.Println(str)
}


func News_execute(news structs.Newsheadlines) string{
	var cmd exec.Cmd
	if news.CountryISO == ""{
		cmd = *exec.Command("newsheadlines")
	} else{
		cmd = *exec.Command("newsheadlines","-country "+news.CountryISO)
	}
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()
	str := parse_output(err1,"newsheadlines",*out)
	log.Print("News Call Executed")
	return str
}


func CallWeather(weather structs.Weather) structs.OutWeather{
	var cmd exec.Cmd
	if weather.Forecast != ""{
		cmd = *exec.Command("weather "+weather.Location+" --forecast")
	} else {
		cmd = *exec.Command("weather "+weather.Location)
	}
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err := cmd.Run()
	log.Print("Weather Call Executed")

	var w structs.OutWeather
	err1 := json.Unmarshal(out.Bytes()[:],&w)

	if err != nil {
		return structs.OutWeather{}
	} else if err1 != nil {
		return structs.OutWeather{}
	}

	return w
}



