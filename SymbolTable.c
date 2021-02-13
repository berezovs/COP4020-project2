#include <string.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "Globals.h"

int counter = 0;

struct symbol
{
    int id;
    char lexeme[WORDLENGTH];
};

struct symbol table[WORDCOUNT];

void insert(char lexeme[], int id)
{
    struct symbol entry;
    entry.id = id;
    strcpy(entry.lexeme, lexeme);
    table[counter++] = entry;
}

int lookup(char lexeme[])
{
    for (int i = 0; i <= counter; ++i)
    {
        if (strcmp(table[i].lexeme, lexeme)==0)
        {
            return table[i].id;
        }
    }
    return NOT_FOUND;
}

void printLexemes()
{
    for (int i = 0; i <= counter; ++i)
    {
        if (table[i].id == ID)
        {
            printf("\"%s\" ", table[i].lexeme);
        }
    }
}