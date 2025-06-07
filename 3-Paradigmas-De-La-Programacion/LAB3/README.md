# Computacion distribuida con Apache Spark.

## Integrantes:

* Gonzalez Juan Pablo.
* Madero Ismael.
* Pellegrino Milena.

En este, nuestro maravilloso laboratorio implementamos un programa que descarga y muestra varias noticias de distintos portales, o tambien computa la cantidad de ocurrencias de entidades nombradas siguiendo una heuristica, contenidas en dichas noticias.<br>
La idea para llevar a cabo estas acciones fue realizarlo con procesamiento distribuido con el Framework Apache Spark.<br>

## Configuración del entorno.
Deben tener instalado jdk-11, y Apache Spark en su computadora.<br>
Luego en el archivo Makefile modificar JAVA_PATH con la referencia absoluta a la ruta donde se encuentra instalado el ejecutable java de jdk-11.<br>
Asimismo modificar SPARK_FOLDER con la referencia absoluta a la ruta donde se encuentra instalado Spark.<br>
Una vez configurado correctamente podran compilar y ejecutar este programa.

## Compilación y ejecución.
- **Compilar**
  ```bash
  make
- **Ejecutar sin argumentos:**  
  ```bash
  make run
- **Ejecutar con argumentos (para ejercicio de heuristica):**
  ```bash
  make run_entity
- **Para limpiar los archivos compilados, ejecuta:**
  ```bash
  make clean

## Decisiones de diseño
Diseñamos dos clases nuevas SparkNamedEntityProcessor y SparkSubscriptionProcessor, las cuales heredan de una nueva clase SparkProcess, dentro de las cuales se levanta un cluster de Spark para trabajar y abstraer del FeedReaderMain toda la logica de Spark.<br>
Observacion: Cada clase crea una sesion distinta de spark.<br>

## Conceptos importantes
1. **Describa el flujo de la aplicación ¿Qué pasos sigue la aplicación desde la lectura del archivo feeds.json hasta la obtención de las entidades nombradas? ¿Cómo se reparten las tareas entre los distintos componentes del programa?**<br>
Primero parsea el archivo json, inicia el spark, dado el Subscriptions se paralleliza sobre cada SingleSubscription para obtener una lista de Feeds, luego se traen al master estos datos, se cierra el spark y se imprimen los feeds por pantalla.<br>
En el caso de las heuristicas se realiza todo lo anterior excepto imprimir por pantalla, se crea una sesion de spark, se paraleliza sobre los feeds para obtener sus articulos y en cada articulo computar sus heuristicas y obtener una lista de entidades nombradas.<br>
Se paraleliza sobre dicha lista para generar un par (key, value) con entidades nombradas y sus ocurrencias.<br>
Finalmente dado que la lista previa contempla NamedEntitys por articulos hay varias entidades repetidas y se paraleliza para sumar dichas ocurrencias en mismas entidades y generar una nueva lista, luego se traen al master esos datos, se cierra el spark y se imprimen las NamedEntitys por pantalla.

2. **¿Por qué se decide usar Apache Spark para este proyecto?** ¿Qué necesidad concreta del problema resuelve?<br>
En nuestro proyecto usamos ApacheSpark, ya que al tener que procesar mucha cantidad de feeds, lo cual conlleva un gran volumen de datos, ya que ademas de procesar los feeds (descargarlos) calculamos las entidades nombradas. Apache Spark es un framework que nos permite hacer todos los procesamientos de estos datos de manera distribuida, es decir, la idea del procesamiento distribuido es repartir los datos en varias computadoras (nodos) para que cada una procese una parte especifica y al funcionar en paralelo se reduce significativamente los tiempos de computo. Lo interesante de Apache Spark es que nos abstrae totalmente la complejidad del procesamiento distribuido, ya que no nos enteramos como funciona internamente, y nos permite solo tener que concentrarnos en la logica del programa.

3. **Liste las principales ventajas y desventajas que encontró al utilizar Spark.**<br>
Ventajas:
- Trabajar grandes cantidades de datos.
- Abstaer la administracion de muchas computadoras.
- Ejecucion mas eficiente.<br><br>
Desventajas:
- El uso exclusivo de Java-11.
- Aprender el uso del Framework (Documentacion confusa).

4. **¿Cómo se aplica el concepto de inversión de control en este laboratorio? Explique cómo y dónde se delega el control del flujo de ejecución. ¿Qué componentes deja de controlar el desarrollador directamente?**<br>
Recordemos que la inversion de control singifica que el flujo de ejecucion del programa no lo controla completamente el programador, sino que se delegan algunas responsabilidades a una libreria, motor o a un framework, como sucede en este caso.  <br> 
En nuestro programa spark maneja una gran parte del flujo gracias al procesamiento distribuido, (cuando hacemos los flatMap, los collects, etc) nosotros le indicamos a Spark, que use estas funcionalidades pero en realidad no sabemos como ni cuando ni en que nodos ni siquiera sabemos bien el orden en que se ejecuta. <br> 
En fin, lo que dejamos de tener control directamente es todo lo que paralelizamos ya que en ese caso el que tiene control es spark. <br>

5. **¿Considera que Spark requiere que el codigo original tenga una integración tight vs loose coupling?**<br>
Consideramos que requiere un codigo con loose coupling esto debido a que es mas facil su integracion con el programa dado que requiere menos modificaciones en el codigo, en caso contrario posiblemente se deba cambiar la logica del programa para permitir su integracion. 

6. **¿El uso de Spark afectó la estructura de su código original? ¿Tuvieron que modificar significativamente clases, métodos o lógica de ejecución del laboratorio 2?**<br>
No tuvo mayor impacto en la estructura, de hecho colaboro con el codigo del main dado que nos permitio la modularizacion de grandes partes del codigo dentro de las clases que creamos.<br>
Tuvimos que agregarle a varias clases la serializacion lo que se considera modificacion despreciable.<br>
