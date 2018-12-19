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
		httpTrafficHandler,
	},
	Route{
	"NewsHeadlines",
	"POST",
	"/news",
		httpNewsHandler,
	},
	Route{
		"Play Music",
		"POST",
		"/music/play",
		httpMusicPlayHandler,
	},
	Route{
		"Currently Playing Music",
		"GET",
		"/music/current",
		httpMusicCurrentHandler,
	},
	Route{
		"Stop Music",
		"GET",
		"/music/stop",
		httpMusicStopHandler,
	},
	Route{
	"Blockbuster",
	"GET",
	"/blockbuster",
		httpBlockbusterHandler,
	},
	Route{
		"Weather",
		"POST",
		"/weather",
		httpWeatherHandler,
	},
	Route{
		"Organizer Create",
		"POST",
		"/organizer/create",
		httpOrganizerCreateHandler,
	},
	Route{
		"Organizer Delete",
		"POST",
		"/organizer/delete",
		httpOrganizerDeleteHandler,
	},
	Route{
		"Organizer",
		"GET",
		"/organizer",
		httpOrganizerHandler,
	},
	Route{
		"Sensor Array",
		"GET",
		"/sensor",
		httpSensorHandler,
	},
}
