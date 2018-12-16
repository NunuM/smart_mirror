import argparse
import pafy
import vlc
import sys
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

DEVELOPER_KEY = 'AIzaSyC3B9tKyRRq95nClQhKxRGR12zFK2-P4V4'
YOUTUBE_API_SERVICE_NAME = 'youtube'
YOUTUBE_API_VERSION = 'v3'
YOUTUBE_URL_VIDEO ='https://www.youtube.com/watch?v='
MAX_VOLUME = 200
MIN_VOLUME = 0

def exit_program(cenas): 
    quit()
   
def pafy_video(video_id):
    url = 'https://www.youtube.com/watch?v={0}'.format(video_id)
    vid = pafy.new(url)

def pafy_playlist(playlist_id):
    url = "https://www.youtube.com/playlist?list={0}".format(playlist_id)
    playlist = pafy.get_playlist(url)


def youtube_search(options):
  youtube = build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION, developerKey=DEVELOPER_KEY)

  search_response = youtube.search().list(
    q=options.search,
    part='id,snippet',
    maxResults=options.max_results
  ).execute()

  videos = []

  for search_result in search_response.get('items', []):
    if search_result['id']['kind'] == 'youtube#video':
      videos.append('%s' % (search_result['id']['videoId']))


  if videos:
    url = YOUTUBE_URL_VIDEO+videos[0]
    print(url)
    video = pafy.new(url)
    best = video.getbestaudio()
    print("Best Audio={0}bps".format(best.bitrate))
    playurl = best.url
    vlc_instance = vlc.Instance(['--no-video','--play-and-exit'])
    player = vlc_instance.media_player_new()
    media = vlc_instance.media_new(playurl)
    event_manager=player.event_manager()
    event_manager.event_attach(vlc.EventType().MediaPlayerEndReached, exit_program)
    media.get_mrl()
    player.set_media(media)
    player.play()
    volume = 50
    player.audio_set_volume(volume)
    command = ''
    while player.get_state() != 6:
        command = raw_input('Type "u" to increase volume;"d" to decrease volume;"s" to stop; "p" to pause; "" to play; : ')
        if command == 'u':
           volume = change_playback_volume(volume, volume+10)
           print("Volume={0}".format(volume))
           player.audio_set_volume(volume)
        elif command == 'd':
           volume = change_playback_volume(volume, volume-10)
           print("Volume={0}".format(volume))
           player.audio_set_volume(volume)
        elif command == 's':
           player.pause()
           break
        elif command == 'p':
           player.pause()
        elif command == '':
           player.play()
        else:
           print("Invalid Option")

def change_playback_volume(current_volume, new_volume):
    if(new_volume > MAX_VOLUME or new_volume < MIN_VOLUME):
        return current_volume
    else:
        return new_volume

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--search', help='Search term', default='Music')
  parser.add_argument('--max-results', help='Max results', default=1)
  args = parser.parse_args()
  youtube_search(args)
