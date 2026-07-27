#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_UNKNOWN
} DataType;

typedef struct Symbol {
    char *name;
    DataType type;
    int is_array;
    int array_size;
    int is_initialized;
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *head;
} SymbolTable;

SymbolTable* create_symbol_table();
Symbol* insert_symbol(SymbolTable *table, const char *name, DataType type);
Symbol* lookup_symbol(SymbolTable *table, const char *name);
void print_symbol_table(SymbolTable *table);
const char* data_type_to_string(DataType type);

#endif