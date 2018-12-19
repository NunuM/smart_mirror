package bus

import (
	"coordinator/structs"
	"coordinator/system_exec"
	"errors"
	"strings"
)



type Aggregator struct {
	NNews NewsAPI
}


type NewsAPI struct {
	FetchNews func(structs.Newsheadlines) string

}


var funcs = Aggregator{
	NNews: NewsAPI{
		FetchNews:system_exec.News_execute,
	},
}


type _DbusCall struct {
	_InterfacePath string
	_ObjectPath string
	Method string
	Functions Aggregator
}


type DbusCalls []_DbusCall

var Calls = DbusCalls{
	{
		"io.smart.News",
		"/io/smart/News",
		".appendNews",
		funcs,
	},
	{
		"io.smart.News",
		"/io/smart/News",
		".numberOfNews",
		funcs,
	},
	{
	"io.smart.News",
	"/io/smart/News",
	".removeNews",
	funcs,
	},
	{
		"io.smart.Weather",
		"/io/smart/Weather",
		".appendWeather",
		funcs,
	},
	{
	"io.smart.Weather",
	"/io/smart/Weather",
	".removeWeather",
	funcs,
	},
	{
	"io.smart.Sensor",
	"/io/smart/Sensor",
	".addReading",
	funcs,
	},
	{
		"io.smart.Sensor",
		"/io/smart/Sensor",
		".appendSensor",
		funcs,
	},
	{
		"io.smart.Sensor",
		"/io/smart/Sensor",
		".numberOfSensors",
		funcs,
	},
	{
		"io.smart.Sensor",
		"/io/smart/Sensor",
		".removeSensor",
		funcs,
	},
	{
		"io.smart.Notes",
		"/io/sensor/Notes",
		".appendNote",
		funcs,
	},
	{
	"io.smart.Notes",
	"/io/sensor/Notes",
	".editNoteAlarm",
	funcs,
	},
	{
		"io.smart.Notes",
		"/io/smart/Notes",
		".numbersOfNotes",
		funcs,
	},
	{
	"io.smart.Notes",
	"/io/smart/Nodes",
	".removeNote",
	funcs,
	},
	{
		"io.smart.Navigation",
		"/io/smart/Navigation",
		".appendView",
		funcs,
	},
	{
		"io.smart.Navigation",
		"/io/smart/Navigation",
		".setApplicationsViewAsRoot",
		funcs,
	},
	{
	"io.smart.Navigation",
	"/io/smart/Navigation",
	".setHomeViewAsRoot",
	funcs,
	},
	{
	"io.smart.Navigation",
	"/io/smart/Navigation",
	".setMediaViewAsRoot",
	funcs,
	},
	{
	"io.smart.Navigation",
	"/io/smart/Navigation",
	".setNewsViewAsRoot",
	funcs,
	},
	{
	"io.smart.Navigation",
	"/io/smart/Navigation",
	".setNotesViewAsRoot",
	funcs,
	},
	{
	"io.smart.Navigation",
	"/io/smart/Navigation",
	".setSensorsViewAsRoot",
	funcs,
	},
	{
		"io.smart.Navigation",
		"/io/smart/Navigation",
		".setWeatherViewAsRoot",
		funcs,
	},
	{
		"io.smart.Media",
		"/io/smart/Media",
		".appendMedia",
		funcs,
	},
	{
		"io.smart.Media",
		"/io/smart/Media",
		".currentPlayingSong",
		funcs,
	},
	{
		"io.smart.Media",
		"/io/smart/Media",
		".numberOfMovies",
		funcs,
	},
	{
		"io.smart.Media",
		"/io/smart/Media",
		".songHasStopped",
		funcs,
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



