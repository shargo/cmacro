#include <stdio.h>

enum TokType {
  Integer = 258,
  Real = 259,
  String = 260,
  Char = 261,
  Variable = 262, /* Since it's parsed by the lexer, technically a variable is a
                     kind of token. However, cmacro ensures variable tokens are
                     turned into variable objects, so a token with this type
                     won't appear anywhere beyond the initial lexing stage. */
  Operator = 263,
  Separator = 264
};

typedef enum { Token, Var, List } NodeType;
