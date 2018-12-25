package dispatcher

import (
	"coordinator/bus"
	"coordinator/structs"
)


//TODO Comunicate with organizer

func AppendNote(note structs.Note){
	go switchToNotesView()
	go appendNote(note)
}


func appendNote(note structs.Note){
	call,err := bus.DbusNotesAPIImpl.FindDbusCall(".appendNote")
	if err == nil {
		result := call.AppendNote(note.Title,note.Notifiable,note.Alarm)
		if !result {
			parseReplyError("Notes.appendNote")
		}
	}else{
		parseInitError("Notes.appendNote")
	}
}


func EditNoteAlarm(note structs.Note){
	go switchToNotesView()
	go editNoteAlarm(note)
}

func editNoteAlarm(note structs.Note){
	call,err := bus.DbusNotesAPIImpl.FindDbusCall(".editNoteAlarm")
	if err == nil {
		result := call.EditNoteAlarm(note.Title,note.Alarm)
		if !result {
			parseReplyError("Notes.editNoteAlarm")
		}
	}else{
		parseInitError("Notes.editNoteAlarm")
	}
}


func NumberOfNotes() int32{
	call,err := bus.DbusNotesAPIImpl.FindDbusCall(".numbersOfNotes")
	if err == nil {
		return call.NumberOfNotes()
	} else{
		go parseInitError("Notes.numbersOfNotes")
	}
	return -1
}


func RemoveNote(note structs.Note){
	go switchToNotesView()
	go removeNote(note)
}

func removeNote(note structs.Note){
	call,err := bus.DbusNotesAPIImpl.FindDbusCall(".removeNote")
	if err == nil {
		result := call.RemoveNote(note.Title)
		if !result {
			parseReplyError("Note.RemoveNote")
		}
	}else{
		parseInitError("Note.RemoveNote")
	}
}


func switchToNotesView(){
	call,err := bus.DbusnavigationAPIImpl.FindDbusCall(".setNotesViewAsRoot")
	if err == nil {
		call.SetNewsViewAsRoot()
	}else{
		parseInitError("Error setting Navigation View to Notes")
	}
}