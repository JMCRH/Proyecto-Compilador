# Compilador equipo 5

**Integrantes**

- Carrichi Chávez José Manuel
  
  - Contacto: josemanuelcarrichi16@gmail.com

- Mendoza Sanchez Leslie Michell
  
  - Contacto:  mendoxa1239@gmail.com

- Salgado Mendoza Victor Manuel
  
  - Contacto: vicmanuel889@gmail.com

**Fecha de primera entrega:**

- 05/nov/2022

**Fecha de segunda entrega:**

- 11/12/2022

## Funcionalidades actuales del compilador:

El compilador entregado actualmente es capaz de realizar la comilación de una calculadora, y termina con la creación de un programa ejecutable.

- ### Análisis léxico:
  
  - El compilador es capaz de realizar una lectura desde un archivo de texto plano y realizará la detección de los elementos léxicos mediante la comprobación de patrones declarados. Los lexemas que es capaz de detectar son los siguientes:
    
    - Números enteros (NE)
    
    - Números decimales (ND)
    
    - Números exponenciales (NEX)
    
    - Identifficadores (ID)
    
    - Operadores aritméticos con jerarquía
      
      - Primer nivel: Correspondiente a multiplicación y división (OA1)
      
      - Segundo nivel:  Correspondiente a los signos de suma y resta (OA2)
    
    - Opeadores relacionales (OR)
    
    - Operadores lógicos (OL)
    
    - Signo de asignación

- ### Análisis sintáctico:
  
  - El compilador es capaz de realizar consultas a la tabla de símbolos para identificar y comprobar la correcta sintaxis en base a las gramáticas establecidad correspondientes a:
    
    - Operaciones algebráicas

- ### Análisis semántico:
  
  - Realiza la identificación y correcta asiganción de tipos de datos en las operaciones algebráicas, desplegando las derivaciones realizadas en la etapa de análisis sintáctico, permitiendo conocer el tipo de dato que se opera.
  - El tipado de las variables se realiza según lo indique el usuario.
  - Se solicita el valor de cada una de las variables.

- ### Creación de codigo intermedio:
  
  - El programa realiza múltiples consultas a la tabla de símbolos para determinar el orden y jerarquía de las operaciones para realizar una códigicación de tres direcciones en notación posfija
  
  - Crea una tabla de variables temporales que permite identificar operandos, operadores y orden de resolución de las operaciones, se utiliza para generar el codigo de bajo nivel.

- ### Optimización de código intermedio:
  
  - Dado que se trata de una calcuadora compilada y todas las operaciones aritméticas son necesarias para obtener el resultado, el código intermedio no tiene suficiente relevancia, sin embargo, se optimiza el programa para realizar las operaciones por jerarquía de operadores.

- ### Generación de código objeto
  
  - El programa utiliza la tabla de varibles temporales para convertir el código de tres direcciones a código objeto, generando un ejecutable "ProgramaPrincipal.exe"

### Especificaciones técnicas:

- AMD A8 2.4 GHz, de 4 núcleos

- 8 GB de RAM

- Unidad SSD de 1 TB

- Sistema Windows 11 pro 21H2 de 64 bits

- Editor Visual Studio Code versión 1.74.0

- Compilador de C/C++ MinGW

## Nota importante:

La entrada del compilador debe estar escrita con espacios entre cada sentencia y debe tener una asignación a una variable, por ejemplo:

<pre><code> z = a + b * 4 / c - d</code></pre>

### Descargar ejecutable:
Para descargar el archivo ejecutable, utilice la liga de [aquí](https://github.com/JMCRH/Proyecto-Compilador/tree/main/Ejecutable)
