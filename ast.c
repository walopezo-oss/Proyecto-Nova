#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static ASTNode *crear(ASTType tipo, char *valor,
                      ASTNode *izquierda,
                      ASTNode *derecha,
                      ASTNode *extra)
{
    ASTNode *n = malloc(sizeof(ASTNode));
    if (!n) {
        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
        exit(EXIT_FAILURE);
    }

    n->tipo = tipo;
    n->valor = valor ? strdup(valor) : NULL;
    n->izquierda = izquierda;
    n->derecha = derecha;
    n->extra = extra;

    return n;
}

ASTNode *ast_programa(ASTNode *declaraciones, ASTNode *sentencias)
{
    return crear(AST_PROGRAMA, "programa", declaraciones, sentencias, NULL);
}

ASTNode *ast_lista(ASTNode *lista, ASTNode *elemento)
{
    return crear(AST_LISTA, "lista", lista, elemento, NULL);
}

ASTNode *ast_declaracion(ASTNode *tipo, char *id)
{
    return crear(AST_DECLARACION, id, tipo, NULL, NULL);
}

ASTNode *ast_asignacion(char *id, ASTNode *expresion)
{
    return crear(AST_ASIGNACION, id, expresion, NULL, NULL);
}

ASTNode *ast_imprimir(ASTNode *expresion)
{
    return crear(AST_IMPRIMIR, "imprimir", expresion, NULL, NULL);
}

ASTNode *ast_operacion(char *operador, ASTNode *izquierda, ASTNode *derecha)
{
    return crear(AST_OPERACION, operador, izquierda, derecha, NULL);
}

ASTNode *ast_identificador(char *id)
{
    return crear(AST_IDENTIFICADOR, id, NULL, NULL, NULL);
}

ASTNode *ast_entero(int valor)
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d", valor);
    return crear(AST_ENTERO, buffer, NULL, NULL, NULL);
}

ASTNode *ast_decimal(double valor)
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%f", valor);
    return crear(AST_DECIMAL, buffer, NULL, NULL, NULL);
}

ASTNode *ast_cadena(char *valor)
{
    return crear(AST_CADENA, valor, NULL, NULL, NULL);
}

ASTNode *ast_booleano(int valor)
{
    return crear(AST_BOOLEANO, valor ? "verdadero" : "falso", NULL, NULL, NULL);
}

ASTNode *ast_tipo(char *tipo)
{
    return crear(AST_TIPO, tipo, NULL, NULL, NULL);
}

ASTNode *ast_si(ASTNode *condicion, ASTNode *entonces, ASTNode *sino)
{
    return crear(AST_SI, "si", condicion, entonces, sino);
}

ASTNode *ast_mientras(ASTNode *condicion, ASTNode *cuerpo)
{
    return crear(AST_MIENTRAS, "mientras", condicion, cuerpo, NULL);
}

static void espacios(int nivel)
{
    for (int i = 0; i < nivel; i++)
        printf("  ");
}

void ast_imprimir_arbol(ASTNode *node, int nivel)
{
    if (!node)
        return;

    espacios(nivel);
    printf("%s\n", node->valor ? node->valor : "nodo");

    ast_imprimir_arbol(node->izquierda, nivel + 1);
    ast_imprimir_arbol(node->derecha, nivel + 1);
    ast_imprimir_arbol(node->extra, nivel + 1);
}
