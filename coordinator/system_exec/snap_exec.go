package system_exec

import (
	"bytes"
	"coordinator/bus"
	"coordinator/structs"
	"encoding/json"
	"fmt"
	"log"
	"os/exec"
)



func Blockbuster_execute(){
	cmd := exec.Command("blockbuster","-j")
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err := cmd.Run()
	str := parse_output(err,"blockbuster",*out)
	fmt.Println(str)
}


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




//TODO Multiple return args vs single return interface
func SensorRequest(i interface{}) interface{}{

}

