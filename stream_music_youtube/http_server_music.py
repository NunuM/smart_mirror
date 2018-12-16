#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
import commands
import os
import time
import sys
import argparse
import psutil
from subprocess import Popen, PIPE, STDOUT

RETURN_CODE_SUCCESS = 200
RETURN_CODE_ERROR = 500

PORT_NUMBER = 8090
ROUTES = [
	'/play', '/pause', '/stop', '/up', '/down'
]

process = {}

#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
	

	def try_play_music(self):
		try:	
			global process    # Needed to modify global copy of process
			if hasattr(process, 'terminate'):
				process.terminate()

			process = Popen(["python", "youtube_stream.py", "--search", "'last christmas'"], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
			#time.sleep(10)   
			#process.wait()
			return RETURN_CODE_SUCCESS
		except Exception as e:
			print(e)			
			return RETURN_CODE_ERROR

	def try_execute_command(self,command):
		try:
			full_command = command+'\n'
			process.stdin.write(b''.join(full_command))
			process.stdin.flush()
			#print(process.stdout.readline())
			return RETURN_CODE_SUCCESS
		except Exception as e:
			print(e)			
			return RETURN_CODE_ERROR

	def try_stop_music(self):
		return_value = self.try_execute_command('s')
		process.terminate()
		return return_value			

	def try_pause_music(self):
		return self.try_execute_command('p')

	def try_change_volume(self, command):
		return self.try_execute_command(command)

	#Handler for the GET requests
	def do_GET(self):
		response_code = RETURN_CODE_SUCCESS		
		#play
		if ROUTES[0] in self.path:
			response_code = self.try_play_music()
		#pause
		elif ROUTES[1] in self.path:
			response_code = self.try_pause_music()
		#stop
		elif ROUTES[2] in self.path:
			response_code = self.try_stop_music()
		#increase volume
		elif ROUTES[3] in self.path:
			response_code = self.try_change_volume('u')
		#decrease volume
		elif ROUTES[4] in self.path:
			response_code = self.try_change_volume('d')
		else:
			response_code = 404

		self.send_header('Content-type','application/json')
		self.end_headers()
		# Send the html message
		self.send_response(response_code)
		if response_code == RETURN_CODE_ERROR:
			self.wfile.write('{"message":"command failed to execute"}')
		else:
			self.wfile.write('{"message":"command executed"}')
			
		return

try:
	#Create a web server and define the handler to manage the
	#incoming request
	server = HTTPServer(('', PORT_NUMBER), myHandler)
	print 'Started httpserver on port ' , PORT_NUMBER
	
	#Wait forever for incoming htto requests
	server.serve_forever()

except KeyboardInterrupt:
	print '^C received, shutting down the web server'
	server.socket.close()
