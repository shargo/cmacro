#include "ast.hpp"

Node* makeToken(char* text, TokenType type, uInt line) {
  assert(text);
  Node* node = malloc(sizeof(Node));
  size_t len = strlen(text);
  Token tok;
  tok.type = type;
  tok.text = malloc(sizeof(char)*len + 1);
  strncpy(tok.text, text, len);
  node->type = TOKEN;
  tok(node) = tok;
  node->line = line;
  return node;
}

Node* makeEmptyList(void) {
  Node* node = malloc(sizeof(Node));
  node->type = LIST;
  node->line = 0;
  list(node).data = NULL;
  list(node).length = 0;
  list(node).cap = 0;
  return node;
}

void addToList(Node* list, Node* node) {
  if(list(list).data == NULL) {
    /* Create */
    list(list).data = malloc(sizeof(Node*)*NODE_LIST_CHUNK_SIZE);
    list(list).cap = NODE_LIST_CHUNK_SIZE;
    list(list).length = 1;
    list(list).data[0] = node;
  }
  else {
    /* Resize */
    if(list(list).length+1 == list(list).cap) {
      list(list).cap += NODE_LIST_CHUNK_SIZE;
      list(list).data = realloc(list(list).data, list(list).cap*sizeof(Node*));
    }
    list(list).data[list(list).length] = node;
    list(list).length++;
  }
}

int eqstr(char* a, char* b) {
  return strcmp(a, b) == 0;
}

int eqtok(Node* tok, char* str) {
  return eqstr(tok(tok).text, str);
}

void printNode(Node* node, FILE* stream, int indent) {
  for(int i = 0; i < indent; i++)
    putc(' ', stream);
  if(node) {
    switch(node->type) {
      case TOKEN:
        fprintf(stream, "%s", tok(node).text);
        break;
      case VARIABLE:
        fprintf(stream, "$(%s)", var(node).text);
        break;
      case LIST:
        putc('\n', stream);
        for(size_t index = 0; index < list(node).length; index++) {
          printNode(list(node).data[index], stream, indent+2);
          putc(' ', stream);
        }
        break;
    }
  }
  else
    fprintf(stream, "(null)");
}

void freeNode(Node* node) {
  if(node) {
    switch(node->type) {
      case TOKEN:
        free(tok(node).text);
        break;
      case VARIABLE:
        free(var(node).text);
        /* TODO: Free the qualifiers list */
        break;
      case LIST:
        break;
    }
    free(node);
  }
}
