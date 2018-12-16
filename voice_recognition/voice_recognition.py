#!/usr/bin/env python3

# NOTE: this example requires PyAudio because it uses the Microphone class

import speech_recognition as sr

def goto_action(actions,text):
    i = 0
    action = 0
    while i < len(actions):
        if actions[i] in text:
           action = actions[i]
           break
        i += 1
    return action

def goto_args(action, text):
    return text.split(action,1)[1].lstrip()

actions = ["music player play","weather", "news", "calendar"]
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
    return_action = goto_action(actions,text)
    print("Google Speech Recognition thinks you said " + text)
    if return_action == 0:
        print("Not a valid command")
    else:
        print("Google Speech Recognition thinks you said command " + return_action)
        print("Executing command...")
        action_arguments=goto_args(return_action,text)
        print("Full command: {0} {1}".format(return_action, action_arguments))


except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))
