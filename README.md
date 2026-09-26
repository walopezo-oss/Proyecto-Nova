# Compilador Nova - Entrega Parcial Semana 11

## Descripción

Este proyecto implementa el front-end inicial del lenguaje Nova.

Incluye:

- Análisis léxico con Flex.
- Análisis sintáctico con Bison.
- Integración Flex + Bison.
- Construcción de un AST inicial.
- Tabla de símbolos básica.
- Prueba de un programa válido.
- Prueba de un programa inválido.
- Instrucciones de compilación y ejecución.

## Estructura del proyecto

- `lexer.l`: analizador léxico.
- `parser.y`: gramática de Bison.
- `ast.h`: definición del AST.
- `ast.c`: implementación del AST.
- `symbol_table.h`: definición de la tabla de símbolos.
- `symbol_table.c`: implementación de la tabla de símbolos.
- `main.c`: programa principal.
- `programa_valido.nova`: prueba válida.
- `programa_invalido.nova`: prueba inválida.
- `Makefile`: automatiza la compilación.

## Requisitos

Se necesita:

- GCC
- Flex
- Bison
- Make

En Linux/WSL, por ejemplo, se pueden instalar con:

```bash
sudo apt update
sudo apt install gcc flex bison make
```

## Compilación

Abrir una terminal dentro de la carpeta del proyecto y ejecutar:

```bash
make
```

Esto generará el ejecutable:

```text
nova
```

## Ejecución de la prueba válida

Linux/WSL:

```bash
./nova programa_valido.nova
```

Windows usando un entorno compatible con Make/GCC:

```bash
nova.exe programa_valido.nova
```

## Ejecución de la prueba inválida

Linux/WSL:

```bash
./nova programa_invalido.nova
```

El archivo contiene errores sintácticos, por lo que Bison debe reportar un error.

## Compilación manual

También se puede compilar sin Make:

```bash
bison -d parser.y
flex lexer.l
gcc -Wall -Wextra -std=c11 -c ast.c
gcc -Wall -Wextra -std=c11 -c symbol_table.c
gcc -Wall -Wextra -std=c11 -c main.c
gcc -Wall -Wextra -std=c11 parser.tab.c lex.yy.c ast.o symbol_table.o main.o -o nova
```

Después:

```bash
./nova programa_valido.nova
```

## Flujo del compilador

```text
Archivo Nova
     |
     v
   Flex
     |
     v
   Tokens
     |
     v
   Bison
     |
     v
 AST inicial
     |
     v
Tabla de símbolos
```

## Construcciones soportadas

### Tipos

```text
entero
decimal
texto
booleano
```

### Variables

```text
entero edad;
texto nombre;
decimal promedio;
booleano activo;
```

### Asignaciones

```text
edad = 20;
nombre = "Wesley";
```

### Impresión

```text
imprimir(edad);
```

### Condicional

```text
si edad > 18 entonces
    imprimir("Mayor");
sino
    imprimir("Menor");
fin
```

### Ciclo

```text
mientras edad < 25 hacer
    edad = edad + 1;
fin
```

## Entrega parcial Semana 11

- [X] Archivo Flex funcional.
- [X] Archivo Bison funcional.
- [X] Integración Flex + Bison.
- [X] AST inicial para construcciones principales.
- [X] Tabla de símbolos básica.
- [X] Programa válido.
- [X] Programa inválido.
- [X] README con instrucciones.
