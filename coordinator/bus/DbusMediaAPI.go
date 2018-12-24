package bus

import (
	"errors"
	"log"
	"strings"
)


const _MEDIA_INTERFACE_PATH = "io.smart.Media"
const _MEDIA_OBJECT_PATH = "/io/smart/Media"


type DbusMedia struct {
	_InterfacePath string
	_ObjectPath string
	Method string
}

type DbusMediaAPI  []DbusMedia

var DbusMediaAPIImpl = DbusMediaAPI{
	{
		_InterfacePath:_MEDIA_INTERFACE_PATH,
		_ObjectPath:_MEDIA_OBJECT_PATH,
		Method:".appendMedia",
	},
	{
		_InterfacePath:_MEDIA_INTERFACE_PATH,
		_ObjectPath:_MEDIA_OBJECT_PATH,
		Method:".currentPlayingSong",
	},
	{
		_InterfacePath:_MEDIA_INTERFACE_PATH,
		_ObjectPath:_MEDIA_OBJECT_PATH,
		Method:".numberOfMovies",
	},
	{
		_InterfacePath:_MEDIA_INTERFACE_PATH,
		_ObjectPath:_MEDIA_OBJECT_PATH,
		Method:".songHasStopped",
	},
}

func (d *DbusMedia) AppendMovie(entry string){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if strings.Contains(entry,"error"){
		DbusNotififyError(entry)
	}
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, entry)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}


func (d *DbusMedia) BulkMovieInsert(entry string){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if strings.Contains(entry,"error"){
		DbusNotififyError(entry)
	}
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, entry)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}

func (d *DbusMedia) CurrentPlayingSong(songName string){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if strings.Contains(songName,"error"){
		DbusNotififyError(songName)
	}
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0, songName)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}

func (d *DbusMedia) NumberOfMovies() (int32){
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

func (d *DbusMedia) SonghasStopped(){
	obj,err := OpenDbusCall(d._InterfacePath,d._ObjectPath)
	if err == nil {
		call := obj.Call(d._InterfacePath+d.Method, 0)
		if call.Err != nil {
			log.Printf("Invocation on interface %s method %s failed with error %v", d._InterfacePath, d.Method, call.Err)
		} else{
			EndDbusCall(call,d.Method)
		}
	}
}


func (d *DbusMediaAPI) FindDbusCall(methodName string) (DbusMedia,error) {
	for _, call := range DbusMediaAPIImpl {
		if strings.EqualFold(call.Method, methodName) {
			return call, nil
		}
	}
	return DbusMedia{}, errors.New("Dbus Call Not Found")
}
