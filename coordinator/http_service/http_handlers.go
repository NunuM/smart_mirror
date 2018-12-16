package http_service

import (
	"coordinator/system_exec"
	"coordinator/structs"
	"encoding/json"
	"net/http"
)

func http_traffic_handler(w http.ResponseWriter,r *http.Request){

}

func http_news_handler(w http.ResponseWriter,r * http.Request){
	var news structs.Newsheadlines
	decoder := json.NewDecoder(r.Body)
	if err:= decoder.Decode(&news); err != nil {
		respond_with_error(w,http.StatusBadRequest,"Invalid request payload")
	}
	defer r.Body.Close()
	go system_exec.News_execute(news)
	reply(w)
}

func http_music_play_handler(w http.ResponseWriter,r * http.Request){

}

func http_music_current_handler(w http.ResponseWriter,r * http.Request){

}

func http_music_stop_handler(w http.ResponseWriter,r * http.Request){

}

func http_blockbuster_handler(w http.ResponseWriter,r * http.Request){
	go system_exec.Blockbuster_execute()
	reply(w)
}

func http_weather_handler(w http.ResponseWriter,r * http.Request){

}

func http_organizer_create_handler(w http.ResponseWriter,r * http.Request){

}

func http_organizer_delete_handler(w http.ResponseWriter,r * http.Request){

}

func http_organizer_handler(w http.ResponseWriter,r * http.Request){

}

func http_sensor_handler(w http.ResponseWriter,r * http.Request){

}

func reply(w http.ResponseWriter){
	respond_with_json(w,http.StatusAccepted,map[string]string{"message": "processing"})
}

func respond_with_error(w http.ResponseWriter,http_status_code int, message string){
	respond_with_json(w,http_status_code,map[string]string{"error":message})
}

func respond_with_json(w http.ResponseWriter,http_status_code int, playload interface{}){
	res,_ := json.Marshal(playload)
	w.Header().Set("Content-Type","application/json")
	w.WriteHeader(http_status_code)
	w.Write(res)
}
