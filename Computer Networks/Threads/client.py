import socket

_HOST = '127.0.0.1'  # The server's hostname or IP address
_PORT = 8080       # The port used by the server
_BUCKET_SIZE = 1024

def get_imput():
    data = input("Command text: ")
    return data

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((_HOST, _PORT))

command_data = get_imput()

client_socket.sendall(command_data.encode('ascii'))
data = client_socket.recv(_BUCKET_SIZE)

print('Command output \n', repr(data))

