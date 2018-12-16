package http_service

import "net/http"

type Route struct {
	Name string
	Method string
	Pattern string
	HandlerFunc http.HandlerFunc
}

type Routes []Route

var routes = Routes{
	Route{
		"Traffic",
		"POST",
		"/traffic",
		http_traffic_handler,
	},
	Route{
	"NewsHeadlines",
	"POST",
	"/news",
	http_news_handler,
	},
	Route{
		"Play Music",
		"POST",
		"/music/play",
		http_music_play_handler,
	},
	Route{
		"Currently Playing Music",
		"GET",
		"/music/current",
		http_music_current_handler,
	},
	Route{
		"Stop Music",
		"GET",
		"/music/stop",
		http_music_stop_handler,
	},
	Route{
	"Blockbuster",
	"GET",
	"/blockbuster",
	http_blockbuster_handler,
	},
	Route{
		"Weather",
		"POST",
		"/weather",
		http_weather_handler,
	},
	Route{
		"Organizer Create",
		"POST",
		"/organizer/create",
		http_organizer_create_handler,
	},
	Route{
		"Organizer Delete",
		"POST",
		"/organizer/delete",
		http_organizer_delete_handler,
	},
	Route{
		"Organizer",
		"GET",
		"/organizer",
		http_organizer_handler,
	},
	Route{
		"Sensor Array",
		"GET",
		"/sensor",
		http_sensor_handler,
	},
}
