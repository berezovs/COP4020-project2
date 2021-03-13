#ifndef PARSER_H
#define PARSER_H
    void getNextToken();
    void assignStatement();
    void expression();
    void term();
    void factor();
    int match(int t);
    void matchEnd();
    void addToPostfix(char lexeme[]); 
    void run();
#endif

