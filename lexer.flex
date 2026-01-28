%top{
    #include "parser.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
    #include "Node.h"
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 
%%

"if"                    {if(USE_LEX_ONLY) {printf("IF ");}}
"else"                  {if(USE_LEX_ONLY) {printf("ELSE ");}}
"while"                 {if(USE_LEX_ONLY) {printf("WHILE ");}}
"for"                   {if(USE_LEX_ONLY) {printf("FOR ");}}
"volatile"              {if(USE_LEX_ONLY) {printf("VOLATILE_TYPE ");}}
"boolean"               {if(USE_LEX_ONLY) {printf("BOOLEAN_TYPE ");}}
"true"|"false"          {if(USE_LEX_ONLY) {printf("BOOLEAN ");}}
"int"                   {if(USE_LEX_ONLY) {printf("INT_TYPE ");}}
"float"                 {if(USE_LEX_ONLY) {printf("FLOAT_TYPE ");}}
"return"                {if(USE_LEX_ONLY) {printf("RETURN ");}}
"print"                 {if(USE_LEX_ONLY) {printf("PRINT ");}}
"read"                  {if(USE_LEX_ONLY) {printf("READ ");}}
"class"                 {if(USE_LEX_ONLY) {printf("CLASS ");}}

"+"                     {if(USE_LEX_ONLY) {printf("PLUSOP ");} else {return yy::parser::make_PLUSOP(yytext);}}
"-"                     {if(USE_LEX_ONLY) {printf("SUBOP ");} else {return yy::parser::make_MINUSOP(yytext);}}
"*"                     {if(USE_LEX_ONLY) {printf("MULTOP ");} else {return yy::parser::make_MULTOP(yytext);}}
"/"                     {if(USE_LEX_ONLY) {printf("DIVISIONOP ");}}
"^"                     {if(USE_LEX_ONLY) {printf("POWOP ");}}

":"                     {if(USE_LEX_ONLY) {printf("IS_OF ");}}
"!"                     {if(USE_LEX_ONLY) {printf("NOT ");}}
"("                     {if(USE_LEX_ONLY) {printf("LP ");} else {return yy::parser::make_LP(yytext);}}
")"                     {if(USE_LEX_ONLY) {printf("RP ");} else {return yy::parser::make_RP(yytext);}}
"{"                     {if(USE_LEX_ONLY) {printf("LCB ");}}
"}"                     {if(USE_LEX_ONLY) {printf("RCB ");}}
"["                     {if(USE_LEX_ONLY) {printf("LB ");}}
"]"                     {if(USE_LEX_ONLY) {printf("RB ");}}
    /* Lägg ev. till [] som array */
"\n"                    {if(USE_LEX_ONLY) {printf("NEWLINE \n");}}
":="                    {if(USE_LEX_ONLY) {printf("ASSIGN ");}}
">"                     {if(USE_LEX_ONLY) {printf("GREATER_THAN ");}}
"<"                     {if(USE_LEX_ONLY) {printf("LESS_THAN ");}}
"&"                     {if(USE_LEX_ONLY) {printf("AND ");}}
"|"                     {if(USE_LEX_ONLY) {printf("OR ");}}
"="                     {if(USE_LEX_ONLY) {printf("EQUAL_TO ");}}
","                     {if(USE_LEX_ONLY) {printf("DELIMITER ");}}
"\."                    {if(USE_LEX_ONLY) {printf("DOT ");}}


[A-Za-z_][A-Za-z0-9_]*    {if(USE_LEX_ONLY) {printf("ID ");}}
[0-9]+[\.][0-9]+         {if(USE_LEX_ONLY) {printf("FLOAT ");}}
0|[1-9][0-9]*           {if(USE_LEX_ONLY) {printf("INT ");} else {return yy::parser::make_INT(yytext);}}

[ \t\r]+              {}
"//"[^\n]*              {}
.                       { if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>>                  {return yy::parser::make_END();}
%%