import socket
import os

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ('127.0.0.1', 8888)

message = raw_input()
sock.sendto(message.encode(), server_address)

if os.fork():
    while True:
        data, address = sock.recvfrom(4096)
        print('Server:' + data)
else:
    while True:
        message = raw_input()

sock.sendto(message.encode(), server_address)
