package http_service

import (
	"coordinator/dispatcher"
	"coordinator/structs"
	"encoding/json"
	"net/http"
	"strings"
)

//TODO Fill missing methods

func httpAppendNewsHandler(w http.ResponseWriter, r *http.Request) {
	var news structs.Newsheadlines
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&news); err != nil {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendNews(news)
		reply(w)
	}
}

func httpRemoveNewsHandler(w http.ResponseWriter, r *http.Request) {
	var news structs.News
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&news); err != nil {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.RemoveNews(news.Title)
		reply(w)
	}
}

func httpNumberOfNewsHandler(w http.ResponseWriter, r *http.Request) {
	var response = dispatcher.NumberOfNews()
	if response == -1 {
		respondWithError(w, http.StatusInternalServerError, "Invalid number of News detected -1")
	} else {
		respondWithJson(w, http.StatusOK, response)
	}
}

func httpAppendWeatherHandler(w http.ResponseWriter, r *http.Request) {
	var weather structs.Weather
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&weather); err != nil || "" == strings.TrimSpace(weather.Location) {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendWeather(weather)
		reply(w)
	}
}

func httpRemoveWeather(w http.ResponseWriter, r *http.Request) {
	var weatherDate structs.WeatherDate
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&weatherDate); err != nil || "" == strings.TrimSpace(weatherDate.Date) {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.RemoveWeather(weatherDate.Date)
		reply(w)
	}
}

func httpAppendMovies(w http.ResponseWriter, r *http.Request) {
	var movie structs.Movies
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&movie); err != nil {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendMovie(movie.NumberOfMovies)
		reply(w)
	}
}

func httpNumberOfMoviesHandler(w http.ResponseWriter, r *http.Request) {
	var response = dispatcher.NumberOfMovies()
	if response == -1 {
		respondWithError(w, http.StatusInternalServerError, "Invalid number of Movies detected -1")
	} else {
		respondWithJson(w, http.StatusOK, response)
	}
}

func httpAppendTrafficHandler(w http.ResponseWriter, r *http.Request) {
	var trafficParams structs.Traffic
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&trafficParams); err != nil || "" == strings.TrimSpace(trafficParams.Location) {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendTraffic(trafficParams)
		reply(w)
	}
}

func httpNumberOfTrafficIncidentsHandler(w http.ResponseWriter, r *http.Request) {
	var response = dispatcher.NumberOfIncidents()
	if response == -1 {
		respondWithError(w, http.StatusInternalServerError, "Invalid number of Traffic Incidents detected -1")
	} else {
		respondWithJson(w, http.StatusOK, response)
	}
}

func httpRemoveIncidentHandler(w http.ResponseWriter, r *http.Request) {
	var incident structs.Incident
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&incident); err != nil || "" == strings.TrimSpace(incident.IncidentId) {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.RemoveIncident(incident.IncidentId)
		reply(w)
	}
}

func httpPlaySongHandler(w http.ResponseWriter, r *http.Request) {
	var song structs.Music
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&song); err != nil || "" == strings.TrimSpace(song.Song_name) {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.PlaySong(song.Song_name)
		reply(w)
	}
}

func httpPauseSongHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.PauseSong()
	reply(w)
}

func httpStopSongHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.StopSong()
	reply(w)
}

func httpUpSongVolumeHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.UpSongVolume()
	reply(w)
}

func httpDownSongVolumeHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.DownSongVolume()
	reply(w)
}

func httpSetMediaViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetMediaViewAsRoot()
	reply(w)
}

func httpSetNewsViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetNewsViewAsRoot()
	reply(w)
}

func httpSetNotesViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetNotesViewAsRoot()
	reply(w)
}

func httpSetSensorViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetSensorViewAsRoot()
	reply(w)
}

func httpSetTrafficViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetTrafficViewAsRoot()
	reply(w)
}

func httpSetWeatherViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetWeatherViewAsRoot()
	reply(w)
}

func httpSetHomeViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetHomeViewAsRoot()
	reply(w)
}

func httpAddDynamicViewHandler(w http.ResponseWriter, r *http.Request){
	var view structs.View
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&view); err != nil || strings.TrimSpace(view.ViewName) == "" || strings.TrimSpace(view.ViewPath) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AppendNavigationView(view)
		reply(w)
	}
}
func httpSetDynamicViewHandler(w http.ResponseWriter, r *http.Request){
	var view structs.View
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&view); err != nil || strings.TrimSpace(view.ViewName) == "" || strings.TrimSpace(view.ViewPath) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.SetDinamicViewAsRoot(view)
		reply(w)
	}
}


func httpSetApplicationViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetApplicationsViewAsRoot()
	reply(w)
}

func httpSetRedditViewHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.SetRedditViewAsRoot()
	reply(w)
}

func httpAppendRedditPostsHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.AppendRedditPosts()
	reply(w)
}

func httpNumberOfRedditPostsHandler(w http.ResponseWriter, r *http.Request) {
	var response = dispatcher.NumberOfPosts()
	if response == -1 {
		respondWithError(w, http.StatusInternalServerError, "Invalid number of Reddit Posts detected -1")
	} else {
		respondWithJson(w, http.StatusOK, response)
	}
}

func httpAppendSensorHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.AppendReading()
	reply(w)

}

func httpAddSensorHandler(w http.ResponseWriter, r *http.Request) {
	var sensor structs.Sensor
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&sensor); err != nil || strings.TrimSpace(sensor.Name) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.AddReading(sensor)
		reply(w)
	}
}

func httpRemoveSensorHandler(w http.ResponseWriter, r *http.Request) {
	var sensor structs.Sensor
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&sensor); err != nil || strings.TrimSpace(sensor.Name) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.RemoveSensor(sensor)
		reply(w)
	}
}

func httpNumberOfSensorssHandler(w http.ResponseWriter, r *http.Request) {
	var response = dispatcher.NumberOfSensors()
	if response == -1 {
		respondWithError(w, http.StatusInternalServerError, "Invalid number of Sensors detected -1")
	} else {
		respondWithJson(w, http.StatusOK, response)
	}
}

func httpLoadOrganizerNotesHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.LoadNotes()
	reply(w)
}

func httpLoadGCalendarNotesHandler(w http.ResponseWriter, r *http.Request) {
	dispatcher.LoadGCalanderNotes()
	reply(w)
}

func httpAppendNoteHandler(w http.ResponseWriter, r *http.Request) {
	var note structs.Note
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&note); err != nil || strings.TrimSpace(note.Title) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.CreateNote(note)
		reply(w)
	}
}

func httpEditNoteAlarmHandler(w http.ResponseWriter, r *http.Request) {
	var note structs.ModifiableNote
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&note); err != nil || strings.TrimSpace(note.NewTitle) == "" || note.Alarm == nil || strings.TrimSpace(*note.Alarm) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.EditNoteAlarm(note)
		reply(w)
	}
}

func httpEditNoteTitleHandler(w http.ResponseWriter, r *http.Request) {
	var note structs.ModifiableNote
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&note); err != nil || strings.TrimSpace(note.NewTitle) == "" || strings.TrimSpace(note.OldTitle) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.EditNoteTitle(note)
		reply(w)
	}
}

func httpRemoveNoteHandler(w http.ResponseWriter, r *http.Request) {
	var note structs.Note
	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&note); err != nil || strings.TrimSpace(note.Title) == "" {
		respondWithError(w, http.StatusBadRequest, "Invalid request payload")
	} else {
		defer r.Body.Close()
		dispatcher.RemoveNote(note)
		reply(w)
	}
}


func httpNumberOfNotesHandler(w http.ResponseWriter, r *http.Request) {
	var response = dispatcher.NumberOfNotes()
	if response == -1 {
		respondWithError(w, http.StatusInternalServerError, "Invalid number of Notes detected -1")
	} else {
		respondWithJson(w, http.StatusOK, response)
	}
}



func reply(w http.ResponseWriter) {
	respondWithJson(w, http.StatusAccepted, map[string]string{"message": "processing"})
}

func respondWithError(w http.ResponseWriter, http_status_code int, message string) {
	respondWithJson(w, http_status_code, map[string]string{"error": message})
}

func respondWithJson(w http.ResponseWriter, http_status_code int, playload interface{}) {
	res, _ := json.Marshal(playload)
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http_status_code)
	w.Write(res)
}
