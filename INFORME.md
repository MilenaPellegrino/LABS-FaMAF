# Informe Lab4 2025 - Redes y Sistemas Distribuidos.

Integrantes:
* Gonzalez Juan Pablo.
* Guerrero Diego Alejandro.
* Madero Ismael.
* Pellegrino Milena.

## Analisis de red inicial.

Una red es un conjunto de nodos conectados entre si que facilitan el envio de paquetes.

Nodos: Miembros de la red que crean, envian y reciben paquetes. En su composicion tienen:
- App: Encargada de crear y recibir paquetes.
- Net: Encargada del reenvio de paquetes (Tanto a App como a Links).
- Links: Canal de comunicacion con otros nodos (Tienen cola y todo lo que reciben lo envian a Net).

Nodos de nuestra red:<br>
![Node[0]](img/Node.png)

En un principio nos fue proporcionada una red funcional para que testeemos y determinemos si dicha red cumple ser **equilibrada**, donde nosotros definimos qué significa que una red sea **equilibrada**.

Nuestra red:<br>
![Red](img/Red.png)

Empezaremos definiendo que es una red equilibrada, para eso dicha red debe cumplir:

1. No sobrecargar nodos si existe otra posibilidad.
2. Enviar paquetes por caminos cortos.

Dicho esto podremos concluir que una red equilibrada **envia paquetes por el camino más corto con menos congestion**.

Analizando dicha red podemos observar que su flujo  de trabajo es el siguiente:

- Todos los paquetes son enviados en sentido de las agujas del reloj.<br>
Esto quiere decir que en la red dada Node[0] envia a Node[7] y todos los demas nodos envian al nodo con numero mas chico.

### Caso 1 
- Node[0] y Node[2] producen paquetes con destino a Node[5].

Ejemplo de ejecucion:<br>A la izq ejecucion del Node[0], a la derecha ejecucion de red, notar que estos ejemplos no son sincrónicos.<br>Los paquetes rojos son producidos por Node[0] y los azules por Node[2]:<br>
![Sample1](img/Sample1.gif) ![Sample](img/Case1Sample.gif)

**Ejecutando esta red durante 200 segundos podemos ver lo sig:**

Promedio de paquetes en colas de salida:<br>
![Buffers](img/Case1Buffers.png)

Puede apreciarse: 
1. La ausencia de las colas de Node[3], Node[4], y Node[5].
2. Node[0] es el de mayor carga.
3. Node[2] tiene ligeramente mayor carga que los nodos del punto 4.
4. Node[1], Node[6], y Node[7] son los que menor carga tienen.

Razonamiento:
1. Esto se debe a que no se envian paquetes por dichos nodos.
2. Envia tanto los paquetes recibidos desde Node[1] como los generados.
3. Unicamente envia los paquetes que genera.
4. Solo envian paquetes recibidos.

Observacion:
Los paquetes se generan mas rapido de lo que se envian, por eso el Node[2] y Node[0] tienen mayor congestion en sus colas.

Conteo de paquetes que pasaron por modulo net:<br>
![Buffers2](img/Case1Buffers2.png)

Puede verse que el Node[2] con único rol generador produjo aproximadamente un total de 189 paquetes, se estima una cantidad de produccion similar en el Node[0] por lo que se observa logico que sea aproximadamente mayor al doble que del Node[2] puesto que ademas de producir, recibe los producidos por Node[2].<br>
En los demas nodos se ve un valor similar de manejo de paquetes pues estos solo reenvian.

Valores de los delays segun llegan:<br>
![Delays](img/Case1Delays.png)

Se aprecia que los delays aumentan a medida que ocurre la ejecucion, esto ocurre pues hay sobrecongestionamiento producido en el Nodo[0], lo que genera cada vez mayores delays.

Cantidad de saltos por paquete:<br>
![Hops](img/Case1Hops.png)

En esta grafica se ven que hay dos tipos de paquetes, los que llegan con 3 hops y los que llegan con 5. Producidos por Node[2] y Node[0] respectivamente. Se observan dominantes los paquetes de 3 Hops, esto indica que llegan aproximadamente un 17% mas paquetes producidos por Node[0]

### Caso 2
- Todos los nodos envian a Node[5]

Ejemplo de ejecucion:<br>
![Sample](img/Case2Sample.gif)

Promedio de paquetes en colas de salida:<br>
![Buffers](img/Case2Buffer.png)

Conteo de paquetes que pasaron por modulo net:<br>
![Buffers2](img/Case2Buffers2.png)

Valores de los delays segun llegan:<br>
![Delays](img/Case2Delays.png)

Cantidad de saltos por paquete:<br>
![Hops](img/Case2Hops.png)

### Extra:
Las graficas fueron generadas usando el sig. link de collab: [lab4_analisis](https://colab.research.google.com/drive/1AdbyTvdN3MwR7wmiGdik1NOO2emff0Gs?usp=sharing)