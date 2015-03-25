#!/usr/bin/env python
import socket
import serial
from time import sleep


def main():

	try:
		msg = "Hello, World!"

		tcp_ip = 'localhost'
		tcp_port = 10000
		buffer_size = 1024

		s = initialize_socket()
		s.connect((tcp_ip, tcp_port))

		s.send('I am alive!')
		s.send('I am alive!')
		s.send('I am alive!')
				
		while True:
			data = s.recv(buffer_size)
			print str(data)
			s.send('Hei')
			print_debuginfo('send complete')

	except Exception, e:
		print_error('Error in main: ' + str(e))
	finally:
		s.close()
		print_warning('Closing socket')
		
def initialize_socket():
	return socket.socket(socket.AF_INET, socket.SOCK_STREAM)

class Colour:
    header = '\033[95m'
    blue = '\033[94m'
    green = '\033[92m'
    warning = '\033[93m'
    error = '\033[91m'
    end_colour = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

def print_debuginfo(msg):
	print Colour.blue + msg +Colour.end_colour

def print_warning(msg):
	print Colour.warning + msg + Colour.end_colour  	

def print_error(msg):
	print Colour.error + msg + Colour.end_colour

def print_header(msg):
	print Colour.error + msg + Colour.end_colour

if __name__ == '__main__':
    main()
