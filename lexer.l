%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%option noyywrap
%option yylineno

DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*

%%

"entero"        { return ENTERO; }
"decimal"       { return DECIMAL; }
"texto"         { return TEXTO; }
"booleano"      { return BOOLEANO; }

"si"            { return SI; }
"entonces"      { return ENTONCES; }
"sino"          { return SINO; }
"fin"           { return FIN; }
"mientras"      { return MIENTRAS; }
"hacer"         { return HACER; }
"imprimir"      { return IMPRIMIR; }

"verdadero"     { return VERDADERO; }
"falso"         { return FALSO; }

"=="            { return IGUAL; }
"!="            { return DIFERENTE; }
"<="            { return MENOR_IGUAL; }
">="            { return MAYOR_IGUAL; }
"&&"            { return Y; }
"||"            { return O; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"="             { return '='; }
"<"             { return '<'; }
">"             { return '>'; }

"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
";"             { return ';'; }

{DIGITO}+"."{DIGITO}+ {
    yylval.decimal = atof(yytext);
    return NUM_DECIMAL;
}

{DIGITO}+ {
    yylval.entero = atoi(yytext);
    return NUM_ENTERO;
}

\"([^\"\\]|\\.)*\" {
    yylval.texto = strdup(yytext);
    return CADENA;
}

{ID} {
    yylval.texto = strdup(yytext);
    return ID;
}

[ \t\r]+  { }
\n        { }
"//".*    { }

. {
    printf("Error léxico en línea %d: carácter '%s'\n", yylineno, yytext);
}

%%
