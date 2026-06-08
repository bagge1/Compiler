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
%token <std::string> ASSIGN COLON NOT DOT COMMA AND OR LESSOREQ GREATEROREQ LESS GREATER EQ DIVOP POW NEQ
%token <std::string> PLUSOP SUBOP MULTOP
%token <std::string> LP RP SBL SBR CBL CBR
%token <std::string> NEWLINE
%token <std::string> IF ELSE FOR PRINT VOL INT_TYPE BOOL_TYPE FLOAT_TYPE RETURN CONT BREAK READ CLASS LEN MAIN ID VOID
%token <std::string> FLOAT INT BOOLEAN
%token END 0 "end of file"

/* Operator precedence and associativity rules */
/* Used to resolve ambiguities in parsing expressions See https://www.gnu.org/software/bison/manual/bison.html#Precedence-Decl */ 

%left OR
%left AND
%nonassoc EQ NEQ GREATER LESS GREATEROREQ LESSOREQ
%left PLUSOP SUBOP
%left MULTOP DIVOP
%right POW
%precedence NOT
%precedence DOT
%precedence SBL


/* Specify types for non-terminals in the grammar */
/* The type specifies the data type of the values associated with these non-terminals */
%type <Node *> root expression factor CommaArgs1 CommaArgs2 CommaArgs1_ CommaArgs2_ statement statementEnd statementBlock statements type var baseType assignment_ else_ for_condition for_increment for_init entry method methodArgs methodArgs_ class classArgs program programArgs main

/* Grammar rules section */
/* This section defines the production rules for the language being parsed */
%%
root:       program {root = $1;};

program:    programArgs entry END{$$ = new Node("Program", "", yylineno);
                                  $$->children.push_back($1);
                                  $$->children.push_back($2);
                                  };
            | statementEnd programArgs entry END{$$ = new Node("Program", "", yylineno);
                                  $$->children.push_back($2);
                                  $$->children.push_back($3);
                                  };

programArgs:%empty {$$ = new Node("programArgs", "", yylineno);}
            | programArgs var statementEnd {$$ = $1;
                                          $$->children.push_back($2);
                                          }
            | programArgs class statementEnd{$$ = $1;
                                          $$->children.push_back($2);
                                          }

class:      CLASS ID CBL classArgs CBR {$$ = new Node("Class", $2, $4->lineno);
                                        $$->children.push_back($4);
                                         };
            | CLASS ID CBL statementEnd classArgs CBR{$$ = new Node("Class", $2, $5->lineno);
                                        $$->children.push_back($5);
                                         };
            ;

classArgs:  %empty {$$ = new Node("ClassArgs", "", yylineno);}
            | classArgs var statementEnd {$$ = $1;
                                          $$->children.push_back($2);
                                          }
            | classArgs method statementEnd{$$ = $1;
                                          $$->children.push_back($2);
                                          }
            ;


entry:      main LP RP COLON INT_TYPE statementBlock{$$ = new Node("MainEntry", $1->value, $1->lineno);
                                                $$->children.push_back($6);
                                       }
            |main LP RP COLON INT_TYPE statementBlock statementEnd{$$ = new Node("MainEntry", $1->value, $1->lineno);
                                                $$->children.push_back($6);
                              }
            ;

main: MAIN{$$ = new Node("main", $1, yylineno);};

method:     ID LP methodArgs RP COLON type statementBlock{
                                        $$ = new Node("Method", $1, $3->lineno);
                                        Node * temp_node = new Node("methodType","",$3->lineno);
                                        temp_node->children.push_back($6);

                                        $$->children.push_back(temp_node);
                                        $3->children.reverse();
                                        $$->children.push_back($3);
                                        $$->children.push_back($7);
                                        }
            ;

methodArgs:  %empty {
                    $$ = new Node("NoArgs", "", yylineno);
                }
            | methodArgs_ {
              $$ = $1;
            }
            ;

methodArgs_: ID COLON type COMMA methodArgs_ {$$ = $5;
                              Node * temp_node = new Node("Variable",$1,yylineno);
                              $$->children.push_back(temp_node);
                              temp_node->children.push_back($3);
                                              }
            | ID COLON type { $$ = new Node("methodArgs", "", yylineno);
                              Node * temp_node = new Node("Variable",$1,yylineno);
                              $$->children.push_back(temp_node);
                              temp_node->children.push_back($3);}
            ;

var:        VOL ID COLON type assignment_ { $$ = new Node("Variable", $2, $4->lineno);
                                            Node * temp_node = new Node("vol","",yylineno);
                                            $$->children.push_back($4);
                                            $$->children.push_back($5);
                                            $$->children.push_back(temp_node);
                                      }
            | ID COLON type assignment_ { $$ = new Node("Variable", $1, $3->lineno);
                                            Node * temp_node = new Node("const","",yylineno);
                                            $$->children.push_back($3);
                                            $$->children.push_back($4);
                                            $$->children.push_back(temp_node);
                                      }
            ;

assignment_:%empty{ $$ = new Node("NoExpression", "", yylineno);}
            | ASSIGN expression {$$ = $2;}
            ;

type:       baseType { $$ = $1;}
            | baseType SBL SBR { $$ = new Node("ArrayExpression",$1->value,yylineno);}
            | ID { $$ = new Node("TypeExpression", $1, yylineno);}
            | VOID { $$ = new Node("VoidType", $1, yylineno);}
            ;


statement:  statementBlock { $$ = $1;}
            | var { $$ = new Node("VarDeclareStatement", "", yylineno);
                                  $$->children.push_back($1);
                                  }
            | expression ASSIGN expression{ 
                                  $$ = new Node("AssignStatement", $2, yylineno);
                                  $$->children.push_back($1);
                                  $$->children.push_back($3);
                                  }
            | IF LP expression RP statement else_ { 
                                  $$ = new Node("IfStatement", $1, yylineno);
                                  $$->children.push_back($3);
                                  $$->children.push_back($5);
                                  $$->children.push_back($6);
                                  }
            | FOR LP for_init COMMA for_condition COMMA for_increment RP statement{ 
                                  $$ = new Node("ForStatement", $1, yylineno);
                                  $$->children.push_back($3);
                                  $$->children.push_back($5);
                                  $$->children.push_back($7);
                                  $$->children.push_back($9);
                                  }
            | PRINT LP expression RP { 
                                  $$ = new Node("PrintStatement", $1, yylineno);
                                  $$->children.push_back($3);
                                  }
            | READ LP expression RP { 
                                  $$ = new Node("ReadStatement", $1, yylineno);
                                  $$->children.push_back($3);
                                  }
            | RETURN expression{ 
                                  $$ = new Node("ReturnStatement", $1, yylineno);
                                  $$->children.push_back($2);
                                  }
            | BREAK               { 
                                  $$ = new Node("BreakStatement", $1, yylineno);
                                  }
            | CONT                { 
                                  $$ = new Node("ContinueStatement", $1, yylineno);
                                  }
            | expression          { 
                                  $$ = new Node("ExpressionStatement", "", yylineno);
                                  $$->children.push_back($1);
                                  }
            ;

for_init: %empty {$$ = new Node("noINIT", "", yylineno);}
            | var {
                    $$ = new Node("newVar", "", yylineno);
                    $$->children.push_back($1);
                  }
            | expression ASSIGN expression{
                    $$ = new Node("AssignStatement", "", yylineno);
                    $$->children.push_back($1);
                    $$->children.push_back($3);
                  }
            ;

for_condition: %empty {$$ = new Node("noCondition", "", yylineno);}
              | expression {$$ = $1;};
              ;

for_increment: expression ASSIGN expression {$$ = new Node("AssignStatement", $2, yylineno);
                                              $$->children.push_back($1);
                                              $$->children.push_back($3);
                                            }

else_:      %empty {$$ = new Node("NoElse", "", yylineno);}
            | ELSE statement {$$ = new Node("ElseStatement", "", yylineno);
                              $$->children.push_back($2);
                              }
            ;

statementEnd: NEWLINE { $$ = new Node("StatementEnd", $1, yylineno);}
            | statementEnd NEWLINE { $$ = $1;}
            ;

statementBlock: CBL statements CBR{ $$ = $2;}
              | CBL statementEnd statements CBR{ $$ = $3;}
              ;


statements: %empty { $$ = new Node("StatementBlock", "", yylineno);}
            | statements statement statementEnd {$$ = $1;
                                    $$->children.push_back($2);
                                  }
            ;
            


expression: expression PLUSOP expression {      /*
                                                  Create a subtree that corresponds to the AddExpression
                                                  The root of the subtree is AddExpression
                                                  The childdren of the AddExpression subtree are the left hand side (expression accessed through $1) and right hand side of the expression (expression accessed through $3)
                                                */
                            $$ = new Node("AddExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            /* printf("r1 "); */
                          }
            | expression SUBOP expression {
                            $$ = new Node("SubExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            /* printf("r2 "); */
                          }
            | expression MULTOP expression {
                            $$ = new Node("MultExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            /* printf("r3 "); */
                          }
            | expression DIVOP expression{
                            $$ = new Node("DivExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression POW expression{
                            $$ = new Node("PowExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression OR expression{
                            $$ = new Node("OrExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression AND expression{
                            $$ = new Node("AndExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression EQ expression{
                            $$ = new Node("EqExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression NEQ expression{
                            $$ = new Node("NeqExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression LESS expression{
                            $$ = new Node("LessExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression GREATER expression{
                            $$ = new Node("GreaterExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression GREATEROREQ expression{
                            $$ = new Node("GreaterOrEqExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression LESSOREQ expression{
                            $$ = new Node("LessOrEqExpression", $2, yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression DOT LEN{
                            $$ = new Node("lengthExpression", "", yylineno);
                            $$->children.push_back($1);
                          }
            | expression SBL expression SBR{
                            $$ = new Node("ArrayIndexExpression", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }         
            | expression DOT ID LP CommaArgs1 RP{
                            $$ = new Node("MethodCallExpression", $3, yylineno);
                            $5->children.reverse();
                            $$->children.push_back($1);
                            $$->children.push_back($5);
                          }
            | ID LP CommaArgs1 RP{
                            $$ = new Node("FunctionCallExpression", $1, yylineno);
                            $3->children.reverse();
                            $$->children.push_back($3);
                          }
            | baseType SBL CommaArgs2 SBR {
                            $$ = new Node("ArrayCreationExpression", "", yylineno);
                            $3->children.reverse();
                            $$->children.push_back($1);
                            $$->children.push_back($3);
            }
            | NOT expression{
                            $$ = new Node("NotExpression", "", yylineno);
                            $$->children.push_back($2);
                          }
            | factor      {$$ = $1; /* printf("r4 ");*/}
            ;

/*
This is for the comma recursives stuff
*/
CommaArgs1:  %empty {
                    $$ = new Node("NoArgs", "", yylineno);
                }
            | CommaArgs1_ {
              $$ = $1;
            }
            ;

CommaArgs2: expression CommaArgs2_ {
              $$ = $2;
              $$->children.push_back($1);
            }
            ;

CommaArgs2_: COMMA expression CommaArgs2_ {$$ = $3;
                                              $$->children.push_back($2);
                                              }
            | %empty { $$ = new Node("CommaArgs", "", yylineno);}
            ; 

CommaArgs1_: expression COMMA CommaArgs1_ {$$ = $3;
                                              $$->children.push_back($1);
                                              }
            | expression { $$ = new Node("CommaArgs", "", yylineno);
                              $$->children.push_back($1);}
            ;



baseType:   INT_TYPE      {  $$ = new Node("IntType", $1, yylineno); }
            | FLOAT_TYPE  {  $$ = new Node("FloatType", $1, yylineno); }
            | BOOL_TYPE   {  $$ = new Node("BoolType", $1, yylineno); }
            ;


factor:     INT           {  $$ = new Node("Int", $1, yylineno); /* printf("r5 ");  Here we create a leaf node Int. The value of the leaf node is $1 */}
            | LP expression RP { $$ = $2; /* printf("r6 ");  simply return the expression */}
            | FLOAT       {  $$ = new Node("Float", $1, yylineno);}
            | BOOLEAN     {  $$ = new Node("Boolean", $1, yylineno);}
            | ID          {  $$ = new Node("Id", $1, yylineno);}
    ;
