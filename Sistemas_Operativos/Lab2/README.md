# Sistemas Operativos 2024

## Laboratorio 2: Semáforos en XV6

Programando nuestras propias llamadas al sistema

## Integrantes

- **Madero Ismael**
- **Castillo Agustin**
- **Gonzalez Juan Pablo**
- **Pellegrino Milena**

## Requisitos

- **sudo apt-get install qemu-system-riscv64 gcc-riscv64-linux-gnu**: Instalar qemu en ubuntu
- **make qemu**: En la carpeta SO24LAB2GO5 para compilar y ejecutar XV6
- **pingpong N**: Ejecutar pingpong (N un numero natural)
- **make grade**: Compilar y ejecutar los test

## Comentarios

1. **MakeFile**

   Modificiamos el makefile en la línea 135 añadiendo el "$U/_pingpong\"
  
2. **Implementación de las syscall del semáforo**

   Implementamos las syscall (sem_open(), sem_up(), sem_down(),sem_close()) en el archivo "proc.c" 
   
3. **Archivos modificados**
    - defs.h
    - param.h
    - proc.c
    - proc.h
    - semaphore.c
    - semaphore.h
    - syscall.c
    - syscall.h
    - sysproc.c
    - pingpong.c
    - user.h
    - usys.pl
    
