#!/usr/bin/env python3

# NOTE: this example requires PyAudio because it uses the Microphone class

import speech_recognition as sr
import requests
import json
import datefinder
import re

key_word = "mirror"


ACCEPTED_COUNTRY_CODES = [
["UNITED ARAB EMIRATES" , "ae"],
["ARGENTINA" , "ar"],
["AUSTRIA" ,"at"],
["AUSTRALIA" ,"au"],
["BELGIUM" ,"be"],
["BULGARIA" ,"bg"],
["BRAZIL" ,"br"],
["CANADA" ,"ca"],
["SWITZERLAND" ,"ch"],
["CHINA" ,"cn"],
["COLOMBIA" ,"co"],
["CUBA" ,"cu"],
["CZECH REPUBLIC" ,"cz"],
["GERMANY" ,"de"],
["EGYPT" ,"eg"],
["FRANCE" ,"fr"],
["UNITED KINGDOM" ,"gb"],
["GREECE" ,"gr"],
["HONG KONG" ,"hk"],
["HUNGARY" ,"hu"],
["INDONESIA" ,"id"],
["IRELAND" ,"ie"],
["ISRAEL" ,"il"],
["INDIA" ,"in"],
["ITALY" ,"it"],
["JAPAN" ,"jp"],
["REPUBLIC OF KOREA" ,"kr"],
["LITHUANIA" ,"lt"],
["LATVIA" ,"lv"],
["MOROCCO" ,"ma"],
["MEXICO" ,"mx"],
["MALAYSIA" ,"my"],
["NIGERIA" ,"ng"],
["NETHERLANDS" ,"nl"],
["NORWAY" ,"no"],
["NEW ZEALAND" ,"nz"],
["PHILIPPINES" ,"ph"],
["POLAND" ,"pl"],
["PORTUGAL" ,"pt"],
["ROMANIA" ,"ro"],
["RUSSIA" ,"ru"],
["SAUDI ARABIA" ,"sa"],
["SWEDEN" ,"se"],
["SINGAPORE" ,"sg"],
["SLOVENIA" ,"si"],
["SLOVAKIA" ,"sk"],
["THAILAND" ,"th"],
["TURKEY" ,"tr"],
["TAIWAN" ,"tw"],
["UKRAINE" ,"ua"],
["UNITED STATES" ,"us"],
["VENEZUELA" ,"ve"],
["SOUTH AFRICA" ,"za"]
]



#example payload
"""
payload = {"number": 12524,
           "type": "issue",
           "action": "show"}
"""


def call_coordinator_api(call, endpoint, payload):
     print(payload)
     url = "http://localhost:8080" + endpoint

     header = {"Content-type": "application/json",
               "Accept": "application/json"}

     try:
         if call == "post" :
             response_decoded_json = requests.post(url, data=payload, headers=header)
         else:
             response_decoded_json = requests.get(url, headers=header)

         response_json = response_decoded_json.json()
         print(response_json)

     except requests.exceptions.HTTPError as errh:
         print ("Http Error:",errh)
     except requests.exceptions.ConnectionError as errc:
         print ("Error Connecting:",errc)
     except requests.exceptions.Timeout as errt:
         print ("Timeout Error:",errt)
     except requests.exceptions.RequestException as err:
         print ("OOps: Something Else",err)

def check_command_display( str ):

     if str == "music":
         print("music display command detected: " + str)
         call_coordinator_api("get", "/navigation/home", "")

     elif str == "home":
         print("house sensors display command detected: " + str)
         call_coordinator_api("get", "/navigation/home", "")

     elif str == "house sensors":
         print("house sensors display command detected: " + str)
         call_coordinator_api("get", "/navigation/sensor", "")

     elif str == "movies":
         print("movies display command detected: " + str)
         call_coordinator_api("get", "/navigation/media", "")

     elif str == "calendar":
         print("calender display command detected: " + str)
         call_coordinator_api("get", "/navigation/notes", "")

     elif str == "news":
         print("news display command detected: " + str)
         call_coordinator_api("get", "/navigation/news", "")

     elif str == "reddit":
         print("reddit display command detected: " + str)
         call_coordinator_api("get", "/navigation/reddit", "")

     elif str == "traffic":
         print("trafic display command detected: " + rest)
         call_coordinator_api("get", "/navigation/traffic", "")

     elif str == "weather":
         print("weather display command detected: " + str)
         call_coordinator_api("get", "/navigation/weather", "")

     else :
         print("invalid display comand: " + str)



def check_command_news( str ):
    if str == "":
        call_coordinator_api("post", "news/append", {})
    else:
        for i, elem in enumerate(ACCEPTED_COUNTRY_CODES):
            if str.lower() == elem[0].lower():
                print("news command detected: " + str   +  elem[1])
                call_coordinator_api("post" ,"news/append", {})




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
        print("weather forecast comand: " + rest)
        call_coordinator_api("post", "/weather/append", {"location": rest , "forecast" : True})
    else:
        #call with forecast false and location == firstWord
        print("weather comand: " + str)
        call_coordinator_api("post", "/weather/append", {"location": firstWord , "forecast" : False})


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
             call_coordinator_api("post", "", {})
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
       call_coordinator_api("get", "/music/stop", "")

   if str == "pause music":
       print("pause music command detected: " + str)
       call_coordinator_api("get", "/music/pause", "")

   if str == "continue  music":
       print("continue music command detected: " + str)
       call_coordinator_api("get", "/music/pause", "")

   elif str == "volume up":
       print("volume up command detected: " + str)
       call_coordinator_api("get", "/music/volume/up", "")

   elif str == "volume down":
       print("volume down command detected: " + str)
       call_coordinator_api("get", "/music/volume/down", "")

   elif str == "house sensors":
       print("house sensors command detected: " + str)
       call_coordinator_api("get" , "/sensor/append", "")

   elif firstWord == "reddit":
       print("movies command detected: " + str)
       call_coordinator_api("get", "/reddit/append", "")

   elif firstWord == "movies":
       print("movies command detected: " + str)
       call_coordinator_api("post", "/movies/append", {})

   elif firstWord == "calendar":
       print("calender command detected: " + str)
       call_coordinator_api("news/append", {})


   elif firstWord == "play":
       print("play command detected: " + firstWord + " - " + rest)
       call_coordinator_api("post", "/music/play", "{\"song_name\":\""+rest+"\"}")

   elif firstWord == "traffic":
       print("trafic command detected: " + firstWord + " - " + rest)
       call_coordinator_api("post", "/traffic/append", {"location": rest })

   elif firstWord == "news":
        check_command_news(rest)

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
