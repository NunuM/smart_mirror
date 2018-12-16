import commands
import os
import time
import sys
import argparse
import psutil
from subprocess import Popen, PIPE

def process_running():
    process = Popen(['python', "youtube_stream.py"], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    process.stdin.write("s")
    print process.communicate()[0]
    process.stdin.close()

def command_formatter(command):
  return 0
  
def try_invoke(args):
  try:
     os.system("python {0}.py {1}".format(args.command, args.args))
  except:
     print("Unable to execute command")

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--command', help='command', default='')
  parser.add_argument('--args', help='arguments', default='')
  args = parser.parse_args()
  #try_invoke(args)
  process_running()
  
  

