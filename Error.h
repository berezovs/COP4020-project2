#ifndef ERROR_H
#define ERROR_H
#define MISSING_BEGIN 600
#define MISSING_END 601
#define MISSING_ASSIGN_OPERATOR 602
#define ILLEGAL_IDENTIFIER 603
#define MISSING_CLOSING_PAR 604
#define MISSING_SEMICOLON 605
#define MISSING_PERIOD 606
#define ILLEGAL_REDEFINITION 607
#define UNDEFINED_VARIABLE 608

void setErrorCode(int code, int lineNo);
void printError();
int getErrorStatus();

#endif