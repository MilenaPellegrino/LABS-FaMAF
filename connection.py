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
        # El ciclo se mantiene hasta cambiar el booleano
        while self.connected:

            # Intenta recibir los datos y almacenarlos en self.buffer
            try:
                data = self.s.recv(4096).decode("ascii")
                self.buffer = ''
                while data:
                    self.buffer += data

                    # Si encuentra el EOL deja de recibir datos
                    if EOL in self.buffer:
                        data = None
                    else:
                        data = self.s.recv(4096).decode("ascii")

            # Si recibe datos que no puede decodificar se desconecta
            except (UnicodeDecodeError):
                self.connected = False
                break

            # Quita el EOL
            self.buffer = self.buffer.split(EOL)[0]

            # Se fija si hay algun \n innecesario
            # Manda error y
            # rearma el mensaje sin el \n
            test = self.buffer.split("\n")
            if (len(test) > 1):
                enviar_error(self, BAD_EOL)
                self.buffer = ''
                for i in range(len(test)):
                    self.buffer += test[i]

            # Guarda en message el arreglo con el comando
            message = self.buffer.split(' ')

            # Intenta matchear el comando y actuar acorde
            try:
                match message[0]:

                    case "quit":
                        # Se fija que el comando quit no
                        # tenga argumentos invalidos
                        #
                        # Si no los tiene ejecuta el comando
                        if (len(message) == 1):
                            self.quit()

                        # Si los tiene envia codigo de error
                        else:
                            enviar_error(self, INVALID_ARGUMENTS)

                    case "get_file_listing":
                        # Se fija que el comando get_file_listing no
                        # tenga argumentos invalidos
                        #
                        # Si no los tiene ejecuta el comando
                        if (len(message) == 1):
                            self.get_file_listing()

                        # Si los tiene envia codigo de error
                        else:
                            enviar_error(self, INVALID_ARGUMENTS)

                    case "get_metadata":
                        # Se fija que el comando get_metadata no
                        # tenga argumentos invalidos
                        #
                        # Si no los tiene ejecuta el comando
                        if (len(message) == 2):
                            self.get_metadata(message[1])

                        # Si los tiene envia codigo de error
                        else:
                            enviar_error(self, INVALID_ARGUMENTS)

                    case "get_slice":
                        # Se fija que el comando get_slice no
                        # tenga argumentos invalidos
                        #
                        # Si no los tiene ejecuta el comando
                        if (len(message) == 4):
                            self.get_slice(message[1], message[2], message[3])

                        # Si los tiene envia codigo de error
                        else:
                            enviar_error(self, INVALID_ARGUMENTS)

                    case "help":
                        # Se fija que el comando help no
                        # tenga argumentos invalidos
                        #
                        # Si no los tiene ejecuta el comando
                        if (len(message) == 1):
                            self.help()

                        # Si los tiene envia codigo de error
                        else:
                            enviar_error(self, INVALID_ARGUMENTS)

                    case _:
                        # Si lo recibido no es un comando
                        # devuelve codigo de error
                        enviar_error(self, INVALID_COMMAND)

            # Si enviando datos algun Pipe se daño
            # significa que la conexion se termino externamente
            # cierra la conexion
            except (BrokenPipeError):
                self.connected = False

    def quit(self) -> None:
        """
        Comando para cerrar la conexión con el cliente
        """
        # Envia codigo de exito
        resp = resp_formato(self, CODE_OK)
        self.s.send(resp.encode("ascii"))

        # Cierra la conexion
        self.connected = False

    def get_file_listing(self) -> None:
        """
        Permite al cliente solicitar al servidor
        la lista de archivos disponibles en el directorio
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
            # Revisa que el archivo tenga caracteres validos
            if not nombre_valido(filename):
                raise FileNotFoundError

            # Guarda la direccion del archivo
            filepath = os.path.join(self.dir, filename)

            # Chequeo si el archivo existe en nuestro directorio
            if not os.path.isfile(filepath):
                raise FileNotFoundError

            # Guarda en data el tamaño del archivo
            data = os.path.getsize(filepath)

            # Devuelvo codigo de exito + contenido del mensaje
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
        # Chequeo que los argumentos sean no negativos
        try:
            offset = int(offset)
            size = int(size)
            if offset < 0 or size < 0:
                raise ValueError

        # Si son negativos envio codigo de error
        # y vuelvo a handle
        except ValueError:
            enviar_error(self, INVALID_ARGUMENTS)
            return

        # Obtengo la direccion del archivo
        filepath = os.path.join(self.dir, filename)

        # Abrimos el archivo
        try:
            file = os.open(filepath, os.O_RDONLY)

        # Si no se encontro devuelvo codigo de error
        # y vuelvo a handle
        except FileNotFoundError:
            enviar_error(self, FILE_NOT_FOUND)
            return

        # Si ocurre cualquier otro error, codigo de error
        # y vuelvo a handle
        except Exception:
            enviar_error(self, INTERNAL_ERROR)
            return

        # Se intenta leer el archivo
        try:
            # Se obtiene el tamaño del archivo
            filesize = os.fstat(file).st_size

            # Chequeamos que no se intente leer más allá de lo razonable
            if offset >= filesize or offset + size > filesize:
                enviar_error(self, BAD_OFFSET)
                return

            # Leemos los datos solicitados, lo encodeamos y formateamos
            data = os.pread(file, size, offset)
            encoded = b64encode(data).decode("ascii")
            resp = resp_formato(self, CODE_OK)
            resp += encoded + EOL
            self.s.send(resp.encode("ascii"))

        # Si no se pudo leer el archivo
        # devuelve error
        except Exception:
            enviar_error(self, INTERNAL_ERROR)

        # Cierra el archivo
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
    # Chequea si el codigo de estado es fatal
    # y cierra la conexion
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
