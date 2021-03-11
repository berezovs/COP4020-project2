#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Lexan.h"
#include "SymbolTable.h"
#include "Parser.h"
#include "Error.h"
#include "Globals.h"


int main(int argc, char *argv[])
{
    setFile(argv[1]);
    insert("begin", BEGIN);
    insert("end", END);
    insert(";", SEMICOLON);
    insert(".", PERIOD);
    insert("int", INT);
    insert("=", EQUAL_SIGN);

    getNextToken();
    if(strcmp(getCurrentLexeme(), "begin")==0){
        getDeclarations();
        run();
    }
    
    if (getErrorStatus() == 1)
    {
        printError();
    }
    else
    {
        printf("Success \t\n");
        printLexemes();
    }

    printf("\n\n");
    return 0;
}

