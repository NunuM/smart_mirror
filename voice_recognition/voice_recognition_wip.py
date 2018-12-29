#!/usr/bin/env python3

# NOTE: this example requires PyAudio because it uses the Microphone class

import speech_recognition as sr
import requests
import json
import datefinder
import re

key_word = "mirror"


#example payload
"""
payload = {"number": 12524,
           "type": "issue",
           "action": "show"}
"""


def call_coordinator_api(endpoint, payload):
     print(payload)
     url = "http://localhost:8080" + endpoint

     header = {"Content-type": "application/json",
               "Accept": "application/json"}

     response_decoded_json = requests.post(url, data=payload, headers=header)
     response_json = response_decoded_json.json()

     print(response_json)


 def check_command_display( str ):

     if str == "music":
         print("music display command detected: " + str)

     elif str == "house sensors":
         print("house sensors display command detected: " + str)

     elif str == "movies":
         print("movies display command detected: " + str)

     elif str == "calendar":
         print("calender display command detected: " + str)

     elif str == "news":
         print("news display command detected: " + str)

     elif str == "reddit":
         print("reddit display command detected: " + str)

     elif str == "traffic":
         print("trafic display command detected: " + rest)

     elif str == "weather":
         print("weather display command detected: " + str)

     else :
         print("invalid display comand: " + str)



def check_command_weather( str ):
    #spit first word if str contains more than one word
    firstWord = str
    rest = ""
    try:
        (firstWord, rest) = str.split(" ",1)
    except ValueError:
        print("Only one word")

    if firstWord == "forecast":
        #call with forecast true and location == rest
        call_coordinator_api("", {})
    else:
        #call with forecast false and location == firstWord
        print(" weather comand: " + str)


def check_command_reminder( str ):
     #spit first word if str contains more than one word
     date_text = str
     name_text = ""
     try:
         (date_text, name_text) = str.split("name",1)
     except ValueError:
         print("Only one word")

     # a generator will be returned by the datefinder module. I'm typecasting it to a list. Please read the note of caution provided at the bottom.
     date_matches = list(datefinder.find_dates(date_text))
     if len(date_matches) == 1:
         # date returned will be a datetime.datetime object. here we are only using the first match.
         date = date_matches[0]
         if name_text != "" :
             print("reminder command detected: " + date.isoformat() + " - " + name_text)
             call_coordinator_api("", {})
         else:
             print("Error - reminder command for date: " + date.isoformat() + "with no name specified")
     else:
         print("invalid reminder comand: " + str)



def check_command( str ):

   #spit first word if str contains more than one word
   firstWord = str
   rest = ""
   try:
       (firstWord, rest) = str.split(" ",1)
   except ValueError:
       print("Only one word")

   if str == "stop music":
       print("stop music command detected: " + str)
       call_coordinator_api("", {})

   elif str == "volume up":
       print("volume up command detected: " + str)
       call_coordinator_api("", {})

   elif str == "volume down":
       print("volume down command detected: " + str)
       call_coordinator_api("", {})

   elif str == "house sensors":
       print("house sensors command detected: " + str)
       call_coordinator_api("", {})

   elif firstWord == "reddit":
       print("movies command detected: " + str)
       call_coordinator_api("/movies/append", {})

   elif firstWord == "movies":
       print("movies command detected: " + str)
       call_coordinator_api("/movies/append", {})

   elif firstWord == "calendar":
       print("calender command detected: " + str)
       call_coordinator_api("news/append", {})

   elif firstWord == "news":
       print("news command detected: " + str)
       call_coordinator_api("news/append", {})

   elif firstWord == "play":
       print("play command detected: " + firstWord + " - " + rest)
       call_coordinator_api("/music/play", "{\"song_name\":\""+rest+"\"}")

   elif firstWord == "traffic":
       print("trafic command detected: " + firstWord + " - " + rest)
       call_coordinator_api("", {})

   elif firstWord == "display":
        check_command_display(rest)

   elif firstWord == "weather":
        check_command_weather(rest)

   elif firstWord == "reminder":
        check_command_reminder(rest)

   else:
       print("invalid comand: " + str)


#check_command("reminder 21st of january 2019 name study for exams")


def listen():
    r = sr.Recognizer()

    for index, name in enumerate(sr.Microphone.list_microphone_names()):
        print("Microphone with name \"{1}\" found for `Microphone(device_index={0})`".format(index, name))
    #with sr.Microphone(device_index=2) as source:
    try:
        with sr.Microphone() as source:
            r.adjust_for_ambient_noise(source,2)
            print("Say something!")
            audio = r.listen(source, 2)

        # recognize speech using Google Speech Recognition
        try:
            # for testing purposes, we're just using the default API key
            # to use another API key, use r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")
            # instead of r.recognize_google(audio)
            text = r.recognize_google(audio).lower()

            print("Google Speech Recognition thinks you said " + text)

            #spit first word if text contains more than one word
            firstWord = text
            rest = ""
            try:
                (firstWord, rest) = text.split(' ',1)
                if( firstWord == key_word and rest != ""):
                    check_command(rest)
                    
            except ValueError:
                print("Only one word")

        except sr.UnknownValueError:
            print("Google Speech Recognition could not understand audio")
        except sr.RequestError as e:
            print("Could not request results from Google Speech Recognition service; {0}".format(e))
    except sr.WaitTimeoutError as e:
        print("Timeout; {0}".format(e))

def main():
    while True:
        listen()

if __name__== "__main__":
  main()
