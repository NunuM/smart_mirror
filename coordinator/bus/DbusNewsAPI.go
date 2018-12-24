package bus

import (
	"errors"
	"log"
	"strings"
)


const _NEWS_INTERFACE_PATH = "io.smart.News"
const _NEWS_OBJECT_PATH = "/io/smart/News"

type DbusNews struct {
	_InterfacePath string
	_ObjectPath string
	Method string
}

type DbusNewsAPI  []DbusNews

var DbusNewsAPIImpl = DbusNewsAPI{
	{
		_InterfacePath: _NEWS_INTERFACE_PATH,
		_ObjectPath:    _NEWS_OBJECT_PATH,
		Method:         ".appendNews",
	},
	{
		_InterfacePath: _NEWS_INTERFACE_PATH,
		_ObjectPath:    _NEWS_OBJECT_PATH,
		Method:         ".numberOfNews",
	},
	{
		_InterfacePath: _NEWS_INTERFACE_PATH,
		_ObjectPath:    _NEWS_OBJECT_PATH,
		Method:         ".removeNews",
	},
}

func (d *DbusNews) AppendNews(str string){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if strings.Contains(str,"error"){
		DbusNotififyError(str)
	}
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, str)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}


func (d *DbusNews) NumberOfNews() (int32){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
		var result int32
		call.Store(&result)
		return result
	}
	return -1
}


func (d *DbusNews) RemoveNews(title string){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, title)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}

}


func (d *DbusNewsAPI) FindDbusCall(methodName string) (DbusNews,error){
	for _, call := range DbusNewsAPIImpl{
		if strings.EqualFold(call.Method,methodName){
			return call,nil
		}
	}
	return DbusNews{},errors.New("Dbus Call Not Found")
}