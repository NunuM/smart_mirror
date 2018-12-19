package http_service

import (
	"coordinator/bus"
	"coordinator/structs"
	"encoding/json"
	"net/http"
)

func httpTrafficHandler(w http.ResponseWriter,r *http.Request){

}

func httpNewsHandler(w http.ResponseWriter,r * http.Request){
	var news structs.Newsheadlines
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&news); err != nil {
		respondWithError(w,http.StatusBadRequest,"Invalid request payload")
	}
	defer r.Body.Close()
	call,err1 := bus.Calls.FindDbusCall(".appendNews")
	if err1 == nil {
		go call.DbusStringCall(call.Functions.NNews.FetchNews(news))
	}
	reply(w)
}

func httpMusicPlayHandler(w http.ResponseWriter,r * http.Request){

}

func httpMusicCurrentHandler(w http.ResponseWriter,r * http.Request){

}

func httpMusicStopHandler(w http.ResponseWriter,r * http.Request){

}

func httpBlockbusterHandler(w http.ResponseWriter,r * http.Request){

}

func httpWeatherHandler(w http.ResponseWriter,r * http.Request){

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
