package structs


type Newsheadlines struct {
	CountryISO string `json:"country_iso"`
}

type News struct {
	Title string `json:"title"`
}

type Traffic struct {
	Distance int `json:"distance"`
	LocationCodes bool `json:"location_codes"`
	Lat_lon float64 `json:"lat_lon"`
	Severity []int `json:"severity"`
	TypeV []int `json:"type_v"`
}

type Music struct {
	Song_name string `json:"song_name"`
}


type Weather struct {
	Location string `json:"location"`
	Forecast bool `json:"forecast"`
}

type WeatherDate struct {
	Date string `json:"date"`
}

type Movies struct {
	NumberOfMovies int32 `json:"number_of_movies"`
}


type Note struct {
	Title string `json:"title"`
	Notifiable bool `json:"notifiable"`
	Alarm string `json:"alarm"`
}