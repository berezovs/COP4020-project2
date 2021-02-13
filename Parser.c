#include <stdio.h>
#include "Parser.h"
#include "Lexan.h"
#include "Globals.h"
#include "SymbolTable.h"

int lookahead;

void getFirstToken()
{
    lookahead = lexan();
    //printf("First token: %d\n", lookahead);
}

int match(int t)
{
    if (lookahead == t)
    {
        //printf("Matched: %d\n", lookahead);
        lookahead = lexan();

        return 1;
    }
    else
    {

        printf("Error on line: %d\n", getLineNumber());
        return 0;
    }
}

void assignStatement()
{
    match(ID);
    if (lookahead != '=')
    {
        printf("Expected assignment operator");
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