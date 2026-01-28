program  ::= (var stmtEnd)* (class)* entry  EOF ;
class    ::= "class" ID "{" (var stmtEnd)* (method)* "}" ;
entry    ::= "main" "("")" ":" "int" stmtBl ;
method   ::= ID "(" (ID ":" type ("," ID ":" type)* )? ")" ":" type stmtBl ;
var      ::= ("volatile")? ID ":" type (":=" expr)? ;
type     ::= ( baseType ("[" "]")? ) | ID | "void" ;
baseType ::= "int" | "float" | "boolean" ;
stmt     ::= stmtBl
           | var stmtEnd
           | lvalue ":=" expr stmtEnd
           | "if" "(" expr ")" stmt ("else" stmt)?
           | "for" "(" ( var | (lvalue ":=" expr) )? "," ( expr )? "," lvalue ":=" expr ")" stmt
           | "print" "(" expr ")" stmtEnd
           | "read" "(" lvalue ")" stmtEnd
           | "return" expr stmtEnd
           | "break" stmtEnd
           | "continue" stmtEnd
           | expr stmtEnd
           ;
expr     ::= expr ( "&" | "|" | "<" | ">" | "<=" | ">=" | "=" | "!=" | "+" | "-" | "*" | "/" | "^") expr
           | expr "[" expr "]"
           | expr "." "length"
           | (expr ".")? ID "(" ( expr ( "," expr )* )? ")"
           | INT
           | FLOAT
           | ID
           | "true"
           | "false"
           | baseType "[" expr ("," expr)* "]"
           | "!" expr
           | "(" expr ")" 
           ;
stmtBl   ::= "{" ( stmt )* "}" ;
lvalue   ::= ID ( ("[" expr "]") | ("." ID) )* ;
stmtEnd  ::= NEWLINE;