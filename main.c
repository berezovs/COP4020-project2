#include <stdio.h>
#include <ctype.h>
#define wordlength 50

int filename = 1;
int lineNumber = 1;
char idLexeme[wordlength];

FILE *getFile(char file[]);
int lexan(FILE *file);
void getLexeme(char ch, FILE *file);

int main(int argc, char *argv[])
{
    FILE *file = getFile(argv[filename]);
    lexan(file);
    printf("%s\n", idLexeme);
}

FILE *getFile(char file[])
{
    FILE *fp;
    fp = fopen(file, "r");
    return fp;
}

int lexan(FILE *file)
{
    char ch;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ' ' || ch == '\t')
            continue;
        else if (ch == '\n')
            lineNumber++;
        else if (isalpha(ch))
        {
            getLexeme(ch, file);
        }
    }
    return 0;
}

void getLexeme(char ch, FILE *file)
{
    int count = 0;
    idLexeme[count++]=ch;
    char previous=0;

    while (1)
    {

        ch = fgetc(file);
        if (isalpha(ch) || isdigit(ch) || ch == '_')
        {
            idLexeme[count++] = ch;
            previous = ch;
        }
        else if(previous=='_'){
            printf("%s %d %s\n", "error on line", lineNumber, "illegal identifier");
            break;
        }
        else
        {
            idLexeme[count] = '\0';
            ungetc(ch, file);
            break;
        }
    }
}