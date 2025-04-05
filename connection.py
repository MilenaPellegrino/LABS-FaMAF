# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Copyright 2014 Carlos Bederián
# $Id: connection.py 455 2011-05-01 00:32:09Z carlos $

import socket
from constants import *
from base64 import b64encode

class Connection(object):
    """
    Conexión punto a punto entre el servidor y un cliente.
    Se encarga de satisfacer los pedidos del cliente hasta
    que termina la conexión.
    """

    def __init__(self, socket, directory):
        self.s = socket
        self.dir = directory
        self.buffer = ''
        self.connected = True

    def handle(self):
        print("Entramos a handle")
        while self.connected:
            data = self.s.recv(4096).decode("ascii")
            while len(data) != 0:
                self.buffer += data
                data = self.s.recv(4096).decode("ascii")
            
            #self.buffer = self.buffer[:EOL]
            message = self.buffer.split()
            print("conectado 2")
            print(message)
            match message[0]:
                case "quit":
                    print("Conectado 3")
                    self.quit
                    #case "get_file_listing":
                    #    self.get_file_listing
                    #case "get_metadata":
                    #    self.get_metadata
                    #case "get_slice":
                    #    self.get_slice
                case _:
                    print("No entro a ningún caso")
                

    def quit(self):
        print("Conectado 4")
        message = CODE_OK ++ EOL
        self.s.send(message.encode("ascii"))
        self.connected = False
        
