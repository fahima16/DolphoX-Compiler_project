#include "symbol_table.h"

SymbolTable* create_symbol_table() {
    SymbolTable *table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->head = NULL;
    return table;
}

Symbol* insert_symbol(SymbolTable *table, const char *name, DataType type) {
    if (lookup_symbol(table, name) != NULL) {
        return NULL; // Already exists
    }

    Symbol *sym = (Symbol*)malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->type = type;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->is_initialized = 0;
    sym->next = table->head;
    table->head = sym;

    return sym;
}

Symbol* lookup_symbol(SymbolTable *table, const char *name) {
    Symbol *curr = table->head;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

const char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_BOOL: return "bool";
        default: return "unknown";
    }
}

void print_symbol_table(SymbolTable *table) {
    printf("\n=== Symbol Table ===\n");
    printf("%-15s %-10s %-10s\n", "Name", "Type", "Is Array");
    printf("-----------------------------------\n");
    Symbol *curr = table->head;
    while (curr) {
        printf("%-15s %-10s %-10s\n", 
               curr->name, 
               data_type_to_string(curr->type), 
               curr->is_array ? "Yes" : "No");
        curr = curr->next;
    }
}