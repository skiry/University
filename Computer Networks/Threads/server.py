import socket
import threading
import subprocess
from time import sleep

_HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
_PORT = 8080        # Port to listen on (non-privileged ports are > 1023)
_BUCKET_SIZE = 1024


class ThreadedServer(object):
    def __init__(self, host, port):
        self.__host = host
        self.__port = port
        self.__socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.__socket.bind((self.__host, self.__port))


    def listen(self):
        self.__socket.listen(5)
        while True:
            cli_con, cli_addr = self.__socket.accept()
            cli_con.settimeout(60)
            threading.Thread(target = self.execute_command_job,args = (cli_con, cli_addr)).start()


    def execute_command_job(self, cli_con, cli_addr):
        sleep(3)
        size = 1024
        command = ""
        while True:
            try:
                print('Connected by', cli_addr)
                data = cli_con.recv(size)
                if data:
                    command = data
                else:
                    raise error('Client disconnected')
            except:
                cli_con.close()
                return False

            command_data = command.decode('ascii').split(" ")

            command_exec = subprocess.Popen(
                command_data,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            out, err = command_exec.communicate()
            print(out,err)
            if err:
                cli_con.sendall(err)
            else:
                cli_con.sendall(out)
            return

server = ThreadedServer(_HOST, _PORT)
server.listen()

