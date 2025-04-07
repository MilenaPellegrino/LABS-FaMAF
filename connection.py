# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Copyright 2014 Carlos Bederián
# $Id: connection.py 455 2011-05-01 00:32:09Z carlos $

import socket
from constants import *
from base64 import b64encode
import os

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
            self.buffer = ''
            while data:
                self.buffer += data
                if EOL in self.buffer:
                    data = None 
                else:
                    data = self.s.recv(4096).decode("ascii")
            self.buffer = self.buffer.split(EOL)[0]
            message = self.buffer.split()
            print(message)
            match message[0]:
                case "quit":
                    if (len(message)==1):
                        self.quit()
                    else:
                        code = str(BAD_REQUEST) + EOL
                        self.s.send(code.encode("ascii"))
                        
                case "get_file_listing":
                    if (len(message)==1):
                        self.get_file_listing()
                    else:
                        code = str(BAD_REQUEST) + EOL
                        self.s.send(code.encode("ascii"))
                case "get_metadata":
                    self.get_metadata(message[1])
                case "get_slice":
                    self.get_slice()
                case _:
                    code = str(BAD_REQUEST) + EOL
                    self.s.send(code.encode("ascii"))

    def quit(self):
        # code = str(CODE_OK) + EOL Creo que aca tendria que decir "OK"
        # Segun el enunciado y en algunos ejemplos de comandos
        resp = resp_formato(self, CODE_OK)
        self.s.send(resp.encode("ascii"))
        self.connected = False
        
    def get_file_listing(self):
        """
        Permite al cliente solicitar al servidor la lista de archivos disponibles en el directorio 
        Respuesta: 
            0 OK\r\n
            archivo1.txt\r\n
            archivo2.jpg\r\n
            \r\n
        """
        # Obtenemos todos los archivos en el directorio
        files = os.listdir(self.dir)
        # La primera linea tine que ser: 0 OK\r\n
        resp = resp_formato(self, CODE_OK)
        for file in files:
            resp += file + EOL
        # Linea vacia del final
        resp += EOL
        self.s.send(resp.encode("ascii"))

#Agregué el parametro filename que es dado desde handle que es el metodo
#que llama a los demás, chequea el case =="get_metadata"
    def get_metadata(self, filename):
        
        #acá le cambie el nombre a la variable
        filepath = os.path.join(self.dir, filename)

        if not os.path.isfile(filepath):
            self.s.send((str(FILE_NOT_FOUND) + EOL).encode("ascii"))
            return

        stat_info = os.stat(filepath)

        #Creamos el método resp_format para poder darle formato de los
        #códigos que le ponemos de parametro, la idea es usar eso
        #esta función, agrega directamente el EOL
        resp = resp_formato(self, CODE_OK)

        #Fijate en la consigna del lab, la respuesta esperada solo contiene
        #<codigo de exito> + EOL
        #<Tamaño del archivo> + EOL
        resp += str(stat_info.st_size)
        resp += EOL
        self.s.send(resp.encode("ascii"))

        #FALTAN TODOS LOS POSIBLES ERRORES
        #INVALID_REQUEST lo vamos a manejar en handle, pero falta otros
        #El que yo agregaría acá es el de INTERNAL_ERROR

    def get_slice(self):
        pass

def resp_formato(self, code):
    """
    Devuelve la respuesta formateada según el código de estado.
    Formato de la respuesta: "<código> <mensaje de error>\r\n"
    """
    if not valid_status(code):
        # Ni idea que hacer si no es ninguno de nuestras lista de codigos de estado
        pass
    # Si el código representa un error fatal, se cierra la conexión
    if fatal_status(code):
        self.connected = False
    # el f-string pasa todo a string y no necesitamos hacer str(code)
    return f"{code} {error_messages[code]}{EOL}"