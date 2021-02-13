#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#define BEGIN 400
#define END 401
#define NOT_FOUND 404
#define FOUND 403
#define ID 300
#define NUM 301
#define PERIOD 299


void insert(char lexeme[] , int id);
void printLexemes();
int lookup(char lexeme[]);

#endif