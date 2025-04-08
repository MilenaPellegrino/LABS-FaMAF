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
                    self.get_slice(message[1], message[2], message[3])
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

    def get_metadata(self, filename):

        
        try:

            if not self.nombre_valido(filename)
            filepath = os.path.join(self.dir, filename)
            
            # Chequeo si el archivo existe en nuestro directorio
            if not os.path.isfile(filepath):
                raise FileNotFoundError
            
            # Leyendo para entender como funcion el os.path.join
            # En la docu encontre: os.path.getsize(path) que te da el tamano directo 
            # sin los otros metadatos, que te da el stat, y usa una sola función en vez de dos 
            
            #os.path.getsize(filepath) VER CUAL USAR 
            stat_info = os.stat(filepath) 

            resp = resp_formato(self, CODE_OK)
            resp += str(stat_info.st_size)
            self.s.send(resp.encode("ascii"))
        
        # Si el archivo no existe
        except FileNotFoundError:
            self.enviar_error(FILE_NOT_FOUND)

        # Cualquier otro error que pueda ocurrir
        except Exception:
            self.enviar_error(INTERNAL_ERROR)
                

    def get_slice(self, filename, offset, size):
        if int(offset) >= 0 and int(size) >= 0:
            file = os.open(self.dir+"/"+filename,os.O_RDONLY)
            resp = resp_formato(self, CODE_OK)
            ret = os.pread(file, int(size), int(offset))
            ret = str(b64encode(ret))
            ret = ret.split("'")[1]
            resp += ret
            resp += EOL
            self.s.send(resp.encode("ascii"))
            os.close(file)

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

def enviar_error(self, code):
    """
    Envía un mensaje de error al cliente con el código dado.
    """
    resp = resp_formato(self, code)
    self.s.send(resp.encode("ascii"))
    return

def nombre_valido(filename):
    """
    Verifica si el nombre del archivo contiene solo caracteres válidos.
    """
    for char in filename:
        if char not in VALID_CHARS:
            return False
    return True