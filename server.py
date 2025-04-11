#!/usr/bin/env python
# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Revisión 2014 Carlos Bederián
# Revisión 2011 Nicolás Wolovick
# Copyright 2008-2010 Natalia Bidart y Daniel Moisset
# $Id: server.py 656 2013-03-18 23:49:11Z bc $

import optparse
import socket
import connection
import threading
from constants import *
from typing import List, Tuple


class Server(object):
    """
    El servidor, que crea y atiende el socket en la dirección y puerto
    especificados donde se reciben nuevas conexiones de clientes.
    """

    def __init__(self, addr: str = DEFAULT_ADDR, port: int = DEFAULT_PORT,
                 directory: str = DEFAULT_DIR) -> None:
        print("Serving %s on %s:%s." % (directory, addr, port))
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.s.bind((addr, port))
        self.dir = directory
        # FALTA: Crear socket del servidor, configurarlo, asignarlo
        # a una dirección y puerto, etc.

    def serve(self) -> None:
        """
        Loop principal del servidor. Se acepta una conexión a la vez
        y se espera a que concluya antes de seguir.
        """
        # Se crea lista que almacenara hilos
        hilos = []

        # Se crea e inicia hilo encargado de cerrar conexiones
        thr_purge = threading.Thread(target=purge,
                                     args=(hilos,),
                                     daemon=True)
        thr_purge.start()

        # Configuacion para escuchar solicitud de conexion
        self.s.listen(N_THREADS)

        while True:

            # Se intentan iniciar nuevos hilos para manejar solicitudes
            try:
                # Creacion del socket, conexion e hilo.
                sock = self.s.accept()[0]
                conn = connection.Connection(sock, self.dir)
                thr = threading.Thread(target=conn.handle, daemon=True)
                thr.start()

                # Se almacena hilo creado en hilos para su
                # posterior cierre
                hilos.append((thr, sock, conn))

            # Si ocurre algun error cierra el servidor
            except (ConnectionError, TimeoutError,
                    RuntimeError, MemoryError,
                    Exception, KeyboardInterrupt):

                break


def purge(hilos: List[tuple[threading.Thread,
                            socket.socket,
                            connection. Connection]]) -> None:
    """
    Elimina los hilos que ya no deben ser atendidos liberando
    así los recursos utilizados
    """
    # Se ejecuta hasta cerrar el server
    while True:
        # Ve la lista de hilos en funcionamiento
        for h in hilos:
            # Si acabo su ejecucion cierra el hilo y el socket
            if not h[2].connected:
                h[0].join()
                h[1].close()


def main() -> None:
    """Parsea los argumentos y lanza el server"""
    parser = optparse.OptionParser()
    parser.add_option(
        "-p", "--port",
        help="Número de puerto TCP donde escuchar", default=DEFAULT_PORT)
    parser.add_option(
        "-a", "--address",
        help="Dirección donde escuchar", default=DEFAULT_ADDR)
    parser.add_option(
        "-d", "--datadir",
        help="Directorio compartido", default=DEFAULT_DIR)

    options, args = parser.parse_args()
    if len(args) > 0:
        parser.print_help()
        sys.exit(1)
    try:
        port = int(options.port)
    except ValueError:
        sys.stderr.write(
            "Numero de puerto invalido: %s\n" % repr(options.port))
        parser.print_help()
        sys.exit(1)

    server = Server(options.address, port, options.datadir)
    server.serve()

if __name__ == '__main__':
    main()
