#include <stdio.h>
#include "Parser.h"
#include "Lexan.h"
#include "Globals.h"
#include "SymbolTable.h"
#include "Error.h"

int lookahead;

void getNextToken()
{
    lookahead = lexan();
}

int match(int t)
{
    if (lookahead == t)
    {
        lookahead = lexan();

        return 1;
    }
    else
    {

        if (t == BEGIN)
        {
            setErrorCode(MISSING_BEGIN, getLineNumber());
        }
        else if (t == END)
        {
            setErrorCode(MISSING_END, getLineNumber());
        }
        else if (t == ')')
        {
            setErrorCode(MISSING_CLOSING_PAR, getLineNumber());
        }
        else if(t=='.'){
            setErrorCode(MISSING_PERIOD, getLineNumber());
        }

        return 0;
    }
}

void assignStatement()
{
    match(ID);
    if (lookahead != '=')
    {
        setErrorCode(MISSING_ASSIGN_OPERATOR, getLineNumber());
    }
    else
    {
        match(lookahead);
        expression();
        match(';');
    }
}

void expression()
{
    term();
    while (lookahead == '+' || lookahead == '-')
    {
        match(lookahead);
        term();
    }
}

void term()
{
    factor();
    while (lookahead == '*' || lookahead == '/')
    {
        match(lookahead);
        factor();
    }
}

void factor()
{
    if (lookahead == ID)
    {
        match(ID);
    }
    else if (lookahead == NUM)
    {
        match(NUM);
    }
    else if (lookahead == '(')
    {
        match('(');
        expression();
        match(')');
    }
    else
    {
        printf("Error occured");
    }
}