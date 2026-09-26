#include <stdio.h>
#include <string.h>
#include "symbol_table.h"

static Symbol tabla[MAX_SYMBOLS];
static int cantidad = 0;

void symbol_init(void)
{
    cantidad = 0;
}

int symbol_exists(const char *nombre)
{
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(tabla[i].nombre, nombre) == 0)
            return 1;
    }

    return 0;
}

int symbol_insert(const char *nombre, const char *tipo)
{
    if (symbol_exists(nombre)) {
        printf("Error semántico: variable '%s' ya declarada\n", nombre);
        return 0;
    }

    if (cantidad >= MAX_SYMBOLS) {
        printf("Error: tabla de símbolos llena\n");
        return 0;
    }

    snprintf(tabla[cantidad].nombre, sizeof(tabla[cantidad].nombre), "%s", nombre);
    snprintf(tabla[cantidad].tipo, sizeof(tabla[cantidad].tipo), "%s", tipo);
    cantidad++;

    return 1;
}

void symbol_print(void)
{
    printf("\n===== TABLA DE SIMBOLOS =====\n");
    printf("%-20s %-20s\n", "NOMBRE", "TIPO");
    printf("----------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        printf("%-20s %-20s\n", tabla[i].nombre, tabla[i].tipo);
    }

    printf("=============================\n");
}
