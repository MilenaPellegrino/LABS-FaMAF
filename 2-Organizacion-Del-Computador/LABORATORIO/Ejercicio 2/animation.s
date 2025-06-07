//.include "help.s"
.include "movimiento_astronauta.s"

.equ SCREEN_WIDTH, 	    640
.equ SCREEN_HEIGH, 		480	

// ====== FONDO DE ANIMACION =======//
fondo_animacion:
	sub SP,SP,8
	stur x30,[SP]

    // Color del fondo
	movz x10, 0x09, lsl 16
	movk x10, 0x0926, lsl 00

	mov x22, SCREEN_HEIGH         // Y Size
loop1:
	mov x27, SCREEN_WIDTH         // X Size
loop0:
	stur w10,[x0]  // Colorear el pixel N
	add x0,x0,4    // Siguiente pixel
	sub x27,x27,1    // Decrementar contador X
	cbnz x27,loop0  // Si no terminó la fila, salto
	sub x22,x22,1    // Decrementar contador Y
	cbnz x22,loop1  // Si no es la última fila, salto

ldr x30, [sp, 0]
add sp, sp, 8
ret
// ====== FIN DEL FONDO DE ANIMACION =======//
