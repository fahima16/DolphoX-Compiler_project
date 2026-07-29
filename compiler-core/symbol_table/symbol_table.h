#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_UNKNOWN
} DataType;

typedef struct Symbol {
    char *name;
    DataType type;
    int is_array;
    int array_size;
    int is_initialized;
    int scope_level;            
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *head;
    int current_scope;
} SymbolTable;


SymbolTable* create_symbol_table(void);
void free_symbol_table(SymbolTable *table);

void enter_scope(SymbolTable *table);
void exit_scope(SymbolTable *table);

/* Insertion & Lookup */
Symbol* insert_symbol(SymbolTable *table, const char *name, DataType type);
Symbol* insert_array_symbol(SymbolTable *table, const char *name, DataType type, int size);
Symbol* lookup_symbol(SymbolTable *table, const char *name);
Symbol* lookup_symbol_current_scope(SymbolTable *table, const char *name);

/* Helpers & Utilities */
DataType string_to_data_type(const char *type_str);
const char* data_type_to_string(DataType type);
void print_symbol_table(SymbolTable *table);

DataType token_to_data_type(int token);

#endif