from threading import Thread
#Failed try on implementing a helpers.py file
# from rov_control.Helpers import *
import socket
import sys


def main():
    # Create a TCP/IC socket
    sock = initialize_socket()

    # Bind the socket to the port
    server_adress = ('',10000)
    print ('starting up on %s port %s' % server_adress , file=sys.stderr)
    sock.bind(server_adress)

    #listen for 1 incoming connections
    sock.listen(1)

    while True:
            # wait for a connection
            print ('waiting for connection', file=sys.stderr)
            (connection, client_address) = sock.accept()

            try:
                print ('connection from', client_address, file=sys.stderr)

                #receive the data in small chunks and retransmit it
                while True:
                    data = connection.recv(20)
                    print ('received "%s"' % data, file=sys.stderr)

                    if data:
                        print ('sending data back to client', file=sys.stderr)
                        connection.sendall(data)
                    else:
                        print ('no more data from' , client_address, file=sys.stderr)
                        break

            finally:
                #clean up the connection
                connection.close()

def initialize_socket():
    return socket.socket(socket.AF_INET, socket.SOCK_STREAM)


# messaging colouring.
def print_warning(msg):
    print (Colour.WARNING + str(msg) + Colour.end_colour)

def print_error(msg):
   print (Colour.error + str(msg) + Colour.end_colour)

def print_header(msg):
   print (Colour.Header + str(msg) + Colour.end_colour)

def print_debug(msg):
   print (Colour.blue + str(msg) + Colour.end_colour)


class Colour:
    header     = '\033[95m'
    blue       = '\033[94m'
    warning    = '\033[92m'
    error      = '\033[91m'
    end_colour = '\033[0m'

    def disable (self):
        self.HEADER  = ''
        self.OKBLUE  = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL    = ''
        self.ENDC    = ''

if __name__ == '__main__':
    main()
