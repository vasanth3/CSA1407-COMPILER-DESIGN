#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of symbols
#define MAX_SYMBOLS 100

// Structure to represent a symbol
typedef struct {
    char name[50];
    int type;  // You can extend this to store additional information about the symbol
} Symbol;

// Structure to represent a symbol table
typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

// Function to initialize the symbol table
void initializeSymbolTable(SymbolTable *table) {
    table->count = 0;
}

// Function to insert a symbol into the symbol table
void insertSymbol(SymbolTable *table, char *name, int type) {
    if (table->count < MAX_SYMBOLS) {
        strcpy(table->symbols[table->count].name, name);
        table->symbols[table->count].type = type;
        table->count++;
        printf("Symbol '%s' inserted into the symbol table.\n", name);
    } else {
        printf("Symbol table is full. Cannot insert symbol '%s'.\n", name);
    }
}

// Function to search for a symbol in the symbol table
int i;
int searchSymbol(SymbolTable *table, char *name) {
    for (i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

// Function to display the contents of the symbol table
void displaySymbolTable(SymbolTable *table) {
    printf("Symbol Table:\n");
    printf("-------------\n");
    for (i = 0; i < table->count; i++) {
        printf("Name: %s, Type: %d\n", table->symbols[i].name, table->symbols[i].type);
    }
}

int main() {
    SymbolTable table;
    initializeSymbolTable(&table);

    // Sample operations
    insertSymbol(&table, "x", 0); // Inserting a symbol "x" of type 0
    insertSymbol(&table, "y", 1); // Inserting a symbol "y" of type 1
    insertSymbol(&table, "z", 0); // Inserting a symbol "z" of type 0

    displaySymbolTable(&table);

    char searchName[50];
    printf("Enter a symbol to search: ");
    scanf("%s", searchName);
    int index = searchSymbol(&table, searchName);
    if (index != -1) {
        printf("Symbol '%s' found at index %d.\n", searchName, index);
    } else {
        printf("Symbol '%s' not found in the symbol table.\n", searchName);
    }

    return 0;
}

