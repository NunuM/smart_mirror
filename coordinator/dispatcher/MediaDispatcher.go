package dispatcher

import (
	"bytes"
	"coordinator/bus"
	"coordinator/structs"
	"encoding/json"
	"log"
	"net/http"
	"net/url"
	"os/exec"
	"strings"
)

//TODO Implement song methods

const BASE_URL = "http://127.0.0.1:8090"

type httpSongStreamRoute struct {
	route string
}

type httpSongStreamRoutes []httpSongStreamRoute

var routes = httpSongStreamRoutes{
	{
		route: "/play",
	},
	{
		route: "/stop",
	},
	{
		route: "/pause",
	},
	{
		route: "/up",
	},
	{
		route: "/down",
	},
}

func blockbuster_execute(numberOfMovies string) string {
	cmd := exec.Command("blockbuster", "-j", "-l",numberOfMovies)
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err := cmd.Run()
	str := parse_output(err, "blockbuster", *out)
	return str
}

func AppendMovie(numberOfMovies int32) {
	go switchToMediaView()
	if numberOfMovies == 1 {
		go appendMovie()
	} else {
		go appendMovies(numberOfMovies)
	}
}

func appendMovie() {
	call, err := bus.DbusMediaAPIImpl.FindDbusCall(".bulkMoviesInsertion")
	if err == nil {
		result := call.AppendMovie(blockbuster_execute("1"))
		if !result {
			parseReplyError("Media.appendMovie")
		}
	} else {
		parseInitError("Media.appendMovie")
	}
}

func appendMovies(numberOfMovies int32) {
	call, err := bus.DbusMediaAPIImpl.FindDbusCall(".bulkMoviesInsertion")
	if err == nil {
		result := call.AppendMovie(blockbuster_execute(string(numberOfMovies)))
		if !result {
			parseReplyError("Media.appendMovie")
		}
	} else {
		parseInitError("Media.appendMovie")
	}
}

func NumberOfMovies() int32 {
	call, err := bus.DbusMediaAPIImpl.FindDbusCall(".numbersOfMovies")
	if err == nil {
		return call.NumberOfMovies()
	} else {
		go parseInitError("Media.numberOfMovies")
	}
	return -1
}

func switchToMediaView() {
	call, err := bus.DbusnavigationAPIImpl.FindDbusCall(".setMediaViewAsRoot")
	if err == nil {
		call.SetMediaViewAsRoot()
	} else {
		parseInitError("Error setting Navigation View to News")
	}
}

func PlaySong(query string){
	go playSong(query)
}

func StopSong(){
	go stopSong()
}

func playSong(query string){
	var Url *url.URL
	Url,err := url.Parse(BASE_URL)
	if err != nil {
		log.Print("Failed to parse "+BASE_URL+" :playSong method")
	} else{
		Url.Path += routes[0].route
		params := url.Values{}
		params.Add("search",query)
		Url.RawQuery = params.Encode()
		resp,httpErr := http.Get(Url.String())
		if httpErr != nil {
			log.Print("Failed to make request to play song "+Url.String())
		} else{
			defer resp.Body.Close()
			decoder := json.NewDecoder(resp.Body)
			var reply structs.SongStreamHttpReply
			if decErr := decoder.Decode(&reply); decErr!=nil{
				log.Print("Failed to decode play song reply")
			} else if strings.Contains(reply.Message,"failed"){
				log.Print("Play Song Request failed on the client side")
			} else{
				go playSongDbus(query)
				log.Print("Play Song Executed with Success")
			}
		}
	}
}

func stopSong(){
	var Url *url.URL
	Url,err := url.Parse(BASE_URL)
	if err != nil {
		log.Print("Failed to parse "+BASE_URL+" :stopSong method")
	} else{
		Url.Path += routes[1].route
		resp,httpErr := http.Get(Url.String())
		if httpErr != nil {
			log.Print("Failed to make request to stop song "+Url.String())
		} else{
			defer resp.Body.Close()
			decoder := json.NewDecoder(resp.Body)
			var reply structs.SongStreamHttpReply
			if decErr := decoder.Decode(&reply); decErr!=nil{
				log.Print("Failed to decode stop song reply")
			} else if strings.Contains(reply.Message,"failed"){
				log.Print("Stop Song Request failed on the client side")
			} else{
				log.Print("Stop Song Executed with Success")
				go stopSongDbus()
			}
		}
	}
}

func PauseSong(){
	go pauseSong()
}

func pauseSong(){
	var Url *url.URL
	Url,err := url.Parse(BASE_URL)
	if err != nil {
		log.Print("Failed to parse "+BASE_URL+" :pauseSong method")
	} else{
		Url.Path += routes[2].route
		resp,httpErr := http.Get(Url.String())
		if httpErr != nil {
			log.Print("Failed to make request to pause song "+Url.String())
		} else{
			defer resp.Body.Close()
			decoder := json.NewDecoder(resp.Body)
			var reply structs.SongStreamHttpReply
			if decErr := decoder.Decode(&reply); decErr!=nil{
				log.Print("Failed to decode pause song reply")
			} else if strings.Contains(reply.Message,"failed"){
				log.Print("Pause Song Request failed on the client side")
			} else{
				log.Print("Pause Song Executed with Success")
			}
		}
	}
}

func UpSongVolume(){
	go upSongVolume()
}


func upSongVolume(){
	var Url *url.URL
	Url,err := url.Parse(BASE_URL)
	if err != nil {
		log.Print("Failed to parse "+BASE_URL+" :upVolumeSong method")
	} else{
		Url.Path += routes[3].route
		resp,httpErr := http.Get(Url.String())
		if httpErr != nil {
			log.Print("Failed to make request to up volume song "+Url.String())
		} else{
			defer resp.Body.Close()
			decoder := json.NewDecoder(resp.Body)
			var reply structs.SongStreamHttpReply
			if decErr := decoder.Decode(&reply); decErr!=nil{
				log.Print("Failed to decode up volume song reply")
			} else if strings.Contains(reply.Message,"failed"){
				log.Print("Up Volume Song Request failed on the client side")
			} else{
				log.Print("Up Song Volume Executed with Success")
			}
		}
	}
}


func DownSongVolume(){
	go downSongVolume()
}


func downSongVolume(){
	var Url *url.URL
	Url,err := url.Parse(BASE_URL)
	if err != nil {
		log.Print("Failed to parse "+BASE_URL+" :downVolumeSong method")
	} else{
		Url.Path += routes[4].route
		resp,httpErr := http.Get(Url.String())
		if httpErr != nil {
			log.Print("Failed to make request to down volume song "+Url.String())
		} else{
			defer resp.Body.Close()
			decoder := json.NewDecoder(resp.Body)
			var reply structs.SongStreamHttpReply
			if decErr := decoder.Decode(&reply); decErr!=nil{
				log.Print("Failed to decode down volume song reply")
			} else if strings.Contains(reply.Message,"failed"){
				log.Print("Down Volume Song Request failed on the client side")
			} else{
				log.Print("Down Song Volume Executed with Success")
			}
		}
	}
}



func stopSongDbus(){
	call, err := bus.DbusMediaAPIImpl.FindDbusCall(".songHasStopped")
	if err == nil {
		result := call.SonghasStopped()
		if !result {
			parseReplyError("Media.songHasStopped")
		}
	} else {
		parseInitError("Media.songHasStopped")
	}
}


func playSongDbus(query string){
	call, err := bus.DbusMediaAPIImpl.FindDbusCall(".currentPlayingSong")
	if err == nil {
		result := call.CurrentPlayingSong(query)
		if !result {
			parseReplyError("Media.currentPlayingSong")
		}
	} else {
		parseInitError("Media.currentPlayingSong")
	}
}