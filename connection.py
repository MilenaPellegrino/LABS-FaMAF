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
                        code = resp_formato(self, BAD_REQUEST)
                        self.s.send(code.encode("ascii"))
                case "get_file_listing":
                    if (len(message)==1):
                        self.get_file_listing()
                    else:
                        code = resp_formato(self, BAD_REQUEST)
                        self.s.send(code.encode("ascii"))
                case "get_metadata":
                    if (len(message)==2):
                        self.get_metadata()
                    else:
                        code = resp_formato(self, BAD_REQUEST)
                        self.s.send(code.encode("ascii"))
                case "get_slice":
                    if(len(message)==4): 
                        self.get_slice(message[1], message[2], message[3])
                    else:
                        code = resp_formato(self, BAD_REQUEST)
                        self.s.send(code.encode("ascii"))
                case _:
                        code = resp_formato(self, BAD_REQUEST)
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

    def get_metadata(self):
        pass

    def get_slice(self, filename, offset, size):

        # Pasa los parametros a INT y verifica que sean no negativos,
        # de lo contrario, devuelve el error INVALID_ARGUMENTS
        try:
            offset = int(offset)
            size = int(size)
            if offset < 0 or size < 0:
                raise ValueError
        except ValueError:
            resp = resp_formato(self, INVALID_ARGUMENTS)
            self.s.send(resp.encode("ascii"))
            return
        
        #os.path.join te junta los que necesites en la forma de path
        #de tu sistema operativo, en Linux es con "/" pero en Windows es
        #con "\"
        filepath = os.path.join(self.dir, filename)

        #Intenta abrir, si el archivo no existe, manda el error
        try:
            file = os.open(filepath, os.O_RDONLY)
        except FileNotFoundError:
            resp = resp_formato(self, FILE_NOT_FOUND)
            self.s.send(resp.encode("ascii"))
            return
        
        #Si ocurrió otro error grave, tira error interno
        except Exception:
            resp = resp_formato(self, INTERNAL_ERROR)
            self.s.send(resp.encode("ascii"))
            return
        
        try:
            #Con esta función averiguo el tamaño en bytes del archivo
            filesize = os.fstat(file).st_size

            #Verifico no estar leyendo más de lo permitido
            if offset >= filesize or offset + size >= filesize:
                resp = resp_formato(self, BAD_OFFSET)
                self.s.send(resp.encode("ascii"))
                return

            #Llego todo OK
            data = os.pread(file, size, offset)
            encoded = b64encode(data).decode("ascii")
            resp = resp_formato(self, CODE_OK)
            resp += encoded + EOL
            self.s.send(resp.encode("ascii"))

        #Si falla con "excepcion sin salida"
        except Exception:
            resp = resp_formato(self, INTERNAL_ERROR)
            self.s.send(resp.encode("ascii"))

        finally:
            os.close(file)

def resp_formato(self, code):
    """
    Devuelve la respuesta formateada según el código de estado.
    Formato de la respuesta: "<código> <mensaje de error>\r\n"
    """
    if fatal_status(code):
        self.connected = False
    return f"{code} {error_messages[code]}{EOL}"
