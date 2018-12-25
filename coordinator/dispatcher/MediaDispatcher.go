package dispatcher

import (
	"bytes"
	"coordinator/bus"
	"os/exec"
)

//TODO Implement song methods

func blockbuster_execute(numberOfMovies string) string{
	cmd := exec.Command("blockbuster","-j", "-l "+numberOfMovies)
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err := cmd.Run()
	str := parse_output(err,"blockbuster",*out)
	return str
}


func AppendMovie(numberOfMovies int32){
	go switchToMediaView()
	if numberOfMovies == 1{
		go appendMovie()
	} else{
		go appendMovies(numberOfMovies)
	}
}

func appendMovie(){
	call,err := bus.DbusMediaAPIImpl.FindDbusCall(".appendMovie")
	if err == nil {
		result := call.AppendMovie(blockbuster_execute("1"))
		if !result {
			parseReplyError("Media.appendMovie")
		}
	}else{
		parseInitError("Media.appendMovie")
	}
}

func appendMovies(numberOfMovies int32){
	call,err := bus.DbusMediaAPIImpl.FindDbusCall(".appendMovie")
	if err == nil {
		result := call.AppendMovie(blockbuster_execute(string(numberOfMovies)))
		if !result {
			parseReplyError("Media.appendMovie")
		}
	}else{
		parseInitError("Media.appendMovie")
	}
}

func NumberOfMovies() int32{
	call,err := bus.DbusMediaAPIImpl.FindDbusCall(".numbersOfMovies")
	if err == nil {
		return call.NumberOfMovies()
	} else{
		go parseInitError("Media.numberOfMovies")
	}
	return -1
}


func switchToMediaView(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setMediaViewAsRoot")
	if err == nil {
		call.SetMediaViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to News")
	}
}




