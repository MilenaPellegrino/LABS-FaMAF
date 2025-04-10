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

    def __init__(self, socket: socket.socket, directory: str) -> None:
        self.s = socket
        self.dir = directory
        self.buffer = ''
        self.connected = True

    def handle(self) -> None:
        """
        Mientras la conexión esté activa, escucha las
        peticiones y las maneja de acuerdo a los
        comandos implementados
        """
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
            
            message = self.buffer.split(' ')
            # print(message)
            match message[0]:
                case "quit":
                    if (len(message)==1):
                        self.quit()
                    else:
                        code = resp_formato(self, INVALID_ARGUMENTS)
                        self.s.send(code.encode("ascii"))
                case "get_file_listing":
                    if (len(message)==1):
                        self.get_file_listing()
                    else:
                        code = resp_formato(self, INVALID_ARGUMENTS)
                        self.s.send(code.encode("ascii"))
                case "get_metadata":
                    if (len(message)==2):
                        self.get_metadata(message[1])
                    else:
                        code = resp_formato(self, INVALID_ARGUMENTS)
                        self.s.send(code.encode("ascii"))
                case "get_slice":
                    if(len(message)==4): 
                        self.get_slice(message[1], message[2], message[3])
                    else:
                        code = resp_formato(self, INVALID_ARGUMENTS)
                        self.s.send(code.encode("ascii"))
                case "help":
                    if(len(message)==1):
                        self.help()
                    else:
                        code = resp_formato(self, INVALID_ARGUMENTS)
                        self.s.send(code.encode("ascii"))
                case _:
                    if (len(message[0].split("\n")) > 1):
                        code = resp_formato(self, BAD_EOL)
                        self.s.send(code.encode("ascii"))
                    else :
                        code = resp_formato(self, INVALID_COMMAND)
                        self.s.send(code.encode("ascii"))

    def quit(self) -> None:
        """
        Comando para cerrar la conexión con el cliente
        """
        resp = resp_formato(self, CODE_OK)
        self.s.send(resp.encode("ascii"))
        self.connected = False
        
    def get_file_listing(self) -> None:
        """
        Permite al cliente solicitar al servidor la lista de archivos disponibles en el directorio 
        Respuesta: 
            0 OK\r\n
            archivo1.txt\r\n
            archivo2.jpg\r\n
            \r\n
        """

        try:
            # Verificamos que el directorio exista y sea válido
            if not os.path.isdir(self.dir):
                raise FileNotFoundError
        
            # Obtenemos todos los archivos en el directorio
            files = os.listdir(self.dir)

        # MANEJO DE LOS ERRORES 

        # No se encontro el directorio o es invalido 
        except FileNotFoundError:
            enviar_error(self, BAD_REQUEST)
            return
        
        # Cualquier otro error que ocurra
        except Exception:
            enviar_error(self, INTERNAL_ERROR)
            return
        
        # Si todo anduvo bien, respondemos 

        # La primera linea tine que ser: 0 OK\r\n
        resp = resp_formato(self, CODE_OK)
        for file in files:
            resp += file + EOL
        # Linea vacia del final
        resp += EOL
        self.s.send(resp.encode("ascii"))

    def get_metadata(self, filename: str) -> None:
        """
        Permite al cliente solicitar el tamaño del archivo filename
        """
        try:
            if not nombre_valido(filename):
                raise FileNotFoundError
            
            filepath = os.path.join(self.dir, filename)
        
            # Chequeo si el archivo existe en nuestro directorio
            if not os.path.isfile(filepath):
                raise FileNotFoundError 
            
            data = os.path.getsize(filepath) 
            resp = resp_formato(self, CODE_OK)
            resp += str(data) + EOL
            self.s.send(resp.encode("ascii"))
        
        # Si el archivo no existe
        except FileNotFoundError:
            enviar_error(self, FILE_NOT_FOUND)

        # Cualquier otro error que pueda ocurrir
        except Exception:
            enviar_error(self, INTERNAL_ERROR)
                

    def get_slice(self, filename: str, offset: str, size: str) -> None:
        """Permite solicitar al cliente el contenido
        (codificado en base64) del archivo filename desde offset hasta size
        """
        #Chequeo que los argumentos sean no negativos
        try:
            offset = int(offset)
            size = int(size)
            if offset < 0 or size < 0:
                raise ValueError
        except ValueError:
            resp = resp_formato(self, INVALID_ARGUMENTS)
            self.s.send(resp.encode("ascii"))
            return
        
        filepath = os.path.join(self.dir, filename)

        #Abrimos el archivo
        try:
            file = os.open(filepath, os.O_RDONLY)
        except FileNotFoundError:
            resp = resp_formato(self, FILE_NOT_FOUND)
            self.s.send(resp.encode("ascii"))
            return
        
        except Exception:
            resp = resp_formato(self, INTERNAL_ERROR)
            self.s.send(resp.encode("ascii"))
            return
        
        try:
            filesize = os.fstat(file).st_size
            #Chequeamos que no se intente leer más allá de lo razonable
            if offset >= filesize or offset + size > filesize:
                resp = resp_formato(self, BAD_OFFSET)
                self.s.send(resp.encode("ascii"))
                return
            #Leemos loo datos necesarios, lo encodeamos y formateamos
            data = os.pread(file, size, offset)
            encoded = b64encode(data).decode("ascii")
            resp = resp_formato(self, CODE_OK)
            resp += encoded + EOL
            self.s.send(resp.encode("ascii"))

        except Exception:
            resp = resp_formato(self, INTERNAL_ERROR)
            self.s.send(resp.encode("ascii"))

        finally:
            os.close(file)

    def help(self) -> None:
        """
        Printea en pantalla los comandos que puedes utilizar
        """
        resp = resp_formato(self, CODE_OK)
        resp += HELP_TEXT
        resp += EOL
        self.s.send(resp.encode("ascii"))

def resp_formato(self: Connection, code: int) -> str:
    """
    Devuelve la respuesta formateada según el código de estado.
    Formato de la respuesta: "<código> <mensaje de error>\r\n"
    """
    if fatal_status(code):
        self.connected = False
    # el f-string pasa todo a string y no necesitamos hacer str(code)
    return f"{code} {error_messages[code]}{EOL}"

def enviar_error(self: Connection, code: int) -> None:
    """
    Envía un mensaje de error al cliente con el código dado.
    """
    resp = resp_formato(self, code)
    self.s.send(resp.encode("ascii"))
    return

def nombre_valido(filename: str) -> bool:
    """
    Verifica si el nombre del archivo contiene solo caracteres válidos.
    """
    for char in filename:
        if char not in VALID_CHARS:
            return False
    return True
