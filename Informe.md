---
title: "laboratorio 3 - Redes y Sistemas Distribuidos"
author:
  - "Guerrero Diego"
  - "Gonzalez Juan Pablo"
  - "Madero Ismael"
  - "Pellegrino Milena"
date: "2025-05-10"
subject: "redes"
subtitle: "Transporte: Informe"
lang: "es"
titlepage: true
titlepage-color: "108062"
titlepage-text-color: "FFFAFA"
titlepage-rule-color: "FFFAFA"
titlepage-rule-height: 2
book: true
classoption: oneside
code-block-font-size: \scriptsize
---

# laboratorio 3 - Redes y Sistemas Distribuidos
# Transporte: Informe

## Resumen
Parrafo resumiendo la totalidad del trabajo y sus resultados

## Índice

1. [Integrantes](#integrantes)
2. [Introducción](#introduccion)
3. [Experimento 1](#experimento-1)
4. [Experimento 2](#experimento-2)
5. [Conclusiones](#conclusiones)
6. [Referencias](#referencias)
7. [Anexo](#anexo)

## Integrantes
  - Guerrero Diego
  - Gonzalez Juan Pablo
  - Madero Ismael
  - Pellegrino Milena

## Introducción

En este laboratorio nos centramos en la capa de transporte, con el objetivo de analizar el tráfico de red bajo tasas de datos acotadas y tamaño de buffers limitados, ademas de diseñar y proponer diferentes soluciones de control de congestión y flujo. 

Para poder realizar esto usamos Omnet++, una bibloteca con un marco de simulación en C++ destinado principalmente a la creación de simuladores de red, nosotros lo utilizamos para poder generar estos modelos de red que posteriormente analizamos. 




# Experimento 1

bla bla bla 

## Caso de estudio 1

explicacion graficos y toda la bola del experimento 1 

## Caso de estudio 2
explicacion graficos y toda la bola del experimento 2

## Preguntas

respuesta de la pregunta que esta en el informe


# Experimento 2

bla bla bla, contar las cosas de como disenamos, etc..

## Caso de estudio 1

explicacion graficos y toda la bola del experimento 1 

## Caso de estudio 2
explicacion graficos y toda la bola del experimento 2

## Preguntas

respuesta de la pregunta que esta en el informe

## Conclusiones

escribir una conclusion o algo asi

## Referencias

- [Documentación oficial de Omnet++](https://omnetpp.org/documentation/)
- [Manual de Omnet++](https://doc.omnetpp.org/omnetpp5/manual/)
- [Introducción a Omnet++ y c++ (filminas)](https://drive.google.com/file/d/1xx5pSrQE5PUczFH7eUAPKU23-dclSdeF/view)
- [Introducción a Omnet++ y c++ (video)](https://www.youtube.com/watch?v=hgRW5rK-CDE&t=1616s)
- [Graficas en Omnet++ con Python y Notebooks](https://www.youtube.com/watch?v=yL1gf04E2_E)
- [Curva de Carga Ofrecida vs Carga Util](https://www.youtube.com/watch?v=W8r8zSPjeAs)
- [Estructura de un informe](https://www.youtube.com/watch?v=yq8zjLZABe0)
Cabe aclarar que vimos el video sobre la estructura del informe, pero solo incluimos algunos apartados como abstract, referencias, introducción. Para los otros nos tomamos la libertad de divididir el informe en secciones de exp1 y exp2 y luego un apartado de conclusiones general. (en el video se proponia que en la introducción pongamos el análisis de los problemas en el caso1 y caso2, en una sección método se explique la tarea de diseño, etc; nosotros decidimos hacerlo de esta manera ya que nos parecio un poco mas prolijo y mas ordenado a la hora en la que alguien lo tenga que leer; igualmente tenemos en cuenta que esto puede ser subjetivo y podriamos haber seguido la alineación propuesta por la catedra). 

## Anexo

Hemos utilizado diferentes herramientas de Inteligencia Artificial a lo largo del laboratorio, en diferentes ocasiones y usos. 

1. Primeramente utilizamos [ChatGPT](https://chatgpt.com/) para entender algunas partes del código proporcionado por la cátedra, que al leer la documentación no nos quedaba del todo claro.

   1. 
      - **Prompt**: Podrías explicarme qué es lo que hace `par("algo")` en OMNeT++.
      - **Respuesta**: *Lo de `par("nombre")` significa que estás accediendo a un parámetro del módulo en OMNeT++. `par("nombre")` te da acceso al valor de un parámetro definido en el archivo .ned del módulo. Es como una variable configurable desde afuera del código C++.*
      - **Verificación**: Lo verificamos observando el código y viendo que lo que se encontraba adentro del paréntesis efectivamente era un parámetro en el archivo `.ned`. Luego de leer la respuesta de ChatGPT, volvíamos a leer la documentación con un poco más de conocimiento para poder entenderlo del todo.

   2. 
      - **Prompt**: ¿Podrías explicarme qué es lo que hace `exponential(0.001)` en el contexto de OMNeT++?
      - **Respuesta**: *Cuando escribís `exponential(0.001)` en OMNeT++, estás diciendo: "Quiero que este valor se genere aleatoriamente siguiendo una distribución exponencial con media 0.001 segundos (o sea, 1 milisegundo)."*
      - **Verificación**: En este caso lo preguntamos porque no encontrábamos fácilmente información sobre el funcionamiento de `exponential(0.001)`. Encontramos un [manual](https://doc-omnetpp-org.translate.goog/omnetpp/manual/?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc) sobre OMNeT++ pero cuando explicaba lo de `exponential` era bastante vago. Para verificar, probamos qué hacía y leímos el código para ver si tenía sentido.

   3. 
      - **Prompt**: ¿Estamos hacineod un proyecto en omentpp, segun la documentación de omentpp esto es lo que hace la función scheduleAt (insertamos una imágen de la doc) lo que yo entiendo es que scheduleAt es un mensaje para el mismo proceso que lo ejecuta esto es correcto?
      - **Respuesta**: *¡Exactamente! 🙌 En OMNeT++, scheduleAt(tiempo, mensaje) agenda un evento (mensaje) para que sea entregado al mismo módulo que lo programó, en el momento tiempo del reloj de simulación*
      - **Verificación**: Acá no verificamos muchos, ya que utilizamos la herramienta para poder ver si lo que habiamos leído sobre [scheduleAt](https://doc.omnetpp.org/omnetpp/apiclassomnetpp_1_1cSimpleModulehtml#a97c57271ca2fc95225ed8514750cac27)  era correcto o estabamos mal encaminados.

2. 



  scheduleAt()