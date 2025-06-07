.include "drawings.s"

.equ GPIO_BASE,    0x3f200000
.equ GPIO_GPFSEL0, 0x00
.equ GPIO_GPLEV0,  0x34

move_astronaut:
	sub SP,SP,8
	stur x30,[SP]
	mov x19,0
mover_astronauta:
	bl step_in_time
	mov x9,GPIO_BASE
	bl check_final
	ldr w14, [x9, GPIO_GPLEV0]	
	and w11, w14, 0b00000010// Usamos la mascara binaria en este caso es para w 
	cbnz w11,mover_arriba
	and w11, w14, 0b00000100// Usamos la mascara binaria en este caso es para a 
	cbnz w11, mover_izquierda
	and w11, w14, 0b00001000// Usamos la mascara binaria en este caso es para s 
	cbnz w11, mover_abajo
	and w11, w14, 0b00010000// Usamos la mascara binaria en este caso es para d 
	cbnz w11, mover_derecha
	b mover_astronauta

ast_dir_to_square_dir:
	sub SP,SP,8
	stur x30,[SP]
	sub x4,x4,10
	sub x3,x3,14
	bl dir_pixel
	ldur x30,[SP]
	add SP,SP,8
	ret

square_dir_to_ast_dir:
	add x4,x4,10
	add x3,x3,14
	ret

tapar_ast:
	sub SP,SP,8
	stur x30,[SP]
	mov x1,30
	mov x2,49
	movz x10,0x00,lsl 16
	movk x10,0x0000,lsl 00
	bl dibujar_rectangulo
	ldur x30,[SP]
	add SP,SP,8
	ret

set_coord:
	bl square_dir_to_ast_dir
	b mover_astronauta

mover_arriba:
	mov x6,29
	bl ast_dir_to_square_dir
	sub x1,x0,2560
	ldur w2,[x1]
loop_arriba:
	add x1,x1,4
	ldur w5,[x1]
	add w2,w2,w5
	cbnz w2,set_coord
	sub x6,x6,1
	cbnz x6,loop_arriba
	bl tapar_ast
	bl square_dir_to_ast_dir
	sub x4,x4,1
	bl dibujar_astronauta2
	mov x19,1
	b mover_astronauta

mover_abajo:
	mov x6,29
	bl ast_dir_to_square_dir
	movz x2,0x1,lsl 16
	movk x2,0xea00,lsl 00
	add x1,x0,x2
	ldur w2,[x1]
loop_abajo:
	add x1,x1,4
	ldur w5,[x1]
	add w2,w2,w5
	cbnz w2,set_coord
	sub x6,x6,1
	cbnz x6,loop_abajo
	bl tapar_ast
	bl square_dir_to_ast_dir
	add x4,x4,1
	bl dibujar_astronauta
	mov x19,0
	b mover_astronauta

mover_izquierda:
	mov x6,48
	bl ast_dir_to_square_dir
	sub x1,x0,4
	ldur w2,[x1]
loop_izquierda:
	add x1,x1,2560
	ldur w5,[x1]
	add w2,w2,w5
	cbnz w2,set_coord
	sub x6,x6,1
	cbnz x6,loop_izquierda
	bl tapar_ast
	bl square_dir_to_ast_dir
	sub x3,x3,1
	cbnz x19,8
	bl dibujar_astronauta
	cbz x19,8
	bl dibujar_astronauta2
	b mover_astronauta

mover_derecha:
	mov x6,48
	bl ast_dir_to_square_dir
	add x1,x0,120
	ldur w2,[x1]
loop_derecha:
	add x1,x1,2560
	ldur w5,[x1]
	add w2,w2,w5
	cbnz w2,set_coord
	sub x6,x6,1
	cbnz x6,loop_derecha
	bl tapar_ast
	bl square_dir_to_ast_dir
	add x3,x3,1
	cbnz x19,8
	bl dibujar_astronauta
	cbz x19,8
	bl dibujar_astronauta2
	b mover_astronauta
check_final:
	mov x7,40
	cmp x4,x7
	b.lt 8
	ret
	mov x7,560
	cmp x3,x7
	b.ge 8
	ret
	ldur x30,[SP]
	ret


