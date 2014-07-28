%e  1019
%p  2807
%n  371
%k  284
%a  1213
%o  1117

WHITESPACE   [ \t\v\n\f]

OCTAL_DIGIT  [0-7]
HEX_DIGIT    [a-fA-F0-9]
DEC_DIGIT    [0-9]

INT_SUFFIX   (l|L|u|U)
FLOAT_SUFFIX (f|F|l|L)

OCTAL        (0{OCTAL_DIGIT}+)
HEX          ([xX]{HEX_DIGIT}+)
DEC          ({DEC_DIGIT}+)

SIGN         [+-]

INTEGER      ({SIGN}?({OCTAL}|{HEX}|{DEC}))
REAL         ({SIGN}?{DEC}\.[eE]?{SIGN}?{DEC})

STR_PREFIX   (u8|u|U|L)
STR_CHAR     [^\"]
STRING       ({STR_PREFIX}?\"{STR_CHAR}*\")

// This is naive but w/e
CHAR_CONTENT [^\']
CHAR         ({STR_PREFIX}?\'{CHAR_CONTENT}*\')

IDENT_CHAR   [a-zA-Z0-9_]
IDENTIFIER   ({ALPHANUMERIC}+)

VAR_CHAR     [^\(\)]
VARIABLE     (\$\({VAR_CHAR}\)+)

OP_CHAR      [^ \t\v\n\f\,\;\(\)\[\]\{\}\.a-zA-Z_0-9]
OP           ({OP_CHAR}+)

SEPARATOR    [\,\;\(\)\[\]\{\}\.]


%{
#include "ast.hpp"
%}

%%

INTEGER   { return Integer; }
REAL      { return Real; }
STRING    { return String; }
CHAR      { return Char; }
VARIABLE  { return Variable; }
OP        { return Operator; }
SEPARATOR { return Separator; }

%%

int yywrap(void)
{
    return 1;
}

void yyerror(const char *s)
{
  fflush(stdout);
  fprintf(stderr, "*** %s\n", s);
}
