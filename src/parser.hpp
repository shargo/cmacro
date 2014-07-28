#include "ast.h"

extern int yylex();
extern FILE* yyin;
extern char *yytext;
extern int yylineno;

Node* nextToken(void);
Node* parseTokens(char* delim);
Node* parse(FILE* stream);
