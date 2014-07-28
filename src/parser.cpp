#include "parser.hpp"

Node* nextToken(void) {
  TokenType type = (TokenType)yylex();
  if(type)
    return makeToken(yytext, type, (uInt)yylineno);
  else
    return NULL;
}

Node* parseTokens(char* delim) {
  Node* token = nextToken();
  Node* list = makeEmptyList();
  while(token && (delim ? !eqtok(token, delim) : 1)) {
    Node* result = NULL;
    if(eqtok(token, "(")) {
      result = parseTokens(")");
    }
    else if(eqtok(token, "[")) {
      result = parseTokens("]");
    } else if(eqtok(token, "{")) {
      result = parseTokens("}");
    } else {
      result = token;
    }
    addToList(list, result);
    token = nextToken();
  }
  return list;
}

Node* parse(FILE* stream) {
  assert(stream);
  yyin = stream;
  Node* parsed = parseTokens(NULL);
  yyin = NULL;
  return parsed;
}
