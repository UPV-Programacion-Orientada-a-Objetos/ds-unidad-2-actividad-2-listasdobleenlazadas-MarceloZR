# Reporte – Unidad 2 – PRT-7 Decoder

## Objetivo
Desarrollar un sistema que decodifique tramas enviadas por un Arduino basadas en el protocolo industrial PRT-7.

## Funcionamiento
Las tramas llegan por puerto serial en el formato:

- `L,<char>`  carga una letra
- `L,Space`   carga un espacio
- `M,<n>`      aplica rotación al rotor (n puede ser positivo o negativo)

Cada trama se procesa y se va generando un mensaje oculto.

## Arquitectura implementada

| Archivo           | Función principal                                    |
|-------------------|--------------------------------------------------------|
| ListaDeCarga.h    | Administra el mensaje final                            |
| RotorDeMapeo.h    | Realiza las rotaciones y mapeo de letras               |
| TramaBase.h       | Clase abstracta para cualquier trama                   |
| TramaLoad.h       | Trama que carga letras/espacios                        |
| TramaMap.h        | Trama que realiza rotación del rotor                   |
| main.cpp          | Abre serial, lee tramas y dirige el procesamiento      |

## Resultado
Se logró decodificar correctamente la secuencia completa.  
El sistema muestra el mensaje reconstruido al final de la ejecución.

---
**Alumno:** Marcelo Antonio Zúñiga Ramírez  
**Matrícula:** 2430299
