%code requires {
#include "ast.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symbol_table.h"

int yylex(void);
void yyerror(const char *s);

ASTNode *root = NULL;
%}

%union {
    int entero;
    double decimal;
    char *texto;
    ASTNode *node;
}

%token ENTERO DECIMAL TEXTO BOOLEANO
%token SI ENTONCES SINO FIN
%token MIENTRAS HACER
%token IMPRIMIR
%token VERDADERO FALSO
%token IGUAL DIFERENTE MENOR_IGUAL MAYOR_IGUAL
%token Y O

%token <entero> NUM_ENTERO
%token <decimal> NUM_DECIMAL
%token <texto> ID
%token <texto> CADENA

%type <node> programa declaraciones declaracion sentencia sentencias
%type <node> asignacion impresion expresion termino factor condicion
%type <node> bloque_si bloque_mientras tipo

%left O
%left Y
%left IGUAL DIFERENTE
%left '<' '>' MENOR_IGUAL MAYOR_IGUAL
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

programa:
    declaraciones sentencias
    {
        root = ast_programa($1, $2);
        $$ = root;
    }
    ;

declaraciones:
      /* vacío */
      { $$ = NULL; }
    | declaraciones declaracion
      { $$ = ast_lista($1, $2); }
    ;

declaracion:
      tipo ID ';'
      {
          symbol_insert($2, $1->valor);
          $$ = ast_declaracion($1, $2);
      }
    ;

tipo:
      ENTERO   { $$ = ast_tipo("entero"); }
    | DECIMAL  { $$ = ast_tipo("decimal"); }
    | TEXTO    { $$ = ast_tipo("texto"); }
    | BOOLEANO { $$ = ast_tipo("booleano"); }
    ;

sentencias:
      /* vacío */
      { $$ = NULL; }
    | sentencias sentencia
      { $$ = ast_lista($1, $2); }
    ;

sentencia:
      asignacion { $$ = $1; }
    | impresion { $$ = $1; }
    | bloque_si { $$ = $1; }
    | bloque_mientras { $$ = $1; }
    ;

asignacion:
      ID '=' expresion ';'
      {
          if (!symbol_exists($1))
              printf("Error semántico: variable '%s' no declarada\n", $1);
          $$ = ast_asignacion($1, $3);
      }
    ;

impresion:
      IMPRIMIR '(' expresion ')' ';'
      { $$ = ast_imprimir($3); }
    ;

bloque_si:
      SI condicion ENTONCES sentencias FIN
      { $$ = ast_si($2, $4, NULL); }
    | SI condicion ENTONCES sentencias SINO sentencias FIN
      { $$ = ast_si($2, $4, $6); }
    ;

bloque_mientras:
      MIENTRAS condicion HACER sentencias FIN
      { $$ = ast_mientras($2, $4); }
    ;

condicion:
      expresion { $$ = $1; }
    ;

expresion:
      expresion '+' termino { $$ = ast_operacion("+", $1, $3); }
    | expresion '-' termino { $$ = ast_operacion("-", $1, $3); }
    | expresion '*' termino { $$ = ast_operacion("*", $1, $3); }
    | expresion '/' termino { $$ = ast_operacion("/", $1, $3); }
    | expresion IGUAL termino { $$ = ast_operacion("==", $1, $3); }
    | expresion DIFERENTE termino { $$ = ast_operacion("!=", $1, $3); }
    | expresion '<' termino { $$ = ast_operacion("<", $1, $3); }
    | expresion '>' termino { $$ = ast_operacion(">", $1, $3); }
    | expresion MENOR_IGUAL termino { $$ = ast_operacion("<=", $1, $3); }
    | expresion MAYOR_IGUAL termino { $$ = ast_operacion(">=", $1, $3); }
    | expresion Y termino { $$ = ast_operacion("&&", $1, $3); }
    | expresion O termino { $$ = ast_operacion("||", $1, $3); }
    | termino { $$ = $1; }
    ;

termino:
      factor { $$ = $1; }
    ;

factor:
      NUM_ENTERO { $$ = ast_entero($1); }
    | NUM_DECIMAL { $$ = ast_decimal($1); }
    | CADENA { $$ = ast_cadena($1); }
    | ID
      {
          if (!symbol_exists($1))
              printf("Error semántico: variable '%s' no declarada\n", $1);
          $$ = ast_identificador($1);
      }
    | VERDADERO { $$ = ast_booleano(1); }
    | FALSO { $$ = ast_booleano(0); }
    | '(' expresion ')' { $$ = $2; }
    | '-' factor %prec UMINUS
      { $$ = ast_operacion("-", ast_entero(0), $2); }
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "Error sintáctico: %s\n", s);
}
