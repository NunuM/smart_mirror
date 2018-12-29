package dispatcher

import (
	"bytes"
	"coordinator/bus"
	"coordinator/structs"
	"log"
	"os/exec"
)


func news_execute(news structs.Newsheadlines) string{
	var cmd exec.Cmd
	if news.CountryISO == ""{
		cmd = *exec.Command("newsheadlines")
	} else{
		cmd = *exec.Command("newsheadlines","-country",news.CountryISO)
	}
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()
	str := parse_output(err1,"newsheadlines",*out)
	log.Print("News Call Executed")
	return str
}


func AppendNews(newsheadlines structs.Newsheadlines){
	go switchToNewsView()
	go appendNews(newsheadlines)
}

func appendNews(newsheadlines structs.Newsheadlines){
	call,err := bus.DbusNewsAPIImpl.FindDbusCall(".appendNews")
	if err == nil {
		result := call.AppendNews(news_execute(newsheadlines))
		if !result {
			parseReplyError("News.AppendNews")
		}
	}else{
		parseInitError("News.appendNews")
	}
}


func NumberOfNews() int32{
	call,err := bus.DbusNewsAPIImpl.FindDbusCall(".numberOfNews")
	if err == nil {
		return call.NumberOfNews()
	} else{
		go parseInitError("News.numberOfNews")
	}
	return -1
}


func RemoveNews(title string){
	go switchToNewsView()
	go removeNews(title)
}

func removeNews(title string){
	call,err := bus.DbusNewsAPIImpl.FindDbusCall(".removeNews")
	if err == nil {
		result := call.RemoveNews(title)
		if !result {
			parseReplyError("News.RemoveNews")
		}
	}else{
		parseInitError("News.RemoveNews")
	}
}

func switchToNewsView(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setNewsViewAsRoot")
	if err == nil {
		call.SetNewsViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to News")
	}
}