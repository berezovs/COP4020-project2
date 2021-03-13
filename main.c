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


    printf("Compiling %s\n", argv[1]);
    getNextToken();
    if(strcmp(getCurrentLexeme(), "begin")==0){
        getDeclarations();
        run();
    }
    else{
        setErrorCode(MISSING_BEGIN, getLineNumber());
    }
    
    if (getErrorStatus() == 1)
    {
        printError();
    }
    else
    {
       // printLexemes();
    }

    printf("\n\n");
    return 0;
}

