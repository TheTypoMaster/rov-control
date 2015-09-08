# Echo client
import socket
import sys

HOST = '192.168.137.2'    # The remote host
PORT = 12000              # The same port as used by the server

def connect():
    s = None
    for res in socket.getaddrinfo(HOST, PORT, socket.AF_UNSPEC, socket.SOCK_STREAM):
        af, socktype, proto, canonname, sa = res
        try:
            s = socket.socket(af, socktype, proto)
        except socket.error as msg:
            s = None
            continue
        try:
            s.connect(sa)
        except socket.error as msg:
            s.close()
            s = None
            continue
        break
    return s

def send_and_recieve(msg, socket):
    socket.sendall(msg)
    data = socket.recv(1024)
    print 'Received', repr(data)

def echo():
    socket = connect()
    send_and_recieve("hi", socket)
