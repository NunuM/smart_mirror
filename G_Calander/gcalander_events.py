# https://developers.google.com/calendar/quickstart/python

#!/usr/bin/python
from __future__ import print_function
import datetime
from googleapiclient.discovery import build
from httplib2 import Http
from oauth2client import file, client, tools
import json
import datetime

# If modifying these scopes, delete the file token.json.
SCOPES = 'https://www.googleapis.com/auth/calendar.readonly'

def main():
    """Shows basic usage of the Google Calendar API.
    Prints the start and name of the next 10 events on the user's calendar.
    """
    # The file token.json stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    store = file.Storage('token.json')
    creds = store.get()
    if not creds or creds.invalid:
        flow = client.flow_from_clientsecrets('credentials.json', SCOPES)
        creds = tools.run_flow(flow, store)
    service = build('calendar', 'v3', http=creds.authorize(Http()))

    # Call the Calendar API
    now = datetime.datetime.utcnow().isoformat() + 'Z' # 'Z' indicates UTC time

    events_result = service.events().list(calendarId='primary', timeMin=now,
                                        maxResults=10, singleEvents=True,
                                        orderBy='startTime').execute()
    events = events_result.get('items', [])

    output = []
    # example output {"title":"ola", "notifiable":true, "alarm":"2018-06-07 22:22"}

    if not events:
        print('No upcoming events found.')
    for event in events:

        start = event['start'].get('dateTime', event['start'].get('date'))
        d = datetime.datetime.strptime(start , "%Y-%m-%dT%H:%M:%SZ")

        day = {
        "title": event['summary'],
        "notifiable": "true",
        "alarm": d.strftime( "%Y-%m-%d %H:%M")
        }
        output.append(day)

    print(json.dumps(output, indent=4, sort_keys=True))

if __name__ == '__main__':
    main()
