
#ifndef LEXAN_H
#define LEXAN_H

#define wordlength 50

void setFile(char file[]);
int isEndOfFile();
int lexan();
int getLineNumber();
void getIdentifier(char ch, FILE *file);
void getNumber(char ch, FILE *file);
void ignoreLine(char ch, FILE *file);
char* getCurrentLexeme();

#endif