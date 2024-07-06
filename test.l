%{
#include "test.tab.h"
%}

%option noyywrap

%%
"printTable" {printf("[l]Requested table\n"); return PRINT_TABLE;}
"TypeOf" {printf("[l]Requested Typeof\n"); return TYPE_OF;}
"Eval" {printf("[l]Requested Eval\n"); return EVAL;}

["][^"]*["] {
  yylval.name = strdup(yytext + 1);
  yylval.name[strlen(yylval.name) - 1] = 0;
  printf("[l]Found string literal:%s\n", yytext);
  return STRING_LITERAL;
}
"%vars" {printf("[l]Started vars\n"); return START_VARS;}
"%func" {printf("[l]Started func\n"); return START_FUNC;}
"%user" {printf("[l]Started user\n"); return START_USER;}
"%main" {printf("[l]Started main\n"); return START_MAIN;}
"%end" {printf("[l]Ended section\n"); return END_SECTION;};
"true" { printf("[l]Found true literal\n");yylval.val = strdup("true"); return BOOLEAN_LITERAL; }
"false" { printf("[l]Found false literal\n");yylval.val = strdup("false"); return BOOLEAN_LITERAL; }
"int" { printf("[l]Found \"int\"\n"); return INT;}
"uint" {printf("[l]Found \"unsigned int\"\n"); return UINT;}
"float" { printf("[l]Found \"float\"\n");return FLOAT; }
"bool" { printf("[l]Found \"bool\"\n");return BOOL; }
"string" { printf("[l]Found \"string\"\n");return STR; }

[-+]?[1-9]+[0-9]* {
  yylval.val = strdup(yytext);  
    printf("[l]Found integer literal:%s\n", yytext);
    return INT_LITERAL;
}


[-+]?[0-9]+\.?[0-9]* {
  yylval.val = strdup(yytext);
  if (strchr(yytext, '.') != NULL) {
    printf("[l]Found float literal:%s\n", yytext);
    return FLOAT_LITERAL;
  }
}

"<=" {printf("[l]Found <=\n");return LEQ;}
">=" {printf("[l]Found >=\n");return GTQ;}
"<" {printf("[l]Found <\n");return LE;}
">" {printf("[l]Found >\n");return GT;}
"==" {printf("[l]Found ==\n"); return EQ;}
"&&" {printf("[l]Found &&\n");return AND;}
"||" {printf("[l]Found ||\n");return OR;}

"+" {printf("[l]Found +\n");return ADD;}
"-" {printf("[l]Found -\n");return SUB;}
"*" {printf("[l]Found *\n");return MUL;}
"/" {printf("[l]Found /\n");return DIV;}

[a-zA-Z][a-zA-Z0-9_]* {
  yylval.name = strdup(yytext);
  printf("[l]Found indentifier:%s\n",yytext);
  return IDENTIFIER;
}


[ \t\n] { /* ignore whitespace */ }
. {printf("Found character:%s\n",yytext);return yytext[0];}

%%