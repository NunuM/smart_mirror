#!/usr/bin/env python3

# NOTE: this example requires PyAudio because it uses the Microphone class

import speech_recognition as sr
import datefinder
import re

key_word = "mirror"




def check_command_reminder( str ):
     #spit first word if str contains more than one word
     date_text = ""
     name_text = ""

     date_text = str.split("name", 1)[0]
     name_text = str.split("name", 1)[1]


     # a generator will be returned by the datefinder module. I'm typecasting it to a list. Please read the note of caution provided at the bottom.
     date_matches = list(datefinder.find_dates(date_text))
     if len(date_matches) == 1:
         # date returned will be a datetime.datetime object. here we are only using the first match.
         date = date_matches[0]
         print("reminder command detected: " + date.isoformat() + " - " + name_text)
     else:
         print("invalid reminder comand: " + str)

def check_command( str ):

   #spit first word if str contains more than one word
   firstWord = str
   rest = ""
   try:
       (firstWord, rest) = str.split(maxsplit=1)
   except ValueError:
       print("Only one word")

   if str == "stop music":
       print("stop music command detected: " + str)

   elif str == "volume up":
       print("volume up command detected: " + str)

   elif str == "volume down":
       print("volume down command detected: " + str)

   elif str == "house sensors":
       print("house sensors command detected: " + str)

   elif firstWord == "weather":
       print("weather command detected: " + str)

   elif firstWord == "movies":
       print("movies command detected: " + str)

   elif firstWord == "calendar":
       print("calender command detected: " + str)

   elif firstWord == "news":
       print("news command detected: " + str)

   elif firstWord == "play":
       print("play command detected: " + firstWord + " - " + rest)

   elif firstWord == "traffic":
       print("trafic command detected: " + firstWord + " - " + rest)

   elif firstWord == "reminder":
        check_command_reminder(rest)

   else:
       print("invalid comand: " + str)

#test
#check_command("reminder 21st of january 2019 name study for exams")


# obtain audio from the microphone
r = sr.Recognizer()
with sr.Microphone() as source:
    print("Say something!")
    audio = r.listen(source)

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
        (firstWord, rest) = text.split(maxsplit=1)
    except ValueError:
        print("Only one word")

    if( firstWord == key_word):
        check_command(rest)

except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))
