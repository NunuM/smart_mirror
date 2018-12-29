package bus

import (
"errors"
"log"
"strings"
)


const _REDDIT_INTERFACE_PATH = "io.smart.Reddit"
const _REDDIT_OBJECT_PATH = "/io/smart/Reddit"

type DbusReddit struct {
	_InterfacePath string
	_ObjectPath string
	Method string
}

type DbusRedditAPI  []DbusReddit

var DbusRedditAPIImpl = DbusRedditAPI{
	{
		_InterfacePath: _REDDIT_INTERFACE_PATH,
		_ObjectPath:    _REDDIT_OBJECT_PATH,
		Method:         ".appendRedditPosts",
	},
	{
		_InterfacePath: _REDDIT_INTERFACE_PATH,
		_ObjectPath:    _REDDIT_OBJECT_PATH,
		Method:         ".numberOfPosts",
	},
	{
		_InterfacePath: _REDDIT_INTERFACE_PATH,
		_ObjectPath:    _REDDIT_OBJECT_PATH,
		Method:         ".clearAllRedditPosts",
	},
}

func (d *DbusReddit) AppendPosts(str string) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if strings.Contains(str,"error"){
		DbusNotififyError(str)
	}
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, str)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}


func (d *DbusReddit) NumberOfPosts() (int32){
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


func (d *DbusReddit) ClearRedditPosts() bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}


func (d *DbusRedditAPI) FindDbusCall(methodName string) (DbusReddit,error){
	for _, call := range DbusRedditAPIImpl{
		if strings.EqualFold(call.Method,methodName){
			return call,nil
		}
	}
	return DbusReddit{},errors.New("Dbus Call Not Found")
}
