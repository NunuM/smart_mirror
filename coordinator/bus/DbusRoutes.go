package bus

import (
	"bytes"
	"coordinator/structs"
	"encoding/json"
	"errors"
	"log"
	"os/exec"
	"strings"
)

type _DbusCall struct {
	_InterfacePath string
	_ObjectPath string
	Method string
}


type DbusCalls []_DbusCall

var Calls = DbusCalls{
	{
		"io.smart.News",
		"/io/smart/News",
		".appendNews",
	},
}



func (d *DbusCalls) FindDbusCall(methodName string) (_DbusCall,error){
	for _, call := range Calls{
		if strings.EqualFold(call.Method,methodName){
			return call,nil
		}
	}
	return _DbusCall{},errors.New("Dbus Call Not Found")
}



func (DbusCalls) News_execute(news structs.Newsheadlines) string{
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

