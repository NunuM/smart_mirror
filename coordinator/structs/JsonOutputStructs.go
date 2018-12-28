package structs


type OutWeather struct {
	Date        string  `json:"date"`
	Description string  `json:"description"`
	Humidity    float64     `json:"humidity"`
	Icon        string  `json:"icon"`
	Pressure    float64     `json:"pressure"`
	Temp        float64     `json:"temp"`
	TempMax     float64     `json:"temp_max"`
	TempMin     float64     `json:"temp_min"`
	WindDeg     float64    `json:"wind_deg"`
	WindSpeed   float64 `json:"wind_speed"`
}

type OutWeatherSlice []OutWeather



type SongStreamHttpReply struct {
	Message string `json:"message"`
}