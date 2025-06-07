<<<<<<< HEAD
# Lab2-OdC
Trabajo de Laboratorio n°2: VC FrameBuffer en QEMU emulando una RPi

# Objetivos
  ● Escribir programas en lenguaje ensamblador ARMv8.
  
  ● Comprender la interfaz de entrada/salida de un microprocesador ARM, utilizando una
    interfaz visual.
    
  ● Comprobar el principio de funcionamiento de una estructura FrameBuffer de video en
    una plataforma Raspberry Pi 3 emulada.
    
  ● Emular el comportamiento de los pines de entrada-salida de propósitos generales
    (GPIO) del microprocesador ARM usando el teclado de la computadora
    
=======
# Lab Org. y Arq. de Computadoras

* Configuración de pantalla: `640x480` pixels, formato `ARGB` 32 bits.
* El registro `X0` contiene la dirección base del FrameBuffer (Pixel 1).
* El código de cada consigna debe ser escrito en el archivo _app.s_.
* El archivo _start.s_ contiene la inicialización del FrameBuffer **(NO EDITAR)**, al finalizar llama a _app.s_.
* El código de ejemplo pinta toda la pantalla un solo color.

## Estructura

* **[app.s](app.s)** Este archivo contiene a apliación. Todo el hardware ya está inicializado anteriormente.
* **[start.s](start.s)** Este archivo realiza la inicialización del hardware.
* **[Makefile](Makefile)** Archivo que describe como construir el software _(que ensamblador utilizar, que salida generar, etc)_.
* **[memmap](memmap)** Este archivo contiene la descripción de la distribución de la memoria del programa y donde colocar cada sección.

* **README.md** este archivo.

## Uso

El archivo _Makefile_ contiene lo necesario para construir el proyecto.
Se pueden utilizar otros archivos **.s** si les resulta práctico para emprolijar el código y el Makefile los ensamblará.

**Para correr el proyecto ejecutar**

```bash
$ make runQEMU
```
Esto construirá el código y ejecutará qemu para su emulación.

Si qemu se queja con un error parecido a `qemu-system-aarch64: unsupported machine type`, prueben cambiar `raspi3` por `raspi3b` en la receta `runQEMU` del **Makefile** (línea 23 si no lo cambiaron).

**Para correr el gpio manager**

```bash
$ make runGPIOM
```

Ejecutar *luego* de haber corrido qemu.

## Como correr qemu y gcc usando Docker containers

Los containers son maquinas virtuales livianas que permiten correr procesos individuales como el qemu y gcc.

Para seguir esta guia primero tienen que instala docker y asegurarse que el usuario que vayan a usar tenga permiso para correr docker (ie dockergrp) o ser root

### Linux
 * Para construir el container hacer
```bash
docker build -t famaf/rpi-qemu .
```
 * Para arrancarlo
```bash
xhost +
cd rpi-asm-framebuffer
docker run -dt --name rpi-qemu --rm -v $(pwd):/local --privileged -e "DISPLAY=${DISPLAY:-:0.0}" -v /tmp/.X11-unix:/tmp/.X11-unix -v "$HOME/.Xauthority:/root/.Xauthority:rw" famaf/rpi-qemu
```
 * Para correr el emulador y el simulador de I/O
```bash
docker exec -d rpi-qemu make runQEMU
docker exec -it rpi-qemu make runGPIOM
```
 * Para terminar el container
```bash
docker kill rpi-qemu
```

### MacOS
En MacOS primero tienen que [instalar un X server](https://medium.com/@mreichelt/how-to-show-x11-windows-within-docker-on-mac-50759f4b65cb) (i.e. XQuartz)
 * Para construir el container hacer
```bash
docker build -t famaf/rpi-qemu .
```
 * Para arrancarlo
```bash
xhost +
cd rpi-asm-framebuffer
docker run -dt --name rpi-qemu --rm -v $(pwd):/local --privileged -e "DISPLAY=host.docker.internal:0" -v /tmp/.X11-unix:/tmp/.X11-unix -v "$HOME/.Xauthority:/root/.Xauthority:rw" famaf/rpi-qemu
```
 * Para correr el emulador y el simulador de I/O
```bash
docker exec -d rpi-qemu make runQEMU
docker exec -it rpi-qemu make runGPIOM
```
 * Para terminar el container
```bash
docker kill rpi-qemu
```
----------------------------------
### Otros comandos utiles
```bash
# Correr el container en modo interactivo
docker run -it --rm -v $(pwd):/local --privileged -e "DISPLAY=${DISPLAY:-:0.0}" -v /tmp/.X11-unix:/tmp/.X11-unix -v "$HOME/.Xauthority:/root/.Xauthority:rw" famaf/rpi-qemu
# Correr un shell en el container
docker exec -it rpi-qemu /bin/bash
```
>>>>>>> master
=======
**Edit a file, create a new file, and clone from Bitbucket in under 2 minutes**

When you're done, you can delete the content in this README and update the file with details for others getting started with your repository.

*We recommend that you open this README in another tab as you perform the tasks below. You can [watch our video](https://youtu.be/0ocf7u76WSo) for a full demo of all the steps in this tutorial. Open the video in a new tab to avoid leaving Bitbucket.*

---

## Edit a file

You’ll start by editing this README file to learn how to edit a file in Bitbucket.

1. Click **Source** on the left side.
2. Click the README.md link from the list of files.
3. Click the **Edit** button.
4. Delete the following text: *Delete this line to make a change to the README from Bitbucket.*
5. After making your change, click **Commit** and then **Commit** again in the dialog. The commit page will open and you’ll see the change you just made.
6. Go back to the **Source** page.

---

## Create a file

Next, you’ll add a new file to this repository.

1. Click the **New file** button at the top of the **Source** page.
2. Give the file a filename of **contributors.txt**.
3. Enter your name in the empty file space.
4. Click **Commit** and then **Commit** again in the dialog.
5. Go back to the **Source** page.

Before you move on, go ahead and explore the repository. You've already seen the **Source** page, but check out the **Commits**, **Branches**, and **Settings** pages.

---

## Clone a repository

Use these steps to clone from SourceTree, our client for using the repository command-line free. Cloning allows you to work on your files locally. If you don't yet have SourceTree, [download and install first](https://www.sourcetreeapp.com/). If you prefer to clone from the command line, see [Clone a repository](https://confluence.atlassian.com/x/4whODQ).

1. You’ll see the clone button under the **Source** heading. Click that button.
2. Now click **Check out in SourceTree**. You may need to create a SourceTree account or log in.
3. When you see the **Clone New** dialog in SourceTree, update the destination path and name if you’d like to and then click **Clone**.
4. Open the directory you just created to see your repository’s files.

Now that you're more familiar with your Bitbucket repository, go ahead and add a new file locally. You can [push your change back to Bitbucket with SourceTree](https://confluence.atlassian.com/x/iqyBMg), or you can [add, commit,](https://confluence.atlassian.com/x/8QhODQ) and [push from the command line](https://confluence.atlassian.com/x/NQ0zDQ).
>>>>>>> 883889a87d6cfa7e3569b95d98c40d5488b3463b
