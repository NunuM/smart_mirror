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
	"AppendNews",
	"POST",
	"/news/append",
		httpAppendNewsHandler,
	},
	Route{
		"NumberOfNews",
		"GET",
		"/news/numberofnews",
		httpNumberOfNewsHandler,
	},
	Route{
		"RemoveNews",
		"POST",
		"/news/remove",
		httpRemoveNewsHandler,

	},
	Route{
		"AppendWeather",
		"POST",
		"/weather/append",
		httpAppendWeatherHandler,
	},
	Route{
	"RemoveWeather",
	"POST",
	"/weather/remove",
	httpRemoveWeather,
	},
	Route{
		"AppendMovies",
		"POST",
		"/movies/append",
		httpAppendMovies,
	},
	Route{
		"NumberOfMovies",
		"GET",
		"/movies/numberofmovies",
		httpNumberOfMoviesHandler,
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
		"Traffic",
		"POST",
		"/traffic",
		httpTrafficHandler,
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
