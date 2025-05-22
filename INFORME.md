# Informe Lab4 2025 - Redes y Sistemas Distribuidos.

Integrantes:
* Gonzales Juan Pablo.
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

Analizando dicha red podemos observar que su flujo de trabajo es el siguiente:

- Node[0] y Node[2] producen paquetes con destino a Node[5].
- Todos los paquetes son enviados en sentido de las agujas del reloj.<br>
Esto quiere decir que en la red dada Node[0] envia a Node[7] y todos los demas nodos envian al nodo con numero mas chico.

Ejemplo de ejecucion:<br>A la izq ejecucion del Node[0], a la derecha ejecucion de red, notar que estos ejemplos no son sincrónicos.<br>Los paquetes rojos son producidos por Node[0] y los azules por Node[2]:<br>
![Sample1](img/Sample1.gif) ![Sample](img/Sample.gif)

Ejecutando esta red durante 200 segundos podemos ver la sig. cantidad de paquetes que pasaron por alguna cola de salida:<br>
![Buffers](img/Buffers.png)

Puede apreciarse: 
1. La ausencia de las colas de Node[3], Node[4], y Node[5].
2. Node[2] y Node[1] son los que menor carga tienen.
3. Node[0] es el de mayor carga.
4. Node[7] y Node[6] poseen misma carga

Razonamiento:
1. Esto se debe a que no se envian paquetes por dichos nodos.
2. Solo envian paquetes producidos por Node[2].
3. Envia tanto los paquetes recibidos como los generados.
4. Enian paquetes producidos por Node[0] y Node[2].