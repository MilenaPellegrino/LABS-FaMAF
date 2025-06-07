
.equ SCREEN_WIDTH, 		640
.equ SCREEN_HEIGH, 		480	

// CONVENCIONES DE USO DE VARIABLES: 
///////		x = x3, y = x4
///////		dato del color = w10 
/////// 	anchos = x1, alturas = x2 

// ========   CALCULAR LA DIRECCION DE UN PIXEL   ======== 
// Parametros: x3 = x, x4 = y. Representan las coordenadas dle pixel que queremos calcular

dir_pixel: 
    mov x0, SCREEN_WIDTH    // Guardamos en x0 el ancho de la pantalla
    mul x0, x0, x4      // Multiplicamos x0 = 640 * x4 = y para obtener la posicion vertical del pixel (en terminos de las filas)
    add x0, x3, x0      // A lo anterior le sumamos x3 = x para obtener la posicion horizonal en termino de las columnas 
    lsl x0, x0, 2       // MUltiplicamos lo que nos dio por 4, ya que en el framebuffer cada pixel ocupa 4bytes (32bits)
    add x0, x0, x20     // Le sumamos la direccion base del framebuffer para obtener la direccion completa del pixel en memoria 
ret

// ========   FIN CALCULAR DIRECCION DE UN PIXEL  ======== 

// ========   PINTAR UN PIXEL EN LA PANTALLA  ======== 
// Prametros x3 = x, x4 = y, w10 = color del pixel que vayamos a pintar 
pintar_pixel: 

    // Primero verifiquemos que las coordenadas esten dentro de la pantalla: 
    cmp x3, #640    // Si me pase por derecha en x 
    b.ge invalid_coordinates
    cmp x3, #0      // Si me fui de rango por izquierda en x 
    b.lt invalid_coordinates
    cmp x4, #480    // Si me fui de rango por arriba en y 
    b.ge invalid_coordinates
    cmp x4, #0      // Si me fui de rango por abajo en y
    b.lt invalid_coordinates

    // Si las direcciones pasadas como parametro son validas: 
    // Calculo la direccion del pixel: 
    sub sp, sp, #16     // Reservamos 16bytes en el stack pointer (en la pila) para guardar los dos registros. Hacemos la resta ya que en esta arquitectura la pila crece hacia abajo 
    stp x29, x30, [sp, #0]  // Guardamos los registros x29 y x30 en la pila
    bl dir_pixel    // Llamamos a la funcion para obtener la direccion en memoria del pixel 
    
    ldp x29, x30, [sp, #0]  // Restauramos los registros dx29 y x30
    add sp, sp, #16     // LIberamos espacio en la pila 

    // Pintamos ell pixel:
    str w10, [x0]   	// Almacena el color en la dirección calculada por dir_pixel 
ret 

invalid_coordinates:
ret   // Ver si hacer otra cosa al pasar una coordenada fuera de rango

// ========   FIN DE PINTAR UN PIXEL EN LA PANTALLA  ======== 

// ========   DIBUJAR RECTANGULO EN LA PANTALLA  ======== 
// Parametros: x3 = x, x4 = y, ancho del rectangulo = x1, altura del rectangulo = x2, color = w10

dibujar_rectangulo: 
	sub SP, SP, 8   // Reservamos espacio en la pila 						
	stur X30, [SP, 0]   // Guardamos el valor de x30 en la pila
	bl dir_pixel    // Calcula la direccion de memoria del primer pixel del rectangulo    			
	ldr X30, [SP, 0]					 			
	add SP, SP, 8   // Liberamos el espacio de la pila utilizado 						
	mov x9, x2		// x9 contiene la altura del rectangulo		
	mov x13, x0	    // EN x13 guardamos la direccion de memoria dle primer pixel del rectangulo						
	rectLoop:
		mov x11, x1     // Guardamos en x11 el ancho del rectangulo
		mov x12, x13	//x12 guarda la direccion de memoria del primer pixel de la fila actual 			
		pintarFila:
			stur w10, [x13]     // Guardamos el color del pixel				
			add x13, x13, 4	    // Avanzamos al siguiente pixel (4bytes, ya que cada pixel ocupa 32bits)	
			sub x11, x11, 1		// Restamos uno al contador de ancho para pintar el resto    	
			cbnz x11, pintarFila    // Si no estoy en el final de la fila, vuelvo a pintar el otro pixel
			mov x13, x12				//si llegue al final de la fila, restauramos la dirección de memoria del primer píxel de la fila actual, o sea me paro en el primer pixel
            
            // Longitud de una fila= Num de pıxeles por fila × Tamano de cada pıxel en bytes = 640×4 = 2560 bytes
			add x13, x13, 2560			// sumo 2560, lo que nos salta a la fila de abajo
			sub x9, x9, 1				// como salte a la fila de abajo, resto uno a la altura
			cbnz x9, rectLoop	    // si no termine de pintar la ultima fila, vuelvo a pintar una fila
ret

// ========   FIN DE DIBUJAR RECTANGULO EN LA PANTALLA  ======== 
// Parametros: x3 = x, x4 = y, ancho del rectangulo = x1, altura del rectangulo = x2, color = w10 (color de fondo)

// ========   PINTAR UNA FILA EN LA PANTALLA  ======== 
// VER PORQUE NO LO PINTA BIEN (no funciona el color)
// PARAMETROS: x3 = x, x4 = y, X6 = tamano, w10 = color
pintar_fila:
    sub SP, SP, 8
    stur X30, [SP, 0]
    sub SP, SP, 8
    stur X6, [SP, 0]
    sub SP, SP, 8
    stur X3, [SP, 0]
loop_fila:
    bl pintar_pixel    // Pintamos el pixel
    add x3, x3, 1     // Avanzamos al siguiente
    sub x6, x6, 1   // Restamos al contador
    cbnz x6, loop_fila // mientras el contador no sea 0 loopeamos

ldr X3, [SP, 0]
add SP, SP, 8
ldr X6, [SP, 0]
add SP, SP, 8
ldr X30, [SP, 0]
add SP, SP, 8
ret


// ========   FIN DE PINTAR UNA FILA EN LA PANTALLA  ======== 

// ========   DIBUJAR CIRCULO POR LA PANTALLA  ======== 
// Parametros: x3 = coordenada x del centro, x4 = coordenada y del centro, x5 = radio,  w10 = color
// Aclaracion: Codigo ideado a traves de la idea del algoritmo de Bresenham
dibujar_circulo:
    sub sp, sp, 8
    stur x30, [sp, 0]
	sub SP,SP,8
	stur x4,[SP]
	sub SP,SP,8
	stur x3,[SP]

    mov x23, x3     // En x23 guardo la coordenada x 
    mov x24, x4     // En x24 guardo la coordenada y

    mov x13, xzr            // x13 representa el desplazamiento en el eje x, lo inicializo en 0
    mov x14, x5             // x14 guarda el desplazamiento en el eje y, lo inicializo con el valor del radio
    mov x15, 1              // x15 va a representar el error para trazar correctamente el circulo (algoritmo de Bresenham) 
    sub x15, x15, x5        // Error inicial restando el radio del circulo

loop_circulo: 
    // 8 combinaciones para pintar el círculo
    mov x3, x23
    add x3, x3, x13
    mov x4, x24
    add x4, x4, x14
    bl pintar_pixel

    mov x3, x23
    add x3, x3, x14
    mov x4, x24
    add x4, x4, x13
    bl pintar_pixel

    mov x3, x23
    sub x3, x3, x14
    mov x4, x24
    add x4, x4, x13
    bl pintar_pixel

    mov x3, x23
    sub x3, x3, x13
    mov x4, x24
    add x4, x4, x14
    bl pintar_pixel

    mov x3, x23
    sub x3, x3, x13
    mov x4, x24
    sub x4, x4, x14
    bl pintar_pixel

    mov x3, x23
    sub x3, x3, x14
    mov x4, x24
    sub x4, x4, x13
    bl pintar_pixel

    mov x3, x23
    add x3, x3, x14
    mov x4, x24
    sub x4, x4, x13
    bl pintar_pixel

    mov x3, x23
    add x3, x3, x13
    mov x4, x24
    sub x4, x4, x14
    bl pintar_pixel

    // Actualizamos el error y los desplazamientos
    cmp x15, xzr
    b.lt actualizar_error_menor

    sub x14, x14, 1          // y = y - 1
    add x16, x13, x13        // x16 = 2 * x
    add x17, x14, x14        // x17 = 2 * y
    add x15, x15, x16        // error += 2 * x
    sub x15, x15, x17        // error -= 2 * y
    add x15, x15, 1          // error += 1
    b fin_actualizacion

actualizar_error_menor:
    add x16, x13, x13        // x16 = 2 * x
    add x15, x15, x16        // error += 2 * x
    add x15, x15, 1          // error += 1

fin_actualizacion:
    add x13, x13, 1          // x = x + 1
    subs x9, x13, x14
    b.lt loop_circulo

// Liberamos los recursos utilizados 
ldur x3,[SP]
add SP,SP,8
ldur x4,[SP]
add SP,SP,8
ldr x30, [sp, 0]
add sp, sp, 8
ret  

// ========   FIN DE DIBUJAR CIRCULO POR LA PANTALLA  ======== 


// ========   PINTAR CIRCULO POR LA PANTALLA  ======== 
// parametros x3= coordenada x del centro, x4 = coordenada y del centro,  x5 = radio, w10 = color

pintar_circulo:

	sub sp, sp, 8
	stur x30, [sp, 0]
		
	mov x7, x3  // Guardar coordenada x del centro
	mov x8, x4  // Guardar coordenada y del centro

	// La idea es ir pintando circulos con radios mas chicos hasta llegar al del radio 0.

	loop_pintar:
		bl dibujar_circulo  // Llama a la función para dibujar el círculo
		mov x3, x7         // Restaurar coordenada x del centro
		mov x4, x8         // Restaurar coordenada y del centro
		sub x5, x5, 1       // Decrementar radio
		cbnz x5, loop_pintar // Si el radio no es cero, repetir el bucle
	ldr x30, [sp, 0]
	add sp, sp, 8
	ret    
// ========   FIN DE PINTAR CIRCULO POR LA PANTALLA  ======== 


// ========   BUCKET PINTAR UN AREA DETERMINADA  ======== 
//x3=coordenada x, x4=coordenada y x10=color a pintar
//x25==0 bucket normal x25!=0 bucket hasta color!
bucket: 
	sub SP,SP,8  		  		//Reservamos espacio en la pila
	stur x30,[SP,0]       		//Guardamos el valor de x30 en la pila	
	sub SP,SP,8  		  		//Reservamos espacio en la pila
	stur x7,[SP,0]       		//Guardamos el valor de x7 en la pila
	sub SP,SP,8  		  		//Reservamos espacio en la pila
	stur x8,[SP,0]       		//Guardamos el valor de x8 en la pila
	sub SP,SP,8  		  		//Reservamos espacio en la pila
	stur x9,[SP,0]       		//Guardamos el valor de x9 en la pila
	movz x9,0x0,lsl 00			//Usamos x9 para llevar registro de cuanta SP es usada, lo inicializo en 0
	bl dir_pixel				//Guarda en x0 la dir del pixel a pintar
	bl normal_or_modified_color	//Guarda en w7 el color a comparar
	stur w10,[x0]				//Pinto el primer pixel
	b pixel_painter
normal_or_modified_color:
	cbz x25,normal_bucket		//Si x25 es 0 guarda en x7 el color previo del primer pixel
	cbnz x25,modified_bucket	//Si x25 es !=0 guarda en x7 el color a pintar
normal_bucket:
	ldur w7,[x0]   				//en x7 guarda el color del pixel
	ret
modified_bucket:
	add w7,w10,0				//en x7 guarda el color a pintar
	ret
pixel_painter:
	sub x0,x0,2560				//ponemos en x0 la dir del pixel superior
	bl normal_or_modified_compare
	add x0,x0,2556				//ponemos en x0 la dir del pixel anterior
	bl normal_or_modified_compare
	add x0,x0,8					//ponemos en x0 la dir del pixel posterior
	bl normal_or_modified_compare
	add x0,x0,2556				//ponemos en x0 la dir del pixel inferior
	bl normal_or_modified_compare
	cbz x9,end_bucket			//Si ya se libero la SP, termino el programa
	cbnz x9,next_dir			//Si no esta liberada la SP,busco el sig pixel almacenado en SP
normal_or_modified_compare:		//Si corresponde, compare pintara el pixel y guardara su direccion en SP
	cbz x25,compare				
	cbnz x25,modified_compare	
compare:
	ldur w8,[x0]	 			//cargamos el color del pixel a comparar en w8
	cmp w8,w7					//compara el color de w8 con el color que desea ser reemplazado
	b.eq dir_to_SP				//Si estos colores son iguales lo pinta y almacena su direccion en SP
	ret
modified_compare:
	ldur w8,[x0]				//cargamos el color del pixel a comparar en w8
	cmp w8,w7					//compara el color de w8 con el del color a pintar
	b.ne dir_to_SP				//Si estos colores son distintos lo pinta y almacena su direccion en SP
	ret
dir_to_SP:
	stur w10,[x0]				//Pinta el pixel
	sub SP,SP,4					//Hace espacio en SP para la dir del pixel
	stur w0,[SP,0]				//Almacena la direccion del pixel en SP
	add x9,x9,1					//Suma 1 al contador de uso de SP
	ret
next_dir:
	ldur w0,[SP,0]				//Guarda en x0 el pixel almacenado en SP
	add SP,SP,4					//Libera espacio del SP
	sub x9,x9,1					//Decrementa el contador de uso de SP
	b pixel_painter				//Va a pintar el pixel
end_bucket:
	ldur x9,[SP,0]				//Devuelve el valor original de x9
	add SP,SP,8					//Libera espacio del SP
	ldur x8,[SP,0]				//Devuelve el valor original de x8
	add SP,SP,8					//Libera espacio del SP
	ldur x7,[SP,0]				//Devuelve el valor original de x7
	add SP,SP,8					//Libera espacio del SP
	ldur x30,[SP,0]				//Devuelve el valor original de x30
	add SP,SP,8					//Libera espacio del SP
	ret							//Termina la funcion
//
// ========   FIN DEL BUCKET PINTAR UN AREA DETERMINADA  ======== 

// ========   PINTAR PUENTECITOS  ======== 
// Parametros: x3=xa, x4=y, x5=xb, x12=para darle altura(parametro poco preciso),x13=sentido, w10=color a pintar
// Aclaraciones: xb debe ser mayor a xa (xb>xa) y la distancia entre el xa y xb debe ser mayor a 2
// x13==0 puente hacia abajo x13!=0 puente hacia arriba.
bridge:
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x30
	stur x30,[SP] 			//|Almaceno x30
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x12
	stur x12,[SP] 			//|Almaceno x12
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x11
	stur x11,[SP] 			//|Almaceno x11
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x9
	stur x9,[SP] 			//|Almaceno x9
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x8
	stur x8,[SP] 			//|Almaceno x8
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x7
	stur x7,[SP] 			//|Almaceno x7
	sub SP,SP,8				//|Reservo espacio en SP para almacenar x4
	stur x4,[SP]  			//|Almaceno x4
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x3
	stur x3,[SP]  			//|Almaceno x3
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x2
	stur x2,[SP] 			//|Almaceno x2
	sub SP,SP,8    			//|Reservo espacio en SP para almacenar x30
	stur x1,[SP] 			//|Almaceno x1
	sub x7,x5,x3    		//Almaceno la distancia entre xa y xb
	add x7,x7,2				//Le sumo a la distancia 2 para contar los pixeles de los extremos
	bl dir_pixel  		  	//Almaceno la direccion del primer pixel (Inicio del puente) en x0
	add x1,x0,0				//Guardo la direccion del primer pixel en x1
	add x3,x5,0     		//Copio xb en x3 para poder usar la siguiente func
	bl dir_pixel	    	//Almaceno la direccion del segundo pixel (Fin del puente) en x0
	movz x8,0x2,lsl 00	 	//En x8 almaceno la cantidad de pixeles que quiero sean pintados de cada lado en cada altura
	add x9,x8,0				//Copio x9 en x8
	lsr x2,x12,2			//Le doy un valor a x2 para modificar initial_high
	lsr x4,x2,1  			//X4 sera mi parametro modificador de altura, le pongo la mitad de x2
	movz x11,0x2,lsl 00		//Inicializo x11 en 2
	cbz x12, bridge_painter	//Si la altura es 0 no hago la altura inicial
initial_high:
	bl paint_both			//Pinto ambos extremos del puente
	bl up_or_down			//Sube o baja los pixeles
	sub x12,x12,1			//Resto la altura total
	sub x4,x4,1				//Le resta 1 al parametro modificador de altura
	sub x2,x2,1				//Le resto 1 al total de la altura inicial
	cbnz x4,initial_high    //Si el parametro para modificar altura no es 0 repito el proceso
	bl move_center			//Muevo ambos pixeles un paso hacia el centro
	lsr x4,x2,1				//Guardo en x4 la mitad de x2
	cbnz x4,initial_high	//Si x2 es 1, voy a bridge_loop
	lsr x2,x12,2			//Guardo en x2 un cuarto de la altura total
intermediate_loop:
	bl paint_both			//Pinto ambos extremos del puente
	bl up_or_down			//Sube o baja los pixeles
	sub x12,x12,1			//Resto la altura inicial total
	sub x2,x2,1				//Resto 1 al parametro de altura intermedia
	cbz x2,set_x2			//Si el parametro de altura intermedia es 0 avanzo a la sig. parte
	bl paint_both			//Pinto ambos extremos del puente
	bl up_or_down			//Sube o baja los pixeles
	bl move_center			//Muevo ambos pixeles un paso hacia el centro
	sub x12,x12,1			//Resto la altura inicial total
	sub x2,x2,1				//Resto 1 al parametro de altura intermedia
	cbz x2,set_x2			//Si el parametro de altura intermedia es 0 avanzo a la sig.parte
	bl paint_both			//Pinto ambos extremos del puente
	bl move_center			//Muevo ambos pixeles un paso hacia el centro
	bl up_or_down			//Sube o baja los pixeles
	sub x12,x12,1			//Resto la altura inicial total
	sub x2,x2,1				//Resto 1 al parametro de altura intermedia
	cbnz x2,intermediate_loop 	//Si la altura total no es 0, repito bridge_loop	
set_x2:
	lsr x2,x12,2			//Seteo el parametro de altura final como un cuarto de x2
bridge_loop:
	bl paint_both			//Pinto ambos extremos del puente
	bl move_center			//Muevo ambos pixeles un paso hacia el centro
	bl paint_both			//Pinto ambos extremos del puente
	bl move_center			//Muevo ambos pixeles un paso hacia el centro
	bl up_or_down			//Sube o baja los pixeles
	sub x12,x12,1			//Resto la altura inicial total
	sub x2,x2,1				//Resto uno al parametro de altura final
	cbz x2,bridge_painter	//Si el parametro de altura final es 0 avanzo a la sig. parte
	bl paint_both			//Pinto ambos extremos del puente
	bl up_or_down			//Sube o baja los pixeles
	bl move_center			//Muevo ambos pixeles un paso hacia el centro
	sub x12,x12,1			//Resto la altura inicial total
	sub x2,x2,1				//Resto uno al parametro de altura total
	cbnz x2,bridge_loop 	//Si la altura total no es 0, repito bridge_loop	
bridge_painter:
	bl paint_both			//Pinto ambos extremos del puente
	bl move_center			//Muevo ambos pixeles un paso hacia el centro, compara x7 con 0.
	sub x9,x9,1				//Resto 1 a x9
	cbnz x9,bridge_painter	//Si x9 no es cero vuelvo a pintar pixeles en esta linea
	b set_high				//Si x9 es cero baja una posicion los pixeles y establece un nuevo limite para x8
	b.gt bridge_painter		//Si no complete el puente vuelvo a pintar
up_or_down:
	cbz x13,minus_high		//Si x13 es 0 baja ambos pixeles extremos
	cbnz x13,plus_high		//Si x13 es !=0 sube ambos pixeles extremos
minus_high:
	add x0,x0,2560			//Baja el pixel final
	add x1,x1,2560			//Baja el pixel inicial
	ret
plus_high:
	sub x0,x0,2560			//Sube el pixel final
	sub x1,x1,2560			//Sube el pixel inicial
	ret
set_high:
	add x9,x8,0        		//Copio x9 en x8
	bl up_or_down			//Sube o baja los pixeles
	sub x11,x11,1			//Resta 1 a x11
	cbnz x11, bridge_painter//Si x11 no es 0 repite bridge_painter
	movz x11,0x2,lsl 00		//Le asigna a x11 el numero 2
	add x8,x8,1				//Aumento el limite de pixeles a pintar para la siguiente fila
	b bridge_painter		//Vuelve a pintar
paint_both:
	stur w10,[x1]			//Pinto el pixel inicial
	stur w10,[x0]			//Pinto el pixel final
	ret
move_center:
	sub x0,x0,4				//Muevo el pixel final a la izquierda
	add x1,x1,4				//Muevo el pixel inicial a la derecha
	sub x7,x7,2				//Resto 2 a x7 para saber que pinte dos columnas del puente
	cmp x7,0x0				//Comparo x7 con 0
	b.le end_bridge			//Si x7 es menor o igual a 0, termina el programa	
	ret
end_bridge:
	ldur x1,[SP]			//|Devuelve a x1 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x2,[SP]			//|Devuelve a x2 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x3,[SP]			//|Devuelve a x3 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x4,[SP]			//|Devuelve a x4 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x7,[SP]			//|Devuelve a x7 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x8,[SP]			//|Devuelve a x8 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x9,[SP]			//|Devuelve a x9 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x11,[SP]			//|Devuelve a x11 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x12,[SP]			//|Devuelve a x12 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ldur x30,[SP]			//|Devuelve a x30 el valor inicial
	add SP,SP,8				//|Libero espacio del SP
	ret						//Termina la funcion

// ========  FIN DE PINTAR PUENTECITOS  ======== 


step_in_time:
	movz x13,0x40,lsl 16
loop_delay:
	sub x13,x13,1
	cbnz x13,loop_delay
	ret

	