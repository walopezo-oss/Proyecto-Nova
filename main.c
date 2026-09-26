#include <stdio.h>
#include "ast.h"
#include "symbol_table.h"
#include "parser.tab.h"

extern FILE *yyin;
extern ASTNode *root;

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Uso: %s archivo.nova\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin) {
        printf("No se pudo abrir el archivo: %s\n", argv[1]);
        return 1;
    }

    symbol_init();

    printf("====================================\n");
    printf("          COMPILADOR NOVA\n");
    printf("====================================\n");
    printf("\nAnalizando archivo: %s\n\n", argv[1]);

    if (yyparse() == 0) {
        printf("Analisis sintactico correcto.\n");

        printf("\n===== AST INICIAL =====\n");
        if (root != NULL)
            ast_imprimir_arbol(root, 0);

        symbol_print();

        printf("\nCompilacion finalizada correctamente.\n");
    } else {
        printf("\nLa compilacion termino con errores.\n");
    }

    fclose(yyin);
    return 0;
}
