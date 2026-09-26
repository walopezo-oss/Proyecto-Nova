#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SYMBOLS 100

typedef struct {
    char nombre[50];
    char tipo[20];
} Symbol;

void symbol_init(void);
int symbol_insert(const char *nombre, const char *tipo);
int symbol_exists(const char *nombre);
void symbol_print(void);

#endif
