.include "animation.s"
.equ SCREEN_WIDTH,   640
.equ SCREEN_HEIGHT,  480
.equ BITS_PER_PIXEL, 32

// Valor de la pantalla para buclear la animacion
.equ SCREEN_WIDTH_ANIMACION,   590
.equ SCREEN_HEIGHT_ANIMACION,  430

.equ GPIO_BASE,    0x3f200000
.equ GPIO_GPFSEL0, 0x00
.equ GPIO_GPLEV0,  0x34

.globl main

// Bucle infinito para la animacion 

// Funcion normal 
main:
    // x0 contiene la direccion base del framebuffer
    mov x20, x0 // Guarda la dirección base del framebuffer en x20

	bl margen_pantalla
	bl laberinto
	bl ventana
	mov x3, 25
	mov x4, 435
	bl dibujar_astronauta
	bl move_astronaut

	bl margen_pantalla2

	// Inicializamos los valores para la animacion: 
	bl fondo_animacion


	mov x3, 50 
	mov x4, 50
	bl animacion

	// +++++++ COMIENZO ANIMACION ++++++++++
animacion:
	bl draw_meteorito
	bl step_in_time
   	bl fondo_animacion

	// Actualiza las posiciones x3 (x) y x4 (y)
    add x3, x3, #1          // Incrementa la posición x
    add x4, x4, #1          // Incrementa la posición y

    // Comprueba si el meteorito ha llegado al borde inferior derecho
    cmp x3, SCREEN_WIDTH_ANIMACION
    b.ge reset_position

    cmp x4, SCREEN_HEIGHT_ANIMACION
    b.ge reset_position

    // Repite el bucle de animación
    bl animacion

// Restablece la posición del cuadrado si alcanza el borde
reset_position:
    mov x3, #50              // Restablece la posición x
    mov x4, #50              // Restablece la posición y
    bl animacion             // Repite el bucle de animación
ret

	// +++++++ FIN ANIMACION ++++++++++

InfLoop:
	b InfLoop
