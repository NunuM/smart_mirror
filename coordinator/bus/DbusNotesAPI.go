package bus

import (
	"errors"
	"log"
	"strings"
)

const _NOTES_INTERFACE_PATH = "io.smart.Notes"
const _NOTES_OBJECT_PATH = "/io/sensor/Notes"

type DbusNotes struct {
	_InterfacePath string
	_ObjectPath string
	Method string
}

type DbusNotesAPI  []DbusNotes

var DbusNotesAPIImpl = DbusNotesAPI{
	{
		_InterfacePath:_NOTES_INTERFACE_PATH,
		_ObjectPath:_NOTES_OBJECT_PATH,
		Method:".appendNote",
	},
	{
		_InterfacePath:_NOTES_INTERFACE_PATH,
		_ObjectPath:_NOTES_OBJECT_PATH,
		Method:".editNoteAlarm",
	},
	{
		_InterfacePath:_NOTES_INTERFACE_PATH,
		_ObjectPath:_NOTES_OBJECT_PATH,
		Method:".editNoteTitle",
	},
	{
		_InterfacePath:_NOTES_INTERFACE_PATH,
		_ObjectPath:_NOTES_OBJECT_PATH,
		Method:".numbersOfNotes",
	},
	{
		_InterfacePath:_NOTES_INTERFACE_PATH,
		_ObjectPath:_NOTES_OBJECT_PATH,
		Method:".removeNote",
	},
}


func (d *DbusNotes) AppendNote(title string,notifiable bool,alarm string) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, title,notifiable,alarm)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}


func (d *DbusNotes) EditNoteAlarm(title string,alarm string) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, title,alarm)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}

func (d *DbusNotes) EditNoteTitle(oldTitle string,newTitle string) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, oldTitle,newTitle)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}

func (d *DbusNotes) NumberOfNotes() int32{
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

func (d *DbusNotes) RemoveNote(title string) bool{
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, title)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			return EndDbusCall(call,d.Method)
		}
	}
	return false
}


func (d *DbusNotesAPI) FindDbusCall(methodName string) (DbusNotes,error){
	for _, call := range DbusNotesAPIImpl{
		if strings.EqualFold(call.Method,methodName){
			return call,nil
		}
	}
	return DbusNotes{},errors.New("Dbus Call Not Found")
}