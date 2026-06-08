%top{
    #include "parser.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
    #include "Node.h"
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 
%%

"main"                  {if(USE_LEX_ONLY) {printf("MAIN ");} else {return yy::parser::make_MAIN(yytext);}}
"if"                    {if(USE_LEX_ONLY) {printf("IF ");} else {return yy::parser::make_IF(yytext);}}
"else"                  {if(USE_LEX_ONLY) {printf("ELSE ");} else {return yy::parser::make_ELSE(yytext);}}
"for"                   {if(USE_LEX_ONLY) {printf("FOR ");} else {return yy::parser::make_FOR(yytext);}}
"volatile"              {if(USE_LEX_ONLY) {printf("VOLATILE_TYPE ");} else {return yy::parser::make_VOLATILE_TYPE(yytext);}}
"boolean"               {if(USE_LEX_ONLY) {printf("BOOLEAN_TYPE ");} else {return yy::parser::make_BOOLEAN_TYPE(yytext);}}
"true"                  {if(USE_LEX_ONLY) {printf("TRUE ");} else {return yy::parser::make_TRUE(yytext);}}
"false"                 {if(USE_LEX_ONLY) {printf("FALSE ");} else {return yy::parser::make_FALSE(yytext);}}
"int"                   {if(USE_LEX_ONLY) {printf("INT_TYPE ");} else {return yy::parser::make_INT_TYPE(yytext);}}
"float"                 {if(USE_LEX_ONLY) {printf("FLOAT_TYPE ");} else {return yy::parser::make_FLOAT_TYPE(yytext);}}
"void"                  {if(USE_LEX_ONLY) {printf("VOID_TYPE ");} else {return yy::parser::make_VOID_TYPE(yytext);}}
"return"                {if(USE_LEX_ONLY) {printf("RETURN ");} else {return yy::parser::make_RETURN(yytext);}}
"print"                 {if(USE_LEX_ONLY) {printf("PRINT ");} else {return yy::parser::make_PRINT(yytext);}}
"read"                  {if(USE_LEX_ONLY) {printf("READ ");} else {return yy::parser::make_READ(yytext);}}
"class"                 {if(USE_LEX_ONLY) {printf("CLASS ");} else {return yy::parser::make_CLASS(yytext);}}
"length"                {if(USE_LEX_ONLY) {printf("LEN ");} else {return yy::parser::make_LEN(yytext);}}
"break"                 {if(USE_LEX_ONLY) {printf("BREAK ");} else {return yy::parser::make_BREAK(yytext);}}
"continue"              {if(USE_LEX_ONLY) {printf("CONTINUE ");} else {return yy::parser::make_CONTINUE(yytext);}}

"+"                     {if(USE_LEX_ONLY) {printf("PLUSOP ");} else {return yy::parser::make_PLUSOP(yytext);}}
"-"                     {if(USE_LEX_ONLY) {printf("SUBOP ");} else {return yy::parser::make_SUBOP(yytext);}}
"*"                     {if(USE_LEX_ONLY) {printf("MULTOP ");} else {return yy::parser::make_MULTOP(yytext);}}
"/"                     {if(USE_LEX_ONLY) {printf("DIVOP ");} else {return yy::parser::make_DIVOP(yytext);}}
"^"                     {if(USE_LEX_ONLY) {printf("POWOP ");} else {return yy::parser::make_POWOP(yytext);}}

"<="                    {if(USE_LEX_ONLY) {printf("LESS_OR_EQUAL_TO ");} else {return yy::parser::make_LESS_OR_EQUAL_TO(yytext);}}
">="                    {if(USE_LEX_ONLY) {printf("GREATER_OR_EQUAL_TO ");} else {return yy::parser::make_GREATER_OR_EQUAL_TO(yytext);}}
"!="                    {if(USE_LEX_ONLY) {printf("NOT_EQUAL_TO ");} else {return yy::parser::make_NOT_EQUAL_TO(yytext);}}
":"                     {if(USE_LEX_ONLY) {printf("IS_OF ");} else {return yy::parser::make_IS_OF(yytext);}}
"!"                     {if(USE_LEX_ONLY) {printf("NOT ");} else {return yy::parser::make_NOT(yytext);}}
"("                     {if(USE_LEX_ONLY) {printf("LP ");} else {return yy::parser::make_LP(yytext);}}
")"                     {if(USE_LEX_ONLY) {printf("RP ");} else {return yy::parser::make_RP(yytext);}}
"{"                     {if(USE_LEX_ONLY) {printf("LCB ");} else {return yy::parser::make_LCB(yytext);}}
"}"                     {if(USE_LEX_ONLY) {printf("RCB ");} else {return yy::parser::make_RCB(yytext);}}
"["                     {if(USE_LEX_ONLY) {printf("LB ");} else {return yy::parser::make_LB(yytext);}}
"]"                     {if(USE_LEX_ONLY) {printf("RB ");} else {return yy::parser::make_RB(yytext);}}
"\n"                    {if(USE_LEX_ONLY) {printf("NEWLINE \n");} else {return yy::parser::make_NEWLINE(yytext);}}
":="                    {if(USE_LEX_ONLY) {printf("ASSIGN ");} else {return yy::parser::make_ASSIGN(yytext);}}
">"                     {if(USE_LEX_ONLY) {printf("GREATER_THAN ");} else {return yy::parser::make_GREATER_THAN(yytext);}}
"<"                     {if(USE_LEX_ONLY) {printf("LESS_THAN ");} else {return yy::parser::make_LESS_THAN(yytext);}}
"&"                     {if(USE_LEX_ONLY) {printf("AND ");} else {return yy::parser::make_AND(yytext);}}
"|"                     {if(USE_LEX_ONLY) {printf("OR ");} else {return yy::parser::make_OR(yytext);}}
"="                     {if(USE_LEX_ONLY) {printf("EQUAL_TO ");} else {return yy::parser::make_EQUAL_TO(yytext);}}
","                     {if(USE_LEX_ONLY) {printf("DELIMITER ");} else {return yy::parser::make_DELIMITER(yytext);}}
"\."                    {if(USE_LEX_ONLY) {printf("DOT ");} else {return yy::parser::make_DOT(yytext);}}


[A-Za-z_][A-Za-z0-9_]*    {if(USE_LEX_ONLY) {printf("ID ");} else {return yy::parser::make_ID(yytext);}}
[0-9]+[\.][0-9]+         {if(USE_LEX_ONLY) {printf("FLOAT ");} else {return yy::parser::make_FLOAT(yytext);}}
0|[1-9][0-9]*           {if(USE_LEX_ONLY) {printf("INT ");} else {return yy::parser::make_INT(yytext);}}

[ \t\r]+              {}
"//"[^\n]*              {}
.                       { if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>>                  {return yy::parser::make_END();}
%%