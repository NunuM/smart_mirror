package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"net/http"
	"strings"
	"time"
)

const URL = "https://newsapi.org/v2/top-headlines?country=%s&apiKey=53e4f86275b1431b8b157ad0e120e2f3"

var ACCEPTED_COUNTRY_CODES = [...]string{"ae", "ar",
	"at", "au", "be", "bg", "br", "ca", "ch",
	"cn", "co", "cu", "cz", "de", "eg", "fr",
	"gb", "gr", "hk", "hu", "id", "ie", "il",
	"in", "it", "jp", "kr", "lt", "lv", "ma",
	"mx", "my", "ng", "nl", "no", "nz", "ph",
	"pl", "pt", "ro", "rs", "ru", "sa", "se",
	"sg", "si", "sk", "th", "tr", "tw", "ua",
	"us", "ve", "za"}

func main(){
	country := flag.String("country","","Country ISO Code. If not provided gets geolocation info from IP address")
	flag.Parse()
	if *country == ""{
		geoLoc,err := getGeoInfo()
		if err != nil {
			fmt.Print("Country ISO Code not specified. Defaulting to fetching Geo Location Info failed.")
		}
		var str = fmt.Sprintf(URL,geoLoc.Country)
		news, err1 := getNewsData(str)
		if err1 != nil {
			fmt.Print("Error fetching news...")
		} else{
			res, err1 := json.MarshalIndent(news,"","    ")
			if err1 == nil {
				fmt.Println(string(res))
			} else{
				fmt.Println(err)
			}

		}
	} else{
		var result bool = false
		for _,cCode := range ACCEPTED_COUNTRY_CODES{
			if strings.EqualFold(*country,cCode){
				result = true
				break
			}
		}
		if result{
			var str = fmt.Sprintf(URL,*country)
			news, err1 := getNewsData(str)
			if err1 != nil {
				fmt.Print("Error fetching news...")
			} else{
				res, err1 := json.MarshalIndent(news,"","    ")
				if err1 == nil {
					fmt.Println(string(res))
				} else{
					fmt.Println(err1)
				}

			}
		}else{
			fmt.Printf("Invalid Country code must be %v",ACCEPTED_COUNTRY_CODES)
		}
	}
}


func getNewsData(url string) ([]Article,error){
	var articles []Article
	reply,err := http.Get(url)
	defer reply.Body.Close()
	if err != nil {
		return articles,err
	}
	decoder := json.NewDecoder(reply.Body)
	var news News
	if err := decoder.Decode(&news); err != nil {
		return articles,err
	}
	for _,ar := range news.Articles{
		var article Article
		article.URL = ar.URL
		article.Author = ar.Author
		article.Content = ar.Content
		article.Description = ar.Description
		article.PublishedAt = ar.PublishedAt
		article.Title = ar.Title
		article.URLToImage = ar.URLToImage
		articles = append(articles,article)
	}
	return articles,nil
}



func getGeoInfo() (GeoLocation,error){
	var geoLoc GeoLocation
	reply, err := http.Get("https://ipapi.co/json")
	if err != nil {
		return geoLoc,err
	}
	defer reply.Body.Close()
	decoder := json.NewDecoder(reply.Body)

	if err := decoder.Decode(&geoLoc); err != nil {
		return geoLoc,err
	}
	return geoLoc,nil
}

type Article struct {
	Author      interface{} `json:"author"`
	Title       string      `json:"title"`
	Description interface{} `json:"description"`
	URL         string      `json:"url"`
	URLToImage  interface{} `json:"urlToImage"`
	PublishedAt time.Time   `json:"publishedAt"`
	Content     interface{} `json:"content"`
}




type News struct {
	Status string `json:"status"`
	TotalResults int `json:"totalResults"`
	Articles []struct {
		Source struct {
			ID string `json:"id"`
			Name string `json:"name"`
		} `json:"source"`
		Author string `json:"author"`
		Title string `json:"title"`
		Description string `json:"description"`
		URL string `json:"url"`
		URLToImage string `json:"urlToImage"`
		PublishedAt time.Time `json:"publishedAt"`
		Content string `json:"content"`
	} `json:"articles"`
}




type GeoLocation struct {
	IP                 string  `json:"ip"`
	City               string  `json:"city"`
	Region             string  `json:"region"`
	RegionCode         string  `json:"region_code"`
	Country            string  `json:"country"`
	CountryName        string  `json:"country_name"`
	ContinentCode      string  `json:"continent_code"`
	InEu               bool    `json:"in_eu"`
	Postal             string  `json:"postal"`
	Latitude           float64 `json:"latitude"`
	Longitude          float64 `json:"longitude"`
	Timezone           string  `json:"timezone"`
	UtcOffset          string  `json:"utc_offset"`
	CountryCallingCode string  `json:"country_calling_code"`
	Currency           string  `json:"currency"`
	Languages          string  `json:"languages"`
	Asn                string  `json:"asn"`
	Org                string  `json:"org"`
}