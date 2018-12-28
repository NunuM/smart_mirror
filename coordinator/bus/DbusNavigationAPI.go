package bus

import (
	"errors"
	"log"
	"strings"
)

const _NAVIGATION_INTERFACE_PATH = "io.smart.Navigation"
const _NAVIGATION_OBJECT_PATH = "/io/smart/Navigation"

type DbusNavigation struct {
	_InterfacePath string
	_ObjectPath    string
	Method         string
}

type DbusNavigationAPI []DbusNavigation

var DbusnavigationAPIImpl = DbusNavigationAPI{
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".appendView",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setApplicationsViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setHomeViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setMediaViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setNewsViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setNotesViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setSensorsViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setWeatherViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setTrafficViewAsRoot",
	},
	{
		_InterfacePath: _NAVIGATION_INTERFACE_PATH,
		_ObjectPath:    _NAVIGATION_OBJECT_PATH,
		Method:         ".setDinamicViewAsRoot",
	},
}

func (d *DbusNavigation) AppendView(viewName string, viewPath string) bool {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, viewName, viewPath)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			return EndDbusCall(call, d.Method)
		}
	}
	return false
}

func (d *DbusNavigation) SetApplicationViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetHomeViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetMediaViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetNewsViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetNotesViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetSensorsViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetWeatherViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetTrafficViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigation) SetDinamicViewAsRoot() {
	obj, err := OpenDbusCall(d._InterfacePath, d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else {
			EndDbusCall(call, d.Method)
		}
	}
}

func (d *DbusNavigationAPI) FindDbusCall(methodName string) (DbusNavigation, error) {
	for _, call := range DbusnavigationAPIImpl {
		if strings.EqualFold(call.Method, methodName) {
			return call, nil
		}
	}
	return DbusNavigation{}, errors.New("Dbus Call Not Found")
}
