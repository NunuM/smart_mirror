package dispatcher

import (
	"bytes"
	"coordinator/bus"
	"coordinator/structs"
	"encoding/json"
	"log"
	"os/exec"
	"strings"
)

func delete_note(note structs.Note) (string, error) {
	var cmd exec.Cmd
	cmd = *exec.Command("organizer", "-j", "-d", note.Title)
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()
	if err1 != nil {
		log.Printf("Delete Note Call error %s\n",err1.Error())
	}
	str := parse_output(err1, "organizer", *out)
	log.Print("Organizer Delete Note Call Executed")
	return str, err1
}

func modify_note(note structs.ModifiableNote) (string, error) {
	var cmd exec.Cmd
	if note.Alarm != nil && "" != strings.TrimSpace(*note.Alarm) {
		cmd = *exec.Command("organizer", "-j", "-a", *note.Alarm, "-u", note.OldTitle, note.NewTitle)
	} else {
		cmd = *exec.Command("organizer", "-j", "-u", note.OldTitle, note.NewTitle)
	}
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()

	if err1 != nil {
		log.Printf("Modify Note Call error %s\n",err1.Error())
	}
	str := parse_output(err1, "organizer", *out)
	log.Print("Organizer Modify Note Call Executed")
	return str, err1
}

func create_note(note structs.Note) (string, error) {
	var cmd exec.Cmd
	if note.Alarm != nil && "" != strings.TrimSpace(*note.Alarm) {
		cmd = *exec.Command("organizer", "-j", "-a", *note.Alarm, "-c", note.Title)
	} else if note.Alarm == nil {
		cmd = *exec.Command("organizer", "-j", "-c", note.Title)
	} else {
		cmd = *exec.Command("organizer", "-j", "-c", note.Title)
	}
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()

	if err1 != nil {
		log.Printf("Create Note Call error %s\n",err1.Error())
	}
	str := parse_output(err1, "organizer", *out)
	log.Print("Organizer Create Note Call Executed")
	return str, err1
}

func loadNotes() {
	var cmd exec.Cmd
	cmd = *exec.Command("organizer", "-f", "-l")
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()

	if err1 != nil {
		log.Printf("Load Notes Call error %s\n",err1.Error())
	}
	if err1 == nil {
		var notes structs.Notes
		decoder := json.NewDecoder(out)
		if err := decoder.Decode(&notes); err == nil {
			for _, n := range notes {
				appendNote(n)
			}
		}
	}
}

func loadGCalenderNotes() {
	var cmd exec.Cmd
	cmd = *exec.Command("gcalender")
	out := &bytes.Buffer{}
	cmd.Stdout = out
	err1 := cmd.Run()

	if err1 != nil {
		log.Printf("Load Notes Google Calender Call error %s\n",err1.Error())
	}
	if err1 == nil {
		var notes structs.Notes
		decoder := json.NewDecoder(out)
		if err := decoder.Decode(&notes); err == nil {
			for _, n := range notes {
				appendNote(n)
			}
		}
	}
}

func LoadNotes() {
	go loadNotes()
}

func LoadGCalanderNotes() {
	go LoadGCalanderNotes()
}

func CreateNote(note structs.Note) {
	go switchToNotesView()
	go createNote(note)
}


func EditNoteAlarm(note structs.ModifiableNote) {
	go switchToNotesView()
	go editNoteAlarm(note)
}

func EditNoteTitle(note structs.ModifiableNote){
	go switchToNotesView()
	go editNoteTitle(note)
}

func RemoveNote(note structs.Note) {
	go switchToNotesView()
	go removeNote(note)
}

func appendNote(note structs.Note) {
	call, err := bus.DbusNotesAPIImpl.FindDbusCall(".appendNote")
	if err == nil {
		result := call.AppendNote(note.Title, true, *note.Alarm)
		if !result {
			parseReplyError("Notes.appendNote")
		}
	} else {
		parseInitError("Notes.appendNote")
	}
}

func createNote(note structs.Note) {
	call, err := bus.DbusNotesAPIImpl.FindDbusCall(".appendNote")
	if err == nil {
		_, err1 := create_note(note)
		if err1 == nil {
			var result bool
			if note.Alarm == nil {
				result = call.AppendNote(note.Title, false, "")
			} else if note.Alarm != nil {
				result = call.AppendNote(note.Title, true, *note.Alarm)
			} else {
				result = call.AppendNote(note.Title, false, "")
			}
			if !result {
				parseReplyError("Notes.appendNote")
			}
		} else {
			notifyError(err1.Error())
		}
	} else {
		parseInitError("Notes.appendNote")
	}
}


func editNoteTitle(note structs.ModifiableNote) {
	call, err := bus.DbusNotesAPIImpl.FindDbusCall(".editNoteTitle")
	if err == nil {
		_, err1 := modify_note(note)
		if err1 == nil {
			result := call.EditNoteAlarm(note.NewTitle, *note.Alarm)
			if !result {
				parseReplyError("Notes.editNoteTitle")
			}
		} else{
			notifyError(err1.Error())
		}
	} else {
		parseInitError("Notes.editNoteTitle")
	}
}



func editNoteAlarm(note structs.ModifiableNote) {
	call, err := bus.DbusNotesAPIImpl.FindDbusCall(".editNoteAlarm")
	if err == nil {
		_, err1 := modify_note(note)
		if err1 == nil {
			result := call.EditNoteAlarm(note.NewTitle, *note.Alarm)
			if !result {
				parseReplyError("Notes.editNoteAlarm")
			}
		} else{
			notifyError(err1.Error())
		}
	} else {
		parseInitError("Notes.editNoteAlarm")
	}
}

func NumberOfNotes() int32 {
	call, err := bus.DbusNotesAPIImpl.FindDbusCall(".numbersOfNotes")
	if err == nil {
		return call.NumberOfNotes()
	} else {
		go parseInitError("Notes.numbersOfNotes")
	}
	return -1
}


func removeNote(note structs.Note) {
	call, err := bus.DbusNotesAPIImpl.FindDbusCall(".removeNote")
	if err == nil {
		result := call.RemoveNote(note.Title)
		if !result {
			parseReplyError("Note.RemoveNote")
		}
	} else {
		parseInitError("Note.RemoveNote")
	}
}

func switchToNotesView() {
	call, err := bus.DbusnavigationAPIImpl.FindDbusCall(".setNotesViewAsRoot")
	if err == nil {
		call.SetNewsViewAsRoot()
	} else {
		parseInitError("Error setting Navigation View to Notes")
	}
}
