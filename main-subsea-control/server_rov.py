from mysocket import Socket, ListenerSocket
from select import select
import time, sys, serial

server_address = ('localhost', 10000)

def main():
	def wait_for_work():
		select(topsites + [listener], sending_sockets, [])

	def get_incomming():
		return select([listener], [], [], 0)[0]

	def get_readable():
		return select(topsites, [], [], 0)[0]

	def get_writeable():
		return select([], sending_sockets, [], 0)[1]

	listener = topsite_listener(*server_address)

	sending_sockets = []

	i = 0;

	while True:
		wait_for_work()

		for socket in get_incomming():
			connection = socket.accept()
			topsites.append(connection)


		for topsite in topsites:
			topsite.writeln('Thank you, all recived')

		for socket in get_readable():
			had_data = socket.transport_in()
			if not had_data:
				socket.close()
				topsites.remove(socket)
				topsite_disconnect(socket)
				print '\033[93m' "Lost the connection with topsite." '\033[37m'

			if socket.hasln():
				handle_topsite(socket)

		for socket in get_writeable():
			socket.transport_out()

		sending_sockets = filter(Socket.is_sending, topsites)

#----------------------- Communication with topsite -----------------------#

class Topsite(Socket):
	def __init__(self):
		self.msg = None;
		self.orders = set()

	@staticmethod
	def from_socket(socket):
		socket.__class__ = Topsite
		Topsite.__init__(socket)
		return socket

class topsite_listener(ListenerSocket):
	def accept(self):
		socket = ListenerSocket.accept(self)
		topsite = Topsite.from_socket(socket)
		print "Topsite connected."
		return topsite

topsites = []

def request():
	# A lot of stuff and orders

	msg = 'Message recived'
	topsite.writeln(msg)
	topsite.msg.add(msg)
		

def handle_topsite(topsite):
	# recieved a line from topsite
	msg = topsite.readln()

	for topsite in topsites:
		topsite.msg = msg

	socket_arduino = get_serial_connection()
	initialise()

	write_to_arduino(msg, socket_arduino)

	print "Topsite: " + msg

def topsite_disconnect(topsite):
	for order in topsite.orders:
		print '\033[93m' "Redirect order." '\033[37m'
		request(*order)

def get_serial_connection():
	# s = serial.Serial('/dev/ttyACM0', 9600); # RSPI
	s = serial.Serial(port='/dev/tty.usbmodem1421', baudrate=9600) # Mac Os X

#-------------------- Communication with Arduino ----------------------

def get_serial_connection():
	# return serial.Serial('sys/dev/ttyACM0', 9600); # RSPI
	# return serial.Serial('/sys/class/tty/ttyACM0', 9600); # Fedora

	# return serial.Serial(port='/dev/tty.usbmodem1421', baudrate=9600) # Mac Os X
	# return serial.Serial(port='/dev/tty.usbmodem1411', baudrate=9600) # Mac Os X
	return serial.Serial('/dev/ttyACM0', 9600); # Ubuntu

def wait(sec):
	time.sleep(sec)


def initialise():
	wait(2)


def write_to_arduino(msg, socket_arduino):
	socket_arduino.write(str(msg) + '\n')



if __name__ == '__main__':
	main()