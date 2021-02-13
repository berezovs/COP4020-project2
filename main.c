#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Lexan.h"
#include "SymbolTable.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
    setFile(argv[1]);
    insert("begin", BEGIN);
    insert("end", END);
    insert(".", PERIOD);

    getFirstToken();

    if (match(BEGIN))
    {
        while (!isEndOfFile())
        {
            if(strcmp(getCurrentLexeme(), "end")==0)
                break;
            //printf("Matched begin \n");
            assignStatement();
            // int i = lookup("serghei");
            // printf("%d \n", i);}
        }
    }
    else
    {
        printf("Syntax error, 'begin' expected \n");
        return 0;
    }

    getFirstToken();
    if(!match('.')){
        printf("Period expected");
    }
    // printf("%s\n", idLexeme);
    // printf("%s \n", number);

    
}
