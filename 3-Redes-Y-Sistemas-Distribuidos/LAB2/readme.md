# Laboratorio 2 - Redes y Sistema Distribuidos 2025
## Grupo 12
### Integrantes: 

1. Gonzalez Juan Pablo
2. Guerrero Diego
3. Madero Ismael 
4. Pellegrino Milena

### Enlaces de entrega
1. [Diapositivas utilizadas](https://www.canva.com/design/DAGkJh1VBV8/P_r_OMeN25J4-WbowdJsjA/edit?utm_content=DAGkJh1VBV8&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)
2. [Video de presentación (en drive)](https://drive.google.com/drive/folders/1mKSFKjGyE0sDVkQimmBLK7Ep0nxj1Yh2?usp=sharing)

### Preguntas
1. ¿Qué estrategias existen para poder implementar este mismo servidor pero con capacidad de atender múltiples clientes simultáneamente? Investigue y responda brevemente qué cambios serían necesarios en el diseño del código.
Existe varias formas para implementar el servidor que soporte multiples clientes. 
- Threads -> Utilizando la bibloteca de python threading y creando un hilo nuevo para cada cliente (que es como lo implementamos nosotros en el laboratorio)
- Multiprocesos -> usando el modulo multiprocessing y os.fork(). Cada vez que llego un cliente, hacer un fork() y crear un nuevo proceso para atenderlo. 
- Poll -> Utilizando la bibloteca polling o select, se va fijando que sockets están listos para leer o para escribir, y asi evita bloqueos y no crea hilos ni procesos adicionales. 
- async -> Usando el modulo adyncio, lo que hace es hacer bucles de los eventos priorizando las operaciones que ya están listas, para asi poder manejar las múltiples conexiones sin hilos adicionales

2. Pruebe ejecutar el servidor en una máquina del laboratorio, mientras utiliza el cliente desde otra, hacia la ip de la máquina servidor. ¿Qué diferencia hay si se corre el servidor desde la IP “localhost”, “127.0.0.1” o la ip “0.0.0.0”?
Si usamos localhost o 127.0.0.1 solo es accesible desde la misma máquina, si corremos nuestro servidor utilizando esto, desde otra máquina diferente no vamos a poder conectarnos, ya que solo escucha conexiones locales. 
En cambio si usamos 0.0.0.0 o la IP de la máquina nos permite conectarnos desde otras máquinas al server. 
