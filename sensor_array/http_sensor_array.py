#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
import commands
import os
import time
import sys
import argparse
import psutil
from subprocess import Popen, PIPE, STDOUT
from urlparse import urlparse

import gas_sensor as Gas, temperature_sensor as Temperature #, luminosity_sensor as Luminosity

DEFAULT_ERROR = {"error":"command failed to execute"}
RETURN_CODE_SUCCESS = 200
RETURN_CODE_ERROR = 500

PORT_NUMBER = 8091
ROUTES = [
	'/temperature', '/gas', '/luminosity'
]

#This class will handles any incoming request from
#the browser 
class myHandler(BaseHTTPRequestHandler):
	

	def invoke_temperature_script(self):
		try:	
			return Temperature.getValues()
		except Exception as e:
			print(e)
			return e            			

	def invoke_gas_script(self):
		try:
			return Gas.getValues()
		except Exception as e:
			print(e)			
			return e

	def invoke_luminosity_script(self):
                try:
			return 0
			#return Luminosity.getValues()
		except Exception as e:
			print(e)			
			return e		

	#Handler for the GET requests
	def do_GET(self):
		response = {}
		response_code = RETURN_CODE_SUCCESS
		#temperature/humidity
		if ROUTES[0] == self.path:
			response = self.invoke_temperature_script()
		#gas
		elif ROUTES[1] == self.path:
			response = self.invoke_gas_script()
		#luminosity
		elif ROUTES[2] == self.path:
			response = self.invoke_luminosity_script()
		else:
			response_code = 404

		self.send_header('Content-type','application/json')
		self.end_headers()
		# Send the html message
		self.send_response(response_code)
		if response_code != RETURN_CODE_SUCCESS or isinstance(response, Exception):
			print("return code = "+str(response_code))
			print(response)
			self.wfile.write(DEFAULT_ERROR)
		else:			
			self.wfile.write(response)
			
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
