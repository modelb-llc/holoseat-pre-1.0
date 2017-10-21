import socket
from contextlib import closing

# from https://stackoverflow.com/a/45690594
def findFreePort():
    with closing(socket.socket(socket.AF_INET, socket.SOCK_STREAM)) as s:
        s.bind(('localhost', 0))
        return s.getsockname()[1]
