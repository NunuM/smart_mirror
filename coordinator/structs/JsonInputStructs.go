package structs


type Newsheadlines struct {
	CountryISO string `json:"country_iso"`
}

type News struct {
	Title string `json:"title"`
}

type Music struct {
	Song_name string `json:"song_name"`
}


type Weather struct {
	Location string `json:"location"`
	Forecast *bool `json:"forecast",omitempty`
}

type WeatherDate struct {
	Date string `json:"date"`
}

type Movies struct {
	NumberOfMovies int32 `json:"number_of_movies"`
}

type Traffic struct {
	Location string `json:"location"`
	LocationCodes *bool `json:"location_codes",omitempty`
	Severity *[]int `json:"severity",omitempty`
	TypeV *[]int `json:"type_v",omitempty`
}

type Incident struct {
	IncidentId string `json:"incident_id"`
}

type View struct {
	ViewName string `json:"view_name"`
	ViewPath string `json:"view_path"`
}


type Note struct {
	Title string `json:"title"`
	Alarm *string `json:"alarm"`
}

type Notes []Note

type ModifiableNote struct {
	OldTitle string `json:"old_title"`
	NewTitle string `json:"new_title"`
	Alarm *string `json:"alarm"`
}

type Sensor struct {
	Name string `json:"name"`
}