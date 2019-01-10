import socket
import os

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ('127.0.0.1',8888)
print('Server started broadcast up on', server_address)
sock.bind(server_address)

data, address = sock.recvfrom(4096)
print('Client:' + data)

if os.fork():
    while True:
        data, address = sock.recvfrom(4096)
        print('Client:' + data)
else:
    while True:
        message = raw_input()
sock.sendto(message.encode(),address)
