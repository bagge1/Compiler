/* Skeleton and definitions for generating a LALR(1) parser in C++ */
%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

/* Required code included before the parser definition begins */
%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
}

/* Code included in the parser implementation file */
%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;
}

/* Token definitions for the grammar */
/* Tokens represent the smallest units of the language, like operators and parentheses */
%token <std::string> PLUSOP SUBOP MULTOP DIVOP POWOP LP RP LCB RCB LB RB MAIN BREAK CONTINUE
%token <std::string> NEWLINE ASSIGN EQUAL_TO GREATER_THAN LESS_THAN LESS_OR_EQUAL_TO GREATER_OR_EQUAL_TO NOT_EQUAL_TO IS_OF AND OR DELIMITER DOT
%token <std::string> IF ELSE NOT FOR VOLATILE_TYPE INT FLOAT ID BOOLEAN_TYPE TRUE FALSE INT_TYPE FLOAT_TYPE VOID_TYPE RETURN PRINT READ CLASS LEN
%token END 0 "end of file"

/* Operator precedence and associativity rules */
/* Used to resolve ambiguities in parsing expressions See https://www.gnu.org/software/bison/manual/bison.html#Precedence-Decl */ 
%left OR
%left AND
%nonassoc GREATER_THAN LESS_THAN GREATER_OR_EQUAL_TO LESS_OR_EQUAL_TO NOT_EQUAL_TO EQUAL_TO
%left PLUSOP SUBOP
%left MULTOP DIVOP
%right POWOP
%precedence NOT IFELSE 
%precedence DOT ELSE
%precedence LB


/* Specify types for non-terminals in the grammar */
/* The type specifies the data type of the values associated with these non-terminals */
%type <Node *> root program expression factor args arglist baseType variable statement stmtBl stmtEnd type entry stmts for_init for_cond for_upd param param_list params method var_list class_body class_list class classes method_decl class_decl
/* Grammar rules section */
/* This section defines the production rules for the language being parsed */
%%

root:    program END {root = $1;};

program: var_list class_list entry {
              $$ = new Node("Program", "", yylineno);
              if ($1 != nullptr){
                for (Node* child : $1->children){ 
                  $$->children.push_back(child);
                }
              }
              if ($2 != nullptr){
                for (Node* child : $2->children){ 
                  $$->children.push_back(child);
                }
              }
              $$->children.push_back($3);
            }
            | stmtBl {
              $$ = new Node("Program", "", yylineno);
              $$->children.push_back($1);
            }
        ;


entry: MAIN LP RP IS_OF INT_TYPE stmtBl {
            $$ = new Node("Main method", "", yylineno);
            $$->children.push_back($6);
            }
            ;

param: ID IS_OF type {
            $$ = new Node("Parameter", $1, yylineno);
            $$->children.push_back($3);
            }
            ;
        
param_list: param {
            $$ = new Node("Parameters", "", yylineno);
            $$->children.push_back($1);
            }
            | param_list DELIMITER param {
            $$ = $1;
            $$->children.push_back($3);
            }
            ;

params: param_list {
            $$ = $1;
            }
            | %empty {
            $$ = nullptr;
            }
            ;

var_list: var_list variable stmtEnd {
              $$ = $1;
              $$->children.push_back($2);
            }
            | var_list stmtEnd {
              $$ = $1;
            }
            | %empty {
              $$ = new Node("VarList", "", yylineno);
            }
            ;

classes: class stmtEnd {
              $$ = new Node("ClassList", "", yylineno);
              $$->children.push_back($1);
            }
            | classes class stmtEnd {
              $$ = $1;
              $$->children.push_back($2);
            }
            | classes stmtEnd {
              $$ = $1;
            }
            ;

class_list: classes {
            $$ = $1;
          }
          | %empty {
            $$ = new Node("ClassList", "", yylineno);
          }

class_body: class_body variable stmtEnd {
              $$ = $1;
              $$->children.push_back($2);
            }
            | class_body method stmtEnd {
              $$ = $1;
              $$->children.push_back($2);
            }
            | class_body stmtEnd {
              $$ = $1;
            }
            | %empty {
              $$ = new Node("ClassBody", "", yylineno);
            }
            ;

class_decl: CLASS ID LCB {
            $$ = new Node("Class", $2, yylineno);
          }
         
class: class_decl class_body RCB {
            $$ = $1;
            if  ($2 != nullptr){
              for(Node* child : $2->children){
                $$->children.push_back(child);
              }
            }
            
          }
          ;

method_decl: ID LP params RP IS_OF type {
             $$ = new Node("Method", $1, yylineno);
             if ($3 != nullptr){
              $$->children.push_back($3);
             } else {
              $$->children.push_back(new Node("Parameters", "None", yylineno));
             }
             Node* ret = new Node("ReturnType", "", yylineno);
             ret->children.push_back($6);
             $$->children.push_back(ret);
            }
            ;

method: method_decl stmtBl{
              $$= $1;
              $$->children.push_back($2);
            }

expression: expression PLUSOP expression {  
                            $$ = new Node("Addition", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            /* printf("r1 "); */
                          }
            | expression SUBOP expression {
                            $$ = new Node("Subtraction", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            /* printf("r2 "); */
                          }
            | expression MULTOP expression {
                            $$ = new Node("Multiplication", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            /* printf("r3 "); */
                          }
            | expression DIVOP expression {
                            $$ = new Node("Division", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression POWOP expression {
                            $$ = new Node("PowerOf", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression AND expression {
                            $$ = new Node("And", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression OR expression {
                            $$ = new Node("Or", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression LESS_THAN expression {
                            $$ = new Node("LessThan", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression GREATER_THAN expression {
                            $$ = new Node("GreaterThan", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression LESS_OR_EQUAL_TO expression {
                            $$ = new Node("LessOrEqual", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression GREATER_OR_EQUAL_TO expression {
                            $$ = new Node("GreaterOrEqual", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            } 
            | expression EQUAL_TO expression {
                            $$ = new Node("EqualTo", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression NOT_EQUAL_TO expression {
                            $$ = new Node("NotEqualTo", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | expression LB expression RB {
                            $$ = new Node("ArrayAccess", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            
            }
            | expression DOT LEN {
                            $$ = new Node("LengthOf", $1->value, yylineno);
                            
            }
            | expression DOT ID LP args RP {
                            $$ = new Node("CallMethod", $3, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($5);
            }
            | ID LP args RP {
                            $$ = new Node("CallMethod", $1, yylineno);
                            $$->children.push_back($3);
            }
            | NOT expression {
                            $$ = new Node("Not", "", yylineno);
                            $$->children.push_back($2);
            }
            | baseType LB args RB {
                            $$ = new Node("Array", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | factor      {$$ = $1; /* printf("r4 ");*/}
            ;

factor:     INT           {  $$ = new Node("int", $1, yylineno); /* printf("r5 ");  Here we create a leaf node Int. The value of the leaf node is $1 */}
            | FLOAT       {  $$ = new Node("float", $1, yylineno);}
            | TRUE        {  $$ = new Node("true", "", yylineno);}
            | FALSE       {  $$ = new Node("false", "", yylineno);}
            | ID          {  $$ = new Node("ID", $1, yylineno);}
            | LP expression RP { $$ = $2; /* printf("r6 ");  simply return the expression */}
    ;

arglist: expression {
                $$ = new Node("Arguments", "", yylineno);
                $$->children.push_back($1);
            }
            | arglist DELIMITER expression {
              $$ = $1;
              $$->children.push_back($3);
            }
            ;

args:  arglist {
                $$ = $1;
          }
          | %empty {
            $$ = new Node("Arguments", "", yylineno);
          }
          ;

baseType: INT_TYPE {
                $$ = new Node("IntType", $1, yylineno);
            }
            | FLOAT_TYPE {
                            $$ = new Node("FloatType", $1, yylineno);
            }
            | BOOLEAN_TYPE {
                            $$ = new Node("BoolType", $1, yylineno);
            }
            ;
          
variable: ID IS_OF type {
              $$ = new Node("Variable", $1, yylineno - 1);
              $$->children.push_back($3);
            }
            | VOLATILE_TYPE ID IS_OF type {
              $$ = new Node("VolatileVariable", $2, yylineno - 1);
              $$->children.push_back($4);
            }
            | ID IS_OF type ASSIGN expression {
              $$ = new Node("AssignVariable", $1, yylineno - 1);
              $$->children.push_back($3);
              $$->children.push_back($5);
            }
            | VOLATILE_TYPE ID IS_OF type ASSIGN expression {
              $$ = new Node("AssignVolatileVariable", $2, yylineno - 1);
              $$->children.push_back($4);
              $$->children.push_back($6);
            }
            ;
          
for_init: variable {
              $$ = new Node("Initilization", "", yylineno);
              $$->children.push_back($1);
            }
            | expression ASSIGN expression {
              $$ = new Node("Initilization", "", yylineno);
              Node* assignNode = new Node("Assign", "", yylineno);
              assignNode->children.push_back($1);
              assignNode->children.push_back($3);
              $$->children.push_back(assignNode);
            }
            | %empty {
              $$ = nullptr;
            }
            ;

for_cond: expression {
              $$ = new Node("Condition", "", yylineno);
              $$->children.push_back($1);
            }
            | %empty {
              $$ = nullptr;
            }
            ;

for_upd: expression ASSIGN expression {
              $$ = new Node("Update", "", yylineno);
              Node* assignNode = new Node("Assign", "", yylineno);
              assignNode->children.push_back($1);
              assignNode->children.push_back($3);
              $$->children.push_back(assignNode);
            }
            ;

stmts: statement {
              $$ = new Node("StatementList", "", yylineno);
              if ($1 != nullptr){
                $$->children.push_back($1);
              }
            }
            | stmts statement {
              $$ = $1;
              if ($2 != nullptr){
                $$->children.push_back($2);
              }
            }

stmtBl: LCB stmts RCB {
              $$ = new Node("StatementBlock", "", yylineno);
              if ($2 != nullptr){
                for (Node* child : $2->children){
                  $$->children.push_back(child);
                }
              }
            }
            | LCB RCB {
              $$ = new Node("EmptyStatementBlock", "", yylineno);
            }
            ;

stmtEnd: NEWLINE {
            $$ = nullptr;
          }
            ;

statement: stmtBl {
              $$ = $1;
            }
            | stmtEnd {
              $$ = nullptr;
            }
            | variable stmtEnd {
              $$ = $1;
            }
            | expression ASSIGN expression stmtEnd {
              $$ = new Node("Assign", "", yylineno);
              $$->children.push_back($1);
              $$->children.push_back($3);
            }
            | IF LP expression RP statement %prec IFELSE{
              $$ = new Node("IfStatement", "", yylineno);
              Node* condNode = new Node("Condition", "", yylineno);
              condNode->children.push_back($3);
              $$->children.push_back(condNode);
              $$->children.push_back($5);
            }
            | IF LP expression RP statement ELSE statement {
              $$ = new Node("IfElseStatement", "", yylineno);
              Node* condNode = new Node("Condition", "", yylineno);
              condNode->children.push_back($3);
              $$->children.push_back(condNode);

              if ($5->type == "StatementBlock"){
                $5->type = "ThenBody";
                $$->children.push_back($5);
              } else {
                Node* thenNode = new Node("ThenBody", "", yylineno);
                thenNode->children.push_back($5);
                $$->children.push_back(thenNode);
              }

              Node* elseNode = new Node("ElseBody", "", yylineno);
              elseNode->children.push_back($7);
              $$->children.push_back(elseNode);
            }
            | FOR LP for_init DELIMITER for_cond DELIMITER for_upd RP statement {
              $$ = new Node("ForStatement", "", yylineno);
              if ($3 != nullptr){
                $$->children.push_back($3);
              }
              if ($5 != nullptr){
                $$->children.push_back($5);
              }
              if ($7 != nullptr){
                $$->children.push_back($7);
              }
              if ($9->type == "StatementBlock"){
                $9->type = "LoopBody";
                $$->children.push_back($9);
              } else {
                  Node* bodyNode = new Node("LoopBody", "", yylineno);
                  bodyNode->children.push_back($9);
                  $$->children.push_back(bodyNode);
              }
            }
            | PRINT LP expression RP stmtEnd {
              $$ = new Node("Print", "", yylineno);
              $$->children.push_back($3);
            }
            | READ LP expression RP stmtEnd {
              $$ = new Node("Read", "", yylineno);
              $$->children.push_back($3);
            }
            | RETURN expression stmtEnd {
              $$ = new Node("Return", "", yylineno);
              $$->children.push_back($2);
            }
            | BREAK stmtEnd {
              $$ = new Node("Break", "", yylineno);
            }
            | CONTINUE stmtEnd {
              $$ = new Node("Continue", "", yylineno);
            }
            | expression stmtEnd {
              $$ = $1;
            }
            ;

type: baseType {
            $$ = $1;
            }
            | baseType LB RB {
            $$ = new Node("Type", "array", yylineno);
            $$->children.push_back($1);
            }
            | ID {
            $$ = new Node("Type", $1, yylineno);
            }
            | VOID_TYPE {
            $$ = new Node("Type", $1, yylineno);
            }
            ;
