package dispatcher

import (
	"coordinator/bus"
	"coordinator/structs"
)

func SetNewsViewAsRoot(){
	go switchToNewsView()
}

func SetMediaViewAsRoot(){
	go switchToMediaView()
}

func SetNotesViewAsRoot(){
	go switchToNotesView()
}

func SetTrafficViewAsRoot(){
	go switchToTrafficView()
}

func SetWeatherViewAsRoot(){
	go switchToWeatherView()
}

func SetApplicationsViewAsRoot(){
	go setApplicationsViewAsRoot()
}

func setApplicationsViewAsRoot(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setApplicationsViewAsRoot")
	if err == nil {
		call.SetNewsViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to Applications")
	}
}


func SetDinamicViewAsRoot(){
 go setDinamicViewAsRoot()
}

func setDinamicViewAsRoot(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setDinamicViewAsRoot")
	if err == nil {
		call.SetNewsViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to Dinamic")
	}
}


func AppendNavigationView(view structs.View){
	go appendNavigationView(view)
}

func appendNavigationView(view structs.View){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".appendView")
	if err == nil {
		result := call.AppendView(view.ViewName,view.ViewPath)
		if !result {
			parseReplyError("Navigation.AppendView")
		}
	}else{
		parseInitError("Navigation.AppendView")
	}
}

