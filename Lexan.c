#include <stdio.h>
#include <ctype.h>
#include "Lexan.h"
#include "SymbolTable.h"
int lineNumber = 1;
char number[wordlength];
char idLexeme[wordlength];
FILE *fp;
char ch;

int getLineNumber(){
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

char* getCurrentLexeme(){
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
    printf("End of file");
    return 0;
}

void getIdentifier(char ch, FILE *file)
{
    int count = 0;
    idLexeme[count++] = ch;
    char previous = 0;

    while (1)
    {

        ch = fgetc(file);
        if (isalpha(ch) || isdigit(ch) || ch == '_')
        {
            idLexeme[count++] = ch;
            if (previous == '_' && ch == '_')
            {
                printf("%s %d %s\n", "error on line", lineNumber, "illegal identifier\n");
            }
            previous = ch;
        }

        else
        {
            idLexeme[count] = '\0';
            if (idLexeme[count - 1] == '_')
            {
                printf("%s %d %s\n", "error on line", lineNumber, "illegal identifier\n");
            }

            ungetc(ch, file);
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
