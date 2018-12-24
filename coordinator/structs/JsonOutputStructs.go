package structs


type OutWeather struct {
	Date        string  `json:"date"`
	Description string  `json:"description"`
	Humidity    int     `json:"humidity"`
	Icon        string  `json:"icon"`
	Pressure    int     `json:"pressure"`
	Temp        int     `json:"temp"`
	TempMax     int     `json:"temp_max"`
	TempMin     int     `json:"temp_min"`
	WindDeg     int     `json:"wind_deg"`
	WindSpeed   float64 `json:"wind_speed"`
}



