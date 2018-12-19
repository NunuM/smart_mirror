package structs


type Newsheadlines struct {
	CountryISO string `json:"country_iso"`
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

