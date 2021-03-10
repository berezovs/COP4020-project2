#include <stdio.h>
#include "Error.h"
#include "Globals.h"

int errorCode = -1;
int errorStatus = 0;
int lNumber = 0;

void setErrorCode(int code, int lineNo)
{
    errorCode = code;
    errorStatus = 1;
    lNumber = lineNo;
}
void printError()
{
    switch (errorCode)
    {
    case MISSING_BEGIN:
        printf("Syntax error: expected 'begin' on line %d\n", lNumber);
        break;
    case MISSING_END:
        printf("Syntax error: expected 'end' on line %d\n", lNumber);
        break;
    case MISSING_ASSIGN_OPERATOR:
        printf("Syntax error: expected '=' on line %d\n", lNumber);
        break;
    case ILLEGAL_IDENTIFIER:
        printf("Syntax error: illegal identifier on line %d\n", lNumber);
        break;
    case MISSING_CLOSING_PAR:
        printf("Syntax error: expected ')' on line %d\n", lNumber);
        break;
    case MISSING_PERIOD:
        printf("Syntax error: expected '.' on line %d\n", lNumber);
        break;
    case ILLEGAL_REDEFINITION:
        printf("Syntax error: illegal variable redefinition on line %d\n", lNumber);
        break;
    default:
        printf("Syntax error: unexpected token on line %d\n", lNumber);
    }
}
int getErrorStatus()
{
    return errorStatus;
}