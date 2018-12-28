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
	"Append News",
	"POST",
	"/news/append",
		httpAppendNewsHandler,
	},
	Route{
		"Number Of News",
		"GET",
		"/news/numberofnews",
		httpNumberOfNewsHandler,
	},
	Route{
		"Remove News",
		"POST",
		"/news/remove",
		httpRemoveNewsHandler,

	},
	Route{
		"Append Weather",
		"POST",
		"/weather/append",
		httpAppendWeatherHandler,
	},
	Route{
	"Remove Weather",
	"POST",
	"/weather/remove",
	httpRemoveWeather,
	},
	Route{
		"Append Movies",
		"POST",
		"/movies/append",
		httpAppendMovies,
	},
	Route{
		"Number Of Movies",
		"GET",
		"/movies/numberofmovies",
		httpNumberOfMoviesHandler,
	},
	Route{
		"Append Traffic",
		"POST",
		"/traffic/append",
		httpAppendTrafficHandler,
	},
	Route{
		"Number Of Traffic Incidents",
		"GET",
		"/traffic/numberofincidents",
		httpNumberOfTrafficIncidentsHandler,
	},
	Route{
		"Remove Incident",
		"POST",
		"/traffic/removeincident",
		httpRemoveIncidentHandler,
	},
	Route{
		"Play Song",
		"POST",
		"/music/play",
		httpPlaySongHandler,
	},
	Route{
		"Pause Song",
		"GET",
		"/music/pause",
		httpPauseSongHandler,
	},
	Route{
		"Stop Song",
		"GET",
		"/music/stop",
		httpStopSongHandler,
	},
	Route{
		"Up Song Volume",
		"GET",
		"/music/volume/up",
		httpUpSongVolumeHandler,
	},
	Route{
		"Down Song Volume",
		"GET",
		"/music/volume/down",
		httpDownSongVolumeHandler,
	},
	Route{
		"Set Media View",
		"GET",
		"/navigation/media",
		httpSetMediaViewHandler,
	},
	Route{
		"Set News View",
		"GET",
		"/navigation/news",
		httpSetNewsViewHandler,
	},

	Route{
		"Set Notes View",
		"GET",
		"/navigation/notes",
		httpSetNotesViewHandler,
	},
	Route{
		"Set Sensor View",
		"GET",
		"/navigation/sensor",
		httpSetSensorViewHandler,
	},
	Route{
		"Set Traffic View",
		"GET",
		"/navigation/traffic",
		httpSetTrafficViewHandler,
	},
	Route{
		"Set Weather View",
		"GET",
		"/navigation/weather",
		httpSetWeatherViewHandler,
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
