%top{
    #include "parser.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
    #include "Node.h"
    #include <string.h>
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 
%%


":="                    {if(USE_LEX_ONLY) {printf("ASSIGN ");}else {return yy::parser::make_ASSIGN(yytext);}}

":"                     {if(USE_LEX_ONLY) {printf("COLON ");}else {return yy::parser::make_COLON(yytext);}}

"!="                    {if(USE_LEX_ONLY) {printf("NEQ ");}else {return yy::parser::make_NEQ(yytext);}}
"!"                     {if(USE_LEX_ONLY) {printf("NOT ");}else {return yy::parser::make_NOT(yytext);}}


"."                     {if(USE_LEX_ONLY) {printf("DOT ");}else {return yy::parser::make_DOT(yytext);}}
","                     {if(USE_LEX_ONLY) {printf("COMMA ");}else {return yy::parser::make_COMMA(yytext);}}
"&"                     {if(USE_LEX_ONLY) {printf("AND ");}else {return yy::parser::make_AND(yytext);}}
"|"                     {if(USE_LEX_ONLY) {printf("OR ");}else {return yy::parser::make_OR(yytext);}}
"<="                     {if(USE_LEX_ONLY) {printf("LESSOREQ ");}else {return yy::parser::make_LESSOREQ(yytext);}}
">="                     {if(USE_LEX_ONLY) {printf("GREATEROREQ ");}else {return yy::parser::make_GREATEROREQ(yytext);}}
"<"                     {if(USE_LEX_ONLY) {printf("LESS ");}else {return yy::parser::make_LESS(yytext);}}
">"                     {if(USE_LEX_ONLY) {printf("GREATER ");}else {return yy::parser::make_GREATER(yytext);}}
"="                     {if(USE_LEX_ONLY) {printf("EQ ");} else {return yy::parser::make_EQ(yytext);}}
"/"                     {if(USE_LEX_ONLY) {printf("DIVOP ");} else {return yy::parser::make_DIVOP(yytext);}}
"^"                     {if(USE_LEX_ONLY) {printf("POW ");} else {return yy::parser::make_POW(yytext);}}
"+"                     {if(USE_LEX_ONLY) {printf("PLUSOP ");} else {return yy::parser::make_PLUSOP(yytext);}}
"-"                     {if(USE_LEX_ONLY) {printf("SUBOP ");} else {return yy::parser::make_SUBOP(yytext);}}
"*"                     {if(USE_LEX_ONLY) {printf("MULTOP ");} else {return yy::parser::make_MULTOP(yytext);}}

"("                     {if(USE_LEX_ONLY) {printf("LP ");} else {return yy::parser::make_LP(yytext);}}
")"                     {if(USE_LEX_ONLY) {printf("RP ");} else {return yy::parser::make_RP(yytext);}}
"["                     {if(USE_LEX_ONLY) {printf("SBL ");}else {return yy::parser::make_SBL(yytext);}}
"]"                     {if(USE_LEX_ONLY) {printf("SBR ");}else {return yy::parser::make_SBR(yytext);}}
"{"                     {if(USE_LEX_ONLY) {printf("CBL ");}else {return yy::parser::make_CBL(yytext);}}
"}"                     {if(USE_LEX_ONLY) {printf("CBR ");}else {return yy::parser::make_CBR(yytext);}}
"\n"                    {if(USE_LEX_ONLY) {printf("NEWLINE \n");}else {return yy::parser::make_NEWLINE(yytext);}}        

[a-zA-Z_][a-zA-Z0-9_]*    {
        if(strcmp(yytext,"if")==0){
            if(USE_LEX_ONLY) {printf("IF ");}else {return yy::parser::make_IF(yytext);}
        }
        else if(strcmp(yytext,"else")==0){
            if(USE_LEX_ONLY){printf("ELSE ");}else {return yy::parser::make_ELSE(yytext);}
        }
        else if(strcmp(yytext,"for")==0){
            if(USE_LEX_ONLY){printf("FOR ");}else {return yy::parser::make_FOR(yytext);}
        }
        else if(strcmp(yytext,"print")==0){
            if(USE_LEX_ONLY) {printf("PRINT ");}else {return yy::parser::make_PRINT(yytext);}
        }
        else if(strcmp(yytext,"volatile")==0){
            if(USE_LEX_ONLY){printf("VOL ");}else {return yy::parser::make_VOL(yytext);}
        }
        else if(strcmp(yytext,"true") == 0 || strcmp(yytext,"false") == 0){
            if(USE_LEX_ONLY){printf("BOOLEAN ");}else {return yy::parser::make_BOOLEAN(yytext);}
        }
        else if(strcmp(yytext,"int")== 0){
            if(USE_LEX_ONLY){printf("INT_TYPE ");}else {return yy::parser::make_INT_TYPE(yytext);}
        }
        else if(strcmp(yytext,"boolean")== 0){
            if(USE_LEX_ONLY){printf("BOOL_TYPE ");}else {return yy::parser::make_BOOL_TYPE(yytext);}
        }
        else if(strcmp(yytext,"float")== 0){
            if(USE_LEX_ONLY){printf("FLOAT_TYPE ");}else {return yy::parser::make_FLOAT_TYPE(yytext);}
        }
        else if(strcmp(yytext,"return")==0){
            if(USE_LEX_ONLY){printf("RETURN ");}else {return yy::parser::make_RETURN(yytext);}
        }
        else if(strcmp(yytext,"continue")==0){
            if(USE_LEX_ONLY){printf("CONT ");}else {return yy::parser::make_CONT(yytext);}
        }
        else if(strcmp(yytext,"break")==0){
            if(USE_LEX_ONLY){printf("BREAK ");}else {return yy::parser::make_BREAK(yytext);}
        }
        else if(strcmp(yytext,"read")==0){
            if(USE_LEX_ONLY){printf("READ ");}else {return yy::parser::make_READ(yytext);}
        }
        else if(strcmp(yytext,"class")==0){
            if(USE_LEX_ONLY){printf("CLASS ");}else {return yy::parser::make_CLASS(yytext);}
        }
        else if(strcmp(yytext,"length")==0){
            if(USE_LEX_ONLY){printf("LEN ");}else {return yy::parser::make_LEN(yytext);}
        }
        else if(strcmp(yytext,"main")==0){
            if(USE_LEX_ONLY){printf("MAIN ");}else {return yy::parser::make_MAIN(yytext);}
        }
        else if(strcmp(yytext,"void")==0){
            if(USE_LEX_ONLY){printf("VOID ");}else {return yy::parser::make_VOID(yytext);}
        }
        else{
            if(USE_LEX_ONLY) {printf("ID ");}else {return yy::parser::make_ID(yytext);}
        }
    }

"-"?[0-9]+"."[0-9]+  {if(USE_LEX_ONLY) {printf("FLOAT ");}else {return yy::parser::make_FLOAT(yytext);}}

0|"-"?[1-9][0-9]*           {if(USE_LEX_ONLY) {printf("INT ");} else {return yy::parser::make_INT(yytext);}}






[ \t\r]+              {}
"//"[^\n]*              {}
.                       { if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>>                  {return yy::parser::make_END();}
%%