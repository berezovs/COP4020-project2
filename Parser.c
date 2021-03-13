#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "Lexan.h"
#include "Globals.h"
#include "SymbolTable.h"
#include "Error.h"

int lookahead;
int regCount = 0;
char LHS[WORDLENGTH];
char postfix[WORDLENGTH];
int position = 0;

void run()
{

    while (!isEndOfFile())
    {
        if (strcmp(getCurrentLexeme(), "end") == 0)
        {
            break;
        }
        position = 0;
        lookahead = lookup(getCurrentLexeme());
        assignStatement();
        regCount = 0;
        postfix[position] = '\0';
        printf("%s = R%d\n", LHS, regCount);
        
        if (getErrorStatus() == 1)
        {
            return;
        }
        else
        {
            printf("*****[%s]*****\n\n", postfix);
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
        postfix[position++] = operand;
        postfix[position++]=',';
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
        postfix[position++] = operand;
        postfix[position++]=',';
        printf("R%d = R%d %c R%d\n", regCount - 2, regCount - 2, operand, regCount - 1);
        regCount--;
    }
}

void factor()
{
    if (lookahead == ID)
    {

        match(ID);
        addToPostfix(getCurrentLexeme());
        printf("R%d = %s\n", regCount, getCurrentLexeme());

        regCount++;
    }
    else if (lookahead == NUM)
    {

        match(NUM);
        addToPostfix(getCurrentNumber());
        printf("R%d = %s\n", regCount, getCurrentNumber());

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

void addToPostfix(char lexeme[])
{
    int size  = strlen(lexeme);
    for(int i= 0; i<size; i++){
        postfix[position++] = lexeme[i];
        
    }
    postfix[position++] = ',';
}
