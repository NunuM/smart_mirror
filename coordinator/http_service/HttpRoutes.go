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
		"Set Application View",
		"GET",
		"/navigation/application",
			httpSetApplicationViewHandler,
	},
	Route{
		"Set Dynamic View",
		"POST",
		"/navigation/dynamic",
		httpSetDynamicViewHandler,
	},
	Route{
		"Set Home View",
		"GET",
		"/navigation/home",
		httpSetHomeViewHandler,
	},
	Route{
		"Add Dynamic View",
		"POST",
		"/navigation/add",
		httpAddDynamicViewHandler,
	},
	Route{
		"Set Reddit View",
		"GET",
		"/navigation/reddit",
		httpSetRedditViewHandler,
	},
	Route{
		"Append Reddit Posts",
		"GET",
		"/reddit/append",
		httpAppendRedditPostsHandler,
	},
	Route{
		"Get Number of Reddit Posts",
		"GET",
		"/reddit/numberofposts",
		httpNumberOfRedditPostsHandler,
	},
	Route{
		"Append Sensor Readings",
		"GET",
		"/sensor/append",
httpAppendSensorHandler,
	},
	Route{
		"Add Sensor Reading",
		"POST",
		"/sensor/addreading",
httpAddSensorHandler,
	},
	Route{
		"Number of Sensors",
		"GET",
		"/sensor/numberofsensors",
httpNumberOfSensorssHandler,
	},
	Route{
	"Remove Sensor",
	"POST",
	"/sensor/remove",
	httpRemoveSensorHandler,
	},
	Route{
		"Load Organizer Notes",
		"GET",
		"/note/organizer",
		httpLoadOrganizerNotesHandler,
	},
	Route{
		"Load Google Calendar Notes",
		"GET",
		"/note/gcalendar",
		httpLoadGCalendarNotesHandler,
	},
	Route{
		"Create Note",
		"POST",
		"/note/append",
		httpAppendNoteHandler,
	},
	Route{
		"Edit Note Alarm",
		"POST",
		"/note/edit/alarm",
		httpEditNoteAlarmHandler,
	},
	{
		"Edit Note Title",
		"POST",
		"/note/edit/title",
		httpEditNoteTitleHandler,
	},
	{
	"Remove Note",
	"POST",
	"/note/remove",
	httpRemoveNoteHandler,
	},
	{
		"Number of Notes",
		"GET",
		"/note/numberofnotes",
		httpNumberOfNotesHandler,
	},
}
