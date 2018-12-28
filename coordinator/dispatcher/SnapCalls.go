package dispatcher

import (
	"bytes"
	"encoding/json"
)


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




