.include "help.s"
.equ SCREEN_WIDTH, 		640
.equ SCREEN_HEIGH, 		480	


// ====== FONDO DEGRADE FACHERO =======//

fondo_degrade:
	sub sp, sp, 8
	stur x30, [sp, 0]

	movz w10, 0x0000        // Inicializar el color a negro (0x00000000)
	mov x3, 0		        // Coordenada x donde lo voy a pintar
	mov x4, 0		        // Coordenada y donde lo voy a pintar
	mov x1, 640		        // Ancho
	mov x2, 1		        // Altura
	mov x6, 0x0000	    // Blanco máximo (0xFFFFFFFF)
	udiv x7, x6, x2	        // Incremento por fila (blanco / altura)

rectangulo_negro:
	bl dibujar_rectangulo
	add w10, w10, w7
	add x4, x4, 1        // Incrementa el color para el siguiente degradado
	add x2, x2, 1
	cmp x2, 280
	b.lt rectangulo_negro


	movz w10, 0x0000        // Inicializar el color a negro (0x00000000)
	mov x3, 0		        // Coordenada x donde lo voy a pintar
	mov x4, 280		        // Coordenada y donde lo voy a pintar
	mov x1, 640		        // Ancho
	mov x2, 1		        // Altura
	mov x6, 0x0001	    // Blanco máximo (0xFFFFFFFF)
	udiv x7, x6, x2	        // Incremento por fila (blanco / altura)

rectangulo_azul:
	bl dibujar_rectangulo
	add w10, w10, w7
	add x4, x4, 6        // Incrementa el color para el siguiente degradado
	add x2, x2, 1
	cmp x2, 200
	b.lt rectangulo_azul

ldr x30, [sp, 0]
add sp, sp, 8
ret

// ====== FIN FONDO DEGRADE FACHERO ======


// ====== FONDO DE ESTRELLAS ======
fondo_estrella:
    sub SP,SP,8     //reservamos espacio en la pila
    stur x30,[SP]	// guardamos el valor de x3 en la pila
	sub SP,SP,8
	stur x30,[SP]
	sub SP,SP,8
	stur x1,[SP]
	sub SP,SP,8
	stur x2,[SP]
	sub SP,SP,8
	stur x3,[SP]
	sub SP,SP,8
	stur x4,[SP]
	sub SP,SP,8
	stur w10,[SP]
	sub SP,SP,4
	stur x5,[SP]
	sub SP,SP,8
	stur x11,[SP]
	sub SP,SP,8

    mov w10, 0xFFFFFF // COLOR
//----------------filas_del_principio-------------------------
	mov x3, 600
	mov x5, 0 //reseteo el radio
	mov x4, 8 //reseteo la fila
        mov x11, 75	
        bl fila_circulos

//mismo circulo, diferente radio
    mov w10, 0xFFFF00
	mov x3, 580 // elijo la posicion en el eje x
	mov x5, 0 //reseteo el radio
	mov x4, 45 //reseteo la fila
	mov x11, 58
    bl fila_circulos

    mov w10, 0xFFFFFF
    mov x3, 580 // elijo la posicion en el eje x
	mov x5, 1 //reseteo el radio
	mov x4, 45 //reseteo la fila
	mov x11, 58
        bl fila_circulos
//hasta aca
////------------------filas_del_medio-------------------------//
	
    mov x3, 639
	mov x5, 0 //reseteo el radio
	mov x4, 70 //reseteo la fila
    mov x11, 71	
        bl fila_circulos

// mismo circulo, diferente radio
    mov w10, 0xFFFF00
	mov x3, 600 // elijo la posicion en el eje x
	mov x5, 0 //reseteo el radio
	mov x4, 110 //reseteo la fila
	mov x11, 75
        bl fila_circulos
	mov w10, 0xFFFFFF
    mov x3, 600 // elijo la posicion en el eje x
	mov x5, 1 //reseteo el radio
	mov x4, 110 //reseteo la fila
	mov x11, 75
        bl fila_circulos
// hasta aca
//
	mov x3, 630
	mov x5, 0 //reseteo el radio
	mov x4, 150 //reseteo la fila
    mov x11, 45	
        bl fila_circulos

//mismo circulo, diferente radio
    mov w10, 0xFFFF00
	mov x3, 600 // elijo la posicion en el eje x
	mov x5, 0 //reseteo el radio
	mov x4, 200 //reseteo la fila
	mov x11, 75
        bl fila_circulos

    mov w10, 0xFFFFFF
    mov x3, 600 // elijo la posicion en el eje x
	mov x5, 1 //reseteo el radio
	mov x4, 200 //reseteo la fila
	mov x11, 75
        bl fila_circulos
//hasta aca
//aca
	mov x3, 630
	mov x5, 0 //reseteo el radio
	mov x4, 250 //reseteo la fila
    mov x11, 105	
        bl fila_circulos

//mismo circulo, diferente radio
    mov w10, 0xFFFF00
	mov x3, 580 // elijo la posicion en el eje x
	mov x5, 0 //reseteo el radio
	mov x4, 300 //reseteo la fila
	mov x11, 58
        bl fila_circulos

    mov w10, 0xFFFFFF
    mov x3, 580 // elijo la posicion en el eje x
	mov x5, 1 //reseteo el radio
	mov x4, 300 //reseteo la fila
	mov x11, 58
        bl fila_circulos
//
	mov x3, 640
	mov x5, 0 //reseteo el radio
	mov x4, 360 //reseteo la fila
    mov x11, 80	
        bl fila_circulos

//---------relleno-----------//
	mov x3, 45
	mov x5, 0 //reseteo el radio
	mov x4, 245 //reseteo la fila
    mov x11, 45	
        bl fila_circulos
    mov w10, 0xFFFFFF
    mov x3, 45 // elijo la posicion en el eje x
	mov x5, 1 //reseteo el radio
	mov x4, 245 //reseteo la fila
	mov x11, 45
        bl fila_circulos
	mov x3, 20
	mov x5, 0 //reseteo el radio
	mov x4, 367 //reseteo la fila
    mov x11, 20	
        bl fila_circulos
    mov w10, 0xFFFFFF
    mov x3, 20 // elijo la posicion en el eje x
	mov x5, 1 //reseteo el radio
	mov x4, 367 //reseteo la fila
	mov x11, 20
        bl fila_circulos
//--------------------filas_fianles-----------------------------------//

    mov x3, 639
	mov x5, 0 //reseteo el radio
	mov x4, 450 //reseteo la fila
        mov x11, 71	
        bl fila_circulos

// mismo circulo, diferente radio
    mov w10, 0xFFFF00
	mov x3, 600 // elijo la posicion en el eje x
	mov x5, 0 //reseteo el radio
	mov x4, 400 //reseteo la fila
	mov x11, 75
        bl fila_circulos

    mov w10, 0xFFFFF0
    mov x3, 600 // elijo la posicion en el eje x
	mov x5, 1 //reseteo el radio
	mov x4, 400 //reseteo la fila
	mov x11, 75
        bl fila_circulos
// hasta aca

//---------------------------------------------------//
    ldur x30,[SP]   
    add SP,SP,8
	ldr x1, [sp, 0]
add sp, sp, 8
ldr x2, [sp, 0]
add sp, sp, 8
ldr x5, [sp, 0]
add sp, sp, 8
ldr x3, [sp, 0]
add sp, sp, 8
ldr x4, [sp, 0]
add sp, sp, 8
ldr x11, [sp, 0]
add sp, sp, 8
ldr w10, [sp, 0]
add sp, sp, 4
ret

// ====== FIN FONDO DE ESTRELLAS ======

// ====== FILAS DE CIRCULOS ======
fila_circulos:
    add x6,x3,0
    add x7,x4,0
    add x8,x5,0
    sub SP,SP,8     //reservamos espacio en la pila
    stur x30,[SP]	// guardamos el valor de x3 en la pila

    bl dibujar_circulo
    add x3,x6,0
    add x4,x7,0
    add x5,x8,0
    sub x3, x3, x11    // Decrementa en 100 en lugar de 200
    cbnz x3, fila_circulos // Comprueba si x6 aún es positivo
    //reseteo los flags
    mov x3, 0
    mov x5, 0
    mov x4, 0
    ldur x30,[SP]   
    add SP,SP,8
ret

// ====== FIN FILAS DE CIRCULOS ======

// ====== DIBUJAR SATURNO EPICOS TO CHETAO ======
draw_saturn:
	sub SP,SP,8					//Guardo x30 en SP
	stur x30,[SP]				//""""""""""""""""
	add x11,x3,0				//Guardo x3 en x11
	lsr x6,x5,3					//Guardo en x6 un octavo del radio
	add x7,x4,150				//Guardo en x7 la altura del primer puente de saturno
	movz x10,0x9f,lsl 16		//Agrego el color del anillo
	movk x10,0x9975,lsl 00		//""""""""""""""""""""""""""
	sub SP,SP,8					//Guardo x4 en SP
	stur x4,[SP]				//"""""""""""""""
	sub SP,SP,8					//Guardo x3 en SP
	stur x3,[SP]				//"""""""""""""""
	sub SP,SP,8					//Guardo x5 en SP
	stur x5,[SP]				//"""""""""""""""
	sub SP,SP,8					//Guardo x6 en SP
	stur x6,[SP]				//"""""""""""""""
	add x5,x3,170				//Guardo en x5 la posicion del inicio interno derecho del anillo
	add x3,x5,0					//Guardo en x3 """""""""""""""""""""""""""""""""""""""""""""""""
	movz x6,0x40,lsl 00			//Defino el tamaño de pintar_fila en 64
	bl pintar_fila				//Pinto la fila
	sub x3,x5,340				//Guardo en x5 la posicion del inicio interno izquierdo del anillo
	movz x12,0x10,lsl 00		//Seteo la altura del anillo interno superior del anillo en 32
	movz x13,0x1,lsl 00			//Seteo x13!=0 para que el bridge sea para arriba
	bl bridge					//Hago el anillo superior interno 
	add x5,x5,64				//Guardo en x5 la posicion del inicio externo derecho del anillo
	sub x3,x3,64				//Guardo en x3 la posicion del inicio externo izquierdo del anillo
	bl pintar_fila				//Pinto la fila
	ldur x6,[SP]				//Recupero el valor original de x6
	add SP,SP,8					//Libero memoria del SP
	movz x12,0x30,lsl 00		//Seteo la altura del anillo externo superior del anillo en 96
	bl bridge					//Hago el anillo superior externo
	add x3,x3,1					//Sumo  1 a x3 para hacer bucket dentro del anillo superior
	sub x4,x4,1					//Resto 1 a x4 """"""""""""""""""""""""""""""""""""""""""""
	movz x25,0x1,lsl 00			//Seteo x25 !=0 para usar el bucket modificado
	bl bucket					//Hago bucket en el anillo superior
	add x4,x4,1					//Sumo 1 a x4
	ldur x5,[SP]				//Cargo en x5 su valor inicial
	add SP,SP,8					//"""""""""""""""""""""""""""
	ldur x3,[SP]				//Cargo en x3 su valor inicial
	sub SP,SP,8					//Avanzo el SP a donde esta guardado x5
	movz x10,0xf1,lsl 16		//Seteo el color base del planeta
	movk x10,0x9225,lsl 00		//"""""""""""""""""""""""""""""""
	bl dibujar_circulo			//Dibujo el circulo
	bl bucket					//Hago bucket modificado
	movz x12,0x0,lsl 00			//Seteo x12==0 para que bridge no tenga altura inicial
	bl set_x3_x5				//Seteo x3 y x5 para usar el bridge
	movz x25,0x0,lsl 00			//Seteo x25 en 0 para que bucket sea normal
	movz x13,0x0,lsl 00			//Seteo x13 en 0 para que bridge sea hacia abajo
	movz x10,0xe5,lsl 16		//Pongo el color del primer arco inferior de saturno
	movk x10,0x7300,lsl 00		//""""""""""""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el primer puente inferior
	bl upper_bridge				//Hago el segundo puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xc8,lsl 16		//Pongo el color del segundo arco inferior de saturno
	movk x10,0x4903,lsl 00		//""""""""""""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el tercer puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0x51,lsl 16		//Pongo el color del tercer arco inferior de saturno
    movk x10,0x220c,lsl 00		//""""""""""""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el cuarto puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xc8,lsl 16		//Pongo el color del cuarto arco inferior de saturno
    movk x10,0x4903,lsl 00		//""""""""""""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el quinto puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0x51,lsl 16		//Pongo el color del quinto arco inferior de saturno
	movk x10,0x220c,lsl 00		//""""""""""""""""""""""""""""""""""""""""""""""""""
	sub x7,x7,x6				//Seteo x7 para que el sig puente sea mas arriba
	bl upper_bridge				//Hago el sexto puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xc8,lsl 16		//Pongo el color del sexto arco inferior
	movk x10,0x4903,lsl 00		//""""""""""""""""""""""""""""""""""""""
	sub x7,x7,x6				//Seteo x7 para que el sig. puente sea mas arriba
	bl upper_bridge				//Hago el septimo puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xff,lsl 16		//Pongo el color del septimo arco inferior
	movk x10,0xae0b,lsl 00		//""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el octavo puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xe5,lsl 16 		//Pongo el color del octavo arco inferior
	movk x10,0x7300,lsl 00		//"""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el noveno puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xc8,lsl 16		//Pongo el color del noveno arco inferior
	movk x10,0x4903,lsl 00		//"""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el decimo puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0x51,lsl 16		//Pongo el color del decimo arco inferior
	movk x10,0x220c,lsl 00		//"""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el undecimo puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xc8,lsl 16		//Pongo el color del undecimo arco inferior
	movk x10,0x4903,lsl 00		//"""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el duodecimo puente inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0xe5,lsl 16		//Pongo el color del duodecimo arco inferior
	movk x10,0x7300,lsl 00		//""""""""""""""""""""""""""""""""""""""""""
	bl upper_bridge				//Hago el trigesimo arco inferior
	bl set_and_bucket			//Relleno el arco
	movz x10,0x9f,lsl 16		//Pongo el color del anillo
	movk x10,0x9975,lsl 00		//"""""""""""""""""""""""""
	ldur x5,[SP]				//Pongo x5 en su valor inicial
	add SP,SP,8					//""""""""""""""""""""""""""""
	ldur x3,[SP]				//Pongo x3 en su valor inicial
	add SP,SP,8					//""""""""""""""""""""""""""""
	ldur x4,[SP]				//Pongo x4 en su valor inicial
	add SP,SP,8					//""""""""""""""""""""""""""""
	add x5,x3,170				//Pongo x5 en la posicion del inicio interno derecho del anillo
	sub x3,x3,170				//Pongo x3 en la posicion del inicio interno izquierdo del anillo
	movz x12,0x10,lsl 00		//Pongo la altura del anillo interno inferior en 32
	bl bridge					//Hago el anillo interno inferior
	add x5,x5,64				//Pongo x5 en la posicion del inicio externo derecho del anillo
	sub x3,x3,64				//Pongo x3 en la posicion del inicio externo derecho del anillo
	movz x12,0x30,lsl 00		//Pongo la altura del anillo externo inferior en 96
	bl bridge					//Hago el anillo externo inferior
	add x3,x3,1					//Modifico x3 para hacer el bucket
	movz x25,0x1,lsl 00			//Pongo x25!=0 para hacer el bucket modificado
	bl bucket					//Relleno el anillo inferior
	b end_saturn				//Termina saturno
set_and_bucket:
	sub SP,SP,8					//Guardo x30 en SP
	stur x30,[SP]				//""""""""""""""""
	add x3,x11,0				//Seteo x3 en su valor inicial
	add x4,x7,x6				//Pongo x4 en un valor para rellenar el arco
	add x4,x4,6					//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
	bl bucket					//Relleno el arco inferior.
	ldur x30,[SP]				//Cargo x30
	add SP,SP,8					//"""""""""
	ret
upper_bridge:
	sub SP,SP,8					//Guardo x30 en SP
	stur x30,[SP]				//""""""""""""""""
	sub x7,x7,x6				//Resto a x7 la distancia entre puentes
	add x4,x7,0					//Pongo en x4 el valor de x7
	add x3,x11,0				//Seteo x3 en su valor inicial
	bl set_x3_x5				//Preparo x3 y x5 para usar bridge
	bl bridge					//Hago el puente
	ldur x30,[SP]				//Cargo x30
	add SP,SP,8					//"""""""""
	ret
end_saturn:
	ldur x30,[SP]				//Cargo x30
	add SP,SP,8					//"""""""""
	ret




set_x3_x5:
	sub SP,SP,8					//Guardo registros para no perderlos
	stur x30,[SP]				//""
	sub SP,SP,8					//""
	stur x9,[SP]				//""
	sub SP,SP,8					//""
	stur x8,[SP]				//""
	sub SP,SP,8					//""
	stur x2,[SP]				//""
	sub SP,SP,8					//""
	stur x1,[SP]				//""
	bl dir_pixel				//Guardo en x0 la posicion del pixel (x3,x4)	
	add x5,x3,0					//Pongo en x5 el valor de x3
	add x1,x0,0					//Guardo en x1 lo que habia en x0
	ldur w9,[x0]				//Cargo en w9 el color previo de esta posicion
compare_x3:	
	sub x0,x0,4					//Muevo x0 un pixel a la izq.
	ldur w8,[x0]				//Cargo el color de este pixel en w8
	cmp w8,w9					//Comparo el color de w8 con el de w9
	b.eq decr_x3				//Si son iguales decremento x3
	b.ne compare_x5				//Si no son iguales avanzo a comparar x5
decr_x3:
	sub x3,x3,1					//Resto 1 a x3
	b compare_x3				//Regreso a comparar x3
compare_x5:
	add x1,x1,4					//Muevo x1 un pixel a la izq
	ldur w8,[x1]				//Cargo el color de este pixel en w8
	cmp w8,w9					//Comparo el color de w8 con el de w9
	b.eq acrem_x5				//Si son iguales incremento x5
	b.ne end_aux				//Si no son iguales termino la funcion
acrem_x5:	
	add x5,x5,1					//Incremento x5 en 1
	b compare_x5				//Regreso a comparar x5
end_aux:
	ldur x1,[SP]				//Recupero los valores iniciales
	add SP,SP,8					//""
	ldur x2,[SP]				//""
	add SP,SP,8					//""
	ldur x8,[SP]				//""
	add SP,SP,8					//""
	ldur x9,[SP]				//""
	add SP,SP,8					//""
	ldur x30,[SP]				//""
	add SP,SP,8					//""
	ret

// ====== FIN DEL EPICO DIBUJO DE SATURNO ======

// ====== DIBUJAR """la luna""" (con muchas comillas)======
// Con el n uevo fondo hay circulos que no se pintan bien
// CORREGIR Y HACERLA MAS FACHERA

draw_moon: 
	sub sp, sp, 8
	stur x30, [sp, 0]
	mov x3, 320
	mov x4, 240
	mov x5, 150

	// Circulo gris para hacer como una sombra
	movz w10, 0xBBB3
	movk w10, 0xBB, lsl 16
	bl dibujar_circulo
	bl bucket	

	mov x3, 270
	mov x4, 170
	mov x5, 30
	// circulo chiquito a la izquierda
	movz w10, 0x7272      // Carga los 16 bits menos significativos
	movk w10, 0x72, lsl 16	
	bl dibujar_circulo
	bl bucket

	#69696D
	mov x3, 400
	mov x4, 320
	mov x5, 30
	// circulo chiquito a la izquierda
	movz w10, 0x696D      // Carga los 16 bits menos significativos
	movk w10, 0x69, lsl 16	
	bl dibujar_circulo
	bl bucket

ldr x30, [sp, 0]
add sp, sp, 8
ret

// ====== FIN de la """la luna""" ======

// ====== DIBUJAR SATELITE ======
// Sin paraemtro por ahora, dibujado en el mismo lugar

draw_satelite:
	sub sp, sp, 8
	stur x30, [sp, 0]

	// Circulo para redondear parte izquierda
	movz w10, 0xA39B      
	movk w10, 0x5C, lsl 16
	mov x3, 75
	mov x4, 60 
	mov x5, 10
	bl pintar_circulo	// Ver si lo puedo pintar con el bucket del isma 

	// Circulo para redondear parte derecha
	mov x3, 105
	mov x4, 60 
	mov x5, 10
	bl pintar_circulo	// Ver si lo puedo pintar con el bucket del isma 	

	// Pata de los paneles: 
	movz w10, 0xE1E6      
	movk w10, 0xEA, lsl 16
	// Pata 1: Arriba a la izquierda
	mov x3, 80 		// Coordenada x donde lo voy a pintar
	mov x4,	41		// Coordenada y donde lo voy a pintar
	mov x1, 2
	mov x2, 10
	bl dibujar_rectangulo

	// Pata 2: Arriba a la derecha
	mov x3, 90 		// Coordenada x donde lo voy a pintar
	mov x4,	41		// Coordenada y donde lo voy a pintar
	mov x1, 2
	mov x2, 10
	bl dibujar_rectangulo

	// Pata 3: Abajo a la izquierda
	mov x3, 80 		// Coordenada x donde lo voy a pintar
	mov x4,	71		// Coordenada y donde lo voy a pintar
	mov x1, 2
	mov x2, 10
	bl dibujar_rectangulo

	// Pata 4: Abajo a la derecha
	mov x3, 90 		// Coordenada x donde lo voy a pintar
	mov x4,	71		// Coordenada y donde lo voy a pintar
	mov x1, 2
	mov x2, 10
	bl dibujar_rectangulo

	// Paneles:
	movz w10, 0x97B0    
	movk w10, 0x41, lsl 16
	// Panel de arriba
	mov x3, 75 		// Coordenada x donde lo voy a pintar
	mov x4,	31		// Coordenada y donde lo voy a pintar
	mov x1, 22
	mov x2, 15
	bl dibujar_rectangulo

	// Panel de abajo
	mov x3, 75 		// Coordenada x donde lo voy a pintar
	mov x4,	75		// Coordenada y donde lo voy a pintar
	mov x1, 22
	mov x2, 15
	bl dibujar_rectangulo

	// Circulito de la punta 
	movz w10, 0x3A47    
	movk w10, 0x7D, lsl 16
	mov x3, 115
	mov x4, 60 
	mov x5, 4
	bl pintar_circulo	// Ver si lo puedo pintar con el bucket del isma 	


	// Rectangulos de la cola:

	// Primer recntagulito (el largito)
	movz w10, 0xE1E6      
	movk w10, 0xEA, lsl 16
	mov x3, 63 		// Coordenada x donde lo voy a pintar
	mov x4,	55		// Coordenada y donde lo voy a pintar
	mov x1, 2		// Ancho
	mov x2, 9		// Altura 
	bl dibujar_rectangulo

	// Segundo recntagulito (el cortito)
	movz w10, 0x7C8D      
	movk w10, 0x6A, lsl 16
	mov x3, 61 		// Coordenada x donde lo voy a pintar
	mov x4,	57		// Coordenada y donde lo voy a pintar
	mov x1, 3		// Ancho
	mov x2, 5		// Altura 
	bl dibujar_rectangulo

	// Antena: 

	// Circulo grande general
	movz w10, 0x3A47    
	movk w10, 0x7D, lsl 16
	mov x3, 41
	mov x4, 59 
	mov x5, 20
	bl pintar_circulo	// Ver si lo puedo pintar con el bucket del isma 	

	// Recatngulo para tapar la parte del circulo y que quede un semicirculo
	// Tener en cuenta si se cambia el color del fondo 
	movz w10, 0x0000, lsl 16
	movk w10, 0x00, lsl 00
	mov x3, 17 		// Coordenada x donde lo voy a pintar
	mov x4,	27		// Coordenada y donde lo voy a pintar
	mov x1, 35		// Ancho
	mov x2, 55		// Altura 
	bl dibujar_rectangulo

	// Rectangulo para terminar el semicirculo
	movz w10, 0xE1E6      
	movk w10, 0xEA, lsl 16
	mov x3, 52 		// Coordenada x donde lo voy a pintar
	mov x4,	42		// Coordenada y donde lo voy a pintar
	mov x1, 1		// Ancho
	mov x2, 35		// Altura 
	bl dibujar_rectangulo

	// Rectangulo para finalizar la cola de la antena
	movz w10, 0x6070      
	movk w10, 0x4F, lsl 16
	mov x3, 42 		// Coordenada x donde lo voy a pintar
	mov x4,	58		// Coordenada y donde lo voy a pintar
	mov x1, 10		// Ancho
	mov x2, 3		// Altura 
	bl dibujar_rectangulo

	// Circulito pra terminar la cola
	#DCA051
	movz w10, 0xA051    
	movk w10, 0xDC, lsl 16
	mov x3, 41
	mov x4, 59 
	mov x5, 3
	bl pintar_circulo	// Ver si lo puedo pintar con el bucket del isma 

	// Parametros del rectangulo obase del satelite 
	movz w10, 0xA39B      
	movk w10, 0x5C, lsl 16
	mov x3, 70 		// Coordenada x donde lo voy a pintar
	mov x4,	51		// Coordenada y donde lo voy a pintar
	mov x1, 40		// Ancho
	mov x2, 20		// Altura
	bl dibujar_rectangulo

ldr x30, [sp, 0]
add sp, sp, 8
ret
// ====== FIN SATELITE ======

//============= ASTRONAUTA =================//

dibujar_astronauta:
// cabeza del astronauta
	sub sp, sp, 8
	stur x30, [sp, 0]
	sub sp, sp, 4
	stur w10, [sp, 0]
	sub sp, sp, 8
	stur x5, [sp, 0]
	sub sp, sp, 8
	stur x4, [sp, 0]
	sub sp, sp, 8
	stur x3, [sp, 0]
	sub sp, sp, 8
	stur x2, [sp, 0]
	sub sp, sp, 8
	stur x1, [sp, 0]

	movz w10, 0xFFFF    
	movk w10, 0xFF, lsl 16
	mov x5, 10
	bl pintar_circulo

	movz w10, 0x0000    
	movk w10, 0x00, lsl 16
	mov x5, 6
	bl pintar_circulo

//cuerpo
	movz w10, 0xFFFF      
	movk w10, 0xFF, lsl 16
	sub x3,x3,14
	add x4,x4,15
	mov x1, 30		// Ancho
	mov x2, 3		// Altura
	bl dibujar_rectangulo

	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,14
	add x4,x4,3
	mov x5, 7
	bl pintar_circulo

//piernas
//pierna derecha
	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	sub x3,x3,5
	add x4,x4,10
	mov x5, 3
	bl pintar_circulo

	movz w10, 0x9B9B      
	movk w10, 0x9B, lsl 16
	sub x3,x3,2
	add x4,x4,6
	mov x1, 3		// Ancho
	mov x2, 5		// Altura
	bl dibujar_rectangulo

	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,1
	sub x4,x4,1
	mov x5, 2
	bl pintar_circulo

//pierna izquierda
	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,11
	sub x4,x4,5
	mov x5, 3
	bl pintar_circulo

	movz w10, 0x9B9B      
	movk w10, 0x9B, lsl 16
	sub x3,x3,1
	add x4,x4,6
	mov x1, 3		// Ancho
	mov x2, 5		// Altura
	bl dibujar_rectangulo
	
	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,1
	sub x4,x4,1
	mov x5, 2
	bl pintar_circulo

ldr x1, [sp, 0]
add sp, sp, 8
ldr x2, [sp, 0]
add sp, sp, 8
ldr x3, [sp, 0]
add sp, sp, 8
ldr x4, [sp, 0]
add sp, sp, 8
ldr x5, [sp, 0]
add sp, sp, 8
ldr w10, [sp, 0]
add sp, sp, 4
ldr x30, [sp, 0]
add sp, sp, 8
ret

//===============ASTRONAUTA 2 =================

dibujar_astronauta2:
// cabeza del astronauta
	sub sp, sp, 8
	stur x30, [sp, 0]
	sub sp, sp, 4
	stur w10, [sp, 0]
	sub sp, sp, 8
	stur x5, [sp, 0]
	sub sp, sp, 8
	stur x4, [sp, 0]
	sub sp, sp, 8
	stur x3, [sp, 0]
	sub sp, sp, 8
	stur x2, [sp, 0]
	sub sp, sp, 8
	stur x1, [sp, 0]

	movz w10, 0xFFFF    
	movk w10, 0xFF, lsl 16
	mov x5, 10
	bl pintar_circulo


//cuerpo
	movz w10, 0xFFFF      
	movk w10, 0xFF, lsl 16
	sub x3,x3,14
	add x4,x4,15
	mov x1, 30		// Ancho
	mov x2, 3		// Altura
	bl dibujar_rectangulo

	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,14
	add x4,x4,3
	mov x5, 7
	bl pintar_circulo

//piernas
//pierna derecha
	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	sub x3,x3,5
	add x4,x4,10
	mov x5, 3
	bl pintar_circulo

	movz w10, 0x9B9B      
	movk w10, 0x9B, lsl 16
	sub x3,x3,2
	add x4,x4,6
	mov x1, 3		// Ancho
	mov x2, 5		// Altura
	bl dibujar_rectangulo

	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,1
	sub x4,x4,1
	mov x5, 2
	bl pintar_circulo

//pierna izquierda
	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,11
	sub x4,x4,5
	mov x5, 3
	bl pintar_circulo

	movz w10, 0x9B9B      
	movk w10, 0x9B, lsl 16
	sub x3,x3,1
	add x4,x4,6
	mov x1, 3		// Ancho
	mov x2, 5		// Altura
	bl dibujar_rectangulo
	
	movz w10, 0xFFFF
	movk w10, 0xFF, lsl 16
	add x3,x3,1
	sub x4,x4,1
	mov x5, 2
	bl pintar_circulo

ldr x1, [sp, 0]
add sp, sp, 8
ldr x2, [sp, 0]
add sp, sp, 8
ldr x3, [sp, 0]
add sp, sp, 8
ldr x4, [sp, 0]
add sp, sp, 8
ldr x5, [sp, 0]
add sp, sp, 8
ldr w10, [sp, 0]
add sp, sp, 4
ldr x30, [sp, 0]
add sp, sp, 8
ret
// ====== FIN ASTRONAUTA ======


// ====== METEORITO ======
// Parametros: X3 = x (la posicion x del centro de la cabeza del meteorito del circulo digamos), x4 = y (la posicion y del centro ... )

draw_meteorito:
	sub sp, sp, 8
	stur x30, [sp, 0]

	sub sp, sp, 8
	stur x3, [sp, 0]
	sub sp, sp, 8
	stur x4, [sp, 0]

	// Guardo los valores originales de x3 y x4, para asi poder ir modificando dentro de cada parte del dibujo
	mov x23, x3
	mov x24, x4

// ---- Parte naranja simulando "fuego" del meteorito ----

// __ Patitas las linitas del fuego 

	movz w10, 0x631E, lsl 0   
	movk w10, 0xF0, lsl 16

	// Patita de la izquierda: 
	sub x3, x23, 32
	sub x4, x24, 7
	mov x1, 4
	mov x2, 9
	bl dibujar_rectangulo

	sub x3, x23, 35
	sub x4, x24, 14
	mov x1, 4
	mov x2, 8
	bl dibujar_rectangulo

	// Patita larga = 4 rectangulos 
	sub x3, x23, 25
	sub x4, x24, 25
	mov x1, 5
	mov x2, 15
	bl dibujar_rectangulo

 
	sub x3, x23, 30
	sub x4, x24, 20
	mov x1, 10
	mov x2, 5
	bl dibujar_rectangulo


	sub x3, x23, 35
	sub x4, x24, 30
	mov x1, 10
	mov x2, 10
	bl dibujar_rectangulo


	sub x3, x23, 25
	sub x4, x24, 35
	mov x1, 4
	mov x2, 10
	bl dibujar_rectangulo

	sub x3, x23, 37
	sub x4, x24, 40
	mov x1, 4
	mov x2, 10
	bl dibujar_rectangulo

	sub x3, x23, 40
	sub x4, x24, 50
	mov x1, 4
	mov x2, 12
	bl dibujar_rectangulo

	sub x3, x23, 35
	sub x4, x24, 45
	mov x1, 10
	mov x2, 10
	bl dibujar_rectangulo

	sub x3, x23, 25
	sub x4, x24, 40
	mov x1, 10
	mov x2, 12
	bl dibujar_rectangulo

	sub x3, x23, 20
	sub x4, x24, 35
	mov x1, 10
	mov x2, 12
	bl dibujar_rectangulo

	sub x3, x23, 15
	sub x4, x24, 30
	mov x1, 7
	mov x2, 7
	bl dibujar_rectangulo

	sub x3, x23, 7
	sub x4, x24, 35
	mov x1, 8
	mov x2, 7
	bl dibujar_rectangulo

	sub x3, x23, 2
	sub x4, x24, 30
	mov x1, 8
	mov x2, 7
	bl dibujar_rectangulo

// ---- Fin de parte naranja simulando "fuego" del meteorito ----


// ---- Parte amarilla alrededor de la cabeza ----

	// Circulo general que rodea a la cabeza
	mov x3, x23
	mov x4, x24
	mov x5, 24
	movz w10, 0xF642, lsl 0   
	movk w10, 0xF6, lsl 16
	bl dibujar_circulo
	mov x25, 1	
	bl bucket
	//bl pintar_circulo

	// __ Patitas las linitas del fuego 

	// Patita de la izquierda: 
	sub x3, x23, 27
	sub x4, x24, 5
	mov x1, 4
	mov x2, 9
	bl dibujar_rectangulo

	sub x3, x23, 30
	sub x4, x24, 10
	mov x1, 4
	mov x2, 8
	bl dibujar_rectangulo

	// Patita larga = 4 rectangulos 
	sub x3, x23, 20
	sub x4, x24, 30
	mov x1, 5
	mov x2, 15
	bl dibujar_rectangulo

	sub x3, x23, 25
	sub x4, x24, 25
	mov x1, 15
	mov x2, 5
	bl dibujar_rectangulo

	sub x3, x23, 30
	sub x4, x24, 35
	mov x1, 10
	mov x2, 10
	bl dibujar_rectangulo

	sub x3, x23, 33
	sub x4, x24, 41
	mov x1, 4
	mov x2, 10
	bl dibujar_rectangulo

	// Patita mediana paralela 
	sub x3, x23, 3
	sub x4, x24, 30
	mov x1, 4
	mov x2, 12
	bl dibujar_rectangulo

	sub x3, x23, 7
	sub x4, x24, 29
	mov x1, 10
	mov x2, 3
	bl dibujar_rectangulo

	sub x3, x23, 7
	sub x4, x24, 36
	mov x1, 3
	mov x2, 8
	bl dibujar_rectangulo

	// Patita chiquita a la derecha 
	add x3, x23, 14
	sub x4, x24, 27
	mov x1, 4
	mov x2, 9
	bl dibujar_rectangulo

	add x3, x23, 10
	sub x4, x24, 33
	mov x1, 4
	mov x2, 9
	bl dibujar_rectangulo

// ---- Fin de parte amarilla alrededor de la cabeza ----

// ---- Cabeza del meteorito (seguro tiene un nombre mas tecnico) ------
// Ver si se puede mejorar
	

	// Circulo general
	mov x3, x23
	mov x4, x24
	mov x5, 20	
	movz w10, 0x7F79    
	movk w10, 0x79, lsl 16
	bl dibujar_circulo	
	movz x25,0x1,lsl 00
	bl bucket
	//bl pintar_circulo

	// Circulo para sombrar los circulos chiquitos 
	mov x5, 17	
	movz w10, 0x7F79    
	movk w10, 0x75, lsl 16
	bl dibujar_circulo	
	movz x25,0x1,lsl 00
	bl bucket
	//bl pintar_circulo

	// Circulo chiquito arriba a la izquierda
	sub x3, x23, 10
	sub x4, x24, 10
	mov x5, 5	
	movz w10, 0x1614    
	movk w10, 0x15, lsl 16
	bl dibujar_circulo	
	movz x25,0x1,lsl 00
	bl bucket
	//bl pintar_circulo

	// Circulo chiquito abajo a la izquierda
	sub x3, x23, 1
	add x4, x24, 20
	mov x5, 5	
	movz w10, 0x1614    
	movk w10, 0x15, lsl 16
	bl dibujar_circulo	
	movz x25,0x1,lsl 00
	bl bucket
	//bl pintar_circulo

	// Rectangulo de la derecha
	add x3, x23, 20
	sub x4, x24, 10
	mov x1, 5
	mov x2, 10
	movz w10, 0x1715   
	movk w10, 0x16, lsl 16
	bl dibujar_rectangulo

	// Sombra del rectangulo de abajo a la derecha
	add x3, x23, 18
	sub x4, x24, 8
	mov x1, 3
	mov x2, 6
	movz w10, 0x3232   
	movk w10, 0x32, lsl 16
	bl dibujar_rectangulo

	// Cuadradito arriba a la izquiera 
	add x3, x23, 16
	sub x4, x24, 18
	mov x1, 5
	mov x2, 5
	movz w10, 0x3131  
	movk w10, 0x31, lsl 16
	bl dibujar_rectangulo

	add x3, x23, 18
	sub x4, x24, 20
	mov x1, 4
	mov x2, 4
	movz w10, 0x3131  
	movk w10, 0x32, lsl 16
	bl dibujar_rectangulo


// ---- Fin cabeza del meteorito ------

// ---- Parte rojo fuerte al final ----
	movz w10, 0x3E3C 
	movk w10, 0xE1, lsl 16

	sub x3, x23, 40
	sub x4, x24, 60
	mov x1, 5
	mov x2, 5
	bl dibujar_rectangulo

// ---- Fin parte rojo fuerte al final ----


ldr x4, [sp, 0]
add sp, sp, 8
ldr x3, [sp, 0]
add sp, sp, 8

ldr x30, [sp, 0]
add sp, sp, 8
ret
// ====== FIN METEORITO ======


// ====== MARGEN DEL FONDO =======//
margen_pantalla:
    sub sp, sp, 8
    stur x30, [sp, 0]

    mov x1, 640     //ancho
    mov x2, 1       //altura
    mov x3, 0       //coordenada x donde lo voy a pintar
    mov x4, 0       //coordenada y donde lo voy a pintar
    mov w10, 0x00FF00   //color verde
    bl dibujar_rectangulo

    mov x1, 640     //ancho
    mov x2, 1       //altura
    mov x3, 0       //coordenada x donde lo voy a pintar
    mov x4, 479         //coordenada y donde lo voy a pintar
    mov w10, 0x00FF00   //color verde
    bl dibujar_rectangulo

    mov x1, 1   //ancho
    mov x2, 479         //altura
    mov x3, 0       //coordenada x donde lo voy a pintar
    mov x4, 0       //coordenada y donde lo voy a pintar
    mov w10, 0x00FF00   //color verde
    bl dibujar_rectangulo

    mov x1, 1   //ancho
    mov x2, 479         //altura
    mov x3, 639         //coordenada x donde lo voy a pintar
    mov x4, 0       //coordenada y donde lo voy a pintar
    mov w10, 0x00FF00   //color verde
    bl dibujar_rectangulo

ldr x30, [sp, 0]
add sp, sp, 8
ret

margen_pantalla2:
    sub sp, sp, 8
    stur x30, [sp, 0]

    mov x1, 640     //ancho
    mov x2, 8       //altura
    mov x3, 0       //coordenada x donde lo voy a pintar
    mov x4, 0       //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 640     //ancho
    mov x2, 8       //altura
    mov x3, 0       //coordenada x donde lo voy a pintar
    mov x4, 471         //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

ldr x30, [sp, 0]
add sp, sp, 8
ret

laberinto:

    sub sp, sp, 8
    stur x30, [sp, 0]

    mov x1, 75  //ancho
    mov x2, 4       //altura
    mov x3, 55      //coordenada x donde lo voy a pintar
    mov x4, 410     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 100 //ancho
    mov x2, 4       //altura
    mov x3, 200         //coordenada x donde lo voy a pintar
    mov x4, 410     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 170 //ancho
    mov x2, 4       //altura
    mov x3, 400         //coordenada x donde lo voy a pintar
    mov x4, 410     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 229         //altura
    mov x3, 570         //coordenada x donde lo voy a pintar
    mov x4, 185     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 200 //ancho
    mov x2, 4       //altura
    mov x3, 570         //coordenada x donde lo voy a pintar
    mov x4, 181     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 160         //altura
    mov x3, 55      //coordenada x donde lo voy a pintar
    mov x4, 250     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 150         //altura
    mov x3, 126         //coordenada x donde lo voy a pintar
    mov x4, 185     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 280         //altura
    mov x3, 200         //coordenada x donde lo voy a pintar
    mov x4, 130     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 129 //ancho
    mov x2, 4       //altura
    mov x3, 75      //coordenada x donde lo voy a pintar
    mov x4, 126     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 70      //altura
    mov x3, 71      //coordenada x donde lo voy a pintar
    mov x4, 60      //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 180 //ancho
    mov x2, 4   //altura
    mov x3, 75      //coordenada x donde lo voy a pintar
    mov x4, 60      //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 270     //altura
    mov x3, 255     //coordenada x donde lo voy a pintar
    mov x4, 60      //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 180 //ancho
    mov x2, 4   //altura
    mov x3, 255     //coordenada x donde lo voy a pintar
    mov x4, 330     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 100     //altura
    mov x3, 330     //coordenada x donde lo voy a pintar
    mov x4, 1       //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 100     //altura
    mov x3, 330     //coordenada x donde lo voy a pintar
    mov x4, 170     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 100 //ancho
    mov x2, 4   //altura
    mov x3, 334     //coordenada x donde lo voy a pintar
    mov x4, 170     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 100 //ancho
    mov x2, 4   //altura
    mov x3, 330     //coordenada x donde lo voy a pintar
    mov x4, 101     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 100 //ancho
    mov x2, 4   //altura
    mov x3, 330     //coordenada x donde lo voy a pintar
    mov x4, 270     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 4   //ancho
    mov x2, 270     //altura
    mov x3, 500     //coordenada x donde lo voy a pintar
    mov x4, 80      //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
    bl dibujar_rectangulo

    mov x1, 166 //ancho
    mov x2, 4   //altura
    mov x3, 334     //coordenada x donde lo voy a pintar
    mov x4, 220     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
    bl dibujar_rectangulo

    mov x1, 70  //ancho
    mov x2, 4   //altura
    mov x3, 1       //coordenada x donde lo voy a pintar
    mov x4, 100     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
	bl dibujar_rectangulo

    mov x1, 135 //ancho
    mov x2, 4   //altura
    mov x3, 504     //coordenada x donde lo voy a pintar
    mov x4, 100     //coordenada y donde lo voy a pintar
    movz w10, 0x9B9B, lsl 00  //color gris
	movk w10, 0x9B, lsl 16
    bl dibujar_rectangulo

ldr x30, [sp, 0]
add sp, sp, 8
ret

ventana:
    sub sp, sp, 8
    stur x30, [sp, 0]

    mov x1, 305 //ancho
    mov x2, 25   //altura
    mov x3, 334		//coordenada x donde lo voy a pintar
    mov x4, 1     //coordenada y donde lo voy a pintar
    mov w10, 0xFFFFFF   //color verde
    bl dibujar_rectangulo

    mov x1, 79 //ancho
    mov x2, 20   //altura
    mov x3, 550		//coordenada x donde lo voy a pintar
    mov x4, 3     //coordenada y donde lo voy a pintar
    mov w10, 0x000020   //color verde
    bl dibujar_rectangulo

    mov x1, 50 //ancho
    mov x2, 20   //altura
    mov x3, 350		//coordenada x donde lo voy a pintar
    mov x4, 3     //coordenada y donde lo voy a pintar
    mov w10, 0x000020   //color verde
    bl dibujar_rectangulo

	mov x3, 370
	mov x4, 15
	bl dibujar_astronauta2

ldr x30, [sp, 0]
add sp, sp, 8
ret
// ====== FIN MARGEN DEL FONDO =======//

// ====== DIBUJAR UNA ESTRELLA ======
draw_star: 
	sub SP,SP,8
	stur x30,[SP]

	movz x10, 0x00, lsl 16
	movk x10, 0x0000, lsl 00
	// Posiciones iniciales de x3 y x4 
	mov x3, x23
	mov x4, x24 
	mov x1, 7 //ancho 
	mov x2, 3 // altuta
	bl dibujar_rectangulo

	mov x1, 3 //ancho 
	mov x2, 7 // altuta
	add x3, x23, 2
	sub x4, x24, 2
	bl dibujar_rectangulo

ldr x30, [sp, 0]
add sp, sp, 8

ret
// ====== FIN DIBUJAR UNA ESTRELLA ======
