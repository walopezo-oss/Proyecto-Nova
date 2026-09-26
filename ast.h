#ifndef AST_H
#define AST_H

typedef enum {
    AST_PROGRAMA,
    AST_LISTA,
    AST_DECLARACION,
    AST_ASIGNACION,
    AST_IMPRIMIR,
    AST_OPERACION,
    AST_IDENTIFICADOR,
    AST_ENTERO,
    AST_DECIMAL,
    AST_CADENA,
    AST_BOOLEANO,
    AST_TIPO,
    AST_SI,
    AST_MIENTRAS
} ASTType;

typedef struct ASTNode {
    ASTType tipo;
    char *valor;
    struct ASTNode *izquierda;
    struct ASTNode *derecha;
    struct ASTNode *extra;
} ASTNode;

ASTNode *ast_programa(ASTNode *declaraciones, ASTNode *sentencias);
ASTNode *ast_lista(ASTNode *lista, ASTNode *elemento);
ASTNode *ast_declaracion(ASTNode *tipo, char *id);
ASTNode *ast_asignacion(char *id, ASTNode *expresion);
ASTNode *ast_imprimir(ASTNode *expresion);
ASTNode *ast_operacion(char *operador, ASTNode *izquierda, ASTNode *derecha);
ASTNode *ast_identificador(char *id);
ASTNode *ast_entero(int valor);
ASTNode *ast_decimal(double valor);
ASTNode *ast_cadena(char *valor);
ASTNode *ast_booleano(int valor);
ASTNode *ast_tipo(char *tipo);
ASTNode *ast_si(ASTNode *condicion, ASTNode *entonces, ASTNode *sino);
ASTNode *ast_mientras(ASTNode *condicion, ASTNode *cuerpo);

void ast_imprimir_arbol(ASTNode *node, int nivel);

#endif
