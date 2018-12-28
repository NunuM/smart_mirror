package http_service

import (
	"coordinator/dispatcher"
	"coordinator/structs"
	"encoding/json"
	"net/http"
	"strings"
)

//TODO Fill missing methods


func httpAppendNewsHandler(w http.ResponseWriter,r * http.Request){
	var news structs.Newsheadlines
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&news); err != nil {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendNews(news)
		reply(w)
	}
}

func httpRemoveNewsHandler(w http.ResponseWriter,r * http.Request){
	var news structs.News
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&news); err != nil {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else{
		defer r.Body.Close()
		dispatcher.RemoveNews(news.Title)
		reply(w)
	}
}

func httpNumberOfNewsHandler(w http.ResponseWriter,r * http.Request){
	var response = dispatcher.NumberOfNews()
	if response == -1 {
		respondWithError(w,http.StatusInternalServerError,"Invalid number of News detected -1")
	} else{
		respondWithJson(w,http.StatusOK,response)
	}
}

func httpAppendWeatherHandler(w http.ResponseWriter,r * http.Request){
	var weather structs.Weather
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&weather); err != nil || "" == strings.TrimSpace(weather.Location) {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else{
		defer r.Body.Close()
		dispatcher.AppendWeather(weather)
		reply(w)
	}
}

func httpRemoveWeather(w http.ResponseWriter,r *http.Request){
  var weatherDate structs.WeatherDate
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&weatherDate); err != nil || "" == strings.TrimSpace(weatherDate.Date) {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else{
		defer r.Body.Close()
		dispatcher.RemoveWeather(weatherDate.Date)
		reply(w)
	}
}

func httpAppendMovies(w http.ResponseWriter,r *http.Request){
	var movie structs.Movies
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&movie); err != nil  {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendMovie(movie.NumberOfMovies)
		reply(w)
	}
}

func httpNumberOfMoviesHandler(w http.ResponseWriter,r * http.Request){
	var response = dispatcher.NumberOfMovies()
	if response == -1 {
		respondWithError(w,http.StatusInternalServerError,"Invalid number of Movies detected -1")
	} else{
		respondWithJson(w,http.StatusOK,response)
	}
}


func httpAppendTrafficHandler(w http.ResponseWriter,r *http.Request){
	var trafficParams structs.Traffic
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&trafficParams); err != nil || "" == strings.TrimSpace(trafficParams.Location) {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendTraffic(trafficParams)
		reply(w)
	}
}


func httpNumberOfTrafficIncidentsHandler(w http.ResponseWriter, r *http.Request){
	var response = dispatcher.NumberOfIncidents()
	if response == -1 {
		respondWithError(w,http.StatusInternalServerError,"Invalid number of Traffic Incidents detected -1")
	}else{
		respondWithJson(w,http.StatusOK,response)
	}
}



func httpRemoveIncidentHandler(w http.ResponseWriter,r *http.Request){
	var incident structs.Incident
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&incident); err != nil || "" == strings.TrimSpace(incident.IncidentId) {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else{
		defer r.Body.Close()
		dispatcher.RemoveIncident(incident.IncidentId)
		reply(w)
	}
}

func httpPlaySongHandler(w http.ResponseWriter,r *http.Request){
	var song structs.Music
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&song); err != nil || "" == strings.TrimSpace(song.Song_name) {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	} else{
		defer r.Body.Close()
		dispatcher.PlaySong(song.Song_name)
		reply(w)
	}
}

func httpPauseSongHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.PauseSong()
	reply(w)
}

func httpStopSongHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.StopSong()
	reply(w)
}

func httpUpSongVolumeHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.UpSongVolume()
	reply(w)
}

func httpDownSongVolumeHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.DownSongVolume()
	reply(w)
}

func httpSetMediaViewHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.SetMediaViewAsRoot()
	reply(w)
}

func httpSetNewsViewHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.SetNewsViewAsRoot()
	reply(w)
}

func httpSetNotesViewHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.SetNotesViewAsRoot()
	reply(w)
}

func httpSetSensorViewHandler(w http.ResponseWriter,r *http.Request){
	//TODO dispatch sensor view
	reply(w)
}

func httpSetTrafficViewHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.SetTrafficViewAsRoot()
	reply(w)
}

func httpSetWeatherViewHandler(w http.ResponseWriter,r *http.Request){
	dispatcher.SetMediaViewAsRoot()
	reply(w)
}



func httpOrganizerCreateHandler(w http.ResponseWriter,r * http.Request){

}

func httpOrganizerDeleteHandler(w http.ResponseWriter,r * http.Request){

}

func httpOrganizerHandler(w http.ResponseWriter,r * http.Request){

}

func httpSensorHandler(w http.ResponseWriter,r * http.Request){

}

func reply(w http.ResponseWriter){
	respondWithJson(w,http.StatusAccepted,map[string]string{"message": "processing"})
}

func respondWithError(w http.ResponseWriter,http_status_code int, message string){
	respondWithJson(w,http_status_code,map[string]string{"error": message})
}

func respondWithJson(w http.ResponseWriter,http_status_code int, playload interface{}){
	res,_ := json.Marshal(playload)
	w.Header().Set("Content-Type","application/json")
	w.WriteHeader(http_status_code)
	w.Write(res)
}
