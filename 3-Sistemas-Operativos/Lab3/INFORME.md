# Primera Parte: Estudiando el planificador de xv6-riscv

### 1.<br> ¿Qué política de planificación utiliza `xv6-riscv` para elegir el próximo proceso a ejecutarse?

Basandonos en la funcion `scheduler(void)`, llegamos a la conclusion que la
politica de planificacion utilizada en xv6-riscv es Round Robin.


### 2.<br> ¿Cúales son los estados en los que un proceso puede permanecer en xv6-riscv y qué los hace cambiar de estado?

Basandonos en el archivo `proc.h` los estados en el cual un proceso puede
permanecer en xv6-riscv son 
`enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };`

- **UNUSED**:<br>
Al llamar `procinit()` en el main del kernel se inicia la tabla de procesos, todos en estado `UNUSED`.<br>
Tambien cuando es llamado `freeproc()` dentro de la funcion `wait()`, `fork()`, `allocproc()`, se cambia el estado de un proceso a `UNUSED`.

- **USED**:<br>
Al llamar `userinit()` dentro de main.c, se llama a su vez `allocproc()` que cambia el estado de un proceso `UNUSED` a `USED` siempre y cuando no haya fallado.

- **SLEEPING**:<br>
En la funcion `sleep()` se cambia el estado del proceso ejecutado actualmente de `RUNNING` a `SLEEPING`.

- **RUNNABLE**:<br>
Al llamar `userinit()` dentro de main.c, cambia de estado `USED` a `RUNNABLE`.<br>
En las funciones de `wakeup()` y `KILL()`, cambian de estado `SLEEPING` a `RUNNABLE`.<br>
En la funcion `yield()` ocurre tambien un cambio de estado `RUNNING` a 
`RUNNABLE`.<br> 
En las funcion `fork()`, cambia el estado del proceso hijo `USED` a `RUNNABLE`.

- **RUNNING**:<br>
La funcion `scheduler()`, verifica si un proceso esta en estado `RUNNABLE` y lo cambia a estado `RUNNING`.

- **ZOMBIE**:<br>
La funcion `exit()` toma el proceso actualmente ejecutado y lo pone en estado `ZOMBIE`.

### 3.<br>a)¿Qué es un *quantum*?<br>b)¿Dónde se define en el código?<br>c)¿Cuánto dura un *quantum* en `xv6-riscv`?<br>Pista: Se puede empezar a buscar desde la system call `uptime` o leyendo la documentación de xv6 en la sección de interrupciones.

**a)** <br>
De acuerdo al OSTEP, un quantum es una porcion fija de tiempo destinada a la ejecucion exclusiva de un proceso, al alcanzarse el tiempo del quantum se da el control al scheduler para que decida el siguiente proceso a ejecutar.

**b)** <br>
Se define en la linea 63 del archivo `start.c` como `timerinit()`.

**c)** <br>
Un quantum en `xv6-riscv` dura 1.000.000 ciclos de clocks, esto es equivalente a 1/10 segundos (100 milisegundos) en qemu. Esto lo podemos ver en el archivo `start.c` en la función `timerinit()` donde se define: 
```
  // ask the CLINT for a timer interrupt.
  int interval = 1000000; // cycles; about 1/10th second in qemu.
```

### 4.<br>a)¿En qué parte del código ocurre el cambio de contexto en `xv6-riscv`?<br>b)¿En qué funciones un proceso deja de ser ejecutado?<br>c)¿En qué funciones se elige el nuevo proceso a ejecutar?
**a)** <br> En `proc.c` en la función `scheduler()` se llama a `swtch.S`: 
```
swtch(&c->context, &p->context);
``` 
para hacer el cambio de contexto. Por lo tanto en la parte del código donde ocurre el cambio de contexto es gracias a la función `scheduler()` en `proc.c` pero el encargado de hacerlo está en el archivo `swtch.S`

**b)** <br>
En las funciones `sleep()` y `exit()`, ya descriptas anteriormente en el inciso 2 [ir al ejercicio 2](#2¿Cúales-son-los-estados-en-los-que-un-proceso-puede-permanecer-en-xv6-riscv-y-qué-los-hace-cambiar-de-estado)

**c)** <br>
El nuevo proceso a ejecutar ocurre en la función `scheduler()` en `proc.c` ya que selecciona procesos en estado `RUNNABLE` y los ejecuta, pasando asi el estado a `RUNNING`. Lo que hace es hacer un bucle entre los procesos y buscar el que tiene un estado `RUNNABLE` cuadno lo encuentra hace el cambio de contexto.


### 5.<br>¿El cambio de contexto consume tiempo de un *quantum*?
<br>
El cambio de contexto sí consume tiempo. Cuando se produce una interrupción de timer, se define el momento de la siguiente interrupción antes de pasar al código del trap que maneja la interrupción actual. Durante todo este tiempo, el quantum sigue corriendo. Luego, el proceso pasa por `yield`, donde se llama a `sched` para realizar el primer cambio de contexto y regresar al planificador. Es ahí cuando se selecciona el nuevo proceso, pero para ese momento ya se ha utilizado una pequeña parte del quantum actual.

<br> <br>

# Segunda Parte: Medir operaciones de cómputo y de entrada/salida
**OBSERVACIONES**
<br>
- Fue necesario añadir cpubench e iobench al Makefile para poder hacerlo ejecutable. <br>
<br>
- El experimento 1 lo realizamos en una nueva branch llamada *experimento1* <br>
<br>
- Para el Experimento 1 fijamos el N = 10 como parámetro de cpubench e iobench ya que es el número que considerabamos los suficientemente grande como para que haya contextswitches y suficientemente pequeño para que los experimentos no duren mucho más de un minuto (tiempo que varía según la computadora)<br>
<br> 
- Al haber fijado el tamaño de los cpubench e iobench se debe ejecutar sin llamar algun parametro, esto se mantendra por el resto del laboratorio. <br>

## Experimento 1: ¿Cómo son planificados los programas iobound y cpubound?

- **1. Que el experimento sea lo suficientemente largo como para que haya cambios de contexto entre los procesos.**

- **2. Que el experimento sea lo suficientemente corto como para que el programa entero de mediciones se ejecute en un tiempo razonable, digamos 1 minuto.**

- **3. Que compile: si las operaciones son demasiado grandes, podemos quedarnos sin memoria en el al ejecutar muchos procesos iobench o que el conteo de la cantidad de operaciones de cpu de overflow.**

- **4. Que las mediciones no sean menores que ni cercanas a 1 en la mayoría de los casos, ya que son casteadas a enteros y se pierde mucha información en el redondeo.**

### 1. <br> Describa los parámetros de los programas cpubench e iobench para este experimento (o sea, los define al principio y el valor de N. Tener en cuenta que podrían cambiar en experimentos futuros, pero que si lo hacen los resultados ya no serán comparables).
En una llamada a `cpubench(n,pid)` el parametro n se encarga de decir cuantas veces debe hacer el cpubench y el pid es el numero asignado a proceso que sirve para diferenciar distintas llamadas. Los parametros de `iobench(n,pid)` se comportan de forma analoga a los de cpubench.<br>
- **cpubench** <br>
    1. `CPU_MATRIX_SIZE`: Define el tamaño de las matrices que se multiplicarán, esta fijado en 128,  o sea que la matriz es de 128 * 128. 
    2. `CPU_EXPERIMENT_LEN`: Define el número de veces que se repetirá la multiplicación de matrices. Como esta fijada en 256,  la multiplicación se realiza 256 veces en cada ciclo.
    2. `N`: Lo fijamos en 10, ya que este número cumplía con todos los requisitos.


- **iobench** 
    1. `IO_OPSIZE`: Define el tamaño de cada operación de entrada/salida en bytes. Está fijado en 64, por lo tanto en cada operación de (I/O), se transferirán 64 bytes de datos.
    2. `IO_EXPERIMENT_LEN`: Define el número de operaciones de escritura y lectura que se realizarán dentro de cada ciclo; está fijado en 512, por lo tanto se realizarán 512 operaciones de escritura y 512 operaciones de lectura para cada ciclo.
    2. `N`: Lo fijamos en 10, por la justificación anterior, y porque el N tenía que ser fijo para realizar los experimentos.
    
### 2. <br> ¿Los procesos se ejecutan en paralelo? ¿En promedio, qué proceso o procesos se ejecutan primero? Hacer una observación cualitativa.

Los procesos se ejecutan en paralelo, si hacemos por ejemplo cpubench 10 & ; cpubench 10 & , obtendremos que en prromedio se ejecuta el primer proceso del primer cpubench y luego del otro cpubench, pero el rendimeinto del segundo cpubench es menor que el primero,esto se debe a que al ejecutarse en paralelo ambos procesos quieran usar el mayor tiempo de cpu posible. Esto hace que el rendimiento de cada cpubench no sea como ejecutarlo normalmente, es decir que no se ejecute en paralelo.

### 3. <br> ¿Cambia el rendimiento de los procesos iobound con respecto a la cantidad y tipo de procesos que se estén ejecutando en paralelo? ¿Por qué?
<br>
El rendimiento del iobench no cambia respecto a la cantidad y tipo de procesos ejecutados en paralelo, esto se debe a que la carga de cpu que hace iobench es minima ya que realiza muchas syscalls, de esta manera dentro de un mismo quantum puede iniciar varios iobound en paralelo, y cuando estos vuelvan de la syscall continuar su ejecucion casi instantaneamente, de esta manera consumiendo la minima cantidad de quantum posible por cada uno.

### 4. <br> ¿Cambia el rendimiento de los procesos cpubound con respecto a la cantidad y tipo de procesos que se estén ejecutando en paralelo? ¿Por qué?
<br>
El rendimiento del cpubench si cambia respecto a la cantidad y tipo de procesos ejecutados en paralelo, esto porque la carga de cpu del cpubench es total y requieren varios quantum para terminar su ejecucion, de esta manera dados los cambios de contexto por quantum y el uso de cpu por otro cpubench, aumenta el tiempo desde que inicio el cpubench hasta que termino y asi restandole rendimiento.

### 5. <br> ¿Es adecuado comparar la cantidad de operaciones de cpu con la cantidad de operaciones iobound?
<br>
No es posible comparar la cantidad de operaciones que realiza cpubound con iobound, ya que iobound al hacer operaciones de I/O son mucho mas lentas que las operaciones de calculo que hace cpubound

cuando ejecutamos `iobench &` 

| pid |           | metrica                | #op  | start_tick | elapsed_tick |
|-----|-----------|------------------------|------|------------|--------------|
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 814        | 170          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 985        | 163          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 1148       | 161          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 1310       | 162          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 1473       | 161          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 1635       | 161          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 1796       | 160          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 1956       | 161          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 2117       | 162          |
| 4   | [iobench] | iops/elapsed_ticks : 6 | 1024 | 2280       | 161          |

cuando ejecutamos `cpubench &`

| pid |            | metrica                   | #op    | start_tick | elapsed_tick |
|-----|------------|---------------------------|--------|------------|--------------|
| $ 7 | [cpubench] | kops/elapsed_ticks : 4129 | 536832 | 4924       | 130          |
| 7   | [cpubench] | kops/elapsed_ticks : 4161 | 536832 | 5055       | 129          |
| 7   | [cpubench] | kops/elapsed_ticks : 4129 | 536832 | 5185       | 130          |
| 7   | [cpubench] | kops/elapsed_ticks : 4129 | 536832 | 5315       | 130          |
| 7   | [cpubench] | kops/elapsed_ticks : 4129 | 536832 | 5445       | 130          |
| 7   | [cpubench] | kops/elapsed_ticks : 4129 | 536832 | 5575       | 130          |
| 7   | [cpubench] | kops/elapsed_ticks : 4161 | 536832 | 5706       | 129          |
| 7   | [cpubench] | kops/elapsed_ticks : 4161 | 536832 | 5836       | 129          |
| 7   | [cpubench] | kops/elapsed_ticks : 4129 | 536832 | 5966       | 130          |
| 7   | [cpubench] | kops/elapsed_ticks : 4129 | 536832 | 6096       | 130          |

## Experimento 2: ¿Qué sucede cuando cambiamos el largo del quantum?
**OBSERVACIONES**
<br>
- Es utilizada una metrica distinta entre el quantum 1k y el 10k, esto es asi por la cuarta parte. <br>
<br>
- La ejecucion en quantum 1k se hace muy tardada.

### 1. <br> ¿Fue necesario modificar las métricas para que los resultados fueran comparables? ¿Por qué?
Si fue necesario, esto se debe a que la metrica antes elegida era una division de operaciones entre ticks transcurridos, al hacer mas chico el quantum ocurren mas interrupciones lo que genera que la cantidad de ticks transcurridos sea bastante mayor que la cantidad de operaciones, lo que hacia que nuestra division resulte en cero.

### 2. <br> ¿Qué cambios se observan con respecto al experimento anterior? ¿Qué comportamientos se mantienen iguales?

Como principal cambio notamos que al cambiar el tiempo del `quantum` con un número menor que el anterior tarda más en ejecutar los procesos y más ticks por procesos tiene.
Los comportamientos con respecto al experimento 1 se mantienen iguales en la cantidad de operaciones realizadas, pero tanto en la cantidad de ticks que tarda cada proceso es distinto al experimento 1.

### 3. <br> ¿Con un quatum más pequeño, se ven beneficiados los procesos iobound o los procesos cpubound?
<br>
Al reducir el quantum, los procesos iobound suelen verse beneficiados en comparación con los cpubound. 
<br>
Esto se debe a que los procesos cpubound realizan muchas operaciones intensivas de CPU (como los cálculos de multiplicación de matrices en cpubench con los cuales ejecutamos los experimentos). Una reducción del quantum no seria beneficioso, ya que al hacer más cambios de contextos, no se logran completar el trabajo total, lo que reduce la eficiencia de su ejecución y aumenta el tiempo total de procesamiento.

<br>
En cambio, los procesos I/O-bound, al realizar operaciones de escritura y lectura, hacen un poco de trabajo en la CPU y después deben esperar a que la operación de lectura o escritura termine. Cuando el quantum es más pequeño, realizan su pequeña tarea en la CPU y luego pueden volver rápidamente a la cola de espera para la siguiente operación de input/output. Así, mientras esperan que las operaciones de input/output terminen, la CPU puede atender a otros procesos y no se queda inactiva, haciendo mucho más eficiente el uso de la CPU.

<br>

# Tercera Parte: Asignar prioridad a los procesos

- **Agregue un campo en `struct proc` que guarde la prioridad del proceso (entre `0` y `NPRIO-1` para `#define NPRIO 3` niveles en total siendo `0` el prioridad minima y el `NPRIO-1` prioridad máxima) y manténgala actualizada según el comportamiento del proceso, además agregue el campo en `struct proc` que guarde la cantidad de veces que fue elegido ese proceso por el planificador para ejecutarse y se mantenga actualizado:**

Con estos cambios el `struct proc` queda de la siguiente manera: 

```
struct proc {
  
  // código existente

  int priority;    // Nivel de prioridad 
  int sched_count;  // Cant. de veces que el proc. fue selec. para su ejecución
}; 
```
<br>

- **MLFQ regla 3: Cuando un proceso se inicia, su prioridad será máxima.**

Esto lo hacemos en la función mlfq_set(), que revisa todos los nuevos procesos `RUNNABLES`, les asigna prioridad maxima y los mete en la mlfq:

```
void
mlfq_set (void) 
{
	struct proc *p;
	for (p = proc; p < &proc[NPROC]; p++) {
		acquire(&p->lock);
		if (p->state==RUNNABLE && p->priority==-1) {
				p->priority=NPRIO-1;   //ASIGNA PRIORIDAD MAXIMA
				pq_enqueue(&mlfq[NPRIO-1],p);
		}
		release(&p->lock);
	}
	return;
}  
```
<br>

- **MLFQ regla 4: Descender de prioridad cada vez que el proceso pasa todo un quantum realizando cómputo. Ascender de prioridad cada vez que el proceso se bloquea antes de terminar su quantum. Nota: Este comportamiento es distinto al del MLFQ del libro.**<br>

Esto lo conseguimos modificando una parte del codigo de `usertrap()` en trap.c:

```
void
usertrap(void)
{
  /////////////////////////////////////
  // give up the CPU if this is a timer interrupt.
  if(which_dev == 2) {
    if (myproc()->state == RUNNING) {
      if (myproc()->priority > 0){
        myproc()->priority--;
      }
    }
    yield();
  }
  else if (myproc()->state != RUNNING) {
    if (myproc()->priority < NPRIO - 1)
      myproc()->priority++;
  }
  //////////////////////////////////////
```
Notar que `NPRIO` esta definido como 3.
 
 <br>

- **Para comprobar que estos cambios se hicieron correctamente, modifique la función `procdump` (que se invoca con `CTRL-P`) para que imprima la prioridad de los procesos. Así, al correr nuevamente `iobench` y `cpubench`, debería darse que luego de un tiempo que los procesos `cpubench` tengan baja prioridad mientras que los `iobench` tengan alta prioridad.**

Con estos cambios el `procdump` queda de la siguiente manera: 

```
void
procdump(void)
{
  
  // Código existente

    printf("%d %s %s priority: %d", p->pid, state, p->name, p->priority);
    printf("\n");
  }
}
``` 

<br>

# Cuarta Parte: Implementar MLFQ

**OBSERVACIONES**
<br>
- Implementamos la mlfq de tamaño 3 con un arreglo de queues, cada queue esta implementada con un struct con un arreglo de procesos de tamaño NPROC, y dos enteros que definen el indice inicial y el indice final, sus funciones estan modularizadas debido al comportamiento de una queue.<br>
- Diseñamos varias funciones para trabajar la **queue**: `pq_dequeue()` añade un elemento al final de la cola, `pq_enqueue()` quita y devuelve el primer elemento de la cola, `pq_peek()` devuelve el primer elemento de la cola, `pq_is_empty()` devuelve 1 si es cola vacia y 0 en caso contrario, y `pq_size()` devuelve la cantidad de elementos de la cola.<br>
- Diseñamos varias funciones para trabajar la **mlfq**: `mlfq_init()` setea los valores iniciales de las colas, `mlfq_get_proc()` devuelve el proximo proceso a ejecutar, `mlfq_switch_prio()` guarda el proceso recibido en la mlfq de acuerdo a su prioridad, `mlfq_set()` itera el array de procesos buscando nuevos procesos `RUNNABLE`.<br>
- Todas las funciones previas estan añadidas al defs.h, definimos queue y su struct en `proc.h`.<br>

**Finalmente implementar la planificación propiamente dicha para que nuestro `xv6-riscv` utilice MLFQ.**

- **1. Modifique el planificador de manera que seleccione el próximo proceso a planificar siguiendo las siguientes reglas:**
  - **MLFQ regla 1: Si el proceso A tiene mayor prioridad que el proceso B, corre A. (y no B)**
  - **MLFQ regla 2: Si dos procesos A y B tienen la misma prioridad, corre el que menos veces fue elegido por el  planificador.**

- **2.Repita las mediciones de la segunda parte para ver las propiedades del nuevo planificador.**<br>
<br>
Dejamos un analisis de como se comporta los planificadores, Round-Robin y MLFQ con distinto Quantum y diferentes metricas [Analisis de datos](https://docs.google.com/spreadsheets/d/16_OrGci7LkNYlrRO6umkzXKj97t0WXAGJcTlYoGmcck/edit?gid=0#gid=0)

### 1. <br> ¿Se puede producir starvation en el nuevo planificador? Justifique su respuesta.
<br>
Si se puede producir un `starvation`, Esto sucede porque en MLFQ, los procesos que consumen menos tiempo de CPU suelen permanecer en las colas de alta prioridad, mientras los procesos mas largos de o intesivos de CPU son enviados a las colas de menor prioridad, es decir que si tenemos muchos procesos que en las colas de alta prioridad es posible que los procesos en las colas de menor prioriridad nunca obtengan tiempo de CPU.


# Puntos estrella

**- Del planificador:**
- **1. Reemplace la política de ascenso de prioridad por la regla 5 de MLFQ de OSTEP: Priority boost.** <br>
- **2. Modifique el planificador de manera que los distintos niveles de prioridad tengan distintas longitudes de *quantum*.** <br>
- **3. Cuando no hay procesos para ejecutar, el planificador consume procesador de manera innecesaria haciendo *busy waiting*. Modifique el planificador de manera que ponga a dormir el procesador cuando no hay procesos para planificar, utilizando la instrucción `hlt`.**<br>
- **4. (Difícil) Cuando xv6-riscv corre en una máquina virtual con 2 procesadores, la performance de los procesos varía significativamente según cuántos procesos haya corriendo simultáneamente. ¿Se sigue dando este fenómeno si el planificador tiene en cuenta la localidad de los procesos e intenta mantenerlos en el mismo procesador?**<br>
- **5. Llevar cuenta de cuánto tiempo de procesador se le ha asignado a cada proceso, con una *system call* para leer esta información desde espacio de usuario.**<br>
<br><br><br><br>


- **Punto estrella 1: Priority boost.** <br>
En la función *scheduler(void)* se inicializa un timer que se incrementa en cada iteración y cuando llega a determinado número (N), se llama a la función *priority_boost()* que en resumen, itera las queue de prioridad 0 y 1 sacando a todos los elementos, cambiandoles la prioridad a 2 y volviendolas a meter en la queue correspondiente. El N fijado es 500 para poder ver el **priority boost** sin tener que crear muchos procesos. A continuación, el código correspondiente a la función ***priority_boost()***:<br><br>


```
void
priority_boost(void){
  
  for (uint64 i = 0; i < NPRIO - 1; i++)
  {
    while (!pq_is_empty(&mlfq[i]))
    {
      struct proc* procces = pq_dequeue(&mlfq[i]);
      procces->priority = 2;
      mlfq_switch_prio(procces);
    }
  }
  return;
}
```
<br><br>
- Observaciones: La función *mlfq_switch_prio()* recibe un proceso y lo encola en la queue correspondiente a su prioridad.