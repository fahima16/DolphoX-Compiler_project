#include "symbol_table.h"
#include "parser/parser.tab.h"  


SymbolTable* create_symbol_table(void) {
    SymbolTable *table = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (table) {
        table->head = NULL;
        table->current_scope = 0;
    }
    return table;
}

void free_symbol_table(SymbolTable *table) {
    if (!table) return;
    Symbol *curr = table->head;
    while (curr) {
        Symbol *next = curr->next;
        free(curr->name);
        free(curr);
        curr = next;
    }
    free(table);
}

void enter_scope(SymbolTable *table) {
    if (table) {
        table->current_scope++;
    }
}

void exit_scope(SymbolTable *table) {
    if (!table || table->current_scope == 0) return;

    /* বর্তমান স্কোপ শেষ হলে সেই স্কোপের সব লোকাল ভেরিয়েবল ডিলিট করে দেওয়া */
    Symbol **curr = &(table->head);
    while (*curr) {
        if ((*curr)->scope_level == table->current_scope) {
            Symbol *temp = *curr;
            *curr = temp->next;
            free(temp->name);
            free(temp);
        } else {
            curr = &((*curr)->next);
        }
    }
    table->current_scope--;
}

Symbol* lookup_symbol_current_scope(SymbolTable *table, const char *name) {
    if (!table || !name) return NULL;

    Symbol *curr = table->head;
    while (curr) {
        if (strcmp(curr->name, name) == 0 && curr->scope_level == table->current_scope) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

/* যেকোনো সক্রিয় স্কোপে (Global + Local) ভেরিয়েবল খুঁজে বের করা */
Symbol* lookup_symbol(SymbolTable *table, const char *name) {
    if (!table || !name) return NULL;

    Symbol *curr = table->head;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

Symbol* insert_symbol(SymbolTable *table, const char *name, DataType type) {
    if (!table || lookup_symbol_current_scope(table, name) != NULL) {
        return NULL; /* একই স্কোপে রি-ডিক্লেয়ারেশন বা ইনভ্যালিড টেবিল */
    }

    Symbol *sym = (Symbol*)malloc(sizeof(Symbol));
    if (!sym) return NULL;

    sym->name = strdup(name);
    sym->type = type;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->is_initialized = 0;
    sym->scope_level = table->current_scope;
    sym->next = table->head;
    table->head = sym;

    return sym;
}

Symbol* insert_array_symbol(SymbolTable *table, const char *name, DataType type, int size) {
    Symbol *sym = insert_symbol(table, name, type);
    if (sym) {
        sym->is_array = 1;
        sym->array_size = size;
    }
    return sym;
}

DataType string_to_data_type(const char *type_str) {
    if (!type_str) return TYPE_UNKNOWN;
    if (strcmp(type_str, "int") == 0) return TYPE_INT;
    if (strcmp(type_str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(type_str, "double") == 0) return TYPE_DOUBLE;
    if (strcmp(type_str, "char") == 0) return TYPE_CHAR;
    if (strcmp(type_str, "string") == 0) return TYPE_STRING;
    if (strcmp(type_str, "bool") == 0) return TYPE_BOOL;
    return TYPE_UNKNOWN;
}

const char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT:    return "int";
        case TYPE_FLOAT:  return "float";
        case TYPE_DOUBLE: return "double";
        case TYPE_CHAR:   return "char";
        case TYPE_STRING: return "string";
        case TYPE_BOOL:   return "bool";
        default:          return "unknown";
    }
}

DataType token_to_data_type(int token) {
    /* parser.tab.h টোকেন ভ্যালু অনুযায়ী ম্যাপিং */
    switch (token) {
        case INT: return TYPE_INT;     /* INT টোকেনের ভ্যালু অনুসারে */
        case FLOAT: return TYPE_FLOAT;
        case DOUBLE: return TYPE_DOUBLE;
        case CHAR: return TYPE_CHAR;
        case STRING: return TYPE_STRING;
        case BOOL: return TYPE_BOOL;
        default:  return TYPE_UNKNOWN;
    }
}

void print_symbol_table(SymbolTable *table) {
    if (!table) return;

    printf("\n======================== SYMBOL TABLE ========================\n");
    printf("%-15s %-10s %-8s %-10s %-12s %-10s\n", "Name", "Type", "Scope", "Is Array", "Size", "Initialized");
    printf("--------------------------------------------------------------\n");

    Symbol *curr = table->head;
    while (curr) {
        printf("%-15s %-10s %-8d %-10s %-12d %-10s\n",
               curr->name,
               data_type_to_string(curr->type),
               curr->scope_level,
               curr->is_array ? "Yes" : "No",
               curr->array_size,
               curr->is_initialized ? "Yes" : "No");
        curr = curr->next;
    }
    printf("==============================================================\n\n");
}
