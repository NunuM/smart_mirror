package dispatcher

import (
	"bytes"
	"coordinator/bus"
	"log"
	"os/exec"
)


func reddit_execute() string {
	var cmd exec.Cmd
	cmd = *exec.Command("reddithotposts")
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()
	str := parse_output(err1, "reddithotposts", *out)
	log.Print("Reddit Call Executed")
	return str
}

func AppendRedditPosts() {
	go switchToRedditView()
	go stagePosts()
}

func stagePosts(){
	clearRedditPosts()
	go appendRedditPosts()
}

func appendRedditPosts() {
	call, err := bus.DbusRedditAPIImpl.FindDbusCall(".appendRedditPosts")
	if err == nil {
		result := call.AppendPosts(reddit_execute())
		if !result {
			parseReplyError(call.Method)
		}
	} else {
		parseInitError(call.Method)
	}
}

func NumberOfPosts() int32 {
	call, err := bus.DbusRedditAPIImpl.FindDbusCall(".numberOfPosts")
	if err == nil {
		return call.NumberOfPosts()
	} else {
		go parseInitError(call.Method)
	}
	return -1
}


func clearRedditPosts() {
	call, err := bus.DbusRedditAPIImpl.FindDbusCall(".clearAllRedditPosts")
	if err == nil {
		result := call.ClearRedditPosts()
		if !result {
			parseReplyError(call.Method)
		}
	} else {
		parseInitError(call.Method)
	}
}

func switchToRedditView() {
	call, err := bus.DbusnavigationAPIImpl.FindDbusCall(".setRedditViewAsRoot")
	if err == nil {
		call.SetNewsViewAsRoot()
	} else {
		parseInitError("Error setting Navigation View to News")
	}
}