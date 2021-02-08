#include <stdio.h>
#include <ctype.h>
#define wordlength 50

int filename = 1;
int lineNumber = 1;
char number[wordlength];
char idLexeme[wordlength];

FILE *getFile(char file[]);
int lexan(FILE *file);
void getIdentifier(char ch, FILE *file);
void getNumber(char ch, FILE *file);
void ignoreLine(char ch, FILE *file);

int main(int argc, char *argv[])
{
    FILE *file = getFile(argv[filename]);
    lexan(file);
    lexan(file);
    printf("%s\n", idLexeme);
    printf("%s \n", number);
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
        else if (ch == '~')
        {
            ignoreLine(ch, file);
        }
        else if (isdigit(ch))
        {
            getNumber(ch, file);
        }
        else if (isalpha(ch))
        {
            getIdentifier(ch, file);
            break;
        }
    }
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
            previous = ch;
            if (previous == '_')
            {
                printf("%s %d %s\n", "error on line", lineNumber, "illegal identifier");
                break;
            }
        }

        else
        {
            idLexeme[count] = '\0';
            if (idLexeme[count - 1] == '_')
            {
                printf("%s %d %s\n", "error on line", lineNumber, "illegal identifier");
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
