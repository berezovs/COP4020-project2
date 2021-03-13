#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "Lexan.h"
#include "Globals.h"
#include "SymbolTable.h"
#include "Error.h"

int lookahead;
int regCount = 0;
int reg_x = 0;
int reg_y = 0;
char LHS[WORDCOUNT];

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
        regCount = 0;
        printf("%s=R%d\n\n", LHS, regCount);

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
    strcpy(LHS, getCurrentLexeme());
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
        char operand = lookahead;
        match(lookahead);
        term();
        printf("R%d = R%d %c R%d\n", regCount - 2, regCount - 2, operand, regCount - 1);
        regCount--;
    }
}

void term()
{
    factor();
    while (lookahead == '*' || lookahead == '/')
    {
        char operand = lookahead;
        match(lookahead);
        factor();
        printf("R%d = R%d %c R%d\n", regCount - 2, regCount - 2, operand, regCount - 1);
        regCount--;
    }
}

void factor()
{
    if (lookahead == ID)
    {

        match(ID);

        printf("R%d=%s\n", regCount, getCurrentLexeme());

        regCount++;
    }
    else if (lookahead == NUM)
    {

        match(NUM);

        printf("R%d=%s\n", regCount, getCurrentNumber());

        regCount++;
    }
    else if (lookahead == '(')
    {
        match('(');
        expression();
        match(')');
    }
    else if (lookahead == NOT_FOUND)
    {
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
