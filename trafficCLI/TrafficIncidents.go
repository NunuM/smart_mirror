package main

import (
	"encoding/json"
	"errors"
	"fmt"
	"math"
	"net/http"
	"strconv"
	"strings"
)

const KEY  = "AnsHzFWFWSnoH8pyuRepCX4qvr9TeOfLDWnBnbt2jtfX8t8lmMRjbvuULPwRlqRq"
const URL_LOCATION_CODES = "http://dev.virtualearth.net/REST/v1/Traffic/Incidents/%f,%f,%f,%f/includeLocationCodes?%skey=%s"
const URL_NO_LOC = "http://dev.virtualearth.net/REST/v1/Traffic/Incidents/%f,%f,%f,%f?%skey=%s"



func (p *pointSlice) String() string {
	return fmt.Sprint("%f",*p);
}

func (p *pointSlice) Set(value string) error {
	strs := strings.Split(value,",")
	if len(strs)!=2{
		return errors.New("invalid number of parameters.Must be 2")
	}
	for i:=0;i<2;i++  {
		n,err := strconv.ParseFloat(strs[i],64)
		if err != nil {
			return err
		}
		if(i == 0 && n< -90.0 || n> 90.0) {
			return errors.New("Value for Latitude must be between -90 and 90")
		}
		if i== 1  && n< - 180.0 || n>180.0{
			return errors.New("Value for Longitude must be between -180 and 180")
		}
		if(i==0){
			*p = append(*p,n)
		}  else{
			*p = append(*p,n)
		}
	}
	return nil
}

type pointSlice []float64
type typeSlice []int
type severitySlice []int

func (s *severitySlice) String() string {
	return fmt.Sprint("%d", *s)
}

func (s *severitySlice) Set(value string) error {
	strs := strings.Split(value, ",")
	if len(strs)==0 &&  value == ""{
		return errors.New("flagged specified, at least one int must be declared")
	}
	for _,str := range strs{
		n,err := strconv.Atoi(str)
		if err != nil {
			return err
		}
		if n < 1 || n > 4 {
			return errors.New("types must be between 1 and 4")
		}
		*s = append(*s, n)
	}
	return nil
}

func (i *typeSlice) String() string {
	return fmt.Sprint("%d", *i)
}

func (i *typeSlice) Set(value string) error{
	strs := strings.Split(value, ",")
	if len(strs)==0 &&  value == ""{
		return errors.New("flagged specified, at least one int must be declared")
	}
	for _,str := range strs{
		n,err := strconv.Atoi(str)
		if err != nil {
			return err
		}
		if n < 1 || n > 11 {
			return errors.New("types must be between 1 and 11")
		}
		*i = append(*i, n)
	}
	return nil
}



type TrafficIncident struct {
	boundingbox BoundingBox
	includeLocationCode bool
	severity severitySlice
	_type typeSlice
}




type BoundingBox struct {
	SouthLatitude float64
	WestLongitude float64
	NorthLatitude float64
	EastLongitude float64
}



func getBoundsFromLatLng(p pointSlice,dist *int) BoundingBox{
	var latChange = float64(*dist)/111.2
	var lonChange = math.Abs(math.Cos(p[0]*(math.Pi/180)))
	return BoundingBox{p[0]-latChange,p[1]-lonChange,p[0]+latChange,p[1]+lonChange}
}


func (t *TrafficIncident)makeRequest() (TrafficResponse,error){
	var url = t.buildURL()
	var traffic TrafficResponse
	resp, err := http.Get(url)
	if err != nil {
		return traffic,err
	}
	defer resp.Body.Close()
	decoder := json.NewDecoder(resp.Body)

	if err := decoder.Decode(&traffic); err != nil {
		return traffic,err
	}
	return traffic,nil
}

func (t *TrafficIncident)buildURL() (string){
	var url = ""
	if t.includeLocationCode {
		var q = t.buildQuery()
		url = fmt.Sprintf(URL_LOCATION_CODES,t.boundingbox.SouthLatitude,
			t.boundingbox.WestLongitude,
			t.boundingbox.NorthLatitude,
			t.boundingbox.EastLongitude,
			q,
			KEY)
	} else{
		var q = t.buildQuery()
		url = fmt.Sprintf(URL_NO_LOC,t.boundingbox.SouthLatitude,
			t.boundingbox.WestLongitude,
			t.boundingbox.NorthLatitude,
			t.boundingbox.EastLongitude,
			q,
			KEY)
	}
	return url
}


func (t *TrafficIncident)buildQuery() (string){
	var serv = ""
	if len(t.severity)>0 {
		for i:=0;i<len(t.severity);i++{
			if(i==len(t.severity)-1){
				serv += fmt.Sprintf("severity%d",t.severity[i])
			} else{
				serv += fmt.Sprintf("severity%d,",t.severity[i])
			}
		}
	}
	var ty = ""
	if len(t._type)>0 {
		for i:=0;i<len(t._type);i++{
			if(i==len(t._type)-1){
				serv += fmt.Sprintf("type%d",t._type[i])
			} else{
				serv += fmt.Sprintf("type%d,",t._type[i])
			}
		}
	}
	var query = ""
	if ty!= "" && serv != ""{
		query = ty+"&"+serv
	} else if ty != ""{
		query = ty +"&"
	} else if serv != ""{
		query = serv +"&"
	}
	return query
}


type TrafficResponse struct {
	AuthenticationResultCode string `json:"authenticationResultCode"`
	BrandLogoURI             string `json:"brandLogoUri"`
	Copyright                string `json:"copyright"`
	ResourceSets             []struct {
		EstimatedTotal int `json:"estimatedTotal"`
		Resources      []struct {
			Type  string `json:"__type"`
			Point struct {
				Type        string    `json:"type"`
				Coordinates []float64 `json:"coordinates"`
			} `json:"point"`
			Congestion   string `json:"congestion"`
			Description  string `json:"description"`
			Detour       string `json:"detour"`
			End          string `json:"end"`
			IncidentID   int    `json:"incidentId"`
			Lane         string `json:"lane"`
			LastModified string `json:"lastModified"`
			RoadClosed   bool   `json:"roadClosed"`
			Severity     int    `json:"severity"`
			Start        string `json:"start"`
			ToPoint      struct {
				Type        string    `json:"type"`
				Coordinates []float64 `json:"coordinates"`
			} `json:"toPoint,omitempty"`
			LocationCodes []string `json:"locationCodes,omitempty"`
			TypeTwo          int      `json:"type"`
			Verified      bool     `json:"verified"`
		} `json:"resources"`
	} `json:"resourceSets"`
	StatusCode        int    `json:"statusCode"`
	StatusDescription string `json:"statusDescription"`
	TraceID           string `json:"traceId"`
}


