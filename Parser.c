#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "Lexan.h"
#include "Globals.h"
#include "SymbolTable.h"
#include "Error.h"

int lookahead;

void run()
{

    while (!isEndOfFile())
    {
        if (strcmp(getCurrentLexeme(), "end") == 0)
        {
            break;
        }

        lookahead = lookup(getCurrentLexeme());

        assignStatement();

        if (getErrorStatus() == 1)
        {
            return;
        }
    }
    matchEnd();
}

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
        else if (t == '.')
        {
            setErrorCode(MISSING_PERIOD, getLineNumber());
        }
        else if (t == ID)
        {
            setErrorCode(UNDEFINED_VARIABLE, getLineNumber());
        }

        return 0;
    }
}

void assignStatement()
{
    if (!match(ID))
        return;

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
    else if(lookahead==NOT_FOUND){
        setErrorCode(UNDEFINED_VARIABLE, getLineNumber());
    }
    else
    {
        printf("Error occured");
    }
}

void matchEnd()
{
    if (strcmp(getCurrentLexeme(), "end") == 0)
    {
        lookahead = lexan();
        if (!match('.'))
        {
            setErrorCode(MISSING_PERIOD, getLineNumber());
            return;
        }
    }
    else if (match(END))
    {

        if (!match('.'))
        {
            setErrorCode(MISSING_PERIOD, getLineNumber());
            return;
        }
    }

    else
    {
        setErrorCode(MISSING_END, getLineNumber());
    }
}
