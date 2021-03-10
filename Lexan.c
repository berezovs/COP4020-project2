#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Lexan.h"
#include "SymbolTable.h"
#include "Globals.h"
#include "Error.h"
int lineNumber = 1;
char number[WORDLENGTH];
char idLexeme[WORDLENGTH];
FILE *fp;
char ch;

int getLineNumber()
{
    return lineNumber;
}

void setFile(char file[])
{

    fp = fopen(file, "r");
}

int isEndOfFile()
{
    if (ch == EOF)
        return 1;
    else
        return 0;
}

char *getCurrentLexeme()
{
    return idLexeme;
}

int lexan()
{

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == ' ' || ch == '\t')
            continue;
        else if (ch == '\n')
        {
            lineNumber++;
            continue;
        }

        else if (ch == '~')
        {
            ignoreLine(ch, fp);
        }
        else if (isdigit(ch))
        {
            getNumber(ch, fp);
            return NUM;
        }
        else if (isalpha(ch))
        {
            getIdentifier(ch, fp);
            int type = lookup(idLexeme);
            if (type == NOT_FOUND)
            {
                insert(idLexeme, ID);
                return ID;
            }
            else
            {
                return type;
            }
        }
        else
        {
            return ch;
        }
    }
    return 0;
}

void getDeclarations()
{
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == ' ' || ch == '\t')
            continue;
        else if (ch == '\n')
        {
            lineNumber++;
            continue;
        }

        else if (ch == '~')
        {
            ignoreLine(ch, fp);
        }
        else if (isdigit(ch))
        {
            getNumber(ch, fp);
        }
        else if (isalpha(ch))
        {
            getIdentifier(ch, fp);
            if (strcmp(idLexeme, "int") == 0)
            {
                getVariables();
            }
            
        }
    }
    printLexemes();
}

void getVariables()
{

    while ((ch = fgetc(fp)) != ';')
    {
        if (isspace(ch))
            continue;
        getIdentifier(ch, fp);
        if (strcmp(idLexeme, ",") == 0)
            continue;

        if (lookup(idLexeme) == NOT_FOUND)
            insert(idLexeme, ID);
        else
        {
            setErrorCode(ILLEGAL_REDEFINITION, lineNumber);
            break;
        }
        //printf("%s\n", idLexeme);
    }

    // getIdentifier(ch, fp);
    // printf("%s\n", idLexeme);
    // getIdentifier(ch, fp);
    // printf("%s\n", idLexeme);
}

void getIdentifier(char chr, FILE *file)
{
    int count = 0;
    idLexeme[count++] = chr;
    char previous = 0;

    while (1)
    {

        chr = fgetc(file);
        if (isalpha(chr) || isdigit(chr) || chr == '_')
        {
            idLexeme[count++] = chr;
            if (previous == '_' && chr == '_')
            {
                setErrorCode(ILLEGAL_IDENTIFIER, getLineNumber());
            }
            previous = chr;
        }

        else
        {
            idLexeme[count] = '\0';
            if (idLexeme[count - 1] == '_')
            {
                setErrorCode(ILLEGAL_IDENTIFIER, getLineNumber());
                break;
            }

            ungetc(chr, file);
            break;
        }
    }
}

void getNumber(char ch, FILE *file)
{
    int count = 0;
    number[count++] = ch;
    while (1)
    {
        ch = fgetc(file);
        if (isdigit(ch))
        {
            number[count++] = ch;
        }
        else
        {
            number[count] = '\0';
            ungetc(ch, file);
            break;
        }
    }
}

void ignoreLine(char ch, FILE *file)
{
    while ((ch = fgetc(file)) != '\n')
    {
        continue;
    }
    ungetc(ch, file);
}
