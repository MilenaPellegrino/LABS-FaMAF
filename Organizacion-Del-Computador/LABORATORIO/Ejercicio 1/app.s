.include "drawings.s"

.equ SCREEN_WIDTH,   640
.equ SCREEN_HEIGHT,  480
.equ BITS_PER_PIXEL, 32

.equ GPIO_BASE,    0x3f200000
.equ GPIO_GPFSEL0, 0x00
.equ GPIO_GPLEV0,  0x34

.globl main

// Funcion normal 
main:
    // x0 contiene la direccion base del framebuffer
    mov x20, x0 // Guarda la dirección base del framebuffer en x20

	bl fondo_degrade
	bl fondo_estrella

	bl dibujar_astronauta

	mov x3, 100
	mov x4, 100
	mov x1, 50
	mov w10, 0xFFFFFF
	

	mov x3, 320
	mov x4, 240
	mov x5, 150
	bl draw_saturn

	// EMPEZAMOS A METERNOS EN EL HERMOSO Y HORRIBLE MUNDO DEL GPIO 
	//Guardamos en x9 la direccion base del GPIO 
	mov x9, GPIO_BASE	// La direccion base es diferente al del manual se debe a que es emulada
	
	// Cargamos en x12 un valor relativamente grande para poder ver la otra escena por pantalla
	ldr x12, = 0x700000


InfLoop:

	// Leemos el estado del 0-31 y lo almacenamos en w14. 
	// Recordemos que x9 tiene la direccion base del GPIO
	/*
	GPIO_GPLEV0 almacena un bit por cada GPIO que se desea leer.
	Cada bit en el registro refleja el estado actual del GPIO correspondiente:
    	- 0 (bajo): Indica que el GPIO está en un nivel bajo (pulsador liberado).
    	- 1 (alto): Indica que el GPIO está en un nivel alto (pulsador presionado).
	 */
	ldr w14, [x9, GPIO_GPLEV0]	

#0B2239
    movz x10, 0x0B, lsl 16
	movk x10, 0x2239, lsl 00 // color del fondo
	// Extraccion del estado del bit 2 de w14 y lo guardamos en w11
	and w11, w14, 0b00000010 // Usamos la mascara binaria 

	/*
	Si el bit 2 de w14 ahora guardado en w11 está en alto (1), 
	signfica que se presiono el pulsador, entonces saltamos a la siguiente escena 
	en este caso, chau saturno hola luna
	*/
	cbnz w11, moon	

	// contador
	mov x13, #0   // Establecemos todos los bits del registro x13 en 0 

	// while(x13 != x12) ...
	// x13 = 0, x12 = 0x700000
	// sumamos de a 1 a x13 jajsjsa, asi qeu tenemos para rato

	delay:
		add x13, x13, #1
		cmp x13, x12
		b.ne delay
	b InfLoop

moon:
	mov x0, x20
	movz w10, 0x29, lsl 16
	movk w10, 0x2936, lsl 00 //color del fondo

	bl fondo_degrade
	bl fondo_estrella

	mov x3, 320
	mov x4, 240
	mov x5, 150
	bl draw_moon

	mov x3, 300
	mov x4, 300
	mov w10, 0xFFFFFF
	bl draw_satelite

	b InfLoop

